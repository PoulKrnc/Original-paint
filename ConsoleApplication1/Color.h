#pragma once
#include <allegro5/color.h>

class Color {
public:
	 ALLEGRO_COLOR color;
	 float r;
	 float g;
	 float b;
	 float a;
	 Color(float r, float g, float b, float a) {
			this->color = al_map_rgba(r, g, b, a);
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
	 }
	 void changeColor(float r, float g, float b, float a) {
			color = al_map_rgba(r, g, b, a);

	 }
	 ALLEGRO_COLOR shade(float shade) {
			float r1 = r + shade;
			float g1 = g + shade;
			float b1 = b + shade;
			if (r1 > 255) { r1 = 255; } else if (r1 < 0) { r1 = 0; }
			if (g1 > 255) { g1 = 255; } else if (g1 < 0) { g1 = 0; }
			if (b1 > 255) { b1 = 255; } else if (b1 < 0) { b1 = 0; }

			return al_map_rgba(r1, g1, b1, a);
	 }
};
