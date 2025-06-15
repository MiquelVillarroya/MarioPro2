#ifndef PARTICLEMANAGER_HH
#define PARTICLEMANAGER_HH

#include "queue.hh"
#include "particle.hh"
#include "window.hh"
#include "globals.hh"

class ParticleManager {
    private:
        Queue<Particle> particles_;
        
    public:
        ~ParticleManager();

        void enqueue(pro2::Pt position, PartType type);
        void update();
        void paint(pro2::Window& window);
};

#endif