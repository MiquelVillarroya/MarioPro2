#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"

class Mario {
 private:
    //Physics
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;

    bool grounded_ = false;
	bool looking_left_ = false;

	void apply_physics_();

    //Control keys
    char left_key_, right_key_, jump_key_;

	
 public:
    Mario(pro2::Pt pos, char left_key, char right_key, char jump_key);
    
    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }

    void set_y(int y) {
        pos_.y = y;
    }

    void set_x(int x) {
        pos_.x = x;
    }

    void set_pos(pro2::Pt pos) {
        pos_.x = pos.x;
        pos_.y = pos.y;
    }

    bool is_grounded() const {
        return grounded_;
    }

    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

    void toggle_grounded() {
        set_grounded(!grounded_);
    }

    void jump();

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
};

#endif