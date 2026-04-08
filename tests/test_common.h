#pragma once

#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>      
#include <vector>
#include "image.h"       

namespace image_processor_test {

using namespace image_processor;  

// Базовая фикстура
class ImageTestBase : public ::testing::Test {
protected:
    void SetUp() override {
        const char* data_dir = std::getenv("TEST_DATA_DIR");
        ASSERT_NE(data_dir, nullptr) << "TEST_DATA_DIR not set";
        test_data_dir_ = data_dir;
    }

    std::string getTestImagePath(const std::string& filename) const {
        return test_data_dir_ + "/" + filename;
    }

    std::string test_data_dir_;
};

class LoadedImageTest : public ImageTestBase {
protected:
    void SetUp() override {
        ImageTestBase::SetUp();
        std::string path = getTestImagePath("test_image1.bmp");
        ASSERT_TRUE(img_.load(path)) << "Failed to load test image";
        original_width_ = img_.getWidth();
        original_height_ = img_.getHeight();
        channels_ = img_.getChannels();
        ASSERT_GT(original_width_, 0);
        ASSERT_GT(original_height_, 0);
        ASSERT_EQ(channels_, 3);

        size_t data_size = original_width_ * original_height_ * channels_;
        original_data_.resize(data_size);
        std::memcpy(original_data_.data(), img_.getData(), data_size);
    }

    Image img_;                     
    int original_width_ = 0;
    int original_height_ = 0;
    int channels_ = 0;
    std::vector<uint8_t> original_data_;
};

} 