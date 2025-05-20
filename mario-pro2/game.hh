#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "mario.hh"
#include "platform.hh"
#include "coin.hh"
#include "window.hh"
#include "finder.hh"

class Game {
 private:
    Mario mario_;

    std::vector<Platform> platforms_;
    Finder<Platform> plat_finder_;
    
    std::vector<Coin*> coins_;
    Finder<Coin> coin_finder_;

    bool finished_;
    bool paused_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

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