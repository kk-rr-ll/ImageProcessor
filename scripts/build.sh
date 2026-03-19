#!/bin/bash

set -e  # exit on error

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# Default parameters
BUILD_TYPE=${1:-Release}
BUILD_DIR="$PROJECT_ROOT/build"
BUILD_TESTS=${BUILD_TESTS:-ON}
BUILD_EXAMPLES=${BUILD_EXAMPLES:-ON}
JOBS=${JOBS:-$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)}

echo -e "${GREEN}=== Building Project ===${NC}"
echo "Project root: $PROJECT_ROOT"
echo "Build type: $BUILD_TYPE"
echo "Build dir: $BUILD_DIR"
echo "Tests: $BUILD_TESTS"
echo "Examples: $BUILD_EXAMPLES"
echo "Jobs: $JOBS"

# create a build folder
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# CMake configuration
echo -e "${YELLOW}Configuring CMake...${NC}"
cmake "$PROJECT_ROOT" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DBUILD_TESTS="$BUILD_TESTS" \
    -DBUILD_EXAMPLES="$BUILD_EXAMPLES" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# build
echo -e "${YELLOW}Building...${NC}"
cmake --build . --parallel "$JOBS"

echo -e "${GREEN}✓ Build complete!${NC}"