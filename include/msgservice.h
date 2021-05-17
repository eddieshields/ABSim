#ifndef ABSIM_MSGSERVICE_H
#define ABSIM_MSGSERVICE_H

#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>

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


inline std::string trimmedString( std::string thing, const unsigned int& length = FCNNAMELENGTH )
{
  size_t pos2=0;
  do {
  pos2                            = thing.find( "ABSIM::" );
  if ( pos2 != std::string::npos ) thing = thing.replace( pos2, 13, "" );
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

  /// @ingroup msgService macro DEBUG
/// Used for printing verbose debugging messages, only if DEBUGLEVEL is defined.  
#ifdef DEBUGLEVEL
#define DEBUG( X )                                                                                                     \
  std::cout << "\033[2;32m" << std::left << std::setw( FCNNAMELENGTH ) << trimmedString( __PRETTY_FUNCTION__ )         \
<< "  DEBUG        "                                                                                       \
<< "\033[0m" << X << std::endl
#else
#define DEBUG( X )
#endif

/// @ingroup msgService macro INFO
/// Used for printing information messages, and will always be printed. 
#define INFO( X )                                                                                                      \
  std::cout << "\033[2;34m" << std::left << std::setw( FCNNAMELENGTH ) << trimmedString( __PRETTY_FUNCTION__ )         \
<< "  INFO         "                                                                                       \
<< "\033[0m" << X << std::endl

/// @ingroup msgService macro INFO
/// Used for printing plain messages, and will always be printed. 
#define PRINT( X )                          \
  std::cout << std::left << X << std::endl;

/// @ingroup msgService macro ERROR
/// Used for printing errors messages, and will always be printed. 
#define ERROR( X )                                                                                                     \
  std::cout << "\033[1;31m" << std::left << std::setw( FCNNAMELENGTH ) << trimmedString( __PRETTY_FUNCTION__ )         \
<< "  ERROR        "                                                                                                   \
<< "\033[0m" << X << std::endl

/// @ingroup msgService macro FATAL
/// Used for printing fatal errors messages, and will always be printed and will terminate the process afterwards.
#define FATAL( X )                                                                                                     \
  { std::cout << "\033[1;31m" << std::left << std::setw( FCNNAMELENGTH ) << trimmedString( __PRETTY_FUNCTION__ )         \
<< "  FATAL        "                                                                                                   \
<< "\033[0m" << X << std::endl;                                                                                         \
throw std::runtime_error( trimmedString( __PRETTY_FUNCTION__)+ " FATAL" ) ;}


/// @ingroup msgService macro FATAL
/// Used for printing warning messages, can be switched off using WARNINGLEVEL. These messages are often harmless, but sometimes not!
#ifdef WARNINGLEVEL
#define WARNING( X )                                                                                                   \
  std::cout << "\033[1;35m" << std::left << std::setw( FCNNAMELENGTH ) << trimmedString( __PRETTY_FUNCTION__ )         \
<< "  WARNING      "                                                                                       \
<< "\033[0m" << X << std::endl
#else
#define WARNING( X )
#endif

#ifdef TRACELEVEL
#define TRACE( X )                                                                                                     \
  std::cout << "\033[1;36m" << std::left << std::setw( FCNNAMELENGTH ) << trimmedString( __PRETTY_FUNCTION__ )         \
<< "  TRACE        "                                                                                       \
<< "\033[0m" << X << std::endl
#else
#define TRACE( X )
#endif


#endif