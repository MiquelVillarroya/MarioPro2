#ifndef BOO_HH
#define BOO_HH

#include "globals.hh"
#include "window.hh"

class Boo {
    private:
        //Position logic
        pro2::Pt pos_centre_;
        pro2::Pt speed_;

        //floats that accumulate decimal displacement for better and smoother movement
        float accu_x_ = 0.0;
        float accu_y_ = 0.0;

        //facing direction
        bool looking_left_;

        //true if boo is being looked by Mario, false otherwise
        bool being_looked_ = false;

    public:
        Boo(pro2::Pt pos) : pos_centre_(pos) {}

        /**
         * @brief updates boo position to follow Mario, only called if Mario is not looking
         * at the boo. Follows mario and passes through objects.
         * Implemented with float values for smoother movement.
         * 
         * @param mario_centre_ point in the centre of Mario
         */
        void update(pro2::Pt mario_centre_);

        /**
         * @brief Draws the boo sprite in the screen, the sprite chosen
         * depends on whether boo is being looked or not
         * 
         * @param window window to draw the sprite
         */
        void paint(pro2::Window& window) const;

        void set_being_looked(bool look) {
            being_looked_ = look;
        }

        pro2::Pt pos() {
            return pos_centre_;
        }

        pro2::Rect get_rect() {
            return {pos_centre_.x - width_logic_/2, pos_centre_.y - height_logic_/2,
            pos_centre_.x + width_logic_/2, pos_centre_.y + height_logic_/2 };
        }

    private:
        static const Sprite boo_texture_1_;
        static const Sprite boo_texture_2_;

        //Drawing sizes
        static const int width_ = 16;
        static const int height_ = 16;

        //Logic sizes, these are taking into account for collisions
        //they are smaller than drawing sizes for better playability
        static const int width_logic_ = 14;
        static const int height_logic_ = 14;
};

#endif