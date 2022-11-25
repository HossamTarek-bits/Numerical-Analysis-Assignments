#include<iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <string>
#include "InputEquation.h"
using namespace std;

void diffTable (double* x, double** y, int n)
{
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			y[j][i] = (y[j + 1][i - 1] - y[j][i - 1]) / (x[j + i] - x[j]);
		}
	}
}
void displaydiffTable (double* x, double** y, int n) {
	/* Displaying Difference Table */
	cout << endl << "DIFFERENCE TABLE" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << x[i];
		for (int j = 0; j < n - i; j++)
		{
			cout << "\t" << y[i][j];
		}
		cout << endl;
	}
}
vector<double> multiYFor (int size, double* xptr, int iterate, double** y) { //returns a vector of coefficients of Xs to be added later
	vector <double> a = { 1 };
	vector <double> b;
	int n;
	int m;
	double divide = 1;
	vector <double> result;
	for (int i = 0; i < size + 1; i++) {

		result.push_back (0);
	}
	for (int k = 0; k < iterate; k++)	//nzbat iterate 7sb elcode hanb3atlo eh
	{
		b = { -xptr[k] , 1 };
		n = b.size ();
		m = a.size ();


		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				result[i + j] += a[i] * b[j];
			}
		}

		for (int l = 0; l < n + m - 1; l++)
		{
			if (l < a.size ())
			{
				a[l] = result[l];
			}
			else
			{
				a.insert (a.end (), result[l]);
			}

		}
		for (int i = 0; i < n + m - 1; i++) {

			result[i] = 0;
		}
	}
	for (int i = 0; i < a.size (); i++)
	{
		a[i] = a[i] * y[0][iterate];

	}
	for (int i = a.size (); i < size; i++)
	{
		a.push_back (0);
	}
	return a;
}
vector<double> multiYBack (int size, double* xptr, int iterate, double** y) { //returns a vector of coefficients of Xs to be added later
	vector <double> a = { 1 };
	vector <double> b;
	int sizeB;
	int sizeA;
	double divide = 1;
	vector <double> result;
	for (int i = 0; i < size + 1; i++) {

		result.push_back (0);
	}
	for (int k = size - 1; k > iterate; k--)	//nzbat iterate 7sb elcode hanb3atlo eh
	{
		b = { -xptr[k] , 1 };
		sizeB = b.size ();
		sizeA = a.size ();


		for (int i = 0; i < sizeA; i++) {
			for (int j = 0; j < sizeB; j++) {
				result[i + j] += a[i] * b[j];
			}
		}
		for (int l = 0; l < sizeB + sizeA - 1; l++)
		{
			if (l < a.size ())
			{
				a[l] = result[l];
			}
			else
			{
				a.insert (a.end (), result[l]);
			}

		}
		for (int i = 0; i < sizeB + sizeA - 1; i++) {

			result[i] = 0;
		}
	}
	for (int i = 0; i < a.size (); i++)
	{
		a[i] = a[i] * y[iterate][size - iterate - 1];

	}
	for (int i = a.size (); i < size; i++)
	{
		a.push_back (0);
	}
	return a;
}
vector<double> sumly (vector<vector<double>> YX, int size)	///coefficients of x in newton forward eq.
{
	vector<double>p;
	for (int i = 0; i < size; i++)
	{
		p.push_back (0);
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			p[i] += YX[j][i];
		}
	}
	return p;
}
void displayPx (vector<double>Px, int size, int choice)
{
	vector<string> outVals;
	string outVal;
	for (int i = size - 1; i >= 0; i--)
	{
		if (choice == 1)
		{
			if (Px[i] != 0) {
				outVal = to_string (Px[i]) + " x^" + to_string (i);
				outVals.push_back (outVal);
			}
		}
		else if (choice == 2)
		{
			if (Px[i] != 0) {
				outVal = to_string (Px[i]) + " y^" + to_string (i);
				outVals.push_back (outVal);
			}
		}
	}
	for (int i = 0; i < outVals.size (); i++) {
		cout << outVals[i];
		if (i != (outVals.size () - 1))
			cout << " + ";
	}
	cout << endl;
}

// If a value if X was given we will use the following 3 functions

double multiply (double value, double* x, int j, int iterate, int method) {
	double z = 1;
	for (; method == 1 ? j < iterate : j > iterate; method == 1 ? j++ : j--) {
		z *= value - x[j];
	}
	return z;
}

//double multFor(double value, double* x ,int j, int iterate) {
//	double z = 1;
//	for (; j < iterate; j++) {
//		z *= value - x[j];
//	}
//	return z;
//}
//
//double multBack(double value, double* x,int j, int iterate) {
//	double z = 1;
//	for (; j > iterate; j--) {
//		z *= value - x[j];
//	}
//	return z;
//}

double forwardNewton (double value, double* x, double** y, int n) {
	double sum = y[0][0];
	for (int i = 1; i < n; i++) {
		sum += y[0][i] * multiply (value, x, 0, i, 1);
	}
	return sum;
}

double backwardNewton (double value, double* x, double** y, int n) {
	double sum = y[n - 1][0];
	for (int i = n - 1; i > 0; i--) {
		sum += y[n - 1 - (i)][i] * multiply (value, x, n - 1, n - 1 - i, 2);
	}
	return sum;
}

int main ()
{
	int i, j, n, method;
	cout << "Enter number of data...:  " << endl;
	cin >> n;
	cout << "Enter data: " << endl;
	double* x = new double[n];
	double** y = new double* [n];
	string input = "";
	for (int i = 0; i < n; i++) {
		y[i] = new double[n];
	}
	double value;	// value is the value of x
	int choice;
	cout << "Find value of: 1) y    2) x \n";
	cin >> choice;
	switch (choice) {
		case 1:
			for (i = 0; i < n; i++)	//construct table of x and y
			{
				cout << "x[" << i << "] = ";
				cin >> input;
				parseEq (input);
				x[i] = evalEq (0);
				cout << "y[" << i << "] = ";
				cin >> input;
				parseEq (input);
				y[i][0] = evalEq (0);
			};

			cout << "Enter value of x...\n";
			break;
		case 2:
			for (i = 0; i < n; i++)	//construct table of x and y
			{
				cout << "y[" << i << "] = ";
				cin >> input;
				parseEq (input);
				x[i] = evalEq (0);
				cout << "x[" << i << "] = ";
				cin >> input;
				parseEq (input);
				y[i][0] = evalEq (0);
			};
			cout << "Enter value of y...\n";
			break;
	};
	cin >> input;
	parseEq (input);
	value = evalEq (0);
	for (int i = 0; i < n; i++) {
		if (value == x[i]) {
			choice == 1 ? cout << "y = " : cout << "x = ";
			cout << y[i][0];
			return 0;
		}
	}

	double a;	// a is value of forward newton equation " y" at x = value 

	// Generating Difference Table
	diffTable (x, y, n);

	// Displaying Difference Table
	displaydiffTable (x, y, n);

	int choiceMeth;
	cout << "1) choose method manually	2) choose method automatically\n";
	cin >> choiceMeth;
	if (choiceMeth == 1) {
		cout << "1) Newton Forward		2) Newton Backward\n";
		cin >> method;
		switch (method) {
			case 1:
				a = forwardNewton (value, x, y, n);
				break;
			case 2:
				a = backwardNewton (value, x, y, n);
				break;
		}
	}
	else if (choiceMeth == 2) {
		double diffFst = abs (value - x[0]);
		double diffLst = abs (value - x[n - 1]);

		if (diffFst <= diffLst) {
			method = 1;
			cout << "Using Newton's Forward\n";
			a = forwardNewton (value, x, y, n);
		}
		else if (diffFst > diffLst) {
			method = 2;
			cout << "Using Newton's Backward\n";
			a = backwardNewton (value, x, y, n);
		}
	}
	vector <vector<double>> Ys;	//two dimentional vector whose columns are the coefficients of X to a specific power and rows indicate the power
	if (method == 1) {
		for (int i = 0; i < n; i++)
		{
			Ys.push_back (multiYFor (n, x, i, y));
		}
	}

	else if (method == 2) {
		for (int i = 0; i < n; i++)
		{
			Ys.push_back (multiYBack (n, x, n - i - 1, y));
		}
	}
	vector<double> Px;
	Px = sumly (Ys, n);
	displayPx (Px, n, choice);

	cout << "The value equal  " << a;

	delete[]x;
	for (int i = 0; i < n; i++) {

		// Declare a memory block
		// of size n
		delete y[i];
	}
	delete[]y;
	return 0;
}

