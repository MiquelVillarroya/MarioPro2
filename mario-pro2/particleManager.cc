#include "particleManager.hh"
#include "globals.hh"
#include "queue.hh"
#include <iostream>


using namespace std;

void ParticleManager::enqueue(pro2::Pt position, PartType type) {
    Particle p (position, type);
    particles_.push(p);
}

void ParticleManager::update() {
    int n = particles_.size();

    for(int i = 0; i < n; ++i) {
        Particle p = particles_.front();
        particles_.pop();

        --p.lifetime_;
        if (p.lifetime_ > 0) {
            particles_.push(p);
        }
    }
}

void ParticleManager::paint(pro2::Window& window) {
    Queue<Particle> temp = particles_;
    while (temp.size() > 0) {
        const Particle p = temp.front();
        temp.pop();
        p.paint(window);
    }
}