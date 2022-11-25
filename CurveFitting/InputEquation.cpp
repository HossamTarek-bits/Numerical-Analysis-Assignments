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

#include "InputEquation.h"

//Mapping the Operators to precedence 
map<string, int> operators = { {"-",1},{"+",1},{"*",2},{"/",2},{"^",3} };

//Mapping name of functions to a pointer of functions
map<string, long double (*) (long double)> functionMap = { {"sin",sin}, {"cos",cos}, {"tan",tan},{"log",log10},{"ln",log} };

//Mapping name of opperators to a pointer of functions
map<string, long double (*) (long double, long double)> operatorsMap = { {"+",sum},{"-",sub},{"*",multply}, {"/",divided},{"^",power} };

//Maping constants to thier values
map<string, long double> constants = { {"e",M_E},{"pi",M_PI},{"x",0},{"-x",0} };



string eq;



using namespace std;

long double sum (long double a, long double b) {
	return a + b;
}
long double sub (long double a, long double b) {
	return a - b;
}
long double multply (long double a, long double b) {
	return a * b;
}
long double divided (long double a, long double b) {
	return a / b;
}
long double power (long double a, long double b) {
	return pow (a, b);
}

/*
Parseing The Input Eq According to Shunting-yard Algorithm
*/

string parseEq (string inputEquation) {
	inputEquation = normalizeEq (inputEquation);
	stack<string> operatorStack;
	string expression;                                          //Output in RPN
	string current;                                             //temp variable hold string of digit or function before adding to The expression 
	for (int i = 0; i < inputEquation.length (); i++)
	{
		if (string (1, inputEquation[i]) != " ") {

			/*if inputEquation[i] is parenthesis*/
			if (string (1, inputEquation[i]) == "(") {
				// if current is function (sin,cos,..) push it to operator stack
				if (!current.empty ()) {
					operatorStack.push (current);
					current = "";
				}
				operatorStack.push (string (1, inputEquation[i]));     // Pushing "(" to The Operatoe Stack 
			}
			else if (string (1, inputEquation[i]) == ")") {
				while (operatorStack.top () != "(") {           //Poping The Operator Stack till we Find The "(" 
					expression = expression + " " + operatorStack.top ();
					operatorStack.pop ();
				}
				operatorStack.pop ();                           //Pop "(" 

				/* If there is function or operator at the top of the operator stack add it to expression */
				if (!operatorStack.empty () && functionMap.find (operatorStack.top ()) != functionMap.end ()) {
					expression = expression + " " + operatorStack.top ();
					operatorStack.pop ();
				}
			}

			/*if inputEquation[i] is a digit*/
			else if (isdigit (inputEquation[i]) || inputEquation[i] == '.') {

				//Add digit or "." to current 
				current = current + inputEquation[i];
			}

			/*if trying[i] is a letter*/
			else if (tolower (inputEquation[i]) >= 'a' && tolower (inputEquation[i]) <= 'z')  // Check if inputEquation[i] is char -could be a function- & tolower : force all char. to be lower cases
			{
				if (tolower (inputEquation[i]) == 'x') {               // Check if the current char is x 
					expression = expression + " x";
				}
				else {
					current += inputEquation[i];
				}
			}

			/*if inputEquation[i] is an operator*/
			else if (operatorStack.empty () || operatorStack.top () == "(")
			{
				if ((inputEquation[i + 1] != ' ') && (string (1, inputEquation[i]) == "-")) //if equation begins with negative
				{
					current += string (1, inputEquation[i]) + string (1, inputEquation[i + 1]);
					i++;
				}
				else //adding first operator to stack
				{
					operatorStack.push (string (1, inputEquation[i]));
				}
			}
			else if (!operatorStack.empty () && operatorStack.top () == "(") //to add the operator after the "(" to operator stack
			{
				operatorStack.push (string (1, inputEquation[i]));
			}
			else if ((inputEquation[i + 1] != ' ') && (string (1, inputEquation[i]) == "-")) //if "-" indicates a negative number
			{
				current += string (1, inputEquation[i]) + string (1, inputEquation[i + 1]);
				i++;  //to avoid duplication because we already added inputEquation[i+1] to current
			}
			else if (operatorStack.top () == "^" && inputEquation[i] == '^') //power has the highest precedence however, if we found two consecutive powers we add both to stack
			{
				operatorStack.push (string (1, inputEquation[i]));
			}
			else if (operators[operatorStack.top ()] < operators[string (1, inputEquation[i])])   //checking precedence, add operator to stack if it has less precedence than the stack top
			{
				operatorStack.push (string (1, inputEquation[i]));
			}
			else /*checking precedence of inputEquation[i], if it's more than or equal to top:
				 - add top to expression
				 -pop it from stack
				 -push trying[i] to stack*/
			{
				while (!operatorStack.empty () && operators[operatorStack.top ()] >= operators[string (1, inputEquation[i])]) {
					expression = expression + " " + operatorStack.top ();
					operatorStack.pop ();
				}
				operatorStack.push (string (1, inputEquation[i]));
			}

		}
		else                                  // if inputEquation[i] = space  
		{
			if (expression != "")
				expression = expression + " " + current;
			else
				expression += current; //at the beginning of the expression
			current = ""; //empty current in both cases after adding to the expression
		}
	}
	// after looping through the string and applying our conditions, if stack isn't empty push everything is expression
	while (!operatorStack.empty ())
	{
		expression += " " + operatorStack.top ();
		operatorStack.pop ();
	}
	eq = expression;
	return expression;
}


/*
Split word By Spaces ---> ( Convert string to Vector strings )
*/
vector<string> split (string word)
{
	word = regex_replace (word, regex (" {2,}"), " ");
	vector<string> words{};
	size_t pos = 0;
	while ((pos = word.find (" ")) != string::npos) {
		words.push_back (word.substr (0, pos));
		word.erase (0, pos + 1);
	}
	words.push_back (word);
	return words;
}


/*
replace series of strings to a string
*/
vector<string> splitAndMerge (vector<string> expression, string exp, int begin, int last) {
	vector<string> newExpress (expression.size () - (last - begin));                 //create new vector with  ~>(3-->1)
	int j = 0;
	for (int i = 0;i < expression.size ();i++) {
		if (i < begin) {
			newExpress[j] = expression[i];
			j++;
		}
		else if (i == begin) {
			newExpress[j] = exp;
			j++;
		}
		else if (i > last) {
			newExpress[j] = expression[i];
			j++;
		};
	}
	return newExpress;
}


/*
Calculate Value of Eq. using given Value X
*/
long double evalEq (long double x) {
	vector<string> ex = split (eq); //the vector of strings returned from the split function
	constants["x"] = x;
	constants["-x"] = 0 - x;
	while (true)     //until there is no more operators  
	{
		int i = 0;
		// increment i until we find an operator or a function 
		while (i < ex.size () && operatorsMap.find (ex[i]) == operatorsMap.end () && functionMap.find (ex[i]) == functionMap.end ()) {
			i++;
		}
		if (i >= ex.size ()) break;
		/*
		calculate result of the operator and the 2 previous operands
		*/
		if (operatorsMap.find (ex[i]) != operatorsMap.end ())
		{
			long double a = constants.find (ex[i - 2]) != constants.end () ? constants[ex[i - 2]] : stod (ex[i - 2]);
			long double b = constants.find (ex[i - 1]) != constants.end () ? constants[ex[i - 1]] : stod (ex[i - 1]);
			long double result = operatorsMap[ex[i]] (a, b);
			ex = splitAndMerge (ex, to_string (result), i - 2, i);
		}
		/*
		 calculate result of the operator and the  previous  function
		 */
		else if (functionMap.find (ex[i]) != functionMap.end ()) {
			long double a;
			a = constants.find (ex[i - 1]) != constants.end () ? constants[ex[i - 1]] : stod (ex[i - 1]);

			long double result = functionMap[ex[i]] (a);
			ex = splitAndMerge (ex, to_string (result), i - 1, i);
		}
	}

	string result;

	for (int i = 0;i < ex.size (); i++) result += (ex[i]);
	result = regex_replace (result, regex ("x"), to_string (x));        // replace every x with its value 
	return stod (result);           // stod --> convert string to double
}


/*
Format the Eq.
*/

string normalizeEq (string eq) {
	eq = regex_replace (eq, regex (" {1,}"), "");   // remove all spaces in Eq. String 

	string normalizedEq = "";

	/*
	Befor --> "x^2-X-1"
	After --> "x ^ 2 - x - 1  "
	*/
	for (int i = 0;i < eq.size ();i++) {
		if (operatorsMap.find (string (1, eq[i])) != operatorsMap.end ()) {
			if (eq[i] == '-') {
				if (i > 0 && (operatorsMap.find (string (1, eq[i - 1])) != operatorsMap.end () || functionMap.find (string (1, eq[i - 1])) != functionMap.end () || eq[i - 1] == '(') || (i == 0)) {
					normalizedEq += " " + string (1, eq[i]);
				}
				else {
					normalizedEq += " " + string (1, eq[i]) + " ";
				}
			}
			else {
				normalizedEq += " " + string (1, eq[i]) + " ";
			}
		}
		else if (eq[i] == '(') {
			normalizedEq += string (1, eq[i]) + " ";
		}
		else if (eq[i] == ')') {
			normalizedEq += " " + string (1, eq[i]);
		}
		else {
			normalizedEq += string (1, eq[i]);
		}

	}
	normalizedEq = regex_replace (normalizedEq, regex (" {2,}"), " ");     // replace more than 1 space to a space 
	return normalizedEq + " ";
}