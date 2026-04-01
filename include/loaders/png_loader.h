#pragma once

#include "../image_loader.h"
#include <cstdio>
#include <memory>

namespace image_processor {

class PngLoader : public ImageLoader {
public:
    PngLoader();
    ~PngLoader();

    bool load(const std::string& filename, Image& image) override;
    bool save(const std::string& filename, const Image& image, int quality = 90) override;
    bool canHandle(const std::string& filename) const override;

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl_;
};

} 