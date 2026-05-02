#ifndef MACROS_H
#define MACROS_H

#ifndef NDEBUG
#include <iostream>
#define DEBUG_CONSOLE(category, str) std::cout << "[" << category << "]: " << str << std::endl;
#else
#define DEBUG_CONSOLE(category, str)
#endif

#endif