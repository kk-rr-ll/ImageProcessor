#pragma once

#include <image.h>

namespace image_processor{
    class ColorProcessor{
        ColorProcessor();
        ~ColorProcessor()=default;

    public:
        static void toGrayscale(Image& img);
        static void toNegative(Image& img);
    };
}