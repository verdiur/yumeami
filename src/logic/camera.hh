#pragma once
#include "common/raii.hh"
#include "logic/world.hh"
namespace yumeami {

  /**
   * @brief Update camera target. First calculates target, then clamps depending
   * on bounds. If multiple entities are marked as target, then the camera will
   * only target the first found entity, and the other entities will be ignored.
   *
   * @param world
   * @param vp
   * @param clamp if true, clamp the target to the boundaries of the world
   */
  void update_camera(World &world, const SafeRenderTex &vp, bool clamp,
                     bool log = false);

  /**
   * @brief Setup world camera fields. Includes an initial update of the camera.
   * @param world
   * @param vp
   * @param clamp if true, clamp the target to the boundaries of the world
   */
  void setup_camera(World &world, const SafeRenderTex &vp, bool clamp);

} // namespace yumeami
