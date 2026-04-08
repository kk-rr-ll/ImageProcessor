#pragma once

#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>
#include <vector>
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

    std::string test_data_dir_;
};

}