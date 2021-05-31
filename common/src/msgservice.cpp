#include "msgservice.h"

MSGSERVICE::detail::NullBuffer MSGSERVICE::detail::null_buffer;

std::ostream MSGSERVICE::null_stream(&MSGSERVICE::detail::null_buffer);