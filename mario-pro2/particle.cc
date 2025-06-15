#include <vector>

#include "particle.hh"
#include "globals.hh"
#include "utils.hh"

using namespace std;
using namespace pro2;

Particle::Particle(Pt pos, PartType type) : pos_(pos), part_type_(type) {
    if (part_type_ == PartType::COIN) lifetime_ = lifetime_coin_;
    else if (part_type_ == PartType::JUMP) lifetime_ = lifetime_jump_;
}

void Particle::paint(pro2::Window& window) const {
    if (part_type_ == PartType::COIN)
        paint_sprite(window, pos_, particle_texture_[0]);
    else if (part_type_ == PartType::JUMP) 
        paint_sprite(window, pos_, particle_texture_[1]);
}


const int _ = -1;
const int g = 0xfff93d; //gold
const int y = 0xfadd00; //yellow
const int o = 0xe0ac12; //orange

const int w = 0xffffff; //white

const vector<Sprite> Particle::particle_texture_ = {
    {
        {_,_,_,_,_,_,_,_,g,_,_,_},
        {_,g,_,_,y,_,_,_,_,_,_,_},
        {_,_,_,_,_,_,_,_,_,_,_,_},
        {_,_,o,_,_,_,_,_,o,_,_,_},
        {_,_,_,y,_,_,_,y,_,_,_,y},
        {_,_,_,_,g,_,g,_,_,_,_,_},
        {_,_,_,_,_,g,_,_,_,_,_,_},
        {_,_,_,_,g,_,g,_,_,_,_,_},
        {_,_,_,y,_,_,_,y,_,_,g,_},
        {_,_,o,_,_,_,_,_,o,_,_,_},
        {_,_,_,_,y,_,_,_,_,_,_,_},
        {_,g,_,_,_,_,_,g,_,_,_,_}
    },
    {
        {_}
    }
};