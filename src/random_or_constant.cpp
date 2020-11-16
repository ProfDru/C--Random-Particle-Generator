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
                                   bool start_random)
    : constant(constant),
      min_value(min),
      max_value(max),
      rand_min(min),
      rand_max(max),
      generator(alg),
      use_random(start_random) {
  // If the distribution is set to a null pointer, create a uniform distribution
  // so distribution is never left as a null pointer.
  if (!dist)
    distribution = std::unique_ptr<Distribution>(new Uniform(0, 1));
  else
    distribution = std::unique_ptr<Distribution>(dist);
}

float RandomOrConstant::get_number() {
  return use_random ? gen_random_number() * scale_factor : constant;
}

inline float RandomOrConstant::gen_random_number() {
  return distribution->get_number(generator);
}

void RandomOrConstant::set_generator(RNG_Algorithm alg) {
  generator.set_type(alg);
}

void RandomOrConstant::set_distribution(Distribution* dist) {
  distribution = std::unique_ptr<Distribution>(dist);
}

}  // namespace rpg