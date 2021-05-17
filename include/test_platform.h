#include <iostream>

void test_platform()
{
  #if defined(__AVX512F__) || defined(__AVX512__)
    std::cout << "Width = 512" << std::endl;
  #elif defined(__AVX__)
    std::cout << "Width = 256" << std::endl;
  #elif defined(__SSE__) || defined(__aarch64__) || defined(__ALTIVEC__)
    std::cout << "Width = 128" << std::endl;
  #else
    std::cout << "Width undefined" << std::endl;
  #endif
}