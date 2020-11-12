#include <random_or_constant.h>
#include <math/random/distributions/uniform.h>
#include <cassert>

using namespace rpg::math::random;
namespace rpg {

RandomOrConstant::RandomOrConstant()
    : constant(0.5),
      min_value(0),
      max_value(1),
      generator(),
      use_random(false),
      distribution(new Uniform(0, 1)){};

RandomOrConstant::RandomOrConstant(float constant,
                                   float min,
                                   float max,
                                   RNG_Algorithm alg,
                                   Distribution* dist,
                                   bool start_random,
                                   bool force_wrap)
    : constant(constant),
      min_value(min),
      max_value(max),
      rand_min(min),
      rand_max(max),
      generator(alg),
      use_random(start_random),
      force_wrap(force_wrap) {
  if (!dist)
    distribution = std::unique_ptr<Distribution>(new Uniform(0, 1));
  else
    distribution = std::unique_ptr<Distribution>(dist);
}

float RandomOrConstant::get_number() {
  return use_random ? gen_random_number() * scale_factor : constant;
}

inline float RandomOrConstant::gen_random_number() {
  assert(distribution.get());
  return distribution->get_number(generator);
  // return std::lerp(rand_min, rand_max, distribution->get_number(generator));
}

void RandomOrConstant::set_generator(RNG_Algorithm alg) {
  generator.set_type(alg);
}

void RandomOrConstant::set_distribution(Distribution* dist) {
  distribution = std::unique_ptr<Distribution>(dist);
}

}  // namespace rpg