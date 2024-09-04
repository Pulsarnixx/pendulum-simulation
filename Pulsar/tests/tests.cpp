#include <gtest/gtest.h>

/*
    Temporary simple test config.
    It will be implemented later during matematicial 
    operation and manipulation

*/
int Factorial(int n){
    if(n == 0) return 1;

    return 0;
}

TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(Factorial(0), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
