#include "io/io.hh"
#include "common/units.hh"
#include "entt/entity/fwd.hpp"
#include "game/collision.hh"
#include "game/components.hh"
#include "game/texture.hh"
#include "game/world.hh"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include <expected>
#include <glaze/json/read.hpp>

/* IMPL *********************************************************************************/

void yumeami::impl::add_collision_tag_to_entity(World &world, const entt::entity entity) {
  // try to get true position
  auto true_pos = world.registry.try_get<TrueTilePos>(entity);
  if (!true_pos) {
    spdlog::error("entity does not have necessary TrueTilePos component");
    return;
  }

  // get collision cell
  int &collision_cell = world.collision.get_static_cell(true_pos->x, true_pos->y);

  // check if collision state is valid
  if (world.registry.all_of<CollisionTag>(entity)) {
    spdlog::info("entity already has a collision flag");
    // if collision cell is invalid, repair
    if (collision_cell == 0) {
      spdlog::info("fixed malformed collision grid");
      collision_cell++;
    }
    return;
  }

  // emplace and update grid
  world.registry.emplace<CollisionTag>(entity);
  collision_cell++;
}


void yumeami::impl::add_tile_to_world_from_tilespec(World &world,
                                                    const TileSpec &tile_spec, tile_int x,
                                                    tile_int y) {
  entt::entity tile = world.registry.create();
  world.registry.emplace<TrueTilePos>(tile, (int)x, (int)y);
  world.registry.emplace<DrawTilePos>(tile, (float)x, (float)y);
  world.registry.emplace<Sprite>(tile, world.spritesheets.at(tile_spec.spritesheet_id),
                                 tile_spec.sprite_row_index,
                                 tile_spec.sprite_column_index);
  if (tile_spec.solid) {
    add_collision_tag_to_entity(world, tile);
  }
}


std::expected<entt::entity, yumeami::ParseError>
yumeami::impl::add_player_to_world(World &world, tile_int x, tile_int y) {

  if (world.registry.view<PlayerTag>()->size() > 0) {
    spdlog::error("player already exists");
    return std::unexpected(ParseError::EXISTS);
  }

  entt::entity player = world.registry.create();
  world.registry.emplace<TrueTilePos>(player, (int)x, (int)y);
  world.registry.emplace<DrawTilePos>(player, (float)x, (float)y);
  // TODO: add player sprite
  add_collision_tag_to_entity(world, player);
  world.registry.emplace<PlayerTag>(player);

  return player;
}

/* PUBLIC *******************************************************************************/

std::expected<yumeami::World, yumeami::ParseError>
yumeami::parse_world(std::string buffer) {

  auto read_result = glz::read_json<WorldSpec>(buffer);
  if (!read_result) {
    spdlog::error("failed to parse world: JSON_ERR");
    return std::unexpected(ParseError::JSON_ERR);
  }

  // create world
  WorldSpec world_spec = read_result.value();
  World world = create_world(world_spec.width, world_spec.height, world_spec.tile_size,
                             world_spec.spx_multiplier);

  // add spreadsheets
  for (SpritesheetSpec sheet_spec : world_spec.spritesheets) {

    // TODO: resolve path better

    Texture texture = LoadTexture(sheet_spec.path.c_str());
    if (IsTextureValid(texture)) {
      unload_world_textures(world);
      spdlog::error("failed to parse world: TEXTURE_ERR for path {}", sheet_spec.path);
      return std::unexpected(ParseError::TEXTURE_ERR);
    }

    auto sheet = create_spritesheet_ptr(
        texture, {sheet_spec.sprite_height, sheet_spec.sprite_width});
    world.spritesheets.push_back(sheet);
  }

  return world;
}
