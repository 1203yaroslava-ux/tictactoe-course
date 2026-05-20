#include "my_player.hpp"

namespace ttt::my_player {

MyPlayer::MyPlayer(const char* name) : m_name(name) {}

void MyPlayer::set_sign(Sign sign) { m_sign = sign; }

const char* MyPlayer::get_name() const { return m_name; }

int MyPlayer::count_in_dir(const State& state, int x, int y, int dx, int dy, Sign sign) const {
    int count = 0;
    int win_len = state.get_opts().win_len;
    for (int i = 1; i < win_len; ++i) {
        int nx = x + dx * i;
        int ny = y + dy * i;
        if (nx < 0 || ny < 0 || nx >= state.get_opts().cols || ny >= state.get_opts().rows)
            break;
        if (state.get_value(nx, ny) == sign)
            ++count;
        else
            break;
    }
    return count;
}

int MyPlayer::evaluate_cell(const State& state, int x, int y, Sign my_sign, Sign opp_sign) const {
    int score = 0;
    int win_len = state.get_opts().win_len;
    const int dirs[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (int i = 0; i < 4; ++i) {
        int dx = dirs[i][0];
        int dy = dirs[i][1];

        int my_len = 1 + count_in_dir(state, x, y, dx, dy, my_sign)
                       + count_in_dir(state, x, y, -dx, -dy, my_sign);

        int opp_len = 1 + count_in_dir(state, x, y, dx, dy, opp_sign)
                         + count_in_dir(state, x, y, -dx, -dy, opp_sign);

        if (my_len >= win_len) score += 100000;
        if (opp_len >= win_len) score += 50000;
        if (my_len == win_len - 1) score += 5000;
        if (my_len == win_len - 2) score += 500;
        if (opp_len == win_len - 1) score += 4000;
        if (opp_len == win_len - 2) score += 400;
        
        score += my_len * 10;
        score += opp_len * 5;
    }
    return score;
}

Point MyPlayer::make_move(const State& state) {
    int max_score = -1;
    Point best_move = {0, 0};
    int cols = state.get_opts().cols;
    int rows = state.get_opts().rows;
    Sign opp_sign = (m_sign == Sign::X) ? Sign::O : Sign::X;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (state.get_value(x, y) != Sign::NONE)
                continue;

            int score = evaluate_cell(state, x, y, m_sign, opp_sign);

            if (score > max_score) {
                max_score = score;
                best_move = {x, y};
            }
        }
    }
    return best_move;
}

}