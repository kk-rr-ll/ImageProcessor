#include "image.h"
#include "loaders/bmp_loader.h"
#include "loaders/jpeg_loader.h"
#include "loaders/png_loader.h"
#include "processors/resampling_processor.h"
#include "processors/color_processor.h"

#include <algorithm>
#include <cctype>

namespace image_processor {

Image::Image() : width_(0), height_(0), channels_(3) {}

Image::~Image() = default;

Image::Image(Image&& other) noexcept
    : data_(std::move(other.data_))
    , width_(other.width_)
    , height_(other.height_)
    , channels_(other.channels_) {
    other.width_ = 0;
    other.height_ = 0;
    other.channels_ = 0;
}

Image& Image::operator=(Image&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        width_ = other.width_;
        height_ = other.height_;
        channels_ = other.channels_;
        
        other.width_ = 0;
        other.height_ = 0;
        other.channels_ = 0;
    }
    return *this;
}

bool Image::load(const std::string& filename) {
    std::unique_ptr<ImageLoader> loader;
    
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    if (ext == "bmp") {
        loader = std::make_unique<BmpLoader>();
    } else if (ext == "jpg" || ext == "jpeg") {
        loader = std::make_unique<JpegLoader>();
    } else if (ext == "png") {
        loader = std::make_unique<PngLoader>();
    } else {
        return false;
    }
    
    return loader->load(filename, *this);
}

bool Image::save(const std::string& filename, int quality) {
    std::unique_ptr<ImageLoader> loader;
    
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    if (ext == "bmp") {
        loader = std::make_unique<BmpLoader>();
    } else if (ext == "jpg" || ext == "jpeg") {
        loader = std::make_unique<JpegLoader>();
    } else if (ext == "png") {
        loader = std::make_unique<PngLoader>();
    } else {
        return false;
    }
    
    return loader->save(filename, *this, quality);
}

void Image::resamplingByWidth(int width, InterpolationMethod interpolationMethod = InterpolationMethod::BILINEAR){
    setImage(ResamplingProcessor::resamplingByWidth(getImage(), width, interpolationMethod));
}

void Image::resamplingByHeight(int height, InterpolationMethod interpolationMethod = InterpolationMethod::BILINEAR){
    setImage(ResamplingProcessor::resamplingByHeight(getImage(), height, interpolationMethod));
}

void Image::resamplingByWidthAndHeight(int width, int height, InterpolationMethod interpolationMethod = InterpolationMethod::BILINEAR){
    setImage(ResamplingProcessor::resamplingByWidthAndHeight(getImage(), width, height, interpolationMethod));
}

void Image::toGray(){
    ColorProcessor::toGray(getImage());
}

void Image::toNegative(){
    ColorProcessor::toNegative(getImage());
}
} 