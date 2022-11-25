// CurveFitting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <string>
#include <iomanip>
#include <regex>
#include <map>
#include "InputEquation.h"
using namespace std;

void polyEq (vector<double> xs, vector<double> ys, int N, int n) {

	vector<double> X (2 * n + 1, 0);                        //Array that will store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
	for (int i = 0; i < 2 * n + 1; i++)
	{
		X[i] = 0;
		for (int j = 0; j < N; j++)
			X[i] = X[i] + pow (xs[j], i);        //consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
	}
	vector<vector <double>> B (n + 1, vector<double> (n + 2, 0));
	vector<double> a (n + 1, 0);            //B is the Normal matrix(augmented) that will store the equations, 'a' is for value of the final coefficients
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			B[i][j] = X[i + j];            //Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix
	vector<double> Y (n + 1, 0);                    //Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
	for (int i = 0; i < n + 1; i++)
	{
		Y[i] = 0;
		for (int j = 0; j < N; j++)
			Y[i] = Y[i] + pow (xs[j], i) * ys[j];        //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
	}
	for (int i = 0; i <= n; i++)
		B[i][n + 1] = Y[i];                //load the values of Y as the last column of B(Normal Matrix but augmented)
	n = n + 1;
	for (int i = 0; i < n; i++)                    //From now Gaussian Elimination starts(can be ignored) to solve the set of linear equations (Pivotisation)
		for (int k = i + 1; k < n; k++)
			if (B[i][i] < B[k][i])
				for (int j = 0; j <= n; j++)
				{
					double temp = B[i][j];
					B[i][j] = B[k][j];
					B[k][j] = temp;
				}
	for (int i = 0; i < n - 1; i++)            //loop to perform the gauss elimination
		for (int k = i + 1; k < n; k++)
		{
			double t = B[k][i] / B[i][i];
			for (int j = 0; j <= n; j++)
				B[k][j] = B[k][j] - t * B[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
		}
	for (int i = n - 1; i >= 0; i--)                //back-substitution
	{                        //x is an array whose values correspond to the values of x,y,z..
		a[i] = B[i][n];                //make the variable to be calculated equal to the rhs of the last equation
		for (int j = 0; j < n; j++)
			if (j != i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
				a[i] = a[i] - B[i][j] * a[j];
		a[i] = a[i] / B[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
	}
	cout << fixed << setprecision (6) << "\nThe values of the coefficients are as follows:\n";
	for (int i = 0; i < n; i++)
		cout << "x^" << i << "=" << a[i] << endl;            // Print the values of x^0,x^1,x^2,x^3,....    
	cout << fixed << setprecision (6) << "\nHence the fitted Polynomial is given by:\ny=";
	for (int i = 0; i < n; i++)
		cout << fixed << setprecision (6) << " + (" << a[i] << ")" << "x^" << i;
	cout << "\n";

}


void expoEq (string eq, vector<double>& xs, vector<double>& ys, int N) {

	regex re ("([a-z]{0,})e\\^\\(*([a-z]{1,})\\)*(\\+[0-9].[0-9]{1,}|\\-[0-9].[0-9]{1,}|\\+[0-9]{1,}|\\-[0-9]{1,})*");
	smatch match;
	regex_search (eq, match, re);
	if (match.str (2).find ("y") != string::npos) {
		for (int i = 0; i < ys.size (); i++) {
			xs[i] = xs[i] * ys[i];
		}
	}

	double constant = 0;
	if (match.str (3) != "") {
		string tmp = match.str (3);
		tmp = tmp.substr (1, tmp.size ());
		constant += match.str (3).substr (0, 1) == "-" ? stod (tmp) : (0 - stod (tmp));
	}
	for (int i = 0; i < ys.size (); i++) {
		ys[i] = ys[i] + constant;
	}
	vector<double> lny (N, 0);
	for (int i = 0; i < N; i++)                        //Calculate the values of ln(yi)
		lny[i] = log (ys[i]);
	double xsum = 0, x2sum = 0, ysum = 0, xysum = 0;                //variables for sums/sigma of xi,yi,xi^2,xiyi etc
	for (int i = 0; i < N; i++)
	{
		xsum = xsum + xs[i];                        //calculate sigma(xi)
		ysum = ysum + lny[i];                        //calculate sigma(yi)
		x2sum = x2sum + pow (xs[i], 2);                //calculate sigma(x^2i)
		xysum = xysum + xs[i] * lny[i];                    //calculate sigma(xi*yi)
	}
	double a = (N * xysum - xsum * ysum) / (N * x2sum - xsum * xsum);            //calculate slope(or the the power of exp)
	double b = (x2sum * ysum - xsum * xysum) / (x2sum * N - xsum * xsum);            //calculate intercept
	double c = exp (b);                        //since b=ln(c)
	vector<double> y_fit (N + 1, 0);                        //an array to store the new fitted values of y    
	for (int i = 0; i < N; i++)
		y_fit[i] = c * exp (a * xs[i]);                    //to calculate y(fitted) at given x points
	//cout << "S.no" << setw(5) << "x" << setw(19) << "y(observed)" << setw(19) << "y(fitted)" << endl;
	//cout << "-----------------------------------------------------------------\n";
	//for (int i = 0; i < N; i++)
	//    cout << fixed << setprecision(6)<< i + 1 << "." << setw(8) << xs[i] << setw(15) << ys[i] << setw(18) << y_fit[i] << endl;//print a table of x,y(obs.) and y(fit.)    
	//cout << "\nThe corresponding line is of the form:\n\nlny = " << a << "x + ln" << b << endl;
	cout << "\nThe exponential fit is given by:\ny = " << c << "e^" << a << "x" << match.str (3);

}

void powEq (string eq, vector<double>xs, vector<double>ys, int N) {
	regex re ("(\\+[0-9]{1,}|\\-[0-9]{1,})");
	smatch match;
	regex_search (eq, match, re);
	double constant = 0;
	if (match.str (1) != "") {
		string tmp = match.str (1);
		tmp = tmp.substr (1, tmp.size ());
		constant += match.str (1).substr (0, 1) != "-" ? stod (tmp) : (0 - stod (tmp));
	}
	for (int i = 0; i < xs.size (); i++) {
		xs[i] = xs[i] + constant;
	}
	double sumX = 0, sumX2 = 0, sumY = 0, sumXY = 0, a, b, A;
	for (int i = 1; i <= N; i++)
	{
		sumX = sumX + log (xs[i]);
		sumX2 = sumX2 + log (xs[i]) * log (xs[i]);
		sumY = sumY + log (ys[i]);
		sumXY = sumXY + log (xs[i]) * log (ys[i]);
	}

	/* Calculating A and b */
	b = (N * sumXY - sumX * sumY) / (N * sumX2 - sumX * sumX);
	A = (sumY - b * sumX) / N;

	/* Transformation of A to a */
	a = exp (A);

	/* Displaying value of a and b */

	cout << fixed << setprecision (6) << "Values are: a = " << a << " and b = " << b;

	cout << " the equation is y = " << a << "(x" << match.str (1) << ")^" << b;
}
int main ()
{
	cout.fixed;
	cout.precision (6);
	int i, j, k, n, N, choice;
	cout << "enter choice " << endl;
	cout << "1) polynomial   2) power    3) exponential" << endl;
	cin >> choice;
	string eq;
	cout << "enter equation ";
	cin >> eq;

	cout << "enter number of points ";
	cin >> N;
	vector<double> xs;
	vector<double> ys;
	string x, y;


	for (int i = 0; i < N; i++) {
		cout << "enter values of x ";
		cin >> x;
		parseEq (x);
		xs.push_back (evalEq (0));
		cout << "enter values of y ";
		cin >> y;
		parseEq (y);
		ys.push_back (evalEq (0));
	}
	if (choice == 1)
	{
		cout << "\nWhat degree of Polynomial do you want to use for the fit?\n ";
		cin >> n;
		polyEq (xs, ys, N, n);
	}

	else if (choice == 2)
		powEq (eq, xs, ys, N - 1);

	else if (choice == 3)
		expoEq (eq, xs, ys, N);

}
