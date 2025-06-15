#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>
#include <set>
#include "platform.hh"
#include "hardBlock.hh"
#include "window.hh"
#include "terrain.hh"

class Mario {
 private:
    //Physics
    const int width = 12;
    const int height = 16;

    pro2::Pt init_pos_;
    pro2::Pt pos_, last_pos_, pos_top_, last_pos_top_,
             pos_left_, last_pos_left_, pos_right_, last_pos_right_; //control point located at the bottom-centre of character
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;

    bool grounded_ = false;
	bool looking_left_ = false;

	void apply_physics_();

    //Gameplay
    int lives_ = 3;
    int score_ = 0;

    //Respawn invincibility
    bool invincible = false;
    int invTimer = 80;

    //Control keys
    char left_key_, right_key_, jump_key_;

	
 public:
    Mario(pro2::Pt pos, char left_key, char right_key, char jump_key);
    
    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }

    pro2::Rect get_rect() const {
        return {pos_.x-width/2,pos_.y-height,pos_.x+width/2-1,pos_.y};
    }

    int get_score() const {
        return score_;
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

    void set_pos_init() {
        pos_.x = init_pos_.x;
        pos_.y = init_pos_.y;
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

    void update(pro2::Window& window, const std::set<Platform*>& platforms,
                const std::set<HardBlock*>& hard_blocks, const std::set<Terrain*>& terrain);

    void update_score();
    void set_score(int n) {
        score_ = n;
    }

    int get_lives() {
        return lives_;
    }
    void set_lives(int l) {
        lives_ = l;
    }
    void get_hurt_() {
        setInvincible(true);
        --lives_;
    }
    bool is_alive() {
        return lives_ >= 0;
    }

    void setInvincible(bool inv) {
        invincible = inv;
    }
    bool isInvincible() {
        return invincible;
    }

    bool is_looking_left() {
        return looking_left_;
    }
    bool is_looking_right() {
        return !looking_left_;
    }

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
};

#endif