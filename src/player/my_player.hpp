
#pragma once

#include "core/game.hpp"

namespace ttt::my_player {

using game::IPlayer;
using game::Point;
using game::Sign;
using game::State;

class MyPlayer : public IPlayer {
private:
  Sign player_sign = Sign::NONE;
  const char* player_id;

public:
  MyPlayer(const char* id);
  void set_sign(Sign sign) override;
  Point make_move(const State& game_state) override;
  const char* get_name() const override;

private:
  int scan_direction(const State& state, int col, int row, int step_x, int step_y, Sign target) const;
  int rank_position(const State& state, int col, int row, Sign me, Sign enemy) const;
};

}
