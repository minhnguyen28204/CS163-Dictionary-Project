#include "Header/MainFunction.hpp"
#include "Header/Trie.hpp"
using namespace std;

int main()
{
    WordSet::switchWordSet(2);
    WordSet::loadAllData();
    Dictionary dictionary;
    dictionary.run();
    return 0;
}
