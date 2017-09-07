// Digital Abacus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>  // Header that defines the standard input/output stream objects:
#include <string>  //  Header introduces string types, character traits and a set of converting functions
#include <sstream> // Header providing string stream classes
#include <regex>  // Header support for regular expressions
using namespace std;

class Abacus {   // class for ease of passing vars
public:  
	string equasion, num1, num2, calc;
	double total;
	void RegMatch();  // function to regex check user input
	void parse();  // function to parse input
	void calculation();  // function to calculate equasion
};

void Abacus::RegMatch() {
	regex  r{ R"(^-?\d*\.?\d*[-+*\/]-?\d*\.?\d*$)" };  //instantiation of the basic_regex class template for characters of type char and the expression assigned
	smatch match;  //  instantiation of the regex match_results class template for matches on string objects
	if (regex_match(equasion, match, r)) {  // if it's a match
		parse();  // run the parse
		calculation();  // run the calc
	}
	else {
		cout << "Invalid expression! You can't fool the Digital Abacus, try again" << "\n" << endl;
	}
}

void Abacus::parse() {
	for (int i = 0; i < equasion.length(); i++) {
		if (num1.empty() && equasion[i] == '-') {  // starts with a negative?
			num1 += equasion[i];  // append to num1
		}
		else if ((equasion[i] == '.' || isdigit(equasion[i])) && (calc.empty())) { // is a decimal point, number and calc is still empty
			num1 += equasion[i];  // append to num1
		}
		else if (!isdigit(equasion[i]) && calc.empty()) { // ah, it's the operator
			calc += equasion[i];  // append to calc
		}
		else {  // everything else
			num2 += equasion[i];  // append to num2
		}
	}
}

void Abacus::calculation() {
	double val1;
	double val2;
	stringstream(num1) >> val1;  // string buffer used to operate on strings
	stringstream(num2) >> val2;  // allows for negative value conversion unlike stof() which doesn't honor negative values in string format

	if (val2 == 0 && calc == "/") {  // if you're trying to divide by zero
		cout << "Invalid expression! You can't fool the Digital Abacus, try again" << "\n" << endl;
	}
	else if (num1.empty() || num2.empty()) {
		cout << "Invalid expression! You can't fool the Digital Abacus, try again" << "\n" << endl;
	}
	else {  // if everything is kosher, the math in switch format

		if (val1 == -0) {
			val1 == 0;
		}
		if (val2 == -0) {
			val2 == 0;
		}
		switch (calc[0]) {
			case '+':
				total = val1+val2;
				break;
			case '-':
				total = val1-val2;
				break;
			case '*':
				total = val1*val2;
				break;
			case '/':
				total = val1/val2;
				break;
		}
		if (total == -0) {
			total = 0;
		}
		cout << "= " << total << "\n" << endl;  // outputs equasion and answer
	}
	num1.clear(); num2.clear(); calc.clear();  // clears values
}

int main()
{
	Abacus fred;
	cout << "Welcome to the Unbreakable Single Operator Digital Abacus" << endl;
	cout << "Type equasion (e.g. 34+56)  Valid operands are +-*/\n" << endl;

	do {
		cout << "Enter calculation or ENTER to exit:\n";
		getline(cin, fred.equasion);  // getline aquires the next cin as a string, constructor = (input, value assignment)
		if (!fred.equasion.empty()) {  // if equasion isn't empty/null (trigger to quit/escap program)
			fred.RegMatch();
		}
		//system("cls");  // clears screen
	} while (!fred.equasion.empty());

    return 0;
}

