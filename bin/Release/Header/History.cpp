#include <iostream>
#include "History.hpp"
#include <fstream>
#include <vector>
#include <stdio.h>
using namespace std;

vector<std::string> loadHistory(std::string& word,bool& exist)
{
    ifstream fin;
    fin.open("\\SearchHistory\\History.txt");
    vector<std::string> vec;
    string tmp;
    if(fin.is_open())
    {
        while(getline(fin,tmp))
        {
            if(tmp!=word)
            vec.push_back(tmp);
            else exist = true;
        }
    }
    fin.close();
    return vec;
}

bool saveWordToTextFile(std::string& word)
{
    bool exist = false;
    vector<std::string> vec = loadHistory(word,exist);
    ofstream fout;
    if(!exist)
    {
        fout.open("\\SearchHistory\\History.txt",ios::app);
        if(!fout.is_open()) return false;
        fout<<word<<endl;
        fout.close();
        return true;
    }
    else
    {
        fout.open("\\SearchHistory\\History.txt");
        if(!fout.is_open()) return false;
        for(int i=0;i<vec.size();i++)
        {
            fout<<vec[i]<<endl;
        }
        fout<<word<<endl;
        fout.close();
        return true;
    }
}

vector<std::string> SearchHistory()
{
    string word = "";
    bool exist = false;
    vector<std::string> vec = loadHistory(word,exist);
    return vec;
}

bool deleteSearchHistory()
{
    remove("\\SearchHistory\\History.txt");
    ofstream fout;
    fout.open("\\SearchHistory\\History.txt");
    if(!fout.is_open()) return false;
    else
    {
        fout.close();
        return true;
    }
}

bool deleteWordInHistory(std::string& word)
{
    bool exist = false;
    vector<std::string> vec = loadHistory(word,exist);
    ofstream fout;
    fout.open("\\SearchHistory\\History.txt");
    if(!fout.is_open()) return false;
    else
    {
        for(int i=0;i<vec.size();i++)
        {
            fout<<vec[i]<<endl;
        }
        fout.close();
        return true;
    }
}
