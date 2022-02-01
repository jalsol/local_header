/*
 * Implementation of functions/classes defined in debugger.h
 */

#include "debugger.h"

#include <iostream>
#include <string>

/*
 * Implementing functions to print single variables (POD, containers, etc)
 */

void __print_single(int x) { std::cerr << x; }
void __print_single(long long x) { std::cerr << x; }
void __print_single(unsigned x) { std::cerr << x; }
void __print_single(unsigned long long x) { std::cerr << x; }
void __print_single(size_t x) { std::cerr << x; }
void __print_single(float x) { std::cerr << x; }
void __print_single(double x) { std::cerr << x; }
void __print_single(long double x) { std::cerr << x; }
void __print_single(char x) { std::cerr << '\'' << x << '\''; }
void __print_single(const std::string& x) { std::cerr << '\"' << x << '\"'; }
void __print_single(const char* x) { std::cerr << '\"' << x << '\"'; }
void __print_single(char* x) { std::cerr << '\"' << x << '\"'; }
void __print_single(bool x) { std::cerr << (x ? "true" : "false"); }

void __print_single(const std::vector<bool>& v) {
    bool first = true;
    std::cerr << "{";
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        if (!first) std::cerr << ", ";
        first = false;
        __print_single(v[i]);
    }
    std::cerr << "}";
}

/*
 * Implementing the output function
 */

#ifndef NOCOLOR
#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[36m"
#define ARROW ">>> "
#else
#define RESET ""
#define RED ""
#define YELLOW ""
#define BLUE ""
#define ARROW ""
#endif // NOCOLOR

void __print_out() { std::cerr << RESET << std::endl; }

/*
 * Implementing Debug Block
 */

int debug_level = 0;
const int __indent_level = 4;

int __level_inc() { return debug_level++; }
int __level_dec() { return --debug_level; }
int __level_cur() { return debug_level; }

DebugBlock::DebugBlock() {
    std::cerr << std::string(__level_inc() * __indent_level, ' ') << "{" << std::endl;
}

DebugBlock::~DebugBlock() {
    std::cerr << std::string(__level_dec() * __indent_level, ' ') << "}" << std::endl;
}
