#include "logic/emplace.hh"
#include "logic/components.hh"


bool yumeami::emplace_zorder(WorldState &wstate, entt::entity ent) {
  DrawPos *draw_pos = wstate.reg.try_get<DrawPos>(ent);
  Elevation *elevation = wstate.reg.try_get<Elevation>(ent);
  Floor *floor = wstate.reg.try_get<Floor>(ent);

  wstate.reg.emplace<ZOrder>(ent, draw_pos, elevation, floor);
  return (draw_pos && elevation && floor);
}
