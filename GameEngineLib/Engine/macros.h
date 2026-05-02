#ifndef MACROS_H
#define MACROS_H

#ifndef NDEBUG
#include <iostream>
#define DEBUG_CONSOLE(str) std::cout << str << std::endl;
#else
#define DEBUG_CONSOLE(str)
#endif

#endif