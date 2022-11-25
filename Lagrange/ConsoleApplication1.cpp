// function lagange.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <string>
#include "InputEquation.h"
using namespace std;


vector<double> multiL (int size, double* xptr, int ietrate)
{
	vector <double> a = { 1 };
	vector <double> b;
	int n;
	int m;
	double divide = 1;
	vector <double> result;
	for (int i = 0; i < size + 1; i++) {

		result.push_back (0);
	}
	for (int k = 0; k < size; k++)
	{
		if (k != ietrate)
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
			divide *= xptr[ietrate] - xptr[k];

		}
	}
	for (int i = 0; i < a.size (); ++i)
	{
		a[i] = a[i] / divide;		//L

	}

	return a;
}
vector<double> multibyy (vector<double> L, double y)
{

	for (int i = 0; i < L.size (); i++)
	{
		L[i] *= y;
	}
	return L;
}
vector<double> sumly (vector<vector<double>> LY, int size)
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
			p[i] += LY[j][i];
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
				(i == 0) ? outVal = to_string (Px[i]) : outVal = to_string (Px[i]) + " x^" + to_string (i);
				outVals.push_back (outVal);
			}
		}
		if (choice == 2)
		{
			if (Px[i] != 0) {
				(i == 0) ? outVal = to_string (Px[i]) : outVal = to_string (Px[i]) + " y^" + to_string (i);
				outVals.push_back (outVal);
			}
		}
	}
	for (int i = 0; i < outVals.size (); i++) {
		cout << outVals[i];
		if (i != (outVals.size () - 1))
			cout << " + ";
	}
	if (outVals.empty ())
		cout << "0";
	cout << endl;
}
void displayvalue (vector<double>Px, int size, int choice, double x)
{
	double y = 0;

	for (int i = size - 1; i >= 0; i--)
	{
		y += Px[i] * pow (x, i);
	}
	choice == 1 ? cout << " Y at x = " : cout << " X at y = ";
	cout << x << " is " << y << endl;
}

int main ()
{
	int size;
	cout << "enter the number of points:  ";
	cin >> size;
	double* xptr = new double[size];
	double* yptr = new double[size];
	vector <vector<double>> L;
	vector <vector<double>> LY;

	/*for (int i = 0; i < size; i++)
	{
		cout << "enter x " << i << endl;
		cin >> *(xptr + i);
		cout << "enter y " << i << endl;
		cin >> *(yptr + i);
	}*/

	int choice;
	do
	{
		cout << "Find value of: 1) y    2) x \n";
		cin >> choice;
	} while (choice != 1 && choice != 2);
	string inputValue;
	if (choice == 1) {
		for (int i = 0; i < size; i++)
		{
			cout << "enter x " << i << endl;
			cin >> inputValue;
			parseEq (inputValue);
			*(xptr + i) = evalEq (0);
			cout << "enter y " << i << endl;
			cin >> inputValue;
			parseEq (inputValue);
			*(yptr + i) = evalEq (0);
		}
	}

	if (choice == 2) {
		for (int i = 0; i < size; i++)
		{
			cout << "enter x " << i << endl;
			cin >> inputValue;
			parseEq (inputValue);
			*(yptr + i) = evalEq (0);
			cout << "enter y " << i << endl;
			cin >> inputValue;
			parseEq (inputValue);
			*(xptr + i) = evalEq (0);
		}
	}

	for (int i = 0; i < size; i++)
	{
		L.push_back (multiL (size, xptr, i));		//i is the number of L
	}

	for (int i = 0; i < size; i++)
	{
		LY.push_back (multibyy (L[i], yptr[i]));
	}
	vector<double>Px;
	Px = sumly (LY, size);

	double x;
	choice == 1 ? cout << "Enter the value of x " : cout << "Enter the value of y ";
	cout << endl;
	cin >> x;
	int flag = 0;
	for (int i = 0; i < size; i++) {
		if (x == xptr[i]) {
			choice == 1 ? cout << "y = " : cout << "x = ";
			cout << yptr[i] << "  ";

			cout << "*FOUND IN TABLE*" << endl;
			flag = 1;
		}
	}
	if (flag == 0)
	{
		displayvalue (Px, size, choice, x);

		cout << "Equation is :  ";
		displayPx (Px, size, choice);
	}
	delete[] xptr;
	delete[]yptr;

}