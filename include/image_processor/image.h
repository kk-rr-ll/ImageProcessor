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

    // resizing methods
    void resize(int newWidth, int newHeight);
    void resizeByWidth(int newWidth);
    void resizeByHeight(int newHeight);
    void resizeToMaxSize(int maxSize);
    void resizeToMinSize(int minSize);

    // getters
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getChannels() const { return channels_; }
    const uint8_t* getData() const { return data_.data(); }
    uint8_t* getData() { return data_.data(); }
    
    // get ImageData for processors
    ImageData getImageData() { return {data_, width_, height_, channels_}; }
    const ImageData getImageData() const { 
        return {const_cast<std::vector<uint8_t>&>(data_), width_, height_, channels_}; 
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