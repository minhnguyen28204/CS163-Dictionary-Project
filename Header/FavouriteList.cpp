#include "FavouriteList.hpp"

std::string favorite::pathEmoji = "FavouriteList\\FavouriteEmoji\\FavouriteEmoji.txt";
std::string favorite::pathSlang = "FavouriteList\\FavouriteSlang\\FavouriteSlang.txt";
std::string favorite::pathEngToEng = "FavouriteList\\FavouriteEngToEng\\FavouriteEngToEng.txt";
std::string favorite::pathEngToVie = "FavouriteList\\FavouriteEngToVie\\FavouriteEngToVie.txt";
std::string favorite::pathVieToEng = "FavouriteList\\FavouriteVieToEng\\FavouriteVieToEng.txt";
std::vector<std::string> favorite::mode{ favorite::pathEmoji,favorite::pathSlang,favorite::pathEngToEng,favorite::pathEngToVie,favorite::pathVieToEng };
std::string favorite::FolEmoji = "FavouriteList\\FavouriteEmoji\\";
std::string favorite::FolSlang = "FavouriteList\\FavouriteSlang\\";
std::string favorite::FolEngToEng = "FavouriteList\\FavouriteEngToEng\\";
std::string favorite::FolEngToVie = "FavouriteList\\FavouriteEngToVie\\";
std::string favorite::FolVieToEng = "FavouriteList\\FavouriteVieToEng\\";
std::vector<std::string> favorite::folder{ favorite::FolEmoji,favorite::FolSlang,favorite::FolEngToEng,favorite::FolEngToVie,favorite::FolVieToEng };

vector<string> favouriteList()
{
	vector<string> favorite;
	ifstream fin;
	fin.open(favorite::mode[Path::curPath]);
	if (!fin.is_open())
		return favorite;
	string word;
	while(getline(fin, word))
	{
		favorite.push_back(word);
	}
	fin.close();
	return favorite;
}

bool isFavourite(std::string& word)
{
	vector<string> vec;
	vec = favouriteList();
	int size = vec.size();
	for (int i = 0; i < size; i++)
	{
		if (vec[i] == word) return true;
	}
	return false;
}

bool addWordToFavList(std::string& word)
{
    ofstream fout;
	fout.open(favorite::mode[Path::curPath], ios::app);
    if(!fout.is_open()) return false;
	fout << word << endl;
	fout.close();
	return true;
}

bool removeWordFromFavList(std::string& word)
{
	vector<string> vec = favouriteList();
	ofstream fout;
	fout.open(favorite::mode[Path::curPath]);
	if (!fout.is_open()) return false;
	int size = vec.size();
	for (int i = 0; i < size; i++)
	{
		if (vec[i] == word) continue;
		else fout << vec[i] << endl;
	}
	fout.close();
	return true;
}
