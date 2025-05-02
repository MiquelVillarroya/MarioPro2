#ifndef COIN_HH
#define COIN_HH

#include <vector>
#include "geometry.hh"
#include "window.hh"


class Coin {
 private:
    int left_, right_, top_, bottom_;

    bool alive_;

    static const int width = 12;
    static const int height = 16;
    static const int spin_vel_ = 8*5;
    static int spin_counter_;

 public:
    Coin(pro2::Pt pos);

    static void update_spin();

    void paint(pro2::Window& window) const;
    pro2::Rect get_rect() const {
        return {left_, top_, right_, bottom_};
    }

    void unalive();

 private:
    static const std::vector<std::vector<int>> coin_texture_1_;
    static const std::vector<std::vector<int>> coin_texture_2_;
    static const std::vector<std::vector<int>> coin_texture_3_;
    static const std::vector<std::vector<int>> coin_texture_4_;
    static const std::vector<std::vector<int>> coin_texture_5_;
};

#endif