#ifndef _LOCAL_H_
#define _LOCAL_H_

#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <climits>
#include <cmath>
#include <cstring>
#include <ctime>
 
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
 
#if __cplusplus >= 201103L
#include <array>
#include <chrono>
#include <random>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#endif

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

void __print_single(int x) { std::cerr << x; }
void __print_single(long long x) { std::cerr << x; }
void __print_single(unsigned x) { std::cerr << x; }
void __print_single(unsigned long long x) { std::cerr << x; }
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

void __print_out() { std::cerr << RESET << std::endl; }

template <class T, class... V>
void __print_out(T t, V... v) {
    __print_single(t);
    if (sizeof...(v)) std::cerr << ", ";
    __print_out(v...);
}

int __db_level = 0;
constexpr int __indent_level = 3;

#define debug(...) \
    { \
        std::cerr << std::string(__db_level * __indent_level, ' '); \
        if (!__db_level) std::cerr << RED << ARROW; \
        std::cerr << BLUE << "[" << #__VA_ARGS__ << "]: " << YELLOW; \
        __print_out(__VA_ARGS__); \
    }

struct debugBlock {
    debugBlock() {
        std::cerr << std::string(__db_level++ * __indent_level, ' ') << "{" << std::endl;
    }
    ~debugBlock() {
        std::cerr << std::string(--__db_level * __indent_level, ' ') << "}" << std::endl;
    }
};

#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#define DB(...) debugBlock CONCAT(__dbbl, __LINE__)

#if MTC
#warning MTC
#endif

#endif // _LOCAL_H_
