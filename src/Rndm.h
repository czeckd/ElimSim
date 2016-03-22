#ifndef __RNDM_H__
#define __RNDM_H__

#include <random>
#include <iostream>


class Rndm
{

public:
	static int number(int from, int to);

private:
	Rndm();
	static Rndm & rndm();
	static std::mt19937 & mt();

	std::random_device _rd;
	std::mt19937       _mt;

};



#endif	// __RNDM_H__
