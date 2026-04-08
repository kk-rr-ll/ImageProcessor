#include "test_common.h"
#include "processors/resampling_processor.h"

using namespace image_processor;
using namespace image_processor_test;

TEST_F(ImageTestBase, SaveAsBmp) {
    Image img;
    std::string load_path = getTestImagePath("test_image1.bmp");
    ASSERT_TRUE(img.load(load_path));

    std::string save_path = getTestImagePath("temp_save.bmp");
    EXPECT_TRUE(img.save(save_path, 90));

    Image loaded;
    EXPECT_TRUE(loaded.load(save_path));
    EXPECT_EQ(loaded.getWidth(), img.getWidth());
    EXPECT_EQ(loaded.getHeight(), img.getHeight());
    EXPECT_EQ(loaded.getChannels(), img.getChannels());

    // Сравниваем данные (попиксельно)
    size_t size = img.getWidth() * img.getHeight() * img.getChannels();
    EXPECT_EQ(std::memcmp(loaded.getData(), img.getData(), size), 0);

    std::remove(save_path.c_str());
}

TEST_F(ImageTestBase, SaveAsJpeg) {
    Image img;
    std::string load_path = getTestImagePath("test_image1.bmp");
    ASSERT_TRUE(img.load(load_path));

    std::string save_path = getTestImagePath("temp_save.jpg");
    EXPECT_TRUE(img.save(save_path, 85));

    Image loaded;
    EXPECT_TRUE(loaded.load(save_path));
    EXPECT_EQ(loaded.getWidth(), img.getWidth());
    EXPECT_EQ(loaded.getHeight(), img.getHeight());
    EXPECT_EQ(loaded.getChannels(), 3);

    EXPECT_NE(loaded.getData(), nullptr);

    std::remove(save_path.c_str());
}

TEST_F(ImageTestBase, SaveAsPng) {
    Image img;
    std::string load_path = getTestImagePath("test_image1.bmp");
    ASSERT_TRUE(img.load(load_path));

    std::string save_path = getTestImagePath("temp_save.png");
    EXPECT_TRUE(img.save(save_path, 0)); 

    Image loaded;
    EXPECT_TRUE(loaded.load(save_path));
    EXPECT_EQ(loaded.getWidth(), img.getWidth());
    EXPECT_EQ(loaded.getHeight(), img.getHeight());
    EXPECT_EQ(loaded.getChannels(), img.getChannels());

    size_t size = img.getWidth() * img.getHeight() * img.getChannels();
    EXPECT_EQ(std::memcmp(loaded.getData(), img.getData(), size), 0);

    std::remove(save_path.c_str());
}

TEST_F(ImageTestBase, SaveWithUnsupportedExtension) {
    Image img;
    std::string load_path = getTestImagePath("test_image1.bmp");
    ASSERT_TRUE(img.load(load_path));

    std::string save_path = getTestImagePath("temp_save.xyz");
    EXPECT_FALSE(img.save(save_path, 90));
    std::remove(save_path.c_str()); 
}

TEST_F(ImageTestBase, SaveWithInvalidQuality) {
    Image img;
    std::string load_path = getTestImagePath("test_image1.bmp");
    ASSERT_TRUE(img.load(load_path));

    std::string save_path = getTestImagePath("temp_save_invalid_quality.jpg");
    EXPECT_NO_THROW(img.save(save_path, -1));
    EXPECT_NO_THROW(img.save(save_path, 101));
    std::remove(save_path.c_str());
}

TEST_F(ImageTestBase, SaveOverwritesExistingFile) {
    Image img;
    std::string load_path = getTestImagePath("test_image1.bmp");
    ASSERT_TRUE(img.load(load_path));

    std::string save_path = getTestImagePath("temp_overwrite.bmp");
    EXPECT_TRUE(img.save(save_path, 90));
    img.resamplingByWidth(100, InterpolationMethod::BILINEAR);
    EXPECT_TRUE(img.save(save_path, 90));

    Image loaded;
    EXPECT_TRUE(loaded.load(save_path));
    EXPECT_EQ(loaded.getWidth(), 100);
    std::remove(save_path.c_str());
}