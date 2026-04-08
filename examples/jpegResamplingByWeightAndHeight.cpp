#include "image.h"
#include <iostream>
#include <cstdlib>

using namespace image_processor;

int main() {
    Image img;

    const char* testDataDir = std::getenv("TEST_DATA_DIR");
    
    std::string loadPath;
    std::string savePath;
    
    loadPath = std::string(testDataDir) + "/test_image1.jpeg";
    savePath = std::string(testDataDir) + "/resampled_image.jpeg";
    std::cout << "Using TEST_DATA_DIR: " << testDataDir << std::endl;
    std::cout << "Loading from: " << loadPath << std::endl;
    
    if (!img.load(loadPath)) {
        std::cerr << "Failed to load image!" << std::endl;
        return 1;
    }
    
    std::cout << "Success! Image loaded.\n";
    std::cout << "Image parameters: \n";
    std::cout << "Width: " << img.getWidth() << "\n";
    std::cout << "Height: " << img.getHeight() << "\n";
    
    int newWidth = img.getWidth() * 5;
    int newHeight = img.getHeight() * 10;
    std::cout << "\nResampling by width and height...\n";
    img.resamplingByWidthAndHeight(newWidth, newHeight, InterpolationMethod::BILINEAR);
    
    std::cout << "Image parameters: \n";
    std::cout << "Width: " << img.getWidth() << "\n";
    std::cout << "Height: " << img.getHeight() << "\n";

    std::cout << "\nSaving to: " << savePath << std::endl;
    if (!img.save(savePath, 90)) {
        std::cerr << "Failed to save image!" << std::endl;
        return 1;
    }
    
    std::cout << "Success! Image saved.\n";
    return 0;
}