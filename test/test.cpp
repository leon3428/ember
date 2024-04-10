#include <gtest/gtest.h>
#include <iostream>
#include <random>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include "my_glm.hpp"

auto printMat(const glm::mat4 &mat) -> void {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << mat[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

auto matEq(const glm::mat4 &m1, const glm::mat4 &m2) -> bool {
  float sum = 0.0f;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if(!std::isinf(m1[i][j]) || !std::isinf(m2[i][j]))
        sum += std::pow(m1[i][j] - m2[i][j], 2);
    }
  }

  sum /= 16;
  if (sum < 1e-9) return true;
  return false;
}

constexpr size_t iter = 1e5;

TEST(MyGlm, translate3D) {
  for (size_t i = 0; i < iter; i++) {
    auto randomVec = glm::linearRand(glm::vec3(-100.0f), glm::vec3(100.0f));
    auto res1 = my_glm::translate3D(randomVec);
    auto res2 = glm::translate(glm::mat4(1.0f), randomVec);

    EXPECT_EQ(res1, res2);
  }
}

TEST(MyGlm, scale3D) {
  for (size_t i = 0; i < iter; i++) {
    auto randomVec = glm::linearRand(glm::vec3(-100.0f), glm::vec3(100.0f));
    auto res1 = my_glm::scale3D(randomVec);
    auto res2 = glm::scale(glm::mat4(1.0f), randomVec);

    EXPECT_EQ(res1, res2);
  }
}

TEST(MyGlm, rotate3D) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(0.0f, 2.0f * M_PI);

  for (size_t i = 0; i < iter; i++) {
    auto randomVec = glm::normalize(glm::linearRand(glm::vec3(-100.0f), glm::vec3(100.0f)));
    auto randomAngle = dis(gen);

    auto res1 = my_glm::rotate3D(randomVec, randomAngle);
    auto res2 = glm::rotate(glm::mat4(1.0f), randomAngle, randomVec);

    EXPECT_TRUE(matEq(res1, res2));
  }
}

TEST(MyGlm, lookAt) {
  for (size_t i = 0; i < iter; i++) {
    auto eye = glm::linearRand(glm::vec3(-100.0f), glm::vec3(100.0f));
    auto center = glm::linearRand(glm::vec3(-100.0f), glm::vec3(100.0f));
    auto viewUp = glm::linearRand(glm::vec3(-100.0f), glm::vec3(100.0f));
    auto res1 = my_glm::lookAtMatrix(eye, center, viewUp);
    auto res2 = glm::lookAt(eye, center, viewUp);

    EXPECT_TRUE(matEq(res1, res2));
  }
}

TEST(MyGlm, frustum) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(0.0f, 100.0f);

  for (size_t i = 0; i < iter; i++) {
    auto r = dis(gen);
    auto b = dis(gen);
    auto n = dis(gen);
    auto f = n + dis(gen);

    auto res1 = my_glm::frustum(-r, r, -b, b, n, f);
    auto res2 = glm::frustum(-r, r, -b, b, n, f);

    EXPECT_TRUE(matEq(res1, res2));
  }
}