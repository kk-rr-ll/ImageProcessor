#pragma once

#include <image.h>

namespace image_processor{
    class ColorProcessor{
        ColorProcessor();
        ~ColorProcessor()=default;

    public:
        static void toGray(Image& img);
        static void toNegative(Image& img);
    };
}