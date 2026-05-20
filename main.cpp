#include "core/game.hpp"
#include "player/my_player.hpp"
#include "player/my_observer.hpp"
#include "core/baseline.hpp"
#include <iostream>
#include <chrono>

using namespace ttt;

int main() {
    game::State::Opts opts;
    opts.rows = 10;
    opts.cols = 10;
    opts.win_len = 5;
    opts.max_moves = 0;

    game::Game game(opts);

    auto my_bot = new my_player::MyPlayer("MySmartBot");
    auto enemy_bot = baseline::get_easy_player("EasyBot");
    auto logger = new my_player::ConsoleWriter();

    game.add_observer(logger);
    game.add_player(game::Sign::X, my_bot);
    game.add_player(game::Sign::O, enemy_bot);

    while (game.get_state().get_status() != game::Status::ENDED) {
        game::Sign current = game.get_state().get_current_player();
        
        auto start = std::chrono::high_resolution_clock::now();
        game::MoveResult result = game.process();
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
        std::cout << "Player " << (current == game::Sign::X ? "X" : "O")
                  << " move time: " << elapsed << " ms\n";

        my_player::ConsoleWriter::print_game_state(game.get_state());

        if (game::is_dq(result)) break;
    }

    delete my_bot;
    delete logger;
    delete enemy_bot;
    
    return 0;
}