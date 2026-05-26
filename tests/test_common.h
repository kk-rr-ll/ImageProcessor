#pragma once

#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include "image.h"

namespace image_processor_test {

using namespace image_processor;

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

    Image loadTestImage(const std::string& filename = "test_image1.bmp") const {
        Image img;
        std::string path = getTestImagePath(filename);
        EXPECT_TRUE(img.load(path)) << "Failed to load " << path;
        return img;
    }

    static bool imagesEqual(const Image& a, const Image& b) {
        if (a.getWidth() != b.getWidth() || a.getHeight() != b.getHeight() || a.getChannels() != b.getChannels())
            return false;
        size_t size = a.getWidth() * a.getHeight() * a.getChannels();
        return std::memcmp(a.getData(), b.getData(), size) == 0;
    }

    static std::vector<uint8_t> copyImageData(const Image& img) {
        size_t size = img.getWidth() * img.getHeight() * img.getChannels();
        std::vector<uint8_t> data(size);
        std::memcpy(data.data(), img.getData(), size);
        return data;
    }

    std::string test_data_dir_;
};

}