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

#ifndef InputEquation
#include "InputEquation.h"
#endif // !InputEquation

using namespace std;

/*
* Update a & b with the interval
* interval -9 -> 0 if negtaiveRoot
* interval 0 -> 9 if !negativeRoot
*/
void getInterval (long double* a, long double* b, bool negativeRoot) {

    int x = negativeRoot ? -9 : 0;
    while (isnan (evalEq (x))) {
        x++;
    }

    for (; evalEq (x) * evalEq (x + 1) > 0 && (negativeRoot ? x <= 0 : x <= 9); x++);
    *a = x;
    *b = x + 1;
}
/*
* execute Bisection Method till reach required Accuracy
*/
long double bisectionMethod (long double a, long double b, long double acc) {
    if (abs (a - b) < acc)
        return a;
    long double c = (a + b) / 2;
    if (evalEq (a) * evalEq (c) <= 0)
        b = c;
    else
        a = c;
    bisectionMethod (a, b, acc);
}


/*
Xn+1 = Xn - (f(Xn) / f'(Xn) )
f'(Xn) = Slope
Xn-1 = a
Xn   = b

*/

long double secantEq (long double a, long double b) {
    return b - (evalEq (b) * (b - a)) / (evalEq (b) - evalEq (a));
}


/*
* execute Secant Method till reach required Accuracy
*/
long double secantMethod (long double a, long double b, long double acc) {
    long double c = secantEq (a, b);
    if (abs (c - b) < acc)
        return c;
    a = b;
    b = c;
    secantMethod (a, b, acc);
}


int main ()
{
    string again;
    do {
        cout << "\nEnter equation Dr. Moanis\n";
        string x;                                 // x is the input Eq.
        getline (cin, x);
        x = normalizeEq (x);                      // handle spaces in string Eq. 
        parseEq (x);                              // handle  Order of Operations
        long double acc;
        do {
            cout << "\nEnter The Accuracy ";cin >> acc;cout << endl;
            if (acc < 0.0000000001) acc = 0.0000000001;
        } while (acc >= 1);
        long double a = 0;
        long double b = 0;
        long double root = 0;
        char choice;
        bool negativeRoot;

        do {
            cout << "1) Positive Root\n2) Negative Root\n"; cin >> choice;
            cout << "Choice: " << choice << endl;
        } while (choice != '1' && choice != '2');

        if (choice == '1') negativeRoot = false;
        else negativeRoot = true;
        getInterval (&a, &b, negativeRoot);
        if (evalEq (a) == 0) {
            cout << "Root is " << a << endl;
            continue;
        }
        else if (evalEq (b) == 0) {
            cout << "Root is " << b << endl;
            continue;
        }

        if (evalEq (a) * evalEq (b) > 0)
        {
            cout << "Root is not found within the interval\n";
            return 0;
        }
        else {
            cout << "Root found at interval ( " << a << " , " << b << " )" << endl;
        }

        do {
            cout << "Choose The Method\n1) Bisection Method\n2) Secant Method\n"; cin >> choice;
        } while (choice != '1' && choice != '2');

        if (choice == '1') root = bisectionMethod (a, b, acc);
        else if (choice == '2') root = secantMethod (a, b, acc);
        cout << "Your root is " << root << endl;
        do
        {
            cout << "Do you want to try again? ( y \\ n ) ";cin >> again;
        } while (again != "y" && again != "n");
        cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');   //clear cin to reuse program 


    } while (again == "y");
}