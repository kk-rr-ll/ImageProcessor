#include <processors/resampling_processor.h>
#include <algorithm>

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


    // f(x, y) = f(Q11)*(1-dx)*(1-dy) + f(Q21)*dx*(1-dy) + f(Q12)*(1-dx)*dy + f(Q22)*dx*dy
    // f(x, y) = левый верхний пиксель * вес + правый верхний пиксель * вес + ...
    // dx = x - x0; dy = y - y0 => дробные смещения по горизонтали; вертикали (от 0 до 1)
    // f(Qij) - пиксель 
    // вес пикселя = площадь прямоугольника противоположного угла
    // !!!Рекомендуется для масштабирования!!!
    Image resizeBilinearPixelBasedSampling(const Image& img, int newWidth, int newHeight){
        Image newImg;
        newImg.setSize(newWidth, newHeight, img.getChannels());

        int imgWidth = img.getWidth();
        int imgHeight = img.getHeight();

        double ratioByX = static_cast<double>(imgWidth) / static_cast<double>(newWidth);
        double ratioByY = static_cast<double>(imgHeight) / static_cast<double>(newHeight);

        for(int x = 0; x < newWidth; x++){
            double imgX = x * ratioByX;
            for(int y = 0; y < newHeight; y++){
                double imgY = y * ratioByY;

                int x0 = static_cast<int>(floor(imgX));
                int y0 = static_cast<int>(floor(imgY));
                int x1 = x0 + 1;
                int y1 = y0 + 1;

                double dx = imgX - x0;
                double dy = imgY - y0;

                double w11 = (1.0-dx)*(1.0-dy);
                double w12 = dx*(1.0-dy);
                double w21 = (1.0-dx)*dy;
                double w22 = dx*dy;

                const uint8_t* p11 = img.getPixelWhithBeginChannel(x0, y0);
                const uint8_t* p12 = img.getPixelWhithBeginChannel(x0, y1);
                const uint8_t* p21 = img.getPixelWhithBeginChannel(x1, y0);
                const uint8_t* p22 = img.getPixelWhithBeginChannel(x1, y1);

                for(int ch = 0; ch < img.getChannels(); ch++){
                    newImg.getPixelWhithBeginChannel(x, y)[ch] = static_cast<uint8_t>(std::clamp((p11[ch]*w11+p12[ch]*w12+p21[ch]*w21+p22[ch]*w22), 0.0, 255.0));
                }
            }
        }
    }
}