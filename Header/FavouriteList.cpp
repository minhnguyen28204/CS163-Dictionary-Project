#include "FavouriteList.hpp"

std::string pathEmoji = "FavouriteList\\FavouriteEmoji\\FavouriteEmoji.txt";
std::string pathSlang = "FavouriteList\\FavouriteSlang\\FavouriteSlang.txt";
std::string pathEngToEng = "FavouriteList\\FavouriteEngToEng\\FavouriteEngToEng.txt";
std::string pathEngToVie = "FavouriteList\\FavouriteEngToVie\\FavouriteEngToVie.txt";
std::string pathVieToEng = "FavouriteList\\FavouriteVieToEng\\FavouriteVieToEng.txt";
std::vector<std::string> mode;
std::string FolEmoji = "FavouriteList\\FavouriteEmoji";
std::string FolSlang = "FavouriteList\\FavouriteSlang";
std::string FolEngToEng = "FavouriteList\\FavouriteEngToEng";
std::string FolEngToVie = "FavouriteList\\FavouriteEngToVie";
std::string FolVieToEng = "FavouriteList\\FavouriteVieToEng";
std::vector<std::string> folder;

vector<string> favouriteList()
{
	mode.push_back(pathEmoji);
	mode.push_back(pathSlang);
	mode.push_back(pathEngToEng);
	mode.push_back(pathEngToVie);
	mode.push_back(pathVieToEng);
	folder.push_back(FolEmoji);
	folder.push_back(FolSlang);
	folder.push_back(FolEngToEng);
	folder.push_back(FolEngToVie);
	folder.push_back(FolVieToEng);
	vector<string> favorite;
	ifstream fin;
	ifstream fin2;
	fin.open(mode[Path::curPath], ios::binary | ios::in);
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
		string fileName = folder[Path::curPath] + output + ".bin";
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
	std::string path = folder[Path::curPath] + word + ".bin";
    fin.open(path);
    if(fin.is_open())
    {
        fin.close();
        throw 'x';
    }
    else fin.close();
    ofstream fout;
	fout.open(mode[Path::curPath], ios::binary | ios::app);
    if(!fout.is_open()) return false;
    fout.write((char*)&word,sizeof(word));
    fout.close();
    fout.open(path,ios::binary);
    if(!fout.is_open()) return false;
    fout.close();
    return true;
}

bool removeWordFromFavList(std::string& word)
{
    std::string path = folder[Path::curPath] + word + ".bin";
    if(!remove(path.c_str())) return true;
    return false;
}
