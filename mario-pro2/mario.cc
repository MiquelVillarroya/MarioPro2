#include "mario.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int h = pro2::black;
const int g = 0xaaaaaa;
const int w = 0x8d573c;

// clang-format off
const vector<vector<int>> Mario::mario_sprite_normal_ = {
    {_, _, _, r, r, r, r, r, _, _, _, _},
    {_, _, r, r, r, r, r, r, r, r, r, _},
    {_, _, h, h, h, s, s, h, s, _, _, _},
    {_, h, s, h, s, s, s, h, s, s, s, _},
    {_, h, s, h, h, s, s, s, h, s, s, s},
    {_, h, h, s, s, s, s, h, h, h, h, _},
    {_, _, _, s, s, s, s, s, s, s, _, _},
    {_, _, r, r, b, r, r, r, _, _, _, _},
    {_, r, r, r, b, r, r, b, r, r, r, _},
    {r, r, r, r, b, b, b, b, r, r, r, r},
    {g, g, r, b, y, b, b, y, b, r, g, g},
    {g, g, g, b, b, b, b, b, b, g, g, g},
    {g, g, b, b, b, b, b, b, b, b, g, g},
    {_, _, b, b, b, _, _, b, b, b, _, _},
    {_, w, w, w, _, _, _, _, w, w, w, _},
    {w, w, w, w, _, _, _, _, w, w, w, w},
};
// clang-format on
Mario::Mario(pro2::Pt pos, char left_key, char right_key, char jump_key)
    : pos_(pos), last_pos_(pos),
    left_key_(left_key), right_key_(right_key), jump_key_(jump_key) {}

void Mario::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x - 6, pos_.y - 15};
    paint_sprite(window, top_left, mario_sprite_normal_, looking_left_);
}

void Mario::apply_physics_() {
    if (grounded_) {
        speed_.y = 0;
        accel_.y = 0;
    }

    // Always falling to check if we aren't grounded
    // If we are, we will return to the same spot

    const int gravity = 1;  // gravity = 1 pixel / frame_time^2
    speed_.y += gravity;

    if (accel_time_ > 0) {
        speed_.y += accel_.y;
        accel_time_--;
    }

    pos_.x += speed_.x;
    pos_.y += speed_.y;
}

void Mario::jump() {
    if (grounded_) {
        accel_.y = -6;
        grounded_ = false;
        accel_time_ = 2;
    }
}

void Mario::update(pro2::Window& window, const set<const Platform*>& platforms,
    const set<const HardBlock*>& hard_blocks) {
    last_pos_ = pos_;

    if (window.is_key_down(jump_key_)) {
        jump();
    }

    // Velocitat horitzontal
    speed_.x = 0; 
    if (window.is_key_down(left_key_)) {
        speed_.x = -4;
    } else if (window.is_key_down(right_key_)) {
        speed_.x = 4;
    }
    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }

    // Apply acceleration and speed
    apply_physics_();

    // Check position
    set_grounded(false);

    for (auto platform : platforms) {
        if (platform->has_crossed_floor_downwards(last_pos_, pos_)) {
            set_grounded(true);
            set_y(platform->top());
        }
    }

    last_pos_top_ = last_pos_ + Pt{0, -height+1};
    pos_top_ = pos_ + Pt{0, -height+1};
    last_pos_right_ = last_pos_ + Pt{width/2-1,-height/2};
    pos_right_ = pos_ + Pt{width/2-1,-height/2};
    last_pos_left_ = last_pos_ + Pt{-width/2,-height/2};
    pos_left_ = pos_ + Pt{-width/2,-height/2};

    for (auto hb : hard_blocks) {
        if (hb->has_crossed_block_downwards(last_pos_, pos_)) {
            set_grounded(true);
            set_y(hb->top()-1);
        }
        else if (hb->has_crossed_block_upwards(last_pos_top_, pos_top_)) {
            set_y(hb->bottom() + height);
        }
        if (hb->has_crossed_block_right(last_pos_left_, pos_left_)) {
            set_x(hb->right() + width/2+1);
        }
        else if (hb->has_crossed_block_left(last_pos_right_, pos_right_)) {
            set_x(hb->left() - width/2);
        }
    }
}

void Mario::update_score() {
    ++score_;
}