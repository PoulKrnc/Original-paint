// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <thread>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>

#include "Color.h"
#include "Object.h"
#include "font.h"
#include "functions.h"
#include "gesture_detector.h"
using namespace Func;
using namespace std; 
/*!
Changes the display to color
[0] -> Color
*/


int main() {
	 al_init();
	 al_init_font_addon();
	 al_init_ttf_addon();

	 ALLEGRO_DISPLAY* display = al_create_display(1350, 750);

	 //ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 64, 0);
	 Font font1 = Font(20, "arial.ttf", 0);
	 ALLEGRO_EVENT_QUEUE* queue;
	 al_set_app_name("Test");
	 queue = al_create_event_queue();
	 al_install_mouse();
	 al_install_keyboard();
	 al_register_event_source(queue, al_get_keyboard_event_source());
	 al_register_event_source(queue, al_get_display_event_source(display));
	 al_register_event_source(queue, al_get_mouse_event_source());

	 //setups
	 float x = 0, y = 0, x_p = 0, y_p = 0;
	 bool mouseBtn1 = false;
	 int width = al_get_display_width(display);

	 Color dark_blue = Color(20, 20, 240, 255);
	 Color light_blue = Color(100, 100, 240, 255);
	 Color white = Color(255, 255, 255, 255);
	 Color black = Color(1, 1, 1, 255);
	 Color red = Color(255, 20,20,255);

	 Options options = Options(black);

	 vector<Pixel> pixels{};
	 vector<Rect> rectangles{};
	 vector<Line> lines{};
	 vector<RectClickDetector> rect_detectors{};

	 bool mouse_clicked = false;
	 bool pre_safety = false;
	 bool runner = true;
	 int frame_count = 0;
	 al_clear_to_color(white.color);


	 vector<void*> refresh1 = { &white };
	 RectClickDetector rcd = RectClickDetector(clearToColor, refresh1, 0, 0, 100, 30, light_blue, "Refresh", font1, black);
	 rcd.rect.draw();
	 rect_detectors.push_back(rcd);
	 vector<void*> blackPencil = { &black, &options };
	 RectClickDetector btnBlack = RectClickDetector(changePencilColor, blackPencil, 100, 0, 30, 30, black);
	 btnBlack.rect.draw();
	 rect_detectors.push_back(btnBlack);
	 vector<void*> darkBluePencil = {&dark_blue, &options};
	 RectClickDetector btnDarkBlue = RectClickDetector(changePencilColor, darkBluePencil, 130, 0, 30, 30, dark_blue);
	 btnDarkBlue.rect.draw();
	 rect_detectors.push_back(btnDarkBlue);
	 vector<void*> redPencil = { &red, &options };
	 RectClickDetector btnRed = RectClickDetector(changePencilColor, redPencil, 160, 0, 30, 30, red);
	 btnRed.rect.draw();
	 rect_detectors.push_back(btnRed);

	 string runner_code = "";

	 while (runner) {
			ALLEGRO_EVENT event{};
			if (!al_is_event_queue_empty(queue)) {
				 al_wait_for_event(queue, &event);
			}
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				 runner = false;
			}
			if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
				 x = event.mouse.x;
				 y = event.mouse.y;
			}
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				 for (int i = 0; i < rect_detectors.size(); i++) {
						if (rect_detectors[i].isClickDetected(x, y)) {
							 runner_code = rect_detectors[i].func_pointer(rect_detectors[i].func_data1);
							 cout<<runner_code<< endl;
						}
				 }
				 mouse_clicked = true;
			}
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				 mouse_clicked = false;
				 pre_safety = false;
			}

			if (mouse_clicked) {
				 if (pre_safety) {
						Line l = Line(x, y, x_p, y_p, 2, options.selectedColor);
						lines.push_back(l);
						l.draw();
				 }
				 x_p = x;
				 y_p = y;
				 pre_safety = true;
				
			}
			frame_count++;
			al_flip_display();
	 }

	 al_uninstall_mouse();
	 al_uninstall_keyboard();
	 al_destroy_event_queue(queue);
	 al_destroy_display(display);
}


