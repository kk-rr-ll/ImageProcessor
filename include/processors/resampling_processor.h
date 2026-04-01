#pragma once

#include <image.h>

namespace image_processor{
    Image resizeNearestNeighborPixelBasedSampling(const Image& img, int newWidth, int newHeight);
    Image resizeBilinearPixelBasedSampling(const Image& img, int newWidth, int newHeight);
}