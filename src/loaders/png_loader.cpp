#include "../../include/image_processor/loaders/png_loader.h"
#include "../../include/image_processor/image.h"

#include <png.h>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <memory>

namespace image_processor {

struct PngLoader::Impl {
    png_structp png;
    png_infop info;
    
    Impl() : png(nullptr), info(nullptr) {}
};
PngLoader::PngLoader() : pImpl_(std::make_unique<Impl>()) {}

PngLoader::~PngLoader() = default;

bool PngLoader::canHandle(const std::string& filename) const {
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext == "png";
}

bool convertToRgb(png_structp png, png_infop info, Image& image) {
    png_byte bit_depth = png_get_bit_depth(png, info);
    png_byte color_type = png_get_color_type(png, info);

    if (bit_depth == 16) {
        png_set_strip_16(png);
    }
    
    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png);
    }
    
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
        png_set_expand_gray_1_2_4_to_8(png);
    }
    
    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png);
    }
    
    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(png);
    }
    
    png_read_update_info(png, info);
    
    image.SetChannels(png_get_channels(png, info));
    
    return true;
}

bool PngLoader::load(const std::string& filename, Image& image) {
    FILE* fp = fopen(filename.c_str(), "rb");
    if (!fp) {
        return false;
    }
    
    png_byte header[8];
    size_t bytesRead = fread(header, 1, 8, fp);
    if (bytesRead != 8 || png_sig_cmp(header, 0, 8)) {
        fclose(fp);
        return false;
    }
    
    auto& png = pImpl_->png;
    auto& info = pImpl_->info;
    
    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(fp);
        return false;
    }
    
    info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);
        return false;
    }
    
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);
        return false;
    }
    
    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);  
    png_read_info(png, info); 
    
    image.width_ = static_cast<int>(png_get_image_width(png, info));
    image.height_ = static_cast<int>(png_get_image_height(png, info));
    
    if (!convertToRgb(png, info, image)) {
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);
        return false;
    }
    
    image.data_.resize(static_cast<size_t>(image.width_) * 
                       static_cast<size_t>(image.height_) * 
                       static_cast<size_t>(image.channels_));
    
    std::vector<png_bytep> rows(static_cast<size_t>(image.height_));
    for (int y = 0; y < image.height_; y++) {
        rows[static_cast<size_t>(y)] = image.data_.data() + 
                                       static_cast<size_t>(y) * 
                                       static_cast<size_t>(image.width_) * 
                                       static_cast<size_t>(image.channels_);
    }
    
    png_read_image(png, rows.data());
    
    png_destroy_read_struct(&png, &info, nullptr);
    fclose(fp);
    
    return true;
}

bool PngLoader::save(const std::string& filename, const Image& image, int /*quality*/) {
    FILE* fp = fopen(filename.c_str(), "wb");
    if (!fp) {
        return false;
    }
    
    auto& png = pImpl_->png;
    auto& info = pImpl_->info;
    
    png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(fp);
        return false;
    }
    
    info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return false;
    }
    
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return false;
    }
    
    png_init_io(png, fp);
    
    int color_type;
    switch (image.channels_) {
        case 1:
            color_type = PNG_COLOR_TYPE_GRAY;       
            break;
        case 2:
            color_type = PNG_COLOR_TYPE_GRAY_ALPHA; 
            break;
        case 3:
            color_type = PNG_COLOR_TYPE_RGB;        
            break;
        case 4:
            color_type = PNG_COLOR_TYPE_RGBA;    
            break;
        default:
            color_type = PNG_COLOR_TYPE_RGB;        
            break;
    }
    
    png_set_IHDR(png, info, 
                 static_cast<png_uint_32>(image.width_), 
                 static_cast<png_uint_32>(image.height_),
                 8,                                   
                 color_type,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    
    png_write_info(png, info);
    
    std::vector<png_bytep> rows(static_cast<size_t>(image.height_));
    for (int y = 0; y < image.height_; y++) {
        rows[static_cast<size_t>(y)] = const_cast<png_bytep>(
            image.data_.data() + 
            static_cast<size_t>(y) * 
            static_cast<size_t>(image.width_) * 
            static_cast<size_t>(image.channels_)
        );
    }
    
    png_write_image(png, rows.data());

    png_write_end(png, nullptr);
    
    png_destroy_write_struct(&png, &info);
    fclose(fp);
    
    return true;
}

} 