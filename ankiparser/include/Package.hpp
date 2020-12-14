#pragma once

#include <string>

namespace Anki
{
	class Package
	{
	public:
		Package();
		Package(const std::string& filename);
		~Package();

		int Open(const std::string& filename);

	private:
		char* collection;
	};
}