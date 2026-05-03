#pragma once

#include <image.h>
#include <string>
#include <vector>

namespace image_processor {

struct FontGlyph {
    std::vector<std::vector<bool>> bitmap;
    int width;
    int height;
    int advance;
    int offsetX;
    int offsetY;
};

class TextRenderer {
public:
    static void drawText(Image& img, 
                        const std::string& text, 
                        int x, int y,
                        const std::vector<uint8_t>& color,
                        int fontSize,
                        const std::string& fontFamily = "default");
};

} // namespace image_processor