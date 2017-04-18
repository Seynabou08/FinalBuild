#include <exception>
#include <iostream>
#include <string>
#ifndef USERINPUTEXCEPTIONS_H
#define USERINPUTEXCEPTIONS_H
using namespace std;

class WrongNumberException : public exception
{
	public:
		WrongNumberException(int min, int max, int e);
		int min;
		int max;
		int entered;
		void what();
};

class NANException : public exception
{
	public:
		NANException(int in);
		~NANException();
		string input;
		void what();
};
#endif