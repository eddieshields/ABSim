#include "random.h"

using namespace ABSIM;

thread_local std::mt19937_64              Random::engine_      = std::mt19937_64();

std::uniform_real_distribution< real_t >  Random::uniform_     = std::uniform_real_distribution< real_t >();
std::exponential_distribution < real_t >  Random::exponential_ = std::exponential_distribution < real_t >();
std::normal_distribution      < real_t >  Random::normal_      = std::normal_distribution      < real_t >();
std::uniform_int_distribution < int_t >   Random::integer_     = std::uniform_int_distribution < int_t > (0,1);