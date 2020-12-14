#include "Package.hpp"
#include <iostream>
#include <fstream>

#include <zip.h>
#include <sqlite3.h>

bool Anki::Package::sqlite_init = false;

static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << "\t";
	}
	std::cout << std::endl;
	return 0;
}

namespace Anki
{
	Package::Package() :
		collection(nullptr)
	{
		if (!sqlite_init)
		{
			srand(time(NULL));
			sqlite3_initialize();
			sqlite_init = true;
		}
	}

	Package::Package(const std::string& filename) :
		Package()
	{
		if(Open(filename)) throw "Failed to load package";
	}

	Package::~Package()
	{
		sqlite3_close(collection);
	}

	int Package::Open(const std::string& filename)
	{
		int err = 0;
		zip* archive = zip_open(filename.c_str(), 0, &err);
		if (err) return err;

		static const char* collection_filename = "collection.anki2";
		struct zip_stat st;
		zip_stat_init(&st);
		zip_stat(archive, collection_filename, 0, &st);

		char* collection_raw = new char[st.size];

		zip_file* collection_file = zip_fopen(archive, collection_filename, 0);
		zip_fread(collection_file, collection_raw, st.size);
		zip_fclose(collection_file);

		zip_close(archive);

		DumpAnki2File(collection_raw, st.size);

		delete[] collection_raw;

		return err;
	}

	void Package::DumpAnki2File(const char* raw, size_t size)
	{
		// SQLite is kinda stupid and can't create a database from data stored in memory.
		// It insists on opening a database file instead. I don't see a way around that unfortunately
		// So I have to dump the database into a file first
		// tmpDbName = std::to_string(rand()) + ".db";
		tmpDbName = "test.db";
		std::ofstream tmp_db(tmpDbName, std::ios::binary);
		tmp_db.write(raw, size);
		tmp_db.close();



		int result = sqlite3_open(tmpDbName.c_str(), &collection);
		if (result)
		{
			std::cerr << result << std::endl;
			return;
		}

		char* errMsg = nullptr;
		result = sqlite3_exec(collection, "SELECT decks FROM col;", callback, 0, &errMsg);
		if (result != SQLITE_OK)
		{
			std::cerr << errMsg << std::endl;
		}
	}
}