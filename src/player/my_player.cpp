#include "my_player.hpp"

namespace ttt::my_player {

MyPlayer::MyPlayer(const char* id) : player_id(id) {}

void MyPlayer::set_sign(Sign sign) { 
    player_sign = sign; 
}

const char* MyPlayer::get_name() const { 
    return player_id; 
}

int MyPlayer::scan_direction(const State& state, int col, int row, int step_x, int step_y, Sign target) const {
    int counter = 0;
    int needed = state.get_opts().win_len;
    
    for (int step = 1; step < needed; ++step) {
        int new_col = col + step_x * step;
        int new_row = row + step_y * step;
        
        if (new_col < 0 || new_row < 0 || 
            new_col >= state.get_opts().cols || 
            new_row >= state.get_opts().rows) {
            break;
        }
        
        if (state.get_value(new_col, new_row) == target) {
            ++counter;
        } else {
            break;
        }
    }
    return counter;
}

int MyPlayer::rank_position(const State& state, int col, int row, Sign me, Sign enemy) const {
    int total_score = 0;
    int win_len = state.get_opts().win_len;
    const int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (int d = 0; d < 4; ++d) {
        int dx = directions[d][0];
        int dy = directions[d][1];

        int my_streak = 1 + scan_direction(state, col, row, dx, dy, me)
                           + scan_direction(state, col, row, -dx, -dy, me);

        int enemy_streak = 1 + scan_direction(state, col, row, dx, dy, enemy)
                             + scan_direction(state, col, row, -dx, -dy, enemy);

        // Критические ситуации
        if (my_streak >= win_len) total_score += 100000;
        if (enemy_streak >= win_len) total_score += 50000;
        
        // Опасные приближения
        if (my_streak == win_len - 1) total_score += 5000;
        if (my_streak == win_len - 2) total_score += 500;
        if (enemy_streak == win_len - 1) total_score += 4000;
        if (enemy_streak == win_len - 2) total_score += 400;
        
        // Базовые очки
        total_score += my_streak * 10;
        total_score += enemy_streak * 5;
    }
    return total_score;
}

Point MyPlayer::make_move(const State& game_state) {
    int best_value = -1;
    Point chosen = {0, 0};
    int width = game_state.get_opts().cols;
    int height = game_state.get_opts().rows;
    Sign opponent = (player_sign == Sign::X) ? Sign::O : Sign::X;

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (game_state.get_value(col, row) != Sign::NONE) {
                continue;
            }

            int current_rank = rank_position(game_state, col, row, player_sign, opponent);

            if (current_rank > best_value) {
                best_value = current_rank;
                chosen = {col, row};
            }
        }
    }
    return chosen;
}

}