#include <iostream>
#include "image.h"

using namespace image_processor;

int main(){
    Image img;

    const char* testDataDir = std::getenv("TEST_DATA_DIR");
    
    std::string loadPath;
    std::string savePath;
    
    loadPath = std::string(testDataDir) + "/test_image1.jpeg";
    savePath = std::string(testDataDir) + "/text_image.jpeg";
    std::cout << "Using TEST_DATA_DIR: " << testDataDir << std::endl;
    std::cout << "Loading from: " << loadPath << std::endl;
    
    if (!img.load(loadPath)) {
        std::cerr << "Failed to load image!" << std::endl;
        return 1;
    }
    
    std::cout << "Success! Image loaded.\n";
    
    std::vector<uint8_t> textColor = {255, 255, 255};
    img.drawText("Hi!", 100, 100, textColor, 48);

    std::cout << "\nSaving to: " << savePath << std::endl;
    if (!img.save(savePath, 90)) {
        std::cerr << "Failed to save image!" << std::endl;
        return 1;
    }
    
    std::cout << "Success! Image saved.\n";
    
    return 0;
}