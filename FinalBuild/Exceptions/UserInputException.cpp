#include "UserInputException.h"

WrongNumberException::WrongNumberException(int max, int min, int e):max(max), min(min), entered(e)
{
	
}

void WrongNumberException::what()
{
	cout << "Incorrect value. needs to be between " << this->min;
	cout << " and " << this->max << endl;
}


NANException::NANException(int in)
{
	this->input = to_string(in);
}
NANException::~NANException()
{
}
void NANException::what()
{
	cout << "Please enter a number" << endl;
	cout << input << endl;
}

