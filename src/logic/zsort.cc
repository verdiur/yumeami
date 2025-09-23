#include "logic/zsort.hh"
#include "entt/entt.hpp"
#include "logic/components.hh"


bool yumeami::ZSort::operator<(const ZSort &other) const {
  int this_elevation = (elevation) ? *elevation : 0;
  float this_y = (draw_pos) ? (float)draw_pos->y : 0;

  int other_elevation = (other.elevation) ? *other.elevation : 0;
  float other_y = (other.draw_pos) ? (float)other.draw_pos->y : 0;

  if (this_elevation != other_elevation)
    return this_elevation < other_elevation;

  return this_y < other_y;
}


bool yumeami::emplace_zsort(entt::registry &reg, entt::entity ent) {
  Elevation *elevation = reg.try_get<Elevation>(ent);
  DrawPos *draw_pos = reg.try_get<DrawPos>(ent);

  reg.emplace<ZSort>(ent, elevation, draw_pos);
  return (elevation && draw_pos);
}
