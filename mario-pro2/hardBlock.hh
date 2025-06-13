#ifndef HARDBLOCK_HH
#define HARDBLOCK_HH

#include "window.hh"
#include "globals.hh"

enum class blockType {
    TERRAIN, BLOCK
};

class HardBlock {
    private:
    int left_, right_, top_, bottom_;

    blockType block_type_;
    static const int block_width_ = 16;
    static const int block_height_ = 16;

    static const Sprite block_texture_;
    static const Sprite terrain_texture_;

    
    public:
        HardBlock() : block_type_(blockType::TERRAIN), left_(0), right_(0), top_(0), bottom_(0) {}
        
        HardBlock(pro2::Pt pos) : left_(pos.x), right_(pos.x+block_width_-1),
        top_(pos.y), bottom_(pos.y+block_height_-1), block_type_(blockType::BLOCK) {}

        HardBlock(int left, int right, int top, int bottom)
            : left_(left), right_(right), top_(top), bottom_(bottom), block_type_(blockType::TERRAIN) {}

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