#pragma once

#include "core/game.hpp"

namespace ttt::my_player {

using game::IPlayer;
using game::Point;
using game::Sign;
using game::State;

class MyPlayer : public IPlayer {
  Sign m_sign = Sign::NONE;
  const char* m_name;

public:
  MyPlayer(const char* name);
  void set_sign(Sign sign) override;
  Point make_move(const State& state) override;
  const char* get_name() const override;

private:
  int count_in_dir(const State& state, int x, int y, int dx, int dy, Sign sign) const;
  int evaluate_cell(const State& state, int x, int y, Sign my_sign, Sign opp_sign) const;
};

}