#ifndef PARTICLEMANAGER_HH
#define PARTICLEMANAGER_HH

#include "queue.hh"
#include "particle.hh"
#include "window.hh"
#include "globals.hh"

/**
 * @brief Class that manages creation, destruction, update and paint of particles.
 * Although only one type of particle is implemented, is designed to handle different types
 * of particles in the same object.
 */

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