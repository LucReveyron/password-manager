#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

// Platform-specific includes
#ifdef _WIN32
#include <windows.h>
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#include <termios.h>
#include <unistd.h>
#else
#error "Unsupported platform"
#endif

void disableEcho();
void restoreEcho();

#endif // UTILS_HPP