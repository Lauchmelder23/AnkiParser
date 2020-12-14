#pragma once

#include <string>

struct sqlite3;

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
		void DumpAnki2File(const char* raw, size_t size);

	private:
		sqlite3* collection;
		std::string tmpDbName;

		static bool sqlite_init;
	};
}