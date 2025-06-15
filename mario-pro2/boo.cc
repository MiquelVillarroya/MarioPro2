#include "boo.hh"
#include "globals.hh"
#include "utils.hh"
#include "geometry.hh"

using namespace std;
using namespace pro2;

void Boo::update(Pt mario_centre_) {
    Pt dir = mario_centre_ - pos_centre_;
    float dx = dir.x;
    float dy = dir.y;
    float dist = sqrt(dx*dx + dy*dy);

    if (dist > 0) {
        dx /= dist;
        dy /= dist;

        accu_x_ += dx;
        accu_y_ += dy;
    }

    speed_ = {0,0};
    if (accu_x_ >= 1) {
        speed_.x = 1;
        accu_x_ -= 1.0;
    }
    else if (accu_x_ <= -1) {
        speed_.x = -1;
        accu_x_ += 1.0;
    }

    if (accu_y_ >= 1) {
        speed_.y = 1;
        accu_y_ -= 1.0;
    }
    else if (accu_y_ <= -1) {
        speed_.y = -1;
        accu_y_ += 1.0;
    }

    pos_centre_.x += speed_.x;
    pos_centre_.y += speed_.y;

    looking_left_ = dx > 0;

    set_being_looked(false);
}

void Boo::paint(pro2::Window& window) const {
    Pt pos_top_left = pos_centre_ + pro2::Pt{-width_/2,-height_/2};
    if (!being_looked_) paint_sprite(window, pos_top_left, boo_texture_1_, looking_left_);
    else paint_sprite(window, pos_top_left, boo_texture_2_, looking_left_);
}

const int _ = -1;
const int b = black;
const int w = white;
const int r = red;
const int p = 0x00ee7cca;
const int f = 0x00ea40b5;

const Sprite Boo::boo_texture_1_ = {
    {_,_,_,_,_,b,b,b,b,b,_,_,_,_,_,_},
    {_,_,_,b,b,w,w,w,w,w,b,b,_,_,_,_},
    {_,_,b,w,w,w,w,w,w,w,w,w,b,_,_,_},
    {_,b,w,w,w,w,w,w,w,w,w,w,w,b,_,_},
    {_,b,w,b,w,b,w,w,w,w,w,w,w,b,_,_},
    {b,w,w,b,w,b,w,w,w,w,b,b,w,w,b,_},
    {b,w,w,w,w,w,w,w,w,b,w,w,b,w,b,_},
    {b,w,r,w,r,w,r,w,w,w,w,w,b,w,b,_},
    {b,w,r,r,r,r,r,w,w,w,w,b,w,w,w,b},
    {b,w,r,r,r,r,r,w,w,w,w,w,w,w,w,b},
    {_,b,w,r,r,r,r,r,w,w,w,w,w,w,w,b},
    {_,b,w,r,w,r,w,r,w,w,w,w,w,w,b,_},
    {_,_,b,w,w,w,w,w,w,w,w,w,b,b,_,_},
    {_,_,_,b,b,b,w,w,w,w,b,b,_,_,_,_},
    {_,_,_,_,_,_,b,b,b,b,_,_,_,_,_,_}

};

const Sprite Boo::boo_texture_2_ = {
    {_,_,_,_,_,b,b,b,b,b,_,_,_,_,_,_},
    {_,_,_,b,b,w,w,w,w,w,b,b,_,_,_,_},
    {_,_,b,w,w,w,w,w,w,w,w,w,b,_,_,_},
    {_,b,w,w,w,w,w,w,w,w,w,w,w,b,_,_},
    {_,b,w,w,w,w,w,w,w,b,b,b,w,w,b,_},
    {b,w,b,b,w,w,w,b,b,w,w,w,w,w,w,b},
    {b,w,w,w,b,p,b,w,w,w,w,w,w,w,w,b},
    {b,w,w,w,b,p,b,w,w,w,w,w,w,w,b,_},
    {b,b,b,b,b,p,b,b,b,b,b,b,w,w,w,b},
    {b,f,p,p,p,p,p,p,p,p,p,f,w,w,w,b},
    {b,w,w,w,w,w,w,w,w,w,w,w,w,w,w,b},
    {_,b,w,w,w,w,w,w,w,w,w,w,w,w,w,b},
    {_,b,w,w,w,b,b,w,w,w,w,w,w,w,b,_},
    {_,_,b,w,w,w,w,w,w,w,w,w,w,b,_,_},
    {_,_,_,b,b,w,w,w,w,w,w,b,b,_,_,_},
    {_,_,_,_,_,b,b,b,b,b,b,_,_,_,_,_}
};