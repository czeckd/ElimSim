#include "Rndm.h"

Rndm::Rndm() : _mt(_rd()) 
{
}

Rndm & Rndm::rndm()
{
	static Rndm rndm;
	return rndm;
}

std::mt19937 & Rndm::mt()
{
	return Rndm::rndm()._mt;
}

int Rndm::number(int from, int to)
{
	std::uniform_int_distribution<int> num(from, to);
	return num(Rndm::mt());
}
