#include "Director.h"

Director::Director()
{
	this->myfile.open("save.txt", ifstream::in);
}

Director::~Director()
{
}
