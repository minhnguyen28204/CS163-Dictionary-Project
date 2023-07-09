#include "FavouriteList.hpp"

vector<string> favouriteList()
{
	vector<string> favorite;
	ifstream fin;
	fin.open("FavoriteList.bin", ios::binary | ios::in);
	if (!fin)
		return favorite;
	int n;
	fin.read((char*)&n, sizeof(int));
	for (int i = 0; i < n; i++)
	{
		int size;
		fin.read((char*)&size, sizeof(int));
		char* word = new char[size + 1];
		fin.read((char*)word, size);
		word[size] = '\0';
		string output = word;
		string fileName = "Favorite Words/" + output + ".bin";
		if (filesystem::exists(fileName))
			favorite.push_back(output);
		delete[] word;
	}
	return favorite;
}