#ifndef HARDBLOCK_HH
#define HARDBLOCK_HH

#include "window.hh"
#include "globals.hh"

/**
 * @brief Class of solid blocks, similar to platform but they have
 * collision in all four sides.
 * Size of one block sprite is 16x16, so they must be constructed in multiples of 16.
 */

 class HardBlock {
    private:
    int left_, right_, top_, bottom_;
    
    public:
        HardBlock(int left, int right, int top, int bottom);

        bool has_crossed_block_downwards(pro2::Pt plast, pro2::Pt pcurr) const;
        bool has_crossed_block_upwards(pro2::Pt plast, pro2::Pt pcurr) const;
        bool has_crossed_block_right(pro2::Pt plast, pro2::Pt pcurr) const;
        bool has_crossed_block_left(pro2::Pt plast, pro2::Pt pcurr) const;

        void paint(pro2::Window& window) const;

        int top() const {
            return top_;
        }
        int bottom() const {
            return bottom_;
        }
        int left() const {
            return left_;
        }
        int right() const {
            return right_;
        }

        pro2::Rect get_rect() const {
            return {left_, top_, right_, bottom_};
        }

    private:
        static const Sprite block_texture_;

        static const int width_ = 16;
        static const int height_ = 16;
};

#endif