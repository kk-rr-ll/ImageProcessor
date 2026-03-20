#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <memory>

namespace image_processor {

class Image;

class ImageLoader {
public:
    virtual ~ImageLoader() = default;
    virtual bool load(const std::string& filename, Image& image) = 0;
    virtual bool save(const std::string& filename, const Image& image, int quality = 90) = 0;
    virtual bool canHandle(const std::string& filename) const = 0;
};

} 