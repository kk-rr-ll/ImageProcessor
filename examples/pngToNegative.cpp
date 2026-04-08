#include "image.h"
#include <iostream>
#include <cstdlib>

using namespace image_processor;

int main() {
    Image img;

    const char* testDataDir = std::getenv("TEST_DATA_DIR");
    
    std::string loadPath;
    std::string savePath;
    
    loadPath = std::string(testDataDir) + "/test_image1.png";
    savePath = std::string(testDataDir) + "/negative_image.png";
    std::cout << "Using TEST_DATA_DIR: " << testDataDir << std::endl;
    std::cout << "Loading from: " << loadPath << std::endl;
    
    if (!img.load(loadPath)) {
        std::cerr << "Failed to load image!" << std::endl;
        return 1;
    }

    std::cout << "Success! Image loaded.\n";

    std::cout << "\nTo negative...\n";
    img.toNegative();

    std::cout << "\nSaving to: " << savePath << std::endl;
    if (!img.save(savePath, 90)) {
        std::cerr << "Failed to save image!" << std::endl;
        return 1;
    }
    
    std::cout << "Success! Image saved.\n";
    return 0;
}