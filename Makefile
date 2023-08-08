
build : compile
	g++ main.o -o main -L "C:\SFML\lib" -lsfml-graphics -lsfml-window -lsfml-system

compile : 
	g++ -c main.cpp -I "C:\SFML\include"
	g++ -c MainFunction.cpp -I "C:\SFML\include"
	g++ -c AddScreen.cpp -I "C:\SFML\include"
	g++ -c FavouriteScreen.cpp -I "C:\SFML\include"
	g++ -c HistoryScreen.cpp -I "C:\SFML\include"
	g++ -c HomeScreen.cpp -I "C:\SFML\include"
	g++ -c QuizScreen.cpp -I "C:\SFML\include"
	g++ -c SearchScreen.cpp -I "C:\SFML\include"
	g++ -c SettingScreen.cpp -I "C:\SFML\include"
	g++ -c FavouriteList.cpp -I "C:\SFML\include"
	g++ -c History.cpp -I "C:\SFML\include"
	g++ -c MenuSideBar.cpp -I "C:\SFML\include"
	g++ -c Random.cpp -I "C:\SFML\include"
	g++ -c TextField.cpp -I "C:\SFML\include"
	g++ -c ViewWordScreen.cpp -I "C:\SFML\include"
	g++ -c Trie.cpp -I "C:\SFML\include"