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

    bool load(const std::string& filename);
    bool save(const std::string& filename, int quality = 90);

    // getters
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getChannels() const { return channels_; }
    const uint8_t* getData() const { return data_.data(); }
    uint8_t* getData() { return data_.data(); }
    uint8_t getPixel(int x, int y, int ch) const{
        return data_[(y * width_ + x) * channels_ + ch];
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