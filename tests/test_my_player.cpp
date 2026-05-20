#include "player/my_player.hpp"
#include "core/game.hpp"
#include <iostream>

using namespace ttt;

void assert_move(const char* name, game::Point expected, game::Point actual) {
    std::cout << "[TEST] " << name << ": ";
    if (expected.x == actual.x && expected.y == actual.y)
        std::cout << "PASSED\n";
    else
        std::cout << "FAILED (expected " << expected.x << "," << expected.y
                  << " got " << actual.x << "," << actual.y << ")\n";
}

int main() {
    std::cout << "--- MyPlayer Unit Tests ---\n";

    // Тест 1: победа
    {
        game::State::Opts opts;
        opts.rows = 3;
        opts.cols = 3;
        opts.win_len = 3;
        opts.max_moves = 0;
        
        game::State state(opts);
        state.process_move(game::Sign::X, 0, 0);
        state.process_move(game::Sign::O, 0, 1);
        state.process_move(game::Sign::X, 1, 0);

        my_player::MyPlayer p("Test");
        p.set_sign(game::Sign::X);
        
        game::Point expected = {2, 0};
        game::Point actual = p.make_move(state);
        assert_move("Winning move", expected, actual);
    }

    // Тест 2: блокировка
    {
        game::State::Opts opts;
        opts.rows = 3;
        opts.cols = 3;
        opts.win_len = 3;
        opts.max_moves = 0;
        
        game::State state(opts);
        state.process_move(game::Sign::X, 0, 0);
        state.process_move(game::Sign::O, 0, 1);
        state.process_move(game::Sign::X, 2, 2);
        state.process_move(game::Sign::O, 1, 1);

        my_player::MyPlayer p("Test");
        p.set_sign(game::Sign::X);
        
        game::Point expected = {2, 1};
        game::Point actual = p.make_move(state);
        assert_move("Block opponent", expected, actual);
    }

    std::cout << "\n--- All tests done ---\n";
    return 0;
}