#pragma once

#include "../image_loader.h"
#include <cstdint>
#include <fstream>

namespace image_processor {

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t signature;       // BM
    uint32_t fileSize;        
    uint32_t reserved;        // reserved (0)
    uint32_t dataOffset;      // Offset to pixel data
    uint32_t headerSize;      // default (40)
    int32_t width;            
    int32_t height;           
    uint16_t planes;          // number of planes (1)
    uint16_t bitsPerPixel;    
    uint32_t compression;     // 0 - whithout compression
    uint32_t imageSize;       
    int32_t xPixelsPerMeter;  // horizontal
    int32_t yPixelsPerMeter;  // vertical
    uint32_t colorsUsed;      
    uint32_t colorsImportant; 
};
#pragma pack(pop)

class BmpLoader : public ImageLoader {
public:
    bool load(const std::string& filename, Image& image) override;
    bool save(const std::string& filename, const Image& image, int quality = 90) override;
    bool canHandle(const std::string& filename) const override;

private:
    bool readHeader(std::ifstream& file, BMPHeader& header);
    bool validateHeader(const BMPHeader& header) const;
    int calculateRowSize(int width, int channels) const;
};

}