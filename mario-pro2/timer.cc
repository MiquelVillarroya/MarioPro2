#include "timer.hh"
#include "globals.hh"
#include "utils.hh"

using namespace pro2;

void Timer::update() {
    frame_ctr_++; 
    if (frame_ctr_ > FPS) {
        sec_ctr_--;
        frame_ctr_ = 1;
    }
    if (sec_ctr_ <= 0) {
        sec_ctr_ = 500;
    }
}

void Timer::paint(pro2::Window& window, Pt pos, Color col) const {
    paint_sprite(window, pos, clock_texture_);
    Pt number_pos_ = {pos.x+clock_width_+1, pos.y + (clock_height_ - FONT_SIZE)/2};
    text_->paint_number(window, {pos.x+clock_width_+1, pos.y+2}, sec_ctr_, col);
}

const int b = black;
const int w = white;
const int _ = -1;

const Sprite Timer::clock_texture_ = {
    {_,_,_,b,b,b,b,b,_,_,_},
    {_,_,b,w,w,w,w,w,b,_,_},
    {_,b,w,w,w,b,w,w,w,b,_},
    {b,w,w,w,w,b,w,w,w,w,b},
    {b,w,w,w,w,b,w,w,w,w,b},
    {b,w,w,w,w,b,b,b,w,w,b},
    {b,w,w,w,w,w,w,w,w,w,b},
    {b,w,w,w,w,w,w,w,w,w,b},
    {_,b,w,w,w,w,w,w,w,b,_},
    {_,_,b,w,w,w,w,w,b,_,_},
    {_,_,_,b,b,b,b,b,_,_,_},
};