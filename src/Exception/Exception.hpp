#ifndef EXCEPTION_ENGIMON_HPP
#define EXCEPTION_ENGIMON_HPP

#include <exception>

class OutOfBoundException : public exception
{
public:
	const char *what() const noexcept
	{
		return "Out of bounds!";
	}
};

class WildEngimonPositionException : public exception
{
public:
	const char *what() const noexcept
	{
		return "Reposition wild Engimon!";
	}
};

#endif