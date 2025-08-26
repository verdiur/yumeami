#include "world_io.hh"
#include "common/direction.hh"
#include "entt/entity/fwd.hpp"
#include "game/components.hh"
#include "game/movement.hh"
#include "game/texture.hh"
#include "game/world.hh"
#include "raylib.h"
#include "rfl/json/read.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <optional>


/* IMPL *********************************************************************************/


bool yumeami::impl::load_spritesheets(World &world, const WorldSpec &spec,
                                      const std::filesystem::path root) {
  for (auto const &[sheet_id, sheet_spec] : spec.spritesheets.get()) {

    std::filesystem::path sheet_path = root / sheet_spec.path.get();
    Texture sheet_texture = LoadTexture(sheet_path.c_str());

    if (!IsTextureValid(sheet_texture)) {
      unload_world_textures(world);
      spdlog::error("failed to load world: failed to load texture {}",
                    sheet_path.string());
      return false;
    }

    auto sheet_ptr = create_spritesheet_ptr(
        sheet_texture, {sheet_spec.sprite_height.get(), sheet_spec.sprite_width.get()});
    world.spritesheets[sheet_id] = sheet_ptr;
  }
  return true;
}


bool yumeami::impl::load_tiles(World &world, const WorldSpec &spec) {
  for (TileInstance tile : spec.tile_data.get()) {

    TilePrefab prefab = spec.tile_prefabs.get().at(tile.prefab_id.get());
    std::shared_ptr<Spritesheet> sheet_ptr;
    try {
      sheet_ptr = world.spritesheets.at(prefab.spritesheet_id.get());
    } catch (std::out_of_range e) {
      spdlog::warn(
          "could not load entity (entity will be ignored, world loading will carry on)");
      return false; // proceed.
    }
    int x = tile.x.get();
    int y = tile.y.get();

    auto entity = world.registry.create();
    world.registry.emplace<TrueTilePos>(entity, x, y);
    world.registry.emplace<DrawTilePos>(entity, static_cast<tile_float>(x),
                                        static_cast<tile_float>(y));
    world.registry.emplace<Sprite>(entity, sheet_ptr, prefab.sprite_row.get(),
                                   prefab.sprite_column.get());

    if (prefab.solid.get()) {
      world.collision.get_static_cell(x, y) = 1;
    }
  }
  return true;
}


/* PUBLIC *******************************************************************************/


std::optional<yumeami::WorldSpec> yumeami::parse_world(std::filesystem::path root) {
  std::filesystem::path cfg_path = root / "world.json";
  spdlog::info(cfg_path.string());

  if (!std::filesystem::exists(cfg_path)) {
    spdlog::error("root folder should contain world.json file");
    return std::nullopt;
  }

  char *buf = LoadFileText(cfg_path.c_str());
  if (!buf) {
    spdlog::error("could not load world.json");
    return std::nullopt;
  }

  spdlog::info(buf);

  auto parse_result = rfl::json::read<yumeami::WorldSpec>(buf);
  if (!parse_result) {
    spdlog::error("could not parse world.json");
    UnloadFileText(buf);
    return std::nullopt;
  }

  UnloadFileText(buf);
  return parse_result.value();
}


std::optional<yumeami::World> yumeami::load_world(const WorldSpec &spec,
                                                  const std::filesystem::path root) {
  // create world
  World world = create_world(spec.width.get(), spec.height.get(), spec.tile_size.get(),
                             spec.spx_multiplier.get());

  if (!impl::load_spritesheets(world, spec, root)) {
    return std::nullopt;
  }

  // load tiles
  impl::load_tiles(world, spec);

  // TODO: load npcs

  // load player
  // TODO: improve
  auto player = world.registry.create();
  world.registry.emplace<PlayerTag>(player);
  world.registry.emplace<TrueTilePos>(player, 0, 0);
  world.registry.emplace<DrawTilePos>(player, static_cast<tile_float>(0),
                                      static_cast<tile_float>(0));
  world.registry.emplace<Velocity>(player, 0.4f);
  world.registry.emplace<Movement>(player);
  world.registry.emplace<Facing>(player, Direction4::LEFT);

  return world;
}
