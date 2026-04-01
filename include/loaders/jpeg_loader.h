#pragma once

#include "../image_loader.h"
#include <cstdio>
#include <setjmp.h>
#include <memory>

struct jpeg_common_struct;
struct jpeg_decompress_struct;
struct jpeg_compress_struct;
struct jpeg_error_mgr;

namespace image_processor {

struct JpegErrorManager {
    struct jpeg_error_mgr* pub; 
    jmp_buf setjmp_buffer;      // buf for longjmp
};

class JpegLoader : public ImageLoader {
public:
    JpegLoader();
    ~JpegLoader();

    bool load(const std::string& filename, Image& image) override;
    bool save(const std::string& filename, const Image& image, int quality = 90) override;
    bool canHandle(const std::string& filename) const override;

private:
    static void errorHandler(jpeg_common_struct* cinfo);
    
    struct Impl;
    std::unique_ptr<Impl> pImpl_;
};

} 