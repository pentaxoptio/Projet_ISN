#include "App.h"
#include <exception>
#include <iostream>
int main()
{
	try
	{
		App app;
		app.run();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

