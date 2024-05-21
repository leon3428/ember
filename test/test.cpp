#include <gtest/gtest.h>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "ember.hpp"

TEST(SanityCheck, SanityCheck) { EXPECT_EQ(5 * 6, 30); }

TEST(BinomialCoef, BinomialCoef) { 
  EXPECT_EQ(ember::binomialCoefficient(7, 2), 21);
  EXPECT_EQ(ember::binomialCoefficient(13, 4), 715);
  EXPECT_EQ(ember::binomialCoefficient(9, 2), 36);
  EXPECT_EQ(ember::binomialCoefficient(19, 13), 27132);
  EXPECT_EQ(ember::binomialCoefficient(4, 1), 4);
  EXPECT_EQ(ember::binomialCoefficient(7, 4), 35);
  EXPECT_EQ(ember::binomialCoefficient(10, 2), 45);
  EXPECT_EQ(ember::binomialCoefficient(15, 7), 6435);
  EXPECT_EQ(ember::binomialCoefficient(13, 8), 1287);
  EXPECT_EQ(ember::binomialCoefficient(11, 5), 462);
  EXPECT_EQ(ember::binomialCoefficient(8, 7), 8);
  EXPECT_EQ(ember::binomialCoefficient(7, 3), 35);
  EXPECT_EQ(ember::binomialCoefficient(15, 11), 1365);
}