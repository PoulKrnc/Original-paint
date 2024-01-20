#pragma once
#include <allegro5/drawing.h>
#include <iostream>
#include <string>

#include "Color.h"
using namespace std;

class Object
{
	
};

class Pixel : public Object {
public:
		int x;
		int y;
		Color color = Color(0, 0, 0, 0);

		Pixel(const int x, const int y, const Color& color) {
				this->color = color;
				this->x = x;
				this->y = y;
		}

		string toString() const {
				return "x=" + to_string(x) + "; y=" + to_string(y) + ";\n";
		}

		void draw() const {
				al_draw_pixel(x, y, color.color);
		}
};

class Rect : public Object {
public:
		int x;
		int y;
		int width;
		int height;
		Color color = Color(0, 0, 0, 0);
		std::vector<Pixel> lst;
		Rect(int x, int y, int width, int height, Color color) {
				this->x = x;
				this->y = y;
				this->width = width;
				this->height = height;
				this->color = color;
				for (int i = 0; i <= width; i++) {
						for (int j = 0; j <= width; j++) {
								Pixel p = Pixel(this->x + i, this->y + j, this->color);
								this->lst.emplace_back(p);
						}
				}
		}

		void printPixels() {
				for (Pixel pixel : lst) {
						cout << pixel.toString();
				}
		}

		string toString() const {
				return "x= " + to_string(x) + "; y=" + to_string(y) + "; w=" + to_string(width) + "; h=" + to_string(height) + ";\n";
		}

		void draw() const {
				for (Pixel pixel : lst) {
						//cout << pixel.toString();
						pixel.draw();
				}
		}
};