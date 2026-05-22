#include "player/my_player.hpp"
#include "core/game.hpp"
#include <iostream>

using namespace ttt;

bool check_coords(game::Point a, game::Point b) {
    return (a.x == b.x) && (a.y == b.y);
}

void report(const char* case_name, bool status) {
    std::cout << "Case " << case_name << ": ";
    std::cout << (status ? "OK" : "FAIL") << std::endl;
}

int main() {
    std::cout << "\nMyPlayer Verification\n\n";

    // Scenario A: Direct win opportunity
    {
        game::State::Opts config;
        config.rows = 3;
        config.cols = 3;
        config.win_len = 3;
        config.max_moves = 0;
        
        game::State field(config);
        field.process_move(game::Sign::X, 0, 0);
        field.process_move(game::Sign::O, 0, 1);
        field.process_move(game::Sign::X, 1, 0);

        my_player::MyPlayer agent("Verifier");
        agent.set_sign(game::Sign::X);
        
        game::Point answer = {2, 0};
        game::Point decision = agent.make_move(field);
        report("win_in_one", check_coords(answer, decision));
    }

    // Scenario B: Prevent opponent victory
    {
        game::State::Opts config;
        config.rows = 3;
        config.cols = 3;
        config.win_len = 3;
        config.max_moves = 0;
        
        game::State field(config);
        field.process_move(game::Sign::X, 0, 0);
        field.process_move(game::Sign::O, 0, 1);
        field.process_move(game::Sign::X, 2, 2);
        field.process_move(game::Sign::O, 1, 1);

        my_player::MyPlayer agent("Verifier");
        agent.set_sign(game::Sign::X);
        
        game::Point answer = {2, 1};
        game::Point decision = agent.make_move(field);
        report("block_threat", check_coords(answer, decision));
    }

    // Scenario C: Build own formation
    {
        game::State::Opts config;
        config.rows = 5;
        config.cols = 5;
        config.win_len = 5;
        config.max_moves = 0;
        
        game::State field(config);
        field.process_move(game::Sign::X, 0, 0);
        field.process_move(game::Sign::O, 0, 1);
        field.process_move(game::Sign::X, 1, 0);
        field.process_move(game::Sign::O, 3, 0);
        
        my_player::MyPlayer agent("Verifier");
        agent.set_sign(game::Sign::X);
        
        game::Point movement = agent.make_move(field);
        bool correct = (movement.x == 2 && movement.y == 0);
        report("extend_line", correct);
    }

    // Scenario D: Opening move
    {
        game::State::Opts config;
        config.rows = 5;
        config.cols = 5;
        config.win_len = 4;
        config.max_moves = 0;
        
        game::State field(config);
        
        my_player::MyPlayer agent("Verifier");
        agent.set_sign(game::Sign::X);
        
        game::Point movement = agent.make_move(field);
        bool valid = (movement.x >= 0 && movement.x < 5 && 
                      movement.y >= 0 && movement.y < 5);
        report("first_move_valid", valid);
    }

    std::cout << "\nVerification Complete\n";
    return 0;
}