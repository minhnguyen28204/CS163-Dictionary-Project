#include "Random.hpp"
#include <ctime>
#include <fstream>

using namespace std;

std::string getWordFromFile(int& first,int& last)
{
    std::string word = "";
    ifstream fin;
    fin.open("Words.bin",ios::binary);
    if(fin.is_open())
    {
        fin.seekg(first);
        fin.read((char*)&word,last-first+1);
        fin.close();
    }
    return word;
}

int getPositionDef(int& last)
{
    ifstream fin;
    fin.open("Words.bin",ios::binary);
    int posDef = 0;
    if(fin.is_open())
    {
        fin.seekg(last+1);
        fin.read((char*)& posDef,sizeof(int));
        fin.close();
    }
    return posDef;
}

std::string getDefFromFile(int& pos)
{
    std::string def = "";
    ifstream fin;
    fin.open("Definition.bin",ios::binary);
    if(fin.is_open())
    {
        fin.seekg(pos);
        int n;
        fin.read((char*)&n,sizeof(int));
        fin.seekg(pos+4);
        fin.read((char*)&def,n);
        fin.close();
    } 
    return def;
}

std::vector<std::string> randomOneWordFourDef()
{
    vector<std::string> vec;
    ifstream fin;
    fin.open("WordsColumn.bin",ios::binary);
    int n;
    if(fin.is_open())
    {
        fin.read((char*)&n,sizeof(int));
        int a[4];
        for(int i=0;i<4;i++)
        {
            a[i] = rand()%n+1;
            if(i==1)
            {
                while(a[i]==a[0])
                {
                    a[i] = rand()%n+1;
                }
            }
            else if(i==2)
            {
                while(a[i]==a[0]||a[i]==a[1])
                {
                    a[i] = rand()%n+1;
                }
            }
            else if(i==3)
            {
                 while(a[i]==a[0]||a[i]==a[1]||a[i]==a[2])
                {
                    a[i] = rand()%n+1;
                }
            }
        }
        for(int i=0;i<4;i++)
        {
            fin.seekg(a[i]*4);
            int last;
            fin.read((char*)&last,sizeof(int));
            int posDef;
            if(i==0) 
            {
                int first;
                if(a[i]>1) {
                    fin.seekg(a[i]*4-4);
                    fin.read((char*)&first,sizeof(int));
                    first+=5;
                }
                else first=0;
                vec.push_back(getWordFromFile(first,last));
            }
            int posDef = getPositionDef(last);
            vec.push_back(getDefFromFile(posDef));
        }
        fin.close();
    }
    return vec;
}