#include "core/game.hpp"
#include "player/my_player.hpp"
#include "player/my_observer.hpp"
#include "core/baseline.hpp"
#include <iostream>
#include <chrono>

using namespace ttt;

int main() {
    game::State::Opts settings;
    settings.rows = 10;
    settings.cols = 10;
    settings.win_len = 5;
    settings.max_moves = 0;

    game::Game match(settings);

    auto first_player = new my_player::MyPlayer("SmartAgent");
    auto second_player = baseline::get_easy_player("RandomBot");
    auto display = new my_player::ConsoleWriter();

    match.add_observer(display);
    match.add_player(game::Sign::X, first_player);
    match.add_player(game::Sign::O, second_player);

    while (match.get_state().get_status() != game::Status::ENDED) {
        game::Sign turn = match.get_state().get_current_player();
        
        auto start_time = std::chrono::high_resolution_clock::now();
        game::MoveResult outcome = match.process();
        auto end_time = std::chrono::high_resolution_clock::now();

        double duration = std::chrono::duration<double, std::milli>(end_time - start_time).count();
        std::cout << "Turn " << (turn == game::Sign::X ? "X" : "O")
                  << " completed in " << duration << " ms\n";

        my_player::ConsoleWriter::print_game_state(match.get_state());

        if (game::is_dq(outcome)) break;
    }

    delete first_player;
    delete display;
    delete second_player;
    
    return 0;
}