#pragma once
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif // _USE_MATH_DEFINES

#ifndef cmath
#include <cmath>
#endif // !cmath

#ifndef iostream
#include <iostream>
#endif // !iostream

#ifndef string
#include <string>
#endif // !string

#ifndef math
#include <math.h>
#endif // !math

#ifndef stack
#include <stack>
#endif // !stack

#ifndef map
#include <map>
#endif // !map

#ifndef regex
#include <regex>
#endif // !regex

#ifndef vector
#include <vector>
#endif // !vector

using namespace std;
long double sum(long double a, long double b);
long double sub(long double a, long double b);
long double multply(long double a, long double b);
long double divided(long double a, long double b);
long double power(long double a, long double b);
string parseEq(string trying);
vector<string> split(string word);
vector<string> splitAndMerge(vector<string> expression, string exp, int begin, int last);
long double evalEq(long double x,long double y);
string normalizeEq(string eq);


