#include "game/debug.hh"
#include "game/components.hh"
#include "game/movement.hh"
#include "game/texture.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <memory>

yumeami::World yumeami::debug::create_player_test_world() {
  World world = {.width = 40, .height = 30};
  entt::entity player = world.registry.create();
  world.registry.emplace<TrueTilePos>(player, 0, 0);
  world.registry.emplace<DrawTilePos>(player, 0.0f, 0.0f);
  world.registry.emplace<Velocity>(player, 0.4);
  world.registry.emplace<Movement>(player);
  world.registry.emplace<Facing>(player, Direction4::LEFT);
  world.registry.emplace<PlayerTag>(player);

  return world;
}


yumeami::World yumeami::debug::create_spritesheet_test_world() {
  // TODO:
  World world = {.width = 40, .height = 30};
  entt::entity player = world.registry.create();
  world.registry.emplace<TrueTilePos>(player, 0, 0);
  world.registry.emplace<DrawTilePos>(player, 0.0f, 0.0f);
  world.registry.emplace<Velocity>(player, 0.4);
  world.registry.emplace<Movement>(player);
  world.registry.emplace<Facing>(player, Direction4::LEFT);
  world.registry.emplace<PlayerTag>(player);

  Texture spritesheet_texture = LoadTexture("assets/testsprite.png");
  auto spritesheet = create_spritesheet_ptr(spritesheet_texture, {16, 16});

  world.spritesheets.push_back(spritesheet);

  for (int r = 0; r < spritesheet->rows; r++) {
    for (int c = 0; c < spritesheet->columns; c++) {
      entt::entity sprite = world.registry.create();
      spdlog::info("{}, {}", r, c);
      world.registry.emplace<DrawTilePos>(sprite, (float)r, (float)c);
      world.registry.emplace<Sprite>(sprite, world.spritesheets.back(), r, c);
    }
  }

  return world;
}
