#pragma once
#include "common/units/fwd.hh"
#include "model/viewport/fwd.hh"
#include "model/world/fwd.hh"
#include <memory>
namespace yumeami {

  struct WorldBuilder {
  private:
    std::unique_ptr<World> world_;

  public:
    WorldBuilder(int width, int height, const Viewport &vp);
    WorldBuilder &build_config(tx tile_size, bool wrap, bool clamp_camera);
    WorldBuilder &build_resources();
    World world();
  };

  /**
   * @brief Setup collision grid of world. Does not check if the grid is blank.
   * For each entity with a collision tag, it increments the corresponding
   * position on the grid. This function is meant to be run after all collidable
   * entities have been spawned.
   *
   * @param world
   */
  void setup_world_collision(World &world);

} // namespace yumeami
