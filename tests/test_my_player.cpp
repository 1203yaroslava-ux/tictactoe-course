#include "player/my_player.hpp"
#include "core/game.hpp"
#include <iostream>
#include <cmath>

using namespace ttt;

bool compare_points(game::Point a, game::Point b) {
    return a.x == b.x && a.y == b.y;
}

void test_result(const char* name, bool success) {
    std::cout << "Test " << name << ": ";
    if (success) {
        std::cout << "PASSED\n";
    } else {
        std::cout << "FAILED\n";
    }
}

int main() {
    std::cout << "MyPlayer Unit Tests\n";

    // Test 1: win in one move
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

        my_player::MyPlayer bot("TestBot");
        bot.set_sign(game::Sign::X);
        
        game::Point expected = {2, 0};
        game::Point actual = bot.make_move(state);
        test_result("winning_move", compare_points(expected, actual));
    }

    // Test 2: block opponent win
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

        my_player::MyPlayer bot("TestBot");
        bot.set_sign(game::Sign::X);
        
        game::Point expected = {2, 1};
        game::Point actual = bot.make_move(state);
        test_result("block_opponent", compare_points(expected, actual));
    }

    // Test 3: bot extends its own line
    {
        game::State::Opts opts;
        opts.rows = 5;
        opts.cols = 5;
        opts.win_len = 5;
        opts.max_moves = 0;
        
        game::State state(opts);
        state.process_move(game::Sign::X, 0, 0);
        state.process_move(game::Sign::O, 0, 1);
        state.process_move(game::Sign::X, 1, 0);
        state.process_move(game::Sign::O, 3, 0);
        
        my_player::MyPlayer bot("TestBot");
        bot.set_sign(game::Sign::X);
        
        game::Point move = bot.make_move(state);
        bool extends_line = (move.x == 2 && move.y == 0);
        test_result("extend_own_line", extends_line);
    }

    // Test 4: bot chooses any valid first move (not failing)
    {
        game::State::Opts opts;
        opts.rows = 5;
        opts.cols = 5;
        opts.win_len = 4;
        opts.max_moves = 0;
        
        game::State state(opts);
        
        my_player::MyPlayer bot("TestBot");
        bot.set_sign(game::Sign::X);
        
        game::Point move = bot.make_move(state);
        bool valid_move = (move.x >= 0 && move.x < 5 && move.y >= 0 && move.y < 5);
        test_result("valid_first_move", valid_move);
    }

    std::cout << "\nTests completed\n";
    return 0;
}