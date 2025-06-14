#ifndef BOO_HH
#define BOO_HH

#include "globals.hh"
#include "window.hh"

class Boo {
    private:
        static const int width_logic_ = 14;
        static const int height_logic_ = 14;

        static const int width_ = 16;
        static const int height_ = 16;


        pro2::Pt pos_centre_;
        pro2::Pt speed_;
        float accu_x_ = 0.0;
        float accu_y_ = 0.0;

        bool looking_left_;

        static const Sprite boo_texture_;

    public:
        Boo(pro2::Pt pos) : pos_centre_(pos) {}

        void update(pro2::Pt mario_centre_);
        void paint(pro2::Window& window) const;

        pro2::Rect get_rect() {
            return {pos_centre_.x - width_logic_/2, pos_centre_.y - height_logic_/2,
            pos_centre_.x + width_logic_/2, pos_centre_.y + height_logic_/2 };
        }

        pro2::Pt pos() {
            return pos_centre_;
        }
};

#endif