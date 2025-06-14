#ifndef HARDBLOCK_HH
#define HARDBLOCK_HH

#include "window.hh"
#include "globals.hh"



class HardBlock {
    private:
    int left_, right_, top_, bottom_;

    static const Sprite block_texture_;
    
    public:
        HardBlock() :  left_(0), right_(0), top_(0), bottom_(0) {}

        HardBlock(int left, int right, int top, int bottom)
            : left_(left), right_(right), top_(top), bottom_(bottom) {}

        void paint(pro2::Window& window) const;

        pro2::Rect get_rect() const {
            return {left_, top_, right_, bottom_};
        }

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

        bool has_crossed_block_downwards(pro2::Pt plast, pro2::Pt pcurr) const;
        bool has_crossed_block_upwards(pro2::Pt plast, pro2::Pt pcurr) const;
        bool has_crossed_block_right(pro2::Pt plast, pro2::Pt pcurr) const;
        bool has_crossed_block_left(pro2::Pt plast, pro2::Pt pcurr) const;
};

#endif