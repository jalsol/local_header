/*
 * Header file including functions used for debugging
 */

#ifndef _DEBUGGER_H
#define _DEBUGGER_H

#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <tuple>

/*
 * Defining functions to print single variables (POD, containers, etc)
 */

// plain-old-data-types
void __print_single(int x);
void __print_single(long long x);
void __print_single(unsigned x);
void __print_single(unsigned long long x);
void __print_single(size_t x);
void __print_single(float x);
void __print_single(double x);
void __print_single(long double x);
void __print_single(char x);
void __print_single(const char* x);
void __print_single(char* x);
void __print_single(bool x);

// STL containers
void __print_single(const std::string& x);
void __print_single(const std::vector<bool>& v);

template <size_t N>
void __print_single(const std::bitset<N>& v) {
    for (size_t i = 0; i < N; ++i) {
        std::cerr << v[i];
    }
}

template <class T, class V>
void __print_single(const std::pair<T, V>& x) {
    std::cerr << '('; __print_single(x.first);
    std::cerr << ", "; __print_single(x.second);
    std::cerr << ')';
}

template <class A, class B, class C, class D>
void __print_single(const std::tuple<A, B, C, D>& p) {
    std::cerr << '(';
    __print_single(std::get<0>(p)); std::cerr << ", ";
    __print_single(std::get<1>(p)); std::cerr << ", ";
    __print_single(std::get<2>(p)); std::cerr << ", ";
    __print_single(std::get<3>(p)); std::cerr << ')';
}

template <class A, class B, class C>
void __print_single(const std::tuple<A, B, C>& p) {
    std::cerr << '(';
    __print_single(std::get<0>(p)); std::cerr << ", ";
    __print_single(std::get<1>(p)); std::cerr << ", ";
    __print_single(std::get<2>(p)); std::cerr << ')';
}

// NOTE: abusing SFINAE, might change to C++20's standard
template <class T>
void __print_single(const T& x) {
    int f = 0;
    std::cerr << "{";
    for (const auto& i : x) {
        std::cerr << (f++ ? ", " : "");
        __print_single(i);
    }
    std::cerr << "}";
}

/*
 * Defining the output function
 */
void __print_out();

template <class T, class... V>
void __print_out(T t, V... v) {
    __print_single(t);
    if (sizeof...(v)) std::cerr << ", ";
    __print_out(v...);
}

/*
 * Debug Block
 * More info: https://quangloc99.github.io/2021/07/30/my-CP-debugging-template.html
 */

// extern int debug_level;
extern const int __indent_level;

int __level_inc();
int __level_dec();
int __level_cur();

struct DebugBlock {
    DebugBlock();
    ~DebugBlock();
};


/*
 * Macros that help with debugging
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

#define debug(...) \
    { \
        std::cerr << std::string(__level_cur() * __indent_level, ' '); \
        if (!__level_cur()) std::cerr << RED << ARROW; \
        std::cerr << BLUE << "[" << #__VA_ARGS__ << "]: " << YELLOW; \
        __print_out(__VA_ARGS__); \
    }

#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#define DB(...) DebugBlock CONCAT(__dbbl, __LINE__)

#endif // _DEBUGGER_H
