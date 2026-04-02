#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <memory>

namespace image_processor {

class ImageLoader;

struct ImageData {
    std::vector<uint8_t>& data;
    const int width;
    const int height;
    const int channels;
};

class Image {
public:
    Image();
    ~Image();

    // prohibition of copying
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

    // permission to move semantics
    Image(Image&& other) noexcept;
    Image& operator=(Image&& other) noexcept;

    // load, save
    bool load(const std::string& filename);
    bool save(const std::string& filename, int quality = 90);

    // resampling
    void resamplingByWidth(int width, InterpolationMethod interpolationMethod);
    void resamplingByHeight(int height, InterpolationMethod interpolationMethod);
    void resamplingByWidthAndHeight(int width, int height, InterpolationMethod interpolationMethod);

    // color
    void toGray();
    void toNegative();

    // getters
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getChannels() const { return channels_; }
    const uint8_t* getData() const { return data_.data(); }
    uint8_t* getData() { return data_.data(); }
    uint8_t getPixel(int x, int y, int ch) const { return data_[(y * width_ + x) * channels_ + ch]; }
    const uint8_t* getPixelWhithBeginChannel(int x, int y) const { return &data_[(y * width_ + x) * channels_]; }
    uint8_t* getPixelWhithBeginChannel(int x, int y) { return &data_[(y * width_ + x) * channels_]; }
    const Image& getImage() const{
        return *this;
    }
    Image& getImage(){
        return *this;
    }

    
    // get ImageData for processors
    ImageData getImageData() { return {data_, width_, height_, channels_}; }
    const ImageData getImageData() const { 
        return {const_cast<std::vector<uint8_t>&>(data_), width_, height_, channels_}; 
    }

    void SetChannels(int channels) { channels_ = channels; }
    void setSize(int width, int height, int channels) {
        width_ = width;
        height_ = height;
        channels_ = channels;
        data_.resize(width * height * channels);
    }
    void setPixel(int x, int y, int ch, uint8_t value){
        data_[(y * width_ + x) * channels_ + ch] = value;
    }
    void setImage(Image img){
        data_.assign(img.getData(), img.getData() + (img.getWidth() * img.getHeight() * img.getChannels()));
        width_ = img.getWidth();
        height_ = img.getHeight();
        channels_ = img.getChannels(); 
    }

private:
    friend class BmpLoader;
    friend class JpegLoader;
    friend class PngLoader;

    std::vector<uint8_t> data_;
    int width_;
    int height_;
    int channels_;
};

} 