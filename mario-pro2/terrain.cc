#include "terrain.hh"
#include "globals.hh"
#include "utils.hh"

using namespace std;

void Terrain::paint(pro2::Window& window) const {
    int xsz = terrain_texture_2_.size();
    int ysz = terrain_texture_2_[0].size();
    for (int i = top_ + 1; i <= top_ + 16; i++) {
        for (int j = left_; j <= right_; j++) {
            window.set_pixel({j, i}, terrain_texture_1_[(i - top_ - 1) % xsz][(j - left_) % ysz]);
        }
    }
    xsz = terrain_texture_2_.size();
    ysz = terrain_texture_2_[0].size();
    for (int i = top_ + 17; i <= bottom_; i++) {
        for (int j = left_; j <= right_; j++) {
            window.set_pixel({j, i}, terrain_texture_2_[(i - top_ - 17) % xsz][(j - left_) % ysz]);
        }
    }
}

bool Terrain::has_crossed_floor_downwards(pro2::Pt plast, pro2::Pt pcurr) const {
    return (left_ <= plast.x && plast.x <= right_) && (left_ <= pcurr.x && pcurr.x <= right_) &&
           (plast.y <= top_ && pcurr.y >= top_);
}

bool Terrain::has_crossed_block_right(pro2::Pt plast, pro2::Pt pcurr) const {
    return (top_ <= plast.y && plast.y <= bottom_) && (top_ <= pcurr.y && pcurr.y <= bottom_) &&
           (plast.x >= right_ && pcurr.x <= right_);
}

bool Terrain::has_crossed_block_left(pro2::Pt plast, pro2::Pt pcurr) const {
    return (top_ <= plast.y && plast.y <= bottom_) && (top_ <= pcurr.y && pcurr.y <= bottom_) &&
           (plast.x <= left_ && pcurr.x >= left_);
}


const int g = 0x007beb08;
const int d = 0x00529a08;
const int p = 0x00e7a24a;
const int s = 0x00d68a29;
const int b = 0x008c5918;

const Sprite Terrain::terrain_texture_1_ = {
    {g,g,g,g,g,g,g,g,g,g,g,g,g,g,g,g},
    {g,g,g,g,g,g,g,g,g,g,g,g,g,g,g,g},
    {g,g,g,g,g,g,g,g,g,g,g,g,g,g,g,g},
    {g,g,g,g,g,g,g,g,d,d,d,d,d,d,d,d},
    {d,d,d,d,d,d,d,d,p,p,p,p,p,p,p,p},
    {p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p},
    {p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p},
    {p,p,p,p,p,p,p,p,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,b,b,b,b,b,b,b,b},
    {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
    {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
    {b,b,b,b,b,b,b,b,s,s,s,s,s,s,s,s},
    
};

const Sprite Terrain::terrain_texture_2_ = {
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,p,p,p,p,p,p,p,p},
    {p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p},
    {p,p,p,p,p,p,p,p,p,p,p,p,p,p,p,p},
    {p,p,p,p,p,p,p,p,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,s,s,s,s,s,s,s,s},
    {s,s,s,s,s,s,s,s,b,b,b,b,b,b,b,b},
    {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
    {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
    {b,b,b,b,b,b,b,b,s,s,s,s,s,s,s,s},
    
};
