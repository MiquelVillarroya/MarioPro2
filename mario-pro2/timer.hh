#ifndef TIMER_HH
#define TIMER_HH

#include "text.hh"
#include "globals.hh"

class Timer {
    private:
        int frame_ctr_;
        int sec_ctr_;

        Text* text_;
        
        static const Sprite clock_;
    public:

        Timer(Text* text);
        Timer(Text* text, int time);

        void update();
        void paint(pro2::Window& window, int x, int y, pro2::Color col = pro2::black) const;
};

#endif