#include "kulka.hpp"

Kulka::Kulka()
{
	x = (float)rand() / RAND_MAX * 1920;
	y = (float)rand() / RAND_MAX * 1080;

	r = (float)rand() / RAND_MAX;
	g = (float)rand() / RAND_MAX;
	b = (float)rand() / RAND_MAX;

	rx = (float)rand() / RAND_MAX * 2 - 1;
	ry = (float)rand() / RAND_MAX * 2 - 1;

	wielkosc = (float)rand() / RAND_MAX * 35;

	if (wielkosc < 5)
		wielkosc = 5;
}

void Kulka::porusz()
{
	x += rx;
	y += ry;

	rx *= 0.999;
	ry *= 0.999;
}