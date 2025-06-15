#ifndef JUTGE_HH
#define JUTGE_HH

#include "window.hh"
#include "utils.hh"
#include "globals.hh"

class Jutge {
    private:
        int left_, right_, top_, bottom_;

    public:
        Jutge(int left, int right, int top, int bottom)
        : left_(left), right_(right), top_(top), bottom_(bottom) {};

        void paint(pro2::Window& window) {
            pro2::paint_sprite(window, {left_, top_}, jutge_texture_);
        };

        pro2::Rect get_rect() {
            return {left_,top_, right_, bottom_};
        };

    private:
        static const Sprite jutge_texture_;

};

#endif