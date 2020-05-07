#ifndef kulka_hpp
#define kulka_hpp
#include <string>

class Kulka
{
public:
	float x,  y,
		  rx, ry,
		  r, g, b,
		  wielkosc;

	Kulka();

	//~Kulka();

	void porusz();
};

#endif