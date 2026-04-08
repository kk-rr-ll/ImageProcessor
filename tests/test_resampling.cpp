#include "test_common.h"
#include "processors/resampling_processor.h"

using namespace image_processor;
using namespace image_processor_test;

class ResamplingTest : public ImageTestBase {
protected:
    Image loadTestImage() const {
        Image img;
        std::string path = getTestImagePath("test_image1.bmp");
        EXPECT_TRUE(img.load(path)) << "Failed to load test image from " << path;
        return img;
    }
};

TEST_F(ResamplingTest, ResamplingByWidthScalesProportionally) {
    Image img = loadTestImage();
    int orig_w = img.getWidth();
    int orig_h = img.getHeight();
    int new_w = orig_w / 2;  
    if (new_w < 1) new_w = 1;

    img.resamplingByWidth(new_w, InterpolationMethod::BILINEAR);

    EXPECT_EQ(img.getWidth(), new_w);
    int expected_h = static_cast<int>(static_cast<double>(orig_h) * new_w / orig_w);
    EXPECT_EQ(img.getHeight(), expected_h);
    EXPECT_NE(img.getData(), nullptr);
}

TEST_F(ResamplingTest, ResamplingByWidthKeepsValidData) {
    Image img = loadTestImage();
    int new_w = img.getWidth() * 2;
    img.resamplingByWidth(new_w, InterpolationMethod::BILINEAR);
    EXPECT_EQ(img.getWidth(), new_w);
    EXPECT_NE(img.getData(), nullptr);
    uint8_t* data = img.getData();
    ASSERT_NE(data, nullptr);
    data[0]; // просто доступ
}

TEST_F(ResamplingTest, ResamplingByHeightScalesProportionally) {
    Image img = loadTestImage();
    int orig_w = img.getWidth();
    int orig_h = img.getHeight();
    int new_h = orig_h / 2;
    if (new_h < 1) new_h = 1;

    img.resamplingByHeight(new_h, InterpolationMethod::BILINEAR);

    EXPECT_EQ(img.getHeight(), new_h);
    int expected_w = static_cast<int>(static_cast<double>(orig_w) * new_h / orig_h);
    EXPECT_EQ(img.getWidth(), expected_w);
    EXPECT_NE(img.getData(), nullptr);
}

TEST_F(ResamplingTest, ResamplingByHeightKeepsValidData) {
    Image img = loadTestImage();
    int new_h = img.getHeight() * 2;
    img.resamplingByHeight(new_h, InterpolationMethod::BILINEAR);
    EXPECT_EQ(img.getHeight(), new_h);
    EXPECT_NE(img.getData(), nullptr);
}

TEST_F(ResamplingTest, ResamplingByWidthAndHeightChangesBoth) {
    Image img = loadTestImage();
    int new_w = img.getWidth() / 2;
    int new_h = img.getHeight() / 2;
    if (new_w < 1) new_w = 1;
    if (new_h < 1) new_h = 1;

    img.resamplingByWidthAndHeight(new_w, new_h, InterpolationMethod::BILINEAR);
    EXPECT_EQ(img.getWidth(), new_w);
    EXPECT_EQ(img.getHeight(), new_h);
    EXPECT_NE(img.getData(), nullptr);
}

TEST_F(ResamplingTest, ResamplingByWidthAndHeightWithDifferentInterpolation) {
    Image img = loadTestImage();
    int new_w = img.getWidth() + 10;
    int new_h = img.getHeight() + 10;

    img.resamplingByWidthAndHeight(new_w, new_h, InterpolationMethod::NEAREST_NEIGHBOR);
    img = loadTestImage();
    img.resamplingByWidthAndHeight(new_w, new_h, InterpolationMethod::BILINEAR);
}

TEST_F(ResamplingTest, ResamplingByZeroSizeIsSafe) {
    Image img = loadTestImage();
    EXPECT_NO_THROW(img.resamplingByWidth(0, InterpolationMethod::BILINEAR));
    EXPECT_NO_THROW(img.resamplingByHeight(0, InterpolationMethod::BILINEAR));
    EXPECT_NO_THROW(img.resamplingByWidthAndHeight(0, 0, InterpolationMethod::BILINEAR));
}