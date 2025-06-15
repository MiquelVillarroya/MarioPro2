#include "hardBlock.hh"
#include "globals.hh"
#include "utils.hh"
#include <iostream>

using namespace pro2;
using namespace std;

HardBlock::HardBlock(int left, int right, int top, int bottom)
    : left_(left), right_(right), top_(top), bottom_(bottom) {
        if (right_-left_ % 16 != 0) cout << "Error in hardblocks dimension, width not divisible by 16!";
        else if (bottom_ - top_ % 16 != 0) cout << "Error in hardblocks dimension, height not divisible by 16!";
}


void HardBlock::paint(pro2::Window& window) const {
    const int xsz = block_texture_.size();
    const int ysz = block_texture_[0].size();
    for (int i = top_+1; i <= bottom_; i++) {
        for (int j = left_; j <= right_; j++) {
            window.set_pixel({j, i}, block_texture_[(i - top_-1) % xsz][(j - left_) % ysz]);
        }
    }
}
bool HardBlock::has_crossed_block_downwards(pro2::Pt plast, pro2::Pt pcurr) const {
    return (left_ <= plast.x && plast.x <= right_) && (left_ <= pcurr.x && pcurr.x <= right_) &&
           (plast.y <= top_ && pcurr.y >= top_);
}

bool HardBlock::has_crossed_block_upwards(pro2::Pt plast, pro2::Pt pcurr) const {
    return (left_ <= plast.x && plast.x <= right_) && (left_ <= pcurr.x && pcurr.x <= right_) &&
           (plast.y >= bottom_ && pcurr.y <= bottom_);
}

bool HardBlock::has_crossed_block_right(pro2::Pt plast, pro2::Pt pcurr) const {
    return (top_ <= plast.y && plast.y <= bottom_) && (top_ <= pcurr.y && pcurr.y <= bottom_) &&
           (plast.x >= right_ && pcurr.x <= right_);
}

bool HardBlock::has_crossed_block_left(pro2::Pt plast, pro2::Pt pcurr) const {
    return (top_ <= plast.y && plast.y <= bottom_) && (top_ <= pcurr.y && pcurr.y <= bottom_) &&
           (plast.x <= left_ && pcurr.x >= left_);
}

const int o = 0x00df7126;
const int p = 0x00e08f58;
const int b = 0x004f290f;
const int s = 0x00a2521c;

const Sprite HardBlock::block_texture_ = {
    {o,p,p,p,p,p,p,p,p,p,p,p,p,p,p,b},
    {p,o,p,p,p,p,p,p,p,p,p,p,p,p,b,s},
    {p,p,o,p,p,p,p,p,p,p,p,p,p,b,s,s},
    {p,p,p,o,p,p,p,p,p,p,p,p,b,s,s,s},
    {p,p,p,p,o,o,o,o,o,o,o,o,s,s,s,s},
    {p,p,p,p,o,o,o,o,o,o,o,o,s,s,s,s},
    {p,p,p,p,o,o,o,o,o,o,o,o,s,s,s,s},
    {p,p,p,p,o,o,o,o,o,o,o,o,s,s,s,s},
    {p,p,p,p,o,o,o,o,o,o,o,o,s,s,s,s},
    {p,p,p,p,o,o,o,o,o,o,o,o,s,s,s,s},
    {p,p,p,p,o,o,o,o,o,o,o,o,s,s,s,s},
    {p,p,p,p,o,o,o,o,o,o,o,o,s,s,s,s},
    {p,p,p,b,s,s,s,s,s,s,s,s,o,s,s,s},
    {p,p,b,s,s,s,s,s,s,s,s,s,s,o,s,s},
    {p,b,s,s,s,s,s,s,s,s,s,s,s,s,o,s},
    {b,s,s,s,s,s,s,s,s,s,s,s,s,s,s,o}
};