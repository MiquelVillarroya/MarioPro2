#ifndef GAME_HH
#define GAME_HH

#include <list>
#include "mario.hh"
#include "platform.hh"
#include "coin.hh"
#include "window.hh"
#include "finder.hh"
#include "text.hh"
#include "timer.hh"
#include "hardBlock.hh"
#include "boo.hh"
#include "terrain.hh"
#include "particleManager.hh"

class Game {
 private:
    Mario mario_;

    //Finders and lists of objects
    std::list<Platform> platforms_;
    Finder<Platform> plat_finder_;

    std::list<HardBlock> hard_blocks_;
    Finder<HardBlock> hard_block_finder_;

    std::list<Terrain> terrain_;
    Finder<Terrain> terrain_finder_;
    
    std::list<Coin*> coins_;
    Finder<Coin> coin_finder_;

    std::list<Boo> boos_;
    Finder<Boo> boo_finder_;


    //update
    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

    //text, timer and particle
    Text* text_;
    Timer timer_;
    ParticleManager* part_manager_;

    
    //level control
    bool finished_;
    bool paused_;
    bool intro_ = true;
    bool win_ = false;

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }
    bool is_paused() const {
        return paused_;
    }

 private:
    static constexpr int sky_blue = 0x5c94fc;
    static const Sprite mini_coin_texture_;
    static const Sprite lives_texture_;

    static const int extra_ = 60;
    static const int top_margin_ = 5;
    
    static const int mini_coin_texture_width_ = 10;
    static const int lives_texture_width_ = 14;
};

#endif