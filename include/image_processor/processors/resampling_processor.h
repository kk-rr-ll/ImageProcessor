#pragma once

#include <image_processor/image.h>

namespace image_processor{
    Image resizeNearestNeighborPixelBasedSampling(const Image& img, int newWidth, int newHeight);
}