#include "Package.hpp"
#include <iostream>
#include <zip.h>

namespace Anki
{
	Package::Package() :
		collection(nullptr)
	{
	}

	Package::Package(const std::string& filename) :
		Package()
	{
		if(Open(filename)) throw "Failed to load package";
	}

	Package::~Package()
	{
		if (collection != nullptr) delete collection;
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

		collection = new char[st.size];

		zip_file* collection_file = zip_fopen(archive, collection_filename, 0);
		zip_fread(collection_file, collection, st.size);
		zip_fclose(collection_file);

		zip_close(archive);

		std::cout << collection << std::endl;

		return err;
	}
}