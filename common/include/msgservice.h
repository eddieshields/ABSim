#ifndef ABSIM_MSGSERVICE_H
#define ABSIM_MSGSERVICE_H

#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>

namespace MSGSERVICE {

  #define RESET   "\033[0m"
  #define BLACK   "\033[30m"      /* Black */
  #define RED     "\033[31m"      /* Red */
  #define GREEN   "\033[32m"      /* Green */
  #define YELLOW  "\033[33m"      /* Yellow */
  #define BLUE    "\033[34m"      /* Blue */
  #define MAGENTA "\033[35m"      /* Magenta */
  #define CYAN    "\033[36m"      /* Cyan */
  #define WHITE   "\033[37m"      /* White */
  #define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
  #define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
  #define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
  #define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
  #define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
  #define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
  #define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
  #define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
  
  #define FCNNAMELENGTH 45

  namespace detail {

    inline std::string trimmedString( std::string thing, const unsigned int& length = FCNNAMELENGTH )
    {
      size_t pos2=0;
      do {
      pos2                            = thing.find( "ABSIM::" );
      if ( pos2 != std::string::npos ) thing = thing.replace( pos2, 7, "" );
      } while( pos2 != std::string::npos );
    
      pos2                                   = thing.find( "std::" );
      if ( pos2 != std::string::npos ) thing.replace( pos2, 5, "" );
    
      pos2                                   = thing.find( "virtual " );
      if ( pos2 != std::string::npos ) thing = thing.replace( pos2, 8, "" );
    
      size_t pos = thing.find( "(" );
    
      if ( pos != std::string::npos ) {
        return pos < length ? thing.substr( 0, pos ) : thing.substr( 0, length );
      }
      return thing.size() < length ? thing : thing.substr( 0, length ) + "...";
    }
    
    inline std::string trimmedFile(std::string thing, const unsigned int& length = FCNNAMELENGTH)
    {
      size_t pos = 0;
      pos = thing.find("absim");
      if ( pos != std::string::npos ) thing = thing.replace(0,pos+6,"");
      return thing;
    }

    class NullBuffer : public std::streambuf
    {
    public:
      int overflow(int c) { return c; }
    };
    extern NullBuffer null_buffer;
    
  } // namespace detail

  extern std::ostream null_stream;

} // namespace MSGSERVICE

#if defined (Debug) || (RelWithDebInfo)
  #define debug_stream std::cout
  #define prefix "[" << MSGSERVICE::detail::trimmedFile( __FILE__ ) << ", L" << __LINE__ << "] "                   \
    << std::left << std::setw( FCNNAMELENGTH ) << MSGSERVICE::detail::trimmedString( __PRETTY_FUNCTION__ ) << "  "
#else
  #define debug_stream MSGSERVICE::null_stream
  #define prefix ""
#endif

#define info()                        \
  std::cout << "\033[2;34m" << prefix \
  << "INFO         "                  \
  << "\033[0m"


#define debug()                          \
  debug_stream << "\033[2;32m" << prefix \
  << "DEBUG        "                     \
  << "\033[0m"


#define warning()                     \
  std::cout << "\033[1;35m" << prefix \
  << "WARNING      "                  \
  << "\033[0m" 

#define error()                       \
  std::cout << "\033[1;31m" << prefix \
  << "ERROR        "                  \
  << "\033[0m"

#define fatal()                       \
  std::cout << "\033[1;31m" << prefix \
  << "  FATAL        "                \
  << "\033[0m"

#define endmsg "\n"

#define leave "\n"

//throw std::runtime_error( trimmedString( __PRETTY_FUNCTION__)+ " FATAL" )

#endif