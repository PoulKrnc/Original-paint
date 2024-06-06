#pragma once
#include <allegro5/drawing.h>
#include <iostream>
#include <functional>
#include <string>

#include "Color.h"
#include "font.h"

class Rect;
class Pixel;
class Circle;
using namespace std;



class Object {
public:
	 vector<Pixel> lst;
	 
	 Object() {

	 }
};

class Pixel : public Object {
public:
	 int x;
	 int y;
	 Color color = Color(0, 0, 0, 0);

	 Pixel(const int x, const int y, const Color color) {
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

class Rect : Object {
public:
	 int x;
	 int y;
	 float width;
	 float height;
	 Color color = Color(0, 0, 0, 0);
	 string text = "";
	 Font font = Font();
	 Color text_color = Color(0,0,0,255);
	 std::vector<Pixel> lst;
	 Rect() {
			x = 0;
			y = 0;
			width = 0;
			height = 0;
	 }
	 Rect(int x, int y, float width, float height, Color color) {
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->color = color;
			for (int i = 0; i <= width; i++) {
				 for (int j = 0; j <= height; j++) {
						Pixel p = Pixel(this->x + i, this->y + j, this->color);
						this->lst.emplace_back(p);
				 }
			}
	 }

	 Rect(int x, int y, float width, float height, Color color, string text, Font font, Color text_color) {
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->color = color;
			this->text = text;
			this->font = font;
			this->text_color = text_color;
			for (int i = 0; i <= width; i++) {
				 for (int j = 0; j <= height; j++) {
						Pixel p = Pixel(this->x + i, this->y + j, this->color);
						this->lst.emplace_back(p);
				 }
			}
	 }

	 Rect(int x, int y, Color color, string text, Font font, Color text_color) {
			this->x = x;
			this->y = y;
			this->color = color;
			this->text = text;
			this->font = font;
			this->text_color = text_color;
			this->width = (font.size) * text.length()/2;
			this->height = font.size;
			for (int i = 0; i <= width; i++) {
				 for (int j = 0; j <= height; j++) {
						Pixel p = Pixel(this->x + i, this->y + j, this->color);
						this->lst.emplace_back(p);
				 }
			}
	 }

	 void setText(string text, Font font, Color text_color) {
			this->text = text;
			this->font = font;
			this->text_color = text_color;
	 }

	 void printPixels() {
			for (Pixel pixel : lst) {
				 cout << pixel.toString();
			}
	 }

	 string toString() const {
			return "x= " + to_string(x) + "; y=" + to_string(y) + "; w=" + to_string(width) + "; h=" + to_string(height) + ";\n";
	 }

	 void draw() {
			for (Pixel pixel : lst) {
				 pixel.draw();
			}
			if (text != "") {
				 const char* char_text = text.c_str();
				 al_draw_text(font.font, text_color.color, ((x + (width / 2)) - ((font.size / 2) * text.length() / 2)), (y + (height / 2) - (font.size / 2)), 0, char_text);
			}
	 }
};

class Circle : Object {
public:
	 int x;
	 int y;
	 int r;
	 int borderFat = 1;
	 Color color = Color(0, 0, 0, 0);
	 Color borderColor = Color(0, 0, 0, 0);
	 std::vector<Pixel> lst;
	 std::vector<Circle> lst1;
	 Circle(int x, int y, int r, Color color) {
			this->x = x;
			this->y = y;
			this->r = r;
			this->color = color;
			init();
	 }
	 Circle(int x, int y, int r, Color color, int borderFat, Color borderColor) {
			this->x = x;
			this->y = y;
			this->r = r;
			this->color = color;
			this->borderFat = borderFat;
			this->borderColor = borderColor;
			init();
			initNoFill();
	 }

	 void init() {
			const double PI = 3.1415926535;
			double i, angle, x1, y1;
			for (double j = 0; j <= this->r; j+= 0.45) {
				 double o = 2 * PI * (r - (j));
				 for (i = 0; i < 361; i += (double)360 / o ) {
						angle = i;
						x1 = ((double)this->r - j) * cos(angle * PI / 180.0);
						y1 = ((double)this->r - j) * sin(angle * PI / 180.0);
						lst.push_back(Pixel((double)this->x + x1, (double)this->y + y1, color.shade(0)));
				 }
			}

	 }

	 void initNoFill() {
			const double PI = 3.1415926535;
			double i, angle, x1, y1;
			double o = 2 * PI * r;
			for (i = 0; i < 360; i += (double)360 / o) {
				 angle = i;
				 x1 = this->r * cos(angle * PI / 180);
				 y1 = this->r * sin(angle * PI / 180);
				 lst1.push_back(Circle(this->x + x1, this->y + y1,borderFat, borderColor));
			}
	 }

	 void draw() {
			for (Pixel pix : lst) {
				 //cout << pixel.toString();
				 pix.draw();
			}
			for (Circle rect : lst1) {
				 //cout << pixel.toString();
				 rect.draw();
			}
	 }
};

bool comparator1(float st1, float st2) {
	 return (st1 < st2);
}

bool comparator2(float st1, float st2) {
	 return (st1 > st2);
}

class Line : public Object {
public:
	 int x1;
	 int x2;
	 int y1;
	 int y2;
	 int width;
	 Color color = Color(0, 0, 0, 0);
	 std::vector<Rect> lst;
	 Line(int x1, int y1, int x2, int y2, int width, Color color) {
			this->x1 = x1;
			this->y1 = y1;
			this->x2 = x2;
			this->y2 = y2;
			this->width = width;
			this->color = color;
			init();
	 }

	 void init() {
			float w_diff = x2 - x1; if (w_diff == 0) { w_diff = 1; }
			float h_diff = y2 - y1; if (h_diff == 0) { h_diff = 1; }
			float k = sqrt((w_diff * w_diff) + (h_diff * h_diff));
			float k1 = k / w_diff;
			float h_for_one = sqrt((k1 * k1) - 1);
			float st1 = 0;
			float y = y1;
			auto comp1 = comparator1;
			if (x1 > x2) {
				 comp1 = comparator2;
			}
			auto comp2 = comparator1;
			if (y1 > y2) {
				 comp2 = comparator2;
			}
			
			if (y1 == y2) {
				 if (x1 == x2) {
						lst.push_back(Rect(x1, y1, width, width, this->color));
				 } else{
				 for (float x = x1; comp1(x, x2);) {

						lst.push_back(Rect(x, y1, width, width, this->color));
						if (x1 > x2) {
							 x -= 1;
						} else if (x1 < x2) {
							 x += 1;
						}
				 } }
			} else {
				 for (float x = x1; comp1(x, x2) || (comp2(y, y2)); ) {
						st1 += h_for_one;
						lst.push_back(Rect(x, y, width, width, this->color));
						while ((st1 >= 1) && (comp2(y, y2) || y == y2)) {
							 lst.push_back(Rect(x, y, width, width, this->color));
							 if (y1 > y2) {
									y -= 1;
									st1--;
							 } else if (y1 < y2) {
									st1--;
									y += 1;
							 }

						}
						if (x1 > x2) {
							 x -= 1;
						} else if (x1 < x2) {
							 x += 1;
						}
				 }
			}
	 }


	 string toString() const {
			return "x= " + to_string(x1) + "; y=" + to_string(y1) + "x= " + to_string(x2) + "; y=" + to_string(y2) + "; w=" + to_string(width) + ";\n";
	 }

	 void draw() const {
			for (Rect rect : lst) {
				 //cout << pixel.toString();
				 rect.draw();
			}
	 }

};

