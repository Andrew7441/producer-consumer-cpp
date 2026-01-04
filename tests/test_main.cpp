#include <gtest/gtest.h>
#include "producer_consumer.h"

TEST(BufferTest, StartsEmpty) {
    reset_buffer();
    EXPECT_TRUE(buffer_empty());
    EXPECT_EQ(buffer_size(), 0u);
}

TEST(BufferTest, ProduceConsumeOnce) {
    reset_buffer();

    // Produce a value
    produce_one(42);
    EXPECT_EQ(buffer_size(), 1u);          // buffer should have 1 item

    // Consume (void function)
    consume_one();
    EXPECT_TRUE(buffer_empty());           // buffer should now be empty
    EXPECT_EQ(buffer_size(), 0u);          // optional: confirm size is 0
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
