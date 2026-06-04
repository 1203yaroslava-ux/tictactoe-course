#include "my_field_initializer.hpp"
#include "core/state.hpp"  

namespace ttt::my_player {
using game::Sign;

void MyFieldInitializer::initialize(FieldBitmap &field) {
    int mid_row = (field.get_rows()-1) / 2; 
    
    for (int col = 0; col < field.get_cols(); ++col) {
        field.set(col, mid_row, Sign::WALL);  
    }
}

IFieldInitializer* MyFieldInitializer::clone() const {
    return new MyFieldInitializer(*this);
}
}