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
		float x = 0, y = 0;
		bool mouseBtn1 = false;
		int width = al_get_display_width(display);
		
		Color blue = Color(20, 20, 240, 1);
		Color white = Color(255, 255, 255, 1);

		vector<Pixel> pixels{};
		for (int i = 0; i <= 40; i++) {
				pixels.push_back(Pixel(301 + i, 301 + i, blue));
		}

		Rect r = Rect(200, 200, 100, 100, white);

		Pixel p = Pixel(110, 110, white);

		bool runner = true;
		while (runner) {
				

				al_clear_to_color(al_map_rgba_f(0, 0, 0, 1));
				al_draw_pixel(100, 100, al_map_rgb(255, 255, 255));
				al_draw_text(font, blue.color, 20, 20, 0, "David je GEJ");

				r.draw();


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
						cout << "event" << "\n";
						cout << event.mouse.x << " " << event.mouse.y << "\n";
						al_draw_pixel(static_cast<float>(event.mouse.x), static_cast<float>(event.mouse.y), al_map_rgb(255, 255, 255));
				}
				
				al_flip_display();
		}
		
		al_uninstall_mouse();
		al_uninstall_keyboard();
		al_destroy_event_queue(queue);
		al_destroy_display(display);
		al_destroy_font(font);
		
}

