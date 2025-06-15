#ifndef TERRAIN_HH
#define TERRAIN_HH

#include <vector>
#include "window.hh"
#include "globals.hh"

/**
 * @brief Class for implementing terrain, similar to platform but with
 * additional lateral physics.
 * Drawing is also custom, grass patches are drawn for the top of terrain
 * and dirt is drawn for the rest of it.
 * Size of one terrain sprite is 16x16, so they must be constructed in multiples of 16.
 */

class Terrain {
 private:
    int left_, right_, top_, bottom_;

 public:
    Terrain(int left, int right, int top, int bottom)
        : left_(left), right_(right), top_(top), bottom_(bottom) {}

    /**
     * @brief paints the platform taking into account two different sprites.
     * The top part is a grass block, and the bottom part is a dirt block 
     * 
     * @param window window where to paint
     */
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

    private:
        static const Sprite terrain_texture_1_;
        static const Sprite terrain_texture_2_;
};

#endif