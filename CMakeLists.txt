cmake_minimum_required(VERSION 3.20)
project(producer_consumer_cpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Include your headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Main executable
add_executable(producer_consumer src/main.cpp)

# Enable testing
enable_testing()

# Fetch GoogleTest for unit tests
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(tests tests/test_main.cpp)
target_link_libraries(tests gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)

