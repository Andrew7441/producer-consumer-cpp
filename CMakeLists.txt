cmake_minimum_required(VERSION 3.20)
project(producer_consumer_cpp LANGUAGES CXX)

cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- library for core logic ---
add_library(pc_lib STATIC
    src/producer_consumer.cpp
)
target_include_directories(pc_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# --- main executable ---
add_executable(producer_consumer
    src/main.cpp
)
target_link_libraries(producer_consumer PRIVATE pc_lib)

# --- testing ---
enable_testing()
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    tests/test_main.cpp
)
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(tests PRIVATE gtest_main pc_lib)

include(GoogleTest)
gtest_discover_tests(tests)





