#include <iostream>
#include <cmath>
#include <thread>
#include <SFML/Graphics.hpp>
#include "kulka.hpp"

const unsigned int W = 1920,
				   H = 1080,
				   R = 3000;

Kulka kulki[50];

int ogranicz (int liczba, int min, int max)
{
	if (liczba > max) return max;
	if (liczba < min) return min;

	return liczba;
}

void przelicz(int start, int koniec, sf::Uint8 *pixels)
{
	float dystansR = 0,
		dystansG = 0,
		dystansB = 0,
		dyst = 0;

	sf::Uint8 *pixel = pixels;

	pixel += start * W * 4;

	//Rysowanie
	for(int y = start; y < koniec; y ++)
	for(int x = 0; x < W; x ++)
	{
		dystansR = 0;
		dystansG = 0;
		dystansB = 0;
		dyst = 0;

		for (auto & kulka : kulki)
		{
			dyst = R * kulka.wielkosc / (pow(kulka.x - x, 2) + pow(kulka.y - y, 2));

			dystansR += dyst * kulka.r;
			dystansG += dyst * kulka.g;
			dystansB += dyst * kulka.b;
		}

		//int i = (x + y * W) * 4;

		*pixel = ogranicz(dystansR, 0, 255);
		pixel++;
		*pixel = ogranicz(dystansG, 0, 255);
		pixel++;
		*pixel = ogranicz(dystansB, 0, 255);
		pixel++;
		*pixel = 255;
		pixel++;
	}
}

int main()
{
	int klatka = 0;
	sf::Image klatkaObraz;

	sf::RenderWindow okno(sf::VideoMode(W, H), "Kolory");

	sf::Uint8* pixels = new sf::Uint8[W*H*4];

	sf::Texture texture;
	texture.create(W, H); 

	sf::Sprite sprite(texture);

	while (okno.isOpen())
	{
		sf::Event event;
		while (okno.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				okno.close();
			}
		}
		// if(klatka % 100 == 0)
		// {
		//     kulki.push_back(Kulka());
		//     std::cout << "Dodano\n";
		// }

		for (auto & kulka : kulki)
		{
			for (auto & kulka2 : kulki)
			{
				if (&kulka != &kulka2)
				{
					kulka.rx -= (kulka.x - kulka2.x) / 100000 * (kulka2.r / kulka.r);
					kulka.ry -= (kulka.y - kulka2.y) / 100000 * (kulka2.r / kulka.r);
				}
			}
			
			kulka.porusz();
			if (kulka.x < 0 || kulka.x > W) kulka.rx = -kulka.rx;
			if (kulka.y < 0 || kulka.y > H) kulka.ry = -kulka.ry;
		}

		//Pętla
		std::thread watki[4] =
		{
			std::thread(przelicz, 0        , H / 4    , pixels),
			std::thread(przelicz, H / 4    , H / 4 * 2, pixels),
			std::thread(przelicz, H / 4 * 2, H / 4 * 3, pixels),
			std::thread(przelicz, H / 4 * 3, H        , pixels)
		};

		watki[0].join();
		watki[1].join();
		watki[2].join();
		watki[3].join();
		

		texture.update(pixels);

		okno.draw(sprite);
		
		okno.display();

		klatka++;

		klatkaObraz.create(W, H, pixels);
		
		klatkaObraz.saveToFile("./klatki/" + std::to_string(klatka) + ".png");

	}
}
