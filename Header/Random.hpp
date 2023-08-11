#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>
#include <vector>

namespace Random
{
	std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	extern std::mt19937 mt;

	//int get(int min, int max);

	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}

//std::string getWordFromFile(int& first,int& last);
//int getPositionDef(int& last);
//std::string getDefFromFile(int& pos);
//std::vector<std::string> randomOneWordFourDef();
//std::vector<std::string> randomOneDefFourWord();

#endif //RANDOM_HPP

