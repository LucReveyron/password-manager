/**
 * @file   utils.cpp
 * @brief  Implementation of utility functions for handling console input echoing.
 * 
 * This file contains the implementation of functions to disable and restore echoing of user input on the console.
 * 
 * @author Luc Reveyron
 * @date   14/03/2024
 */

#include "../include/utils.hpp"

// Function to turn off echoing
void disableEcho() {
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif
}

// Function to restore echoing
void restoreEcho() {
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode);
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}