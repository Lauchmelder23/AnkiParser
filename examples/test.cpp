#include <iostream>
#include <Package.hpp>

int main(int argc, char** argv)
{
	if (argc != 2) 
	{
		std::cerr << "Usage: " << argv[0] << " <apkg file>" << std::endl;
		return 1;
	}

	try 
	{
		Anki::Package pkg(argv[1]);
	}
	catch (const char* e)
	{
		std::cerr << e << std::endl;
	}

	return 0;
}