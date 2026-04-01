#include "loaders/jpeg_loader.h"
#include "image.h"

#include <jpeglib.h>
#include <jerror.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <memory>

namespace image_processor {

struct JpegLoader::Impl {

    jpeg_decompress_struct cinfo;   // struct libjpeg for load
    
    jpeg_compress_struct cinfo_out; // struct libjpeg for save
    
    JpegErrorManager jerr;
    
    jpeg_error_mgr std_err;
    
    Impl() {
        std::memset(&cinfo, 0, sizeof(cinfo));
        std::memset(&cinfo_out, 0, sizeof(cinfo_out));
        std::memset(&jerr, 0, sizeof(jerr));
        std::memset(&std_err, 0, sizeof(std_err));
        
        jerr.pub = &std_err;
    }
    
    ~Impl() = default;
};

JpegLoader::JpegLoader() : pImpl_(std::make_unique<Impl>()) {}

JpegLoader::~JpegLoader() = default;

bool JpegLoader::canHandle(const std::string& filename) const {
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext == "jpg" || ext == "jpeg";
}

void JpegLoader::errorHandler(jpeg_common_struct* cinfo) {
    JpegErrorManager* myerr = reinterpret_cast<JpegErrorManager*>(cinfo->err);
    
    longjmp(myerr->setjmp_buffer, 1);
}

bool JpegLoader::load(const std::string& filename, Image& image) {
    FILE* infile = fopen(filename.c_str(), "rb");
    if (!infile) {
        return false;
    }
    
    auto& cinfo = pImpl_->cinfo;
    auto& jerr = pImpl_->jerr;
    
    cinfo.err = jpeg_std_error(jerr.pub);
    jerr.pub->error_exit = errorHandler;
    
    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        return false;
    }
    
    jpeg_create_decompress(&cinfo);
    
    jpeg_stdio_src(&cinfo, infile);
    
    jpeg_read_header(&cinfo, TRUE);
    
    cinfo.out_color_space = JCS_RGB;
    
    jpeg_start_decompress(&cinfo);
    
    image.width_ = cinfo.output_width;
    image.height_ = cinfo.output_height;
    image.channels_ = cinfo.output_components; 
    
    image.data_.resize(image.width_ * image.height_ * image.channels_);
    
    while (cinfo.output_scanline < cinfo.output_height) {
        uint8_t* rowPtr = image.data_.data() + cinfo.output_scanline * image.width_ * image.channels_;
        jpeg_read_scanlines(&cinfo, &rowPtr, 1);
    }
    
    jpeg_finish_decompress(&cinfo);
    
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    
    return true;
}

bool JpegLoader::save(const std::string& filename, const Image& image, int quality) {
    FILE* outfile = fopen(filename.c_str(), "wb");
    if (!outfile) {
        return false;
    }
    
    auto& cinfo = pImpl_->cinfo_out;
    auto& jerr = pImpl_->jerr;
    
    cinfo.err = jpeg_std_error(jerr.pub);
    jerr.pub->error_exit = errorHandler;
    
    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_compress(&cinfo);
        fclose(outfile);
        return false;
    }
    
    jpeg_create_compress(&cinfo);
    
    jpeg_stdio_dest(&cinfo, outfile);
    
    cinfo.image_width = image.width_;
    cinfo.image_height = image.height_;
    cinfo.input_components = image.channels_;
    
    if (image.channels_ == 1) {
        cinfo.in_color_space = JCS_GRAYSCALE;   // black-and-white
    } else {
        cinfo.in_color_space = JCS_RGB;         // color       
    }
    
    jpeg_set_defaults(&cinfo);
    
    jpeg_set_quality(&cinfo, quality, TRUE);
    
    jpeg_start_compress(&cinfo, TRUE);
    
    while (cinfo.next_scanline < cinfo.image_height) {
        uint8_t* rowPtr = const_cast<uint8_t*>(
            image.data_.data() + cinfo.next_scanline * image.width_ * image.channels_
        );
        
        jpeg_write_scanlines(&cinfo, &rowPtr, 1);
    }
    
    jpeg_finish_compress(&cinfo);
    
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);
    
    return true;
}

} 