#pragma once
#include <iostream>
#include <string>
#include "Color.h"
using namespace std;

namespace Func {

	 class Options {
	 public:
			Color selectedColor = Color(255, 255, 255, 255);
			Options(Color c) {
				 selectedColor = c;
			}
	 };

	 /*[0]->Color*/
	 string clearToColor(vector<void*> args) {
			Color c = (*((Color*)args[0]));
			al_clear_to_color(c.color);
			al_flip_display();
			return "c-CLEARED";
	 }

	 /*
	 [0]->Color
	 [1]->Options
	 */
	 string changePencilColor(vector<void*> args) {
			Color* c = ((Color*)args[0]);
			Options* o = ((Options*)args[1]);
			o->selectedColor = *c;
			return "c-COLOR_CHANGED";
	 }
};