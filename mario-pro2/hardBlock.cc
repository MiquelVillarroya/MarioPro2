#include "hardBlock.hh"
#include "globals.hh"
#include "utils.hh"
#include <iostream>

using namespace pro2;

void HardBlock::paint(pro2::Window& window) const {
    if (block_type_ == blockType::BLOCK) {
        paint_sprite(window, {left_, top_}, block_texture_);
    }
    else if (block_type_ == blockType::TERRAIN) {
        std::cout << "terrain";
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

const Sprite HardBlock::terrain_texture_ = {
    {}
};