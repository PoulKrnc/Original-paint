#pragma once
#include <allegro5/color.h>

class Color
{
public:
		ALLEGRO_COLOR color;
		int r;
		int g;
		int b;
		int a;
		Color(int r, int g, int b, int a)
		{
				this->color = al_map_rgba(r, g, b, a);
				this->r = r;
				this->g = g;
				this->b = b;
				this->a = a;
		}
		void changeColor(int r, int g, int b, int a)
		{
				color = al_map_rgba(r, g, b, a);

		}
		ALLEGRO_COLOR shade(int shade)
		{
				int r1 = r + shade;
				int g1 = g + shade;
				int b1 = b + shade;
				if (r1 > 255) { r1 = 255; }
				else if (r1 < 0) { r1 = 0; }
				if (g1 > 255) { g1 = 255; }
				else if (g1 < 0) { g1 = 0; }
				if (b1 > 255) { b1 = 255; }
				else if (b1 < 0) { b1 = 0; }

				return al_map_rgba(r1, g1, b1, a);
		}
};
