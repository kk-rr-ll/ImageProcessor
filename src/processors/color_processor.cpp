#include <processors/color_processor.h>

namespace image_processor{
    void ColorProcessor::toGray(Image& img){
        int width = img.getWidth();
        int height = img.getHeight();
        int channels = img.getChannels();

        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++){
                uint8_t* pixel = img.getPixelWhithBeginChannel(x,y);

                uint8_t r = pixel[0];
                uint8_t g = pixel[1];
                uint8_t b = pixel[2];

                uint8_t gray = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
                
                pixel[0] = gray;
                pixel[1] = gray;
                pixel[2] = gray;
            }
        }
    }
}