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

class Game {
 private:
    Mario mario_;

    std::list<Platform> platforms_;
    Finder<Platform> plat_finder_;

    std::list<HardBlock> hard_blocks_;
    Finder<HardBlock> hard_block_finder;
    
    std::list<Coin*> coins_;
    Finder<Coin> coin_finder_;

    bool finished_;
    bool paused_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

    Text* text_;

    Timer timer_;

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
    static const std::vector<std::vector<int>> mini_coin_texture_;

};

#endif