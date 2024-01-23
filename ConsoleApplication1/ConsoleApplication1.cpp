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
using namespace std; 

int main() {
	 al_init();
	 al_init_font_addon();
	 al_init_ttf_addon();

	 ALLEGRO_DISPLAY* display = al_create_display(740, 580);
	 ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 64, 0);
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
	 Color white = Color(255, 255, 255, 255);
	 Color black = Color(1, 1, 1, 255);

	 vector<Pixel> pixels{};
	 vector<Rect> rectangles{};
	 vector<Line> lines{};

	

	 bool mouse_clicked = false;
	 bool pre_safety = false;
	 bool runner = true;
	 int frame_count = 0;
	 //al_clear_to_color(white.color);
	 while (runner) {
			
			/*if (frame_count % 10 == 0) {
				 for (Pixel pixel : pixels) {
						pixel.draw();
				 }
			}

			if (frame_count % 100 == 0) {
				 for (Line line : lines) {
						line.draw();
				 }
			}

			if (frame_count >= 0) {
				 for (Rect rect : rectangles) {
						rect.draw();
				 }
			}*/

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
				 mouse_clicked = true;
			}
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				 mouse_clicked = false;
				 pre_safety = false;
			}

			if (mouse_clicked) {
				 if (pre_safety) {
						Line l = Line(x, y, x_p, y_p, 2, dark_blue);
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
	 al_destroy_font(font);

}

