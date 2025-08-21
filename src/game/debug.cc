#include "game/debug.hh"
#include "entt/entity/fwd.hpp"
#include "game/components.hh"
#include "game/movement.hh"
#include "game/texture.hh"
#include "game/world.hh"
#include "raylib.h"


yumeami::World yumeami::debug::create_player_test_world() {
  World world = create_world();
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
  World world = create_world(30, 40);
  entt::entity player = world.registry.create();
  world.registry.emplace<TrueTilePos>(player, 0, 0);
  world.registry.emplace<DrawTilePos>(player, 0.0f, 0.0f);
  world.registry.emplace<Velocity>(player, 0.4);
  world.registry.emplace<Movement>(player);
  world.registry.emplace<Facing>(player, Direction4::LEFT);
  world.registry.emplace<PlayerTag>(player);

  Texture spritesheet_texture = LoadTexture("assets/test_spritesheet.png");
  auto spritesheet = create_spritesheet_ptr(spritesheet_texture, {16, 16});

  world.spritesheets.push_back(spritesheet);

  for (int r = 0; r < spritesheet->rows; r++) {
    for (int c = 0; c < spritesheet->columns; c++) {
      entt::entity sprite = world.registry.create();
      world.registry.emplace<DrawTilePos>(sprite, (float)c, (float)r);
      world.registry.emplace<Sprite>(sprite, world.spritesheets.back(), r, c);
    }
  }

  return world;
}


yumeami::World yumeami::debug::create_collision_test_world() {
  World world = create_world();
  entt::entity player = world.registry.create();
  world.registry.emplace<TrueTilePos>(player, 0, 0);
  world.registry.emplace<DrawTilePos>(player, 0.0f, 0.0f);
  world.registry.emplace<Velocity>(player, 0.4);
  world.registry.emplace<Movement>(player);
  world.registry.emplace<Facing>(player, Direction4::LEFT);
  world.registry.emplace<PlayerTag>(player);

  entt::entity coll = world.registry.create();
  world.registry.emplace<TrueTilePos>(coll, 3, 4);
  world.registry.emplace<DrawTilePos>(coll, 3.0f, 4.0f);
  world.collision.get_static_cell(3, 4) = 1;

  return world;
}
