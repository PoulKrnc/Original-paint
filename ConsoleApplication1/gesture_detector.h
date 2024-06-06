#pragma once
#include "Object.h"
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include "Color.h"

class RectClickDetector {
public:
   int x;
   int y;
   int width;
   int height;
   Rect rect;
   string (*func_pointer) (vector<void*> args);
   vector<void*> func_data1{};
   RectClickDetector(string func(vector<void*> args), vector<void*> func_data, int x, int y, int width, int height, Color c) {
      this->x = x;
      this->y = y;
      this->width = width;
      this->height = height;
      this->rect = Rect(x, y, width, height, c);
      this->func_pointer = func;
      for (int i = 0; i < func_data.size(); i++) {
         this->func_data1.push_back(func_data[i]);
      }
   }

   RectClickDetector(string func(vector<void*> args), vector<void*> func_data, int x, int y, int width, int height, Color c, string text, Font font, Color text_color) {
      this->x = x;
      this->y = y;
      this->width = width;
      this->height = height;
      this->rect = Rect(x, y, width, height, c, text, font, text_color);
      this->func_pointer = func;
      for (int i = 0; i < func_data.size(); i++) {
         this->func_data1.push_back(func_data[i]);
      }
   }

   RectClickDetector(string func(vector<void*> args), vector<void*> func_data, int x, int y, Color c, string text, Font font, Color text_color) {
      this->x = x;
      this->y = y;
      this->width = (font.size) * text.length() / 2;
      this->height = font.size;
      this->rect = Rect(x, y, c, text, font, text_color);
      this->func_pointer = func;
      for (int i = 0; i < func_data.size(); i++) {
         this->func_data1.push_back(func_data[i]);
      }
   }

   bool isClickDetected(int x, int y) {
      if (x >= this->x && x <= (this->x + this->width) && y >= this->y && y <= (this->y + this->height)) {
         return true;
      }
      return false;
   }
};