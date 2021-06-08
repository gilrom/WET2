#ifndef WET1_EXCEPTIONS
#define WET1_EXCEPTIONS

#include <exception>

namespace wet2
{
    class Exception : public std::exception {};
    class EmptyTree : public Exception {};
    class NotFound : public Exception {};
    class NotExist : public Exception {};
}
#endif