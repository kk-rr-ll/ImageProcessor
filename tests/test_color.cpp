#include "test_common.h"

using namespace image_processor;
using namespace image_processor_test;

TEST_F(ImageTestBase, ToGrayscale_ChangesChannelsCorrectly) {
    Image img = loadTestImage();
    int w = img.getWidth(), h = img.getHeight(), c = img.getChannels();
    ASSERT_EQ(c, 3);

    img.toGrayscale();

    EXPECT_EQ(img.getWidth(), w);
    EXPECT_EQ(img.getHeight(), h);
    EXPECT_EQ(img.getChannels(), c);

    uint8_t* data = img.getData();
    for (int i = 0; i < w * h; ++i) {
        uint8_t r = data[i * c + 0];
        uint8_t g = data[i * c + 1];
        uint8_t b = data[i * c + 2];
        EXPECT_EQ(r, g) << "Pixel " << i << " R != G";
        EXPECT_EQ(r, b) << "Pixel " << i << " R != B";
    }
}

TEST_F(ImageTestBase, ToGrayscale_TwiceKeepsGrayscale) {
    Image img = loadTestImage();
    img.toGrayscale(); 
    img.toGrayscale();

    int w = img.getWidth(), h = img.getHeight(), c = img.getChannels();
    uint8_t* data = img.getData();
    for (int i = 0; i < w * h; ++i) {
        uint8_t r = data[i * c + 0];
        uint8_t g = data[i * c + 1];
        uint8_t b = data[i * c + 2];
        EXPECT_EQ(r, g) << "Pixel " << i << " R != G after second grayscale";
        EXPECT_EQ(r, b) << "Pixel " << i << " R != B after second grayscale";
    }
}

TEST_F(ImageTestBase, ToNegative_InvertsPixels) {
    Image img = loadTestImage();
    auto original = copyImageData(img);

    img.toNegative();
    uint8_t* data = img.getData();
    size_t size = original.size();
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(data[i], 255 - original[i]) << "Byte " << i;
    }
}

TEST_F(ImageTestBase, ToNegative_TwiceRestoresOriginal) {
    Image img = loadTestImage();
    auto original = copyImageData(img);

    img.toNegative();
    img.toNegative();
    auto restored = copyImageData(img);

    EXPECT_EQ(original, restored);
}

TEST_F(ImageTestBase, ToNegative_DoesNotChangeDimensions) {
    Image img = loadTestImage();
    int w = img.getWidth(), h = img.getHeight(), c = img.getChannels();

    img.toNegative();

    EXPECT_EQ(img.getWidth(), w);
    EXPECT_EQ(img.getHeight(), h);
    EXPECT_EQ(img.getChannels(), c);
}