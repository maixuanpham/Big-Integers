/*  Program:			MSVS 2012/2015
	Author:				Mai Pham
	Class:				CSCI 140
	Date:				04/13/2017
	Description:		Project 2 - Big Integers + A EC
	I certify that the code below is my own work.
	Exception(s): N/A
*/

#include <iostream>
#include <string>
using namespace std;

int validate(string num1, string oper, string num2);
int check(string number);
void string2array(string num, int number[]);
void add(int number1[], int number2[], int number3[], int &over);
void subtract(int number1[], int number2[], int number3[]);
void multiply(int number1[], int number2[], int number3[], int &over);
void output(string num1, string oper, string num2, int number[]);

const int SIZE = 20;

int main()
{
	int number1[SIZE] = { 0 }, number2[SIZE] = { 0 }, number3[SIZE] = { 0 };
	string num1, oper, num2;
	int over = 0;

	cout << "Simple Math Calculation by Mai Pham\n";
	cout << "This program would do simple math calculation:\n";
	cout << "addition, subtraction, and multiplication.\n\n";

	cout << "Enter an expression --> ";
	cin >> num1 >> oper >> num2;

	while (!(num1 == "0" && oper == "%" && num2 == "0"))
	{
		if (validate(num1, oper, num2) == 0)
		{
			string2array(num1, number1);
			string2array(num2, number2);

			if (oper == "+")
				add(number1, number2, number3, over);
			else if (oper == "-")
				subtract(number1, number2, number3);
			else if (oper == "*")
				multiply(number1, number2, number3, over);

			if (over == 0)
				output(num1, oper, num2, number3);
			else
				cout << "Integer Overflow." << endl;

			memset(number1, 0, sizeof(number1));
			memset(number2, 0, sizeof(number2));
			memset(number3, 0, sizeof(number3));
		}
		cout << "\nEnter an expression --> ";
		cin >> num1 >> oper >> num2;
	}
	cout << "Thanks for using my program. Good bye!" << endl;
	return 0;
}
int validate(string num1, string oper, string num2)
{
	if (num1.length() > SIZE || num2.length() > SIZE)
	{
		cout << "Invalid operand (too large)." << endl;
		return 1;
	}
	if (oper != "+" && oper != "-" && oper != "*")
	{
		cout << "Invalid operator." << endl;
		return 1;
	}
	if (check(num1) == 1 || check(num2) == 1)
	{
		cout << "Invalid operand (bad digit)." << endl;
		return 1;
	}
	return 0;
}
int check(string number)
{
	for (int i = 0; i < number.length(); i++)
	{
		if (number[i] < '0' || number[i] > '9')
			return 1;
	}
	return 0;
}
void string2array(string num, int number[])
{
	int j = SIZE - 1;
	int i = num.length() - 1;
	while (i >= 0)
	{
		number[j] = num[i] - '0';
		j--;
		i--;
	}
}
void add(int number1[], int number2[], int number3[], int &over)
{
	int temp = 0;
	over = 0;
	for (int i = SIZE - 1; i >= 0; i--)
	{
		number3[i] = temp + number1[i] + number2[i];
		if (number3[i] >= 10)
		{
			number3[i] %= 10;
			temp = 1;
		}
		else
			temp = 0;
	}
	if (temp == 0)
		over = 0;
	else
		over = 1;
}
void subtract(int number1[], int number2[], int number3[])
{
	int temp = 0;
	for (int i = SIZE - 1; i >= 0; i--)
	{
		number3[i] = number1[i] - temp - number2[i];
		if (number3[i] < 0)
		{
			number3[i] = ((number1[i] - temp) + 10) - number2[i];
			temp = 1;
		}
		else
			temp = 0;
	}
}
void multiply(int number1[], int number2[], int number3[], int &over)
{
	int i, j, k, product;
	int carry1 = 0, carry2 = 0;
	over = 0;
	k = 0;
	for (i = SIZE - 1; i >= 0; i--)
	{
		for (j = SIZE - 1; j >= 0; j--)
		{
			product = number1[j] * number2[i];
			product += carry1;
			if (product >= 10)
			{
				carry1 = product / 10;
				product %= 10;
			}
			else
				carry1 = 0;

			number3[j - k] += product + carry2;

			if (number3[j - k] >= 10)
			{
				carry2 = number3[j - k] / 10;
				number3[j - k] %= 10;
			}
			else
				carry2 = 0;

			if ((j - k) <= 0) 
			{
				if (carry1 != 0 || carry2 != 0)
					over = 1;
				break;
			}
		}
		k++;
	}
}
void output(string num1, string oper, string num2, int number[])
{
	int length = SIZE - 1;
	cout << num1 << " " << oper << " " << num2 << " = ";
	for (int i = 0; i < SIZE; i++)
	{
		if (number[i] != 0)
		{
			length = i;
			break;
		}
	}
	for (int i = length; i < SIZE; i++)
		cout << number[i];
	cout << endl;
}