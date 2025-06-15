#ifndef TIMER_HH
#define TIMER_HH

#include "text.hh"
#include "globals.hh"

/**
 * @brief A timer that runs until it hits 0. It is updated every second
 * and drawed with a clock sprite and the timer counter
 */

class Timer {
    private:
        //Timer control
        int frame_ctr_ = 1;
        int sec_ctr_;

        //Pointer to text object
        Text* text_;
        
    public:
        Timer(Text* text) : sec_ctr_(500), text_(text) {}
        Timer(Text* text, int time) : sec_ctr_(time), text_(text) {}  

        /**
         * @brief Decreases the `sec_ctr` by one every second, the rate is dependent
         * of the `FPS` parameter
         */
        void update();

        /**
         * @brief Paints in the screen the `sec_ctr_` timer with the `clock_texture_` sprite
         * 
         * @param window window to paint the timer
         * @param pos top-left point to start the drawing
         * @param col color of the numbers, `black` by default
         */
        void paint(pro2::Window& window, pro2::Pt pos, pro2::Color col = pro2::black) const;

    private:
        static const Sprite clock_texture_;
        static const int clock_width_ = 11;
        static const int clock_height_ = 11;

};

#endif