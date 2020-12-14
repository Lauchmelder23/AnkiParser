#include <iostream>
#include <Package.hpp>
#include <zip.h>

int main(int argc, char** argv)
{
	if (argc != 2) 
	{
		std::cerr << "Usage: " << argv[0] << " <apkg file>" << std::endl;
		return 1;
	}

	Anki::Package pkg;
	int result = pkg.Open(argv[1]);
	if (result)
	{
		zip_error err;
		zip_error_init_with_code(&err, result);
		std::cerr << "Could not open package: " << zip_error_strerror(&err) << " (" << result << ")" << std::endl;
	}

	return 0;
}