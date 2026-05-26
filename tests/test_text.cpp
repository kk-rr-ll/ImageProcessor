#include "test_common.h"
#include <random>

using namespace image_processor;
using namespace image_processor_test;

TEST_F(ImageTestBase, DrawText_DoesNotCrash) {
    Image img = loadTestImage();
    std::vector<uint8_t> color = {255, 0, 0};
    EXPECT_NO_THROW(img.drawText("Hello", 10, 10, color, 16, "Arial"));
}

TEST_F(ImageTestBase, DrawText_ChangesPixels) {
    Image img;
    img.setSize(200, 100, 3);
    uint8_t* data = img.getData();
    size_t size = img.getWidth() * img.getHeight() * img.getChannels();
    for (size_t i = 0; i < size; ++i) {
        data[i] = 128;
    }
    auto before = copyImageData(img);

    std::vector<uint8_t> color = {255, 255, 255};
    img.drawText("Test", 10, 10, color, 20, "Arial");

    auto after = copyImageData(img);
    EXPECT_NE(before, after) << "Image did not change after drawing text";
}

TEST_F(ImageTestBase, DrawText_InBounds) {
    Image img;
    img.setSize(100, 100, 3);
    // Заполняем чёрным
    std::memset(img.getData(), 0, 100 * 100 * 3);

    std::vector<uint8_t> white = {255, 255, 255};
    img.drawText("A", 10, 10, white, 20, "Arial");

    bool changed = false;
    for (int dy = -5; dy <= 20; ++dy) {
        for (int dx = -5; dx <= 20; ++dx) {
            int x = 10 + dx, y = 10 + dy;
            if (x >= 0 && x < 100 && y >= 0 && y < 100) {
                uint8_t* pixel = img.getPixelWithBeginChannel(x, y);
                if (pixel[0] != 0 || pixel[1] != 0 || pixel[2] != 0) {
                    changed = true;
                    break;
                }
            }
        }
    }
    EXPECT_TRUE(changed) << "No white pixels found near the text position";
}