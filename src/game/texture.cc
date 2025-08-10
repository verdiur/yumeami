#include "texture.hh"
#include "raylib.h"


Rectangle yumeami::calc_spritesheet_rec(int row_index, int column_index,
                                        const Spritesheet &spritesheet) {
  return Rectangle{static_cast<float>(column_index * spritesheet.sprite_size.x),
                   static_cast<float>(row_index * spritesheet.sprite_size.y),
                   static_cast<float>(spritesheet.sprite_size.x),
                   static_cast<float>(spritesheet.sprite_size.y)};
}


Rectangle yumeami::calc_spritesheet_rec(const Sprite &sprite) {
  return Rectangle{
      .x = static_cast<float>(sprite.column_index * sprite.spritesheet->sprite_size.x),
      .y = static_cast<float>(sprite.row_index * sprite.spritesheet->sprite_size.y),
      .width = static_cast<float>(sprite.spritesheet->sprite_size.x),
      .height = static_cast<float>(sprite.spritesheet->sprite_size.y)};
}
