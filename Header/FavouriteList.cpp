#include "FavouriteList.hpp"

vector<string> favouriteList()
{
	vector<string> favorite;
	ifstream fin;
	ifstream fin2;
	fin.open("FavoriteList/FavoriteList.bin", ios::binary | ios::in);
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
		string fileName = "FavoriteList/" + output + ".bin";
		fin2.open(fileName);
		if (fin2)
		{
			favorite.push_back(output);
			fin2.close();
		}
		delete[] word;
	}
	fin.close();
	return favorite;
}

bool addWordToFavList(std::string& word)
{
    ifstream fin;
    std::string path = "FavouriteList/" + word + ".bin";
    fin.open(path);
    if(fin.is_open()) 
    {
        fin.close();
        throw 'x';
    }
    else fin.close();
    ofstream fout;
	string fileName = "FavouriteList/FavouriteList.bin";
	fin.open(fileName);
	if (!fin)
		return false;
	int num;
	fin.read((char*)&num, sizeof(int));
	num++;
	fin.close();
    fout.open(fileName,ios::binary|ios::app);
    if(!fout.is_open()) return false;
    fout.write((char*)&word,sizeof(word));
	fout.seekp(0, ios::beg);
	fout.write((char*)&num, sizeof(int));
    fout.close();
    fout.open(path,ios::binary);
    if(!fout.is_open()) return false;
    fout.close();
    return true;
}

bool removeWordFromFavList(std::string& word)
{
    std::string path = "FavouriteList/" + word + ".bin";
    if(!remove(path.c_str())) return true;
    return false;
}