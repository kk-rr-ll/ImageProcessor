#pragma once

#include <image.h>

namespace image_processor{
    enum class InterpolationMethod{
        NEAREST_NEIGHBOR,
        BILINEAR
    };

    class ResamplingProcessor{
        ResamplingProcessor();
        ~ResamplingProcessor();

        public:
            static Image resamplingByWidth(const Image& img, int width, InterpolationMethod InterpolationMethod);
            static Image resamplingByHeight(const Image& img, int height, InterpolationMethod InterpolationMethod);
            static Image resamplingByWidthAndHeight(const Image& img, int width, int height, InterpolationMethod InterpolationMethod);
        private:
            static Image resizeNearestNeighborPixelBasedSampling(const Image& img, int newWidth, int newHeight);
            static Image resizeBilinearPixelBasedSampling(const Image& img, int newWidth, int newHeight);
    };
}