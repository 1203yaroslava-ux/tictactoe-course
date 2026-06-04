#include "player/my_field_initializer.hpp"
#include "core/state.hpp"
#include "player/my_observer.hpp"
#include <iostream>

using namespace ttt;

int main() {
    game::State::Opts config;
    config.rows = 10;
    config.cols = 10;
    config.win_len = 5;
    config.max_moves = 0;
    
    my_player::MyFieldInitializer initializer;
    game::State field(config, &initializer);  
    
    my_player::ConsoleWriter::print_game_state(field);  
    
    return 0;
}