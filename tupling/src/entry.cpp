#include "entry.h"

template <typename T>
std::string suffix() { return "/F"; }

// Template specializations for different types.
template<> std::string suffix<bool>() { return "/O"; }

template<> std::string suffix<unsigned int>() { return "i"; }

template<> std::string suffix<int>() { return "/I"; }

template<> std::string suffix<float>() { return "/F"; }

template<> std::string suffix<double>() { return "/D"; }