#include "test_common.h"

using namespace image_processor;
using namespace image_processor_test;

TEST_F(ImageTestBase, LoadValidBmp) {
    Image img;
    EXPECT_TRUE(img.load(getTestImagePath("test_image1.bmp")));
    EXPECT_GT(img.getWidth(), 0);
    EXPECT_GT(img.getHeight(), 0);
    EXPECT_EQ(img.getChannels(), 3);
    EXPECT_NE(img.getData(), nullptr);
}

TEST_F(ImageTestBase, LoadValidPng) {
    Image img;
    EXPECT_TRUE(img.load(getTestImagePath("test_image1.png")));
    EXPECT_GT(img.getWidth(), 0);
    EXPECT_GT(img.getHeight(), 0);
    EXPECT_NE(img.getData(), nullptr);
}

TEST_F(ImageTestBase, LoadValidJpeg) {
    Image img;
    EXPECT_TRUE(img.load(getTestImagePath("test_image1.jpeg")));
    EXPECT_GT(img.getWidth(), 0);
    EXPECT_GT(img.getHeight(), 0);
    EXPECT_NE(img.getData(), nullptr);
}

TEST_F(ImageTestBase, LoadUnsupportedExtension) {
    Image img;
    EXPECT_FALSE(img.load("file.xyz"));
}

TEST_F(ImageTestBase, LoadNonexistentFile) {
    Image img;
    EXPECT_FALSE(img.load(getTestImagePath("missing.bmp")));
}

TEST_F(ImageTestBase, SaveToTempFile) {
    Image img;
    ASSERT_TRUE(img.load(getTestImagePath("test_image1.bmp")));
    
    std::string temp_file = getTestImagePath("temp_test_save.bmp");
    EXPECT_TRUE(img.save(temp_file, 90));
    
    Image loaded;
    EXPECT_TRUE(loaded.load(temp_file));
    EXPECT_EQ(loaded.getWidth(), img.getWidth());
    EXPECT_EQ(loaded.getHeight(), img.getHeight());
    
    std::remove(temp_file.c_str());
}