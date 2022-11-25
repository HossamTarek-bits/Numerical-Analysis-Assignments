// test0000.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<iomanip>
#include "InputEquation.h" 
#include<string>
using namespace std;
double fneq(double xn, double yn)
{
    return evalEq(xn, yn);
}
double eulereq(double h, double yn, double fn)
{
    return yn + h * fn;
}
double eulerEqMod(double h, double yn, double fn,double fne)
{
    return yn +(h/2)*(fn+fne);
}

int main()
{
    double y0,h,x0,xn;
    vector<double>ye;
    vector<double>ydashe;
    vector<double> x;
    vector<double> y;
    vector<double> ydash;
    string eq;
    int choiceXY;
    char choice;
    cout << "enter equation " << endl;
    cin >> eq;
    eq = normalizeEq(eq);
    parseEq(eq);
    cout << "Find value of  1) x   2) y   : ";
    cin>>choiceXY;
    cout << "enter x0: ";
    cin >> x0;
    cout << "enter y0: ";
    cin >> y0;
    cout << "enter h: ";
    cin >> h;
    choiceXY==2?cout << "Find value of y at x = ": cout << "Find value of x at y = ";
    cin >> xn;
    int i = 0;
    choiceXY==2?x.push_back(x0): y.push_back(x0);
    choiceXY==2?y.push_back(y0): x.push_back(y0);
    cout << "euler or modifed euler? e or m: ";
    cin >> choice;
    while (x[i] <= xn)
    {    
        ydash.push_back(choiceXY==2?fneq(x[i], y[i]):1/(fneq(x[i], y[i])));
       
        i++;
        x.push_back(x[i - 1] + h);
        if (choice == 'e') {
            y.push_back(eulereq(h, y[i - 1], ydash[i - 1]));
            choiceXY == 2 ? cout << "x" << i - 1 << "  " << setw(8) << x[i - 1]
                << setw(8) << "y" << i - 1 << "  " << setw(8) << y[i - 1]
                << setw(8) << "ydash" << i - 1 << "  " << setw(8) << ydash[i - 1]
               <<endl :
                cout << "x" << i - 1 << "  " << setw(8) << y[i - 1]
                << setw(8) << "y" << i - 1 << "  " << setw(8) << x[i - 1]
                << setw(8) << "xdash" << i - 1 << "  " << setw(8) << ydash[i - 1]
                 << endl;
        }
        else if (choice == 'm')
        {
            
            ye.push_back(eulereq(h, y[i - 1], ydash[i - 1]));
            ydashe.push_back(choiceXY == 2 ? fneq(x[i],ye[i-1]):1/( fneq(x[i], ye[i - 1])));
            y.push_back(eulerEqMod( h,  y[i-1], ydash[i-1], ydashe[i-1]));
            choiceXY == 2 ? cout << "x" << i - 1 << "  " << setw(8) << x[i - 1]
                << setw(8) << "y" << i - 1 << "  " << setw(8) << y[i - 1]
                << setw(8) << "ydash" << i - 1 << "  " << setw(8) << ydash[i - 1]
                << setw(8) << "ye" << i - 1 << "  " << setw(8) << ye[i - 1]
                << setw(8) << "ydashe" << i - 1 << "  " << setw(8) << ydashe[i - 1] << endl :
                cout << "x" << i - 1 << "  " << setw(8) << y[i - 1]
                << setw(8) << "y" << i - 1 << "  " << setw(8) << x[i - 1]
                << setw(8) << "xdash" << i - 1 << "  " << setw(8) << ydash[i - 1]
                << setw(8) << "xe" << i - 1 << "  " << setw(8) << ye[i - 1]
                << setw(8) << "xdashe" << i - 1 << "  " << setw(8) << ydashe[i - 1] << endl;
        }
        
    }
    cout << y[y.size()-2];


}

