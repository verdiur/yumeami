/**
 * @file camera.hh
 * @brief Camera control functions
 */

#pragma once
#include "common/raii.hh"
#include "logic/world.hh"
namespace yumeami {

  struct CameraBounds {
    float left;
    float right;
    float top;
    float bottom;
    float width;
    float height;
  };

  /**
   * @brief Update camera target. First calculates target, then clamps depending
   * on bounds. If multiple entities are marked as target, then the camera will
   * only target the first found entity, and the other entities will be ignored.
   *
   * @param world
   * @param vp
   * @param clamp if true, clamp the target to the boundaries of the world. If
   * the world is smaller than the viewport, then the camera will target the
   * center of the world.
   */
  void update_camera(World &world, const SafeRenderTex &vp, bool log = false);

  /**
   * @brief Setup world camera fields. Includes an initial update of the camera.
   * @param world
   * @param vp
   * @param clamp if true, clamp the target to the boundaries of the world
   */
  void setup_camera(World &world, const SafeRenderTex &vp);

  CameraBounds get_camera_bounds(const WorldState &wstate,
                                 const SafeRenderTex &vp);

} // namespace yumeami
