#include "coin.hh"
#include "utils.hh"
#include <cmath>
#include <iostream>
using namespace pro2;
using namespace std;

int Coin::spin_counter_ = spin_vel_;

Coin::Coin(pro2::Pt pos) : centre_(pos), it_moves_(false) {}

Coin::Coin(pro2::Pt pos, movType type, pro2::Pt mov_point, float speed)
    : centre_(pos), it_moves_(true), mov_type_(type), mov_point_(mov_point), init_pos_(centre_), mov_speed_(speed) {
        if (mov_type_ == movType::LINEAR) {
            dir_ = {mov_point.x - centre_.x, mov_point.y - centre_.y};
            dist_ = 0;
        }
        else if (mov_type_ == movType::CIRCULAR) {
            angle_ = atan2(centre_.y - mov_point_.y, centre_.x - mov_point_.x); //angle coin_centre - rotating_point
            dist_ = vecNorm({centre_.x - mov_point_.x, centre_.y - mov_point_.y}); //distance coin_centre - rotating_point
        }
}

void Coin::update_spin() {
    --spin_counter_;
    if (spin_counter_ <= 0) spin_counter_ = spin_vel_;
}

void Coin::update() {
    if (it_moves_) {
        if (mov_type_ == movType::LINEAR) {
            //Movement direction
            if (dist_ >= 1) forward_ = false;
            else if (dist_ <= 0) forward_ = true;

            //Update distance
            if (forward_) dist_ += 0.025;
            else dist_ -= 0.025;

            //Update position
            centre_.x = init_pos_.x + dir_.x * dist_;
            centre_.y = init_pos_.y + dir_.y * dist_;
        }
        else if (mov_type_ == movType::CIRCULAR) {
            //Update angle
            angle_ += 0.05;
            if (angle_ >= 2*M_PI) angle_ = 0.0;

            //Update position
            centre_.x = mov_point_.x + dist_ * cos(angle_);
            centre_.y = mov_point_.y + dist_ * sin(angle_);
        }
    }
}

void Coin::paint(pro2::Window& window) const {
    Pt topleft_ = {centre_.x-width/2, centre_.y-height/2,};
    if (spin_counter_ > spin_vel_*(0.875))
        paint_sprite(window, topleft_, coin_texture_1_);
    else if (spin_counter_ > spin_vel_*(0.75))
        paint_sprite(window, topleft_, coin_texture_2_);
    else if (spin_counter_ > spin_vel_*(0.625))
        paint_sprite(window, topleft_, coin_texture_3_);
    else if (spin_counter_ > spin_vel_*(0.5))
        paint_sprite(window, topleft_, coin_texture_4_);
    else if (spin_counter_ > spin_vel_*(0.375))
        paint_sprite(window, topleft_, coin_texture_5_);
    else if (spin_counter_ > spin_vel_*(0.25))
        paint_sprite(window, topleft_, coin_texture_4_);
    else if (spin_counter_ > spin_vel_*(0.125))
        paint_sprite(window, topleft_, coin_texture_3_);
    else 
        paint_sprite(window, topleft_, coin_texture_2_);
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