#include "coin.hh"
#include "utils.hh"
using namespace pro2;
using namespace std;

int Coin::spin_counter_ = spin_vel_;

Coin::Coin(pro2::Pt pos)
    : left_(pos.x), top_(pos.y), right_(pos.x + width), bottom_ (pos.y + width),
    alive_(true) {}

void Coin::update_spin() {
    --spin_counter_;
    if (spin_counter_ <= 0) spin_counter_ = spin_vel_;
}

void Coin::unalive() {
    alive_ = false;
}

void Coin::paint(pro2::Window& window) const {
    if (alive_) {
    if (spin_counter_ > spin_vel_*(0.875))
        paint_sprite(window, {left_, top_}, coin_texture_1_);
    else if (spin_counter_ > spin_vel_*(0.75))
        paint_sprite(window, {left_, top_}, coin_texture_2_);
    else if (spin_counter_ > spin_vel_*(0.625))
        paint_sprite(window, {left_, top_}, coin_texture_3_);
    else if (spin_counter_ > spin_vel_*(0.5))
        paint_sprite(window, {left_, top_}, coin_texture_4_);
    else if (spin_counter_ > spin_vel_*(0.375))
        paint_sprite(window, {left_, top_}, coin_texture_5_);
    else if (spin_counter_ > spin_vel_*(0.25))
        paint_sprite(window, {left_, top_}, coin_texture_4_);
    else if (spin_counter_ > spin_vel_*(0.125))
        paint_sprite(window, {left_, top_}, coin_texture_3_);
    else 
        paint_sprite(window, {left_, top_}, coin_texture_2_);
    }
}


const int _ = -1; //transparent
const int b = 0x000000; //black
const int w = 0xffffff; //white
const int g = 0xfff93d; //gold
const int y = 0xfadd00; //yellow
const int o = 0xe0ac12; //orange

const vector<vector<int>> Coin::coin_texture_1_ = {
    {_, _, _, _, b, b, b, b, _, _, _, _},
    {_, _, b, b, w, w, w, w, b, b, _, _},
    {_, b, w, w, y, y, y, y, y, o, b, _},
    {_, b, w, y, g, w, w, g, y, o, b, _},
    {b, w, y, g, w, g, y, b, g, y, o, b},
    {b, w, y, g, w, g, y, b, g, y, o, b},
    {b, w, y, g, w, g, y, b, g, y, o, b},
    {b, w, y, g, w, g, y, b, g, y, o, b},
    {b, w, y, g, w, g, y, b, g, y, o, b},
    {b, w, y, g, w, g, y, b, g, y, o, b},
    {b, w, y, g, w, y, y, b, g, y, o, b},
    {b, w, y, g, w, y, y, b, g, y, o, b},
    {_, b, y, g, g, b, b, g, y, o, b, _},
    {_, b, y, y, y, y, y, y, o, o, b, _},
    {_, _, b, b, o, o, o, o, b, b, _, _},
    {_, _, _, _, b, b, b, b, _, _, _, _},
};

const vector<vector<int>> Coin::coin_texture_2_ = {
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, b, b, w, w, b, b, _, _, _},
    {_, _, b, w, w, y, y, y, o, b, _, _},
    {_, _, b, w, y, g, g, y, o, b, _, _},
    {_, b, w, y, g, w, b, g, y, o, b, _},
    {_, b, w, y, g, w, b, g, y, o, b, _},
    {_, b, w, y, g, w, b, g, y, o, b, _},
    {_, b, w, y, g, w, b, g, y, o, b, _},
    {_, b, w, y, g, w, b, g, y, o, b, _},
    {_, b, w, y, g, w, b, g, y, o, b, _},
    {_, b, w, y, g, w, b, g, y, o, b, _},
    {_, b, w, y, g, w, b, g, y, o, b, _},
    {_, _, b, y, g, g, g, y, o, b, _, _},
    {_, _, b, y, y, y, y, o, o, b, _, _},
    {_, _, _, b, b, o, o, b, b, _, _, _},
    {_, _, _, _, b, b, b, b, _, _, _, _},
};

const vector<vector<int>> Coin::coin_texture_3_ = {
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, b, w, w, b, _, _, _, _},
    {_, _, _, b, w, y, y, o, b, _, _, _},
    {_, _, _, b, w, g, g, o, b, _, _, _},
    {_, _, b, w, y, w, b, y, o, b, _, _},
    {_, _, b, w, y, w, b, y, o, b, _, _},
    {_, _, b, w, y, w, b, y, o, b, _, _},
    {_, _, b, w, y, w, b, y, o, b, _, _},
    {_, _, b, w, y, w, b, y, o, b, _, _},
    {_, _, b, w, y, w, b, y, o, b, _, _},
    {_, _, b, w, y, w, b, y, o, b, _, _},
    {_, _, b, w, y, w, b, y, o, b, _, _},
    {_, _, _, b, y, g, g, o, b, _, _, _},
    {_, _, _, b, y, y, y, o, b, _, _, _},
    {_, _, _, _, b, o, o, b, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
};

const vector<vector<int>> Coin::coin_texture_4_ = {
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, b, w, w, b, _, _, _, _},
    {_, _, _, _, b, y, y, b, _, _, _, _},
    {_, _, _, _, b, g, g, b, _, _, _, _},
    {_, _, _, b, w, g, y, o, b, _, _, _},
    {_, _, _, b, w, g, y, o, b, _, _, _},
    {_, _, _, b, w, g, y, o, b, _, _, _},
    {_, _, _, b, w, g, y, o, b, _, _, _},
    {_, _, _, b, w, g, y, o, b, _, _, _},
    {_, _, _, b, w, g, y, o, b, _, _, _},
    {_, _, _, b, w, g, y, o, b, _, _, _},
    {_, _, _, b, w, g, y, o, b, _, _, _},
    {_, _, _, _, b, g, g, b, _, _, _, _},
    {_, _, _, _, b, y, y, b, _, _, _, _},
    {_, _, _, _, b, o, o, b, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
};

const vector<vector<int>> Coin::coin_texture_5_ = {
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, b, _, _, _, _, _},
};