#include <image_processor/processors/resampling_processor.h>

namespace image_processor {
    Image resizeNearestNeighborPixelBasedSampling(const Image& img, int newWidth, int newHeight){
        Image newImg;
        newImg.setSize(newWidth, newHeight, img.getChannels());

        int imgWidth = img.getWidth();
        int imgHeight = img.getHeight();

        double ratioByX = static_cast<double>(imgWidth) / static_cast<double>(newWidth);
        double ratioByY = static_cast<double>(imgHeight) / static_cast<double>(newHeight);

        for(int x = 0; x < newWidth; x++){
            for(int y = 0; y < newHeight; y++){
                int nearestPixelByX = x * ratioByX;
                int nearestPixelByY = y * ratioByY;

                if(imgWidth < nearestPixelByX) nearestPixelByX = imgWidth - 1;
                if(imgHeight < nearestPixelByY) nearestPixelByY = imgHeight - 1;

                for(int ch = 0; ch < img.getChannels(); ch++){
                    newImg.setPixel(x, y, ch, img.getPixel(nearestPixelByX, nearestPixelByY, ch));
                }
            }
        }

        return newImg;
    }
}