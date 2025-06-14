#ifndef TERRAIN_HH
#define TERRAIN_HH

#include <vector>
#include "window.hh"
#include "globals.hh"

class Terrain {
 private:
    int left_, right_, top_, bottom_;

	static const Sprite terrain_texture_1_;
    static const Sprite terrain_texture_2_;

 public:
    Terrain() : left_(0), right_(0), top_(0), bottom_(0) {}
    Terrain(int left, int right, int top, int bottom)
        : left_(left), right_(right), top_(top), bottom_(bottom) {}

    void paint(pro2::Window& window) const;

    bool has_crossed_floor_downwards(pro2::Pt plast, pro2::Pt pcurr) const;
    bool has_crossed_block_right(pro2::Pt plast, pro2::Pt pcurr) const;
    bool has_crossed_block_left(pro2::Pt plast, pro2::Pt pcurr) const;

    int top() const {
        return top_;
    }
    int right() const {
        return right_;
    }
    int left() const {
        return left_;
    }

    pro2::Rect get_rect() const {
        return {left_, top_, right_, bottom_};
    }
};

#endif