#include <gtest/gtest.h>
#include <cstdlib>
#include "image.h"

using namespace image_processor;

class ImageLoadTest : public ::testing::Test {
protected:
    void SetUp() override {
        const char* data_dir = std::getenv("TEST_DATA_DIR");
        ASSERT_NE(data_dir, nullptr) << "TEST_DATA_DIR not set";
        test_data_dir_ = data_dir;
    }
    std::string test_data_dir_;
};

TEST_F(ImageLoadTest, LoadValidBmp) {
    Image img;
    std::string path = test_data_dir_ + "/test_image1.bmp";
    EXPECT_TRUE(img.load(path));
    EXPECT_GT(img.getWidth(), 0);
    EXPECT_GT(img.getHeight(), 0);
    EXPECT_EQ(img.getChannels(), 3);
    EXPECT_NE(img.getData(), nullptr);
}

TEST_F(ImageLoadTest, LoadValidPng) {
    Image img;
    std::string path = test_data_dir_ + "/test_image1.png";
    EXPECT_TRUE(img.load(path));
    EXPECT_GT(img.getWidth(), 0);
    EXPECT_GT(img.getHeight(), 0);
    EXPECT_NE(img.getData(), nullptr);
}

TEST_F(ImageLoadTest, LoadValidJpeg) {
    Image img;
    std::string path = test_data_dir_ + "/test_image1.jpeg";
    EXPECT_TRUE(img.load(path));
    EXPECT_GT(img.getWidth(), 0);
    EXPECT_GT(img.getHeight(), 0);
    EXPECT_NE(img.getData(), nullptr);
}

TEST_F(ImageLoadTest, LoadUnsupportedExtension) {
    Image img;
    EXPECT_FALSE(img.load("file.xyz"));
}

TEST_F(ImageLoadTest, LoadNonexistentFile) {
    Image img;
    EXPECT_FALSE(img.load(test_data_dir_ + "/missing.bmp"));
}