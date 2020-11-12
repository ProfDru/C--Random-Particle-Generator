#pragma once

#include <math/random/distribution.h>
#include <random>
#include <concepts>

namespace rpg::math::random {

template <typename T>
concept RandomNumberDistribuiton = requires(T a, Generator& g) {
  { a(g) }
  ->std::floating_point;
};

template <RandomNumberDistribuiton dist_t>
class TMPDistribution : public Distribution {
 protected:
  dist_t dist;

  TMPDistribution(dist_t distribution) : dist(distribution){};

 public:
  inline float get_number(Generator& in) override { return dist(in); }
  ~TMPDistribution(){};
};

class ExtremeDistribution
    : public TMPDistribution<std::extreme_value_distribution<float>> {
 public:
  inline ExtremeDistribution(float std, float mean)
      : TMPDistribution(std::extreme_value_distribution(std, mean)){};
};

class WeibullDistribution
    : public TMPDistribution<std::weibull_distribution<float>> {
 public:
  inline WeibullDistribution(float a, float b)
      : TMPDistribution(std::weibull_distribution<float>(a, b)){};
};

class ChiSquaredDistribution
    : public TMPDistribution<std::chi_squared_distribution<float>> {
 public:
  inline ChiSquaredDistribution(float dof)
      : TMPDistribution(std::chi_squared_distribution(dof)){};
};

class StudentDistribution
    : public TMPDistribution<std::student_t_distribution<float>> {
 public:
  inline StudentDistribution(float dof)
      : TMPDistribution(std::student_t_distribution<float>(dof)){};
};

class FisherDistribution
    : public TMPDistribution<std::fisher_f_distribution<float>> {
 public:
  inline FisherDistribution(float m, float n)
      : TMPDistribution(std::fisher_f_distribution<float>(m, n)){};
};

class GammaDistribution
    : public TMPDistribution<std::gamma_distribution<float>> {
 public:
  inline GammaDistribution(float alpha, float beta)
      : TMPDistribution(std::gamma_distribution<float>(alpha, beta)){};
};
class ExponentialDistribution
    : public TMPDistribution<std::exponential_distribution<float>> {
 public:
  inline ExponentialDistribution(float lambda)
      : TMPDistribution(std::exponential_distribution<float>(lambda)){};
};

}  // namespace rpg::math::random