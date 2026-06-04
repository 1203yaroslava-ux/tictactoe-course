#pragma once
#include "core/field.hpp"

namespace ttt::my_player {
using game::IFieldInitializer;
using game::FieldBitmap;

class MyFieldInitializer : public IFieldInitializer {
public:
    void initialize(FieldBitmap &field) override;
    IFieldInitializer* clone() const override;
};
}