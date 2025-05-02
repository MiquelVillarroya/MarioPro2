#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "mario.hh"
#include "platform.hh"
#include "coin.hh"
#include "window.hh"

class Game {
 private:
    Mario                 mario_;
    std::vector<Platform> platforms_;
    std::vector<Coin*>     coins_;

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