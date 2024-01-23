#pragma once

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Font {
public:
   float size;
   const char* filename;
   int flags;
   const ALLEGRO_FONT* font;
   Font() {
      size = 10;
      filename = "arial.ttf";
      flags = 0;
      font = al_load_ttf_font(filename, size, flags);
   }
   Font(float size, const char* filename, int flags) {
      this->size = size;
      this->filename = filename;
      this->flags = flags;
      font = al_load_ttf_font(filename, size, flags);
   }
};