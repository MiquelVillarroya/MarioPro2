#ifndef PARTICLE_HH
#define PARTICLE_HH

#include "window.hh"
#include "globals.hh"

class Particle {
    private:
        pro2::Pt pos_ = {0,0};
        PartType part_type_ = PartType::COIN;
        static const int lifetime_coin_ = 60;
        static const int lifetime_jump_ = 50;

    public:
        Particle(pro2::Pt pos, PartType type);
        Particle() {};

        int lifetime_ = 0;

        void paint(pro2::Window& window) const;

    private:
        static const std::vector<Sprite> particle_texture_;
};


#endif