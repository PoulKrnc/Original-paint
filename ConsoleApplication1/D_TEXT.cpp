
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

using namespace std;

class DText
{
public:
		string text;
		DText() {

		}

		ALLEGRO_FONT* init() {
				ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 64, 0);
				return font;
		}

private:

};


