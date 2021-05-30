#ifndef ABSIM_WELCOME_H
#define ABSIM_WELCOME_H

#include <iostream>

namespace ABSIM {

static const char* welcome_message = R"(  
  **************************************************************
  *                                                            *
  *         ___      .______        _______. __  .___  ___.    *
  *        /   \     |   _  \      /       ||  | |   \/   |    * 
  *       /  ^  \    |  |_)  |    |   (----`|  | |  \  /  |    * 
  *      /  /_\  \   |   _  <      \   \    |  | |  |\/|  |    * 
  *     /  _____  \  |  |_)  | .----)   |   |  | |  |  |  |    * 
  *    /__/     \__\ |______/  |_______/    |__| |__|  |__|    * 
  *                                                            *
  *                                                            *
  *                Accelerated Basic Simulation                *
  *                                                            *
  **************************************************************)";

  int print_banner();

  static int dum = print_banner();


  static bool welcomed_;

  int print_banner() {
    if ( !welcomed_ ) {
        std::cout << "\033[1;31m" << welcome_message << "\033[0m\n";
    }
    welcomed_ = true;
    return 0;
  }

} // namespace ABSIM

#endif