#ifndef ABSIM_CLOCK_H
#define ABSIM_CLOCK_H

#include "msgservice.h"
#include "types.h"

#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>

using clock_r = std::chrono::time_point<std::chrono::high_resolution_clock>;

namespace ABSIM {

  /**
   * @class Clock
   * 
   * @brief Class to perform timings of task.
   * 
   * @details 
   * 
   * @author Edward Shields
   * @date 30/06/2021
   */
  class Clock
  {
  private:
    static std::clock_t c_start;   
    static std::clock_t c_end;
    static clock_r      t_start;
    static clock_r      t_end;
  
  public:
    /**
     * Start the clock.
     */
    static void Start();

    /**
     * Stop the clock.
     */
    static void Stop();

    /**
     * Print the recorded time.
     * 
     * @param task Task that was timed.
     */
    static void Print(std::string task);
  };

  #define CLOCK_START Clock::Start()

  #define CLOCK_STOP Clock::Stop()

  #define CLOCK_TASK( X ) Clock::Print( X );

} // namespace ABSIM



#endif