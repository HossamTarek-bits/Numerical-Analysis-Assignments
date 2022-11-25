#include <iostream>
#include <vector>
#include "InputEquation.h"
using namespace std;


double trapz (vector<double> arr, double h) {
	double result = arr[0] + arr.back ();
	for (int i = 1;i < arr.size () - 1;i++) {
		result += 2 * arr[i];
	}
	return result * h / 2;
}


double simpson_1_3 (vector<double> arr, double h) {
	double result = arr[0] + arr.back ();
	for (int i = 1;i < arr.size () - 1;i++) {
		if(i %2 ==0)
			result += 2 * arr[i];
		else
			result += 4 * arr[i];
	}
	return result * h / 3;
}

double simpson_3_8 (vector<double> arr, double h) {
	double result = arr[0] + arr.back ();
	for (int i = 1;i < arr.size () - 1;i++) {
		if(i %3 ==0)
			result += 2 * arr[i];
		else
			result += 3 * arr[i];
	}
	return result * 3*h / 8;
}
#pragma optimize( "", on ) 
int main()
{
	double h;
	vector<double> xs;
	vector<double> ys;
	while (true) {
		xs = {};
		ys = {};
		h = 0;
		cout<< "1) Enter the equation in the form of y = f(x) \n";
		cout << "2) Enter the number of points \n";
		cout << "Choose 1 or 2: ";
		string choice;
		cin >> choice;
		if (choice == "1") {
			cout << "Enter the number of intervals: ";
			int n;
			cin >> n;
			cout << "\nEnter the lower bound: ";
			double a;
			cin >> a;
			cout << "\nEnter the upper bound: ";
			double b;
			cin >> b;
			cout << "Enter the function: ";
			cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');
			string f;
			getline (cin, f);
			h = (b-a)/n;
			for(double i = a; i <= b; i += h) {
				xs.push_back(i);
			}
			f = normalizeEq(f);
			parseEq(f);
			for(int i = 0; i < xs.size(); i++) {
				ys.push_back(evalEq(xs[i]));
			}
		}
		else{
			do{
				cout << "enter x & y values: ";
				double x, y;
				cin >> x >> y;
				xs.push_back(x);
				ys.push_back(y);
				cout << "enter another x & y values? (y/n): ";
				cin >> choice;
			}while(choice == "y");
			h = xs[1] - xs[0];
		}
		cout << "1) Trapezoidal Rule \n";
		cout << "2) Simpson's 1/3 Rule \n";
		cout << "3) Simpson's 3/8 Rule \n";
		cout << "4) Exit \n";
		cin >> choice;
		if(choice == "1") {
			cout << "Trapezoidal Rule: " << trapz(ys, h) << endl;
		}
		else if(choice == "2") {
			if((xs.size()-1) % 2 == 0) {
				cout << "Simpson's 1/3 Rule: " << simpson_1_3(ys, h) << endl;
			}
			else {
				cout << "Interval must be even. \n";
				continue;	
			}
		}
		else if(choice == "3") {
			if((xs.size()-1) % 3 == 0) {
				cout << "Simpson's 3/8 Rule: " << simpson_3_8(ys, h) << endl;
			}
			else {
				cout << "Interval must be divisible by 3. \n";
				continue;	
			}
		}
		else if(choice == "4") {
			break;
		}
		else {
			cout << "Invalid input. Please try again. \n";
		}
		cout << "Try again? (y/n): ";
		cin >> choice;
		if(choice == "n") {
			break;
		}
	}
}
