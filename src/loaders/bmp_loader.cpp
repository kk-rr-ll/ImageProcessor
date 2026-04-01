#include "loaders/bmp_loader.h"
#include "image.h"

#include <fstream>
#include <algorithm>
#include <cmath>

namespace image_processor {

bool BmpLoader::canHandle(const std::string& filename) const {
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    return ext == "bmp";
}

bool BmpLoader::readHeader(std::ifstream& file, BMPHeader& header) {
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    
    return file.good();
}

bool BmpLoader::validateHeader(const BMPHeader& header) const {
    // 'BM' = 0x4D42 (little-endian)
    if (header.signature != 0x4D42) {
        return false;
    }
    
    if (header.planes != 1) {
        return false;
    }
    
    if (header.bitsPerPixel != 24 && header.bitsPerPixel != 32) {
        return false;
    }
    
    if (header.compression != 0) {
        return false;
    }
    
    return true;
}

int BmpLoader::calculateRowSize(int width, int channels) const {
    int bytesPerRow = width * channels;
    
    // align to the nearest multiple of 4
    return ((bytesPerRow + 3) / 4) * 4;
}

bool BmpLoader::load(const std::string& filename, Image& image) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return false;  
    }
    
    BMPHeader header;
    if (!readHeader(file, header) || !validateHeader(header)) {
        return false;  
    }
    
    int width = header.width;
    int height = std::abs(header.height);  
    int channels = header.bitsPerPixel / 8;  // 24bit=3ch, 32bit=4ch
    
    // move to pixel data
    file.seekg(header.dataOffset);
    
    int rowSize = calculateRowSize(width, channels);
    std::vector<uint8_t> rowData(rowSize);
    
    image.data_.resize(width * height * channels);
    image.width_ = width;
    image.height_ = height;
    image.channels_ = channels;
    
    // BMP stores lines from bottom to top
    for (int y = height - 1; y >= 0; y--) {
        file.read(reinterpret_cast<char*>(rowData.data()), rowSize);
        
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channels; c++) {
                image.data_[(y * width + x) * channels + c] = 
                    rowData[x * channels + c];
            }
        }
    }
    
    return file.good();
}

bool BmpLoader::save(const std::string& filename, const Image& image, int /*quality*/) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        return false;  
    }
    
    BMPHeader header = {};
    header.signature = 0x4D42;            
    header.fileSize = sizeof(BMPHeader) + image.width_ * image.height_ * image.channels_;
    header.dataOffset = sizeof(BMPHeader);  
    header.headerSize = 40;                  
    header.width = image.width_;
    header.height = image.height_;
    header.planes = 1;                     
    header.bitsPerPixel = image.channels_ * 8;
    header.imageSize = image.width_ * image.height_ * image.channels_;
    
    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    
    int rowSize = calculateRowSize(image.width_, image.channels_);
    std::vector<uint8_t> rowData(rowSize, 0);  
    
    // BMP stores lines from bottom to top
    for (int y = image.height_ - 1; y >= 0; y--) {
        for (int x = 0; x < image.width_; x++) {
            for (int c = 0; c < image.channels_; c++) {
                rowData[x * image.channels_ + c] = 
                    image.data_[(y * image.width_ + x) * image.channels_ + c];
            }
        }
        
        file.write(reinterpret_cast<const char*>(rowData.data()), rowSize);
    }
    
    return file.good();
}

} 