#include <math/random/generator.h>

namespace rpg::math::random {

// helper constant for the visitor #3
template <class>
inline constexpr bool always_false_v = false;

// helper type for the visitor #4
template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

REngine determine_generator_variant(RNG_Algorithm alg) {
  switch (alg) {
    case RNG_Algorithm::KNUTH:
      return std::knuth_b();
    case RNG_Algorithm::MINSTD:
      return std::minstd_rand();
    case RNG_Algorithm::MT19937:
      return std::mt19937();
    case RNG_Algorithm::RANLUX48:
      return std::ranlux48();
    case RNG_Algorithm::RANLUX48_B:
      return std::ranlux48_base();
    default:
      return std::minstd_rand();
  }
}

Generator::Generator(RNG_Algorithm alg)
    : alg(alg),
      reng(determine_generator_variant(alg)),
      device(std::random_device()) {
  seed_engine();
}

gen_t Generator::operator()() {
  return get_rand();
}

void Generator::seed_engine() {
  const auto true_random = this->device();

  std::visit(overloaded{[true_random](auto& arg) { arg.seed(true_random); }},
             reng);
}

gen_t Generator::get_rand() {
  return std::visit(
      overloaded{[](auto& arg) { return static_cast<gen_t>(arg()); }}, reng);
}

gen_t Generator::min() const {
  return std::visit(
      overloaded{[](auto arg) { return static_cast<gen_t>(arg.min()); }}, reng);
}
gen_t Generator::max() const {
  return std::visit(
      overloaded{[](auto arg) { return static_cast<gen_t>(arg.max()); }}, reng);
}

}  // namespace rpg::math::random