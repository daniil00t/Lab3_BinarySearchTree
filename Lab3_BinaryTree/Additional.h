#pragma once
#include <complex>
#include <string>

using namespace std;


template<typename _Tp>
inline constexpr bool
operator<(const complex<_Tp>& __x, const complex<_Tp>& __y) {
    if (pow(__x.real(), 2) + pow(__x.imag(), 2) < pow(__y.real(), 2) + pow(__y.imag(), 2)) {
        return true;
    }
    else {
        return false;
    }
}

template<typename _Tp>
inline constexpr bool
operator>(const complex<_Tp>& __x, const complex<_Tp>& __y) {
    if (pow(__x.real(), 2) + pow(__x.imag(), 2) > pow(__y.real(), 2) + pow(__y.imag(), 2)) {
        return true;
    }
    else {
        return false;
    }
}

inline bool
operator>(string a, string b) {
    return a.size() > b.size();
}
inline bool
operator<(string a, string b) {
    return a.size() < b.size();
}


inline string
to_string(complex<double> __val)
{
    string str;
    str = str + to_string(__val.real()) + " " + to_string(__val.imag());
    return str;
}

inline string
to_string(string __val)
{
    return __val;
}
