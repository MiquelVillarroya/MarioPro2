#include "game.hh"
#include "utils.hh"
#include "text.hh"
#include "boo.hh"
#include "terrain.hh"

#include <vector>

using namespace pro2;
using namespace std;

Game::Game(int width, int height)
    : mario_({width / 2, 150}, Keys::Left, Keys::Right, Keys::Space),
      finished_(false), paused_(false), 
      text_(new Text), timer_(text_) {
    platforms_.push_back(Platform(100, 300, 200, 211));
    platforms_.push_back(Platform(0, 200, 250, 261));
    //test
    hard_blocks_.push_back(HardBlock(300, 400, 200, 211));
    hard_blocks_.push_back(HardBlock(100, 200, 148, 164));
    terrain_.push_back(Terrain(0,700,300,400));
    boos_.push_back(Boo({300, 50}));

    for (int i = 0; i < 100; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
        coins_.push_back(new Coin({300-1 + i*200, 70}, movType::CIRCULAR, {325 + i*200, 70}));
        coins_.push_back(new Coin({350 + i*200, 70}, movType::CIRCULAR, {325 + i*200, 70}));
        coins_.push_back(new Coin({325 + i*200, 45-1}, movType::CIRCULAR, {325 + i*200, 70}));
        coins_.push_back(new Coin({325 + i*200, 95}, movType::CIRCULAR, {325 + i*200, 70}));
        if (i%2 == 0)
            coins_.push_back(new Coin({425+i*200, 50}, movType::LINEAR, {425 + i*200, 80}));
        else 
            coins_.push_back(new Coin({375+i*200, 70}, movType::LINEAR, {450 + i*200, 70}));
    }
    plat_finder_ = Finder<Platform>(platforms_);
    hard_block_finder_ = Finder<HardBlock>(hard_blocks_);
    coin_finder_ = Finder<Coin> (coins_);
    boo_finder_ = Finder<Boo> (boos_);
    terrain_finder_ = Finder<Terrain>(terrain_);
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if(window.was_key_pressed('P')) {
        paused_ = !paused_;
    }
    else if (window.was_key_pressed('R') and !mario_.is_alive()) {
        mario_.set_pos({window.width()/2, 150});
        window.set_camera_topleft({0,0});
        mario_.set_lives(3);
    }
    else if (window.was_key_pressed(Keys::Backspace)) {
        intro = false;
    }
}

void Game::update_objects(pro2::Window& window) {    //While the platform-player logic is managed inside player, other logic will be managed here
    //Update objects

    auto nearby_plat = plat_finder_.query(window.camera_rect());
    auto nearby_hard_blocks = hard_block_finder_.query(window.camera_rect());
    auto nearby_terrain = terrain_finder_.query(window.camera_rect());
    mario_.update(window, nearby_plat, nearby_hard_blocks, nearby_terrain);

    //all coins are updated (not only those in the window) because if not, the coin circles will desynchronize
    for (Coin* c : coins_) {
        c->update();
        coin_finder_.update(c);
    }
    Coin::update_spin();
    

    //Check for collisions
    Rect mario_rect = mario_.get_rect();
    auto nearby_coins = coin_finder_.query(window.camera_rect());
    auto itc = nearby_coins.begin();
    while (itc != nearby_coins.end()) {
        if (checkCollision((*itc)->get_rect(), mario_rect)) {
            coin_finder_.remove(*itc);
            coins_.remove(const_cast<Coin*>(*itc)); //Only instance of needing a non-const Finder, not worth changing for only this occasion
            delete *itc;
            mario_.update_score();
        }
        ++itc;
    }

    Pt mario_pos = mario_.pos() - Pt{0, 8};
    auto nearby_boos = boo_finder_.query(window.camera_rect());
    for (auto b : nearby_boos) {
        if (mario_.is_looking_left() and mario_pos.x < b->pos().x
        or mario_.is_looking_right() and mario_pos.x > b->pos().x) {
            b->update(mario_pos);
        }
        if (!mario_.isInvincible() and checkCollision(mario_rect, b->get_rect())) {
            mario_.get_hurt_();
            mario_.set_pos_init();
            window.set_camera_topleft({0,0});
        }
    }
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos() - Pt {0, 40};
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = 0, dy = 0;
    if (pos.x > right) {
        dx = pos.x - right;
    } else if (pos.x < left) {
        dx = pos.x - left;
    }
    if (pos.y < top) {
        dy = pos.y - top;
    } else if (pos.y > bottom) {
        dy = pos.y - bottom;
    }
    
    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    if (!intro and !is_paused() and mario_.is_alive()) {
        update_objects(window);
        update_camera(window);
        timer_.update();
    }
}

void Game::paint(pro2::Window& window) {
    if (intro) {
        window.clear(black);
        text_->paint_phrase(window, {0,0}, "hola", white);
    }
    else if (mario_.is_alive()) {
        window.clear(sky_blue);

        auto nearby_plat = plat_finder_.query(window.camera_rect());
        for (auto p : nearby_plat) {
            p->paint(window);
        }

        auto nearby_coin = coin_finder_.query(window.camera_rect());
        for (auto c : nearby_coin) {
            c->paint(window);
        }

        auto nearby_hard_blocks = hard_block_finder_.query(window.camera_rect());
        for (auto hb : nearby_hard_blocks) {
            hb->paint(window);
        }

        auto nearby_boos = boo_finder_.query(window.camera_rect());
        for (auto b : nearby_boos) {
            b->paint(window);
        }

        auto nearby_terrain = terrain_finder_.query(window.camera_rect());
        for (auto t : nearby_terrain) {
            t->paint(window);
        }

        mario_.paint(window);

        //print score
        int score = mario_.get_score();
        Pt cam_topleft = window.topleft();
        int space = 5;

        paint_sprite(window, cam_topleft + Pt{space, 3}, mini_coin_texture_);
        space += 10;
        text_->paint_char(window, cam_topleft + Pt{space, 5}, 'x');
        space += 9;
        text_->paint_number(window, cam_topleft + Pt{space, 5}, score);

        timer_.paint(window, cam_topleft + Pt{window.width()-40, 3});

        paint_sprite(window, cam_topleft + Pt{window.width()-81, 5}, lives_texture_);
        text_->paint_char(window, cam_topleft + Pt{window.width()-67, 5}, 'x');
        text_->paint_number(window, cam_topleft + Pt{window.width()-58, 5}, mario_.get_lives());    
    }
    else {
        window.clear(black);
        text_->paint_phrase(window, {150,150}, "gameover", white);
        text_->paint_phrase(window, {150,200}, "pressr", white);
    }
}

const int _ = -1; //transparent
const int b = 0x000000; //black
const int w = 0xffffff; //white
const int g = 0xfff93d; //gold
const int y = 0xfadd00; //yellow
const int o = 0xe0ac12; //orange

const Sprite Game::mini_coin_texture_ = {
    {_, _, b, b, b, _, _, _},
    {_, b, w, w, w, b, _, _},
    {b, w, y, y, b, o, b, _},
    {b, w, y, g, b, o, b, _},
    {b, w, y, g, b, o, b, _},
    {b, w, y, g, b, o, b, _},
    {b, w, y, g, b, o, b, _},
    {b, w, y, b, o, o, b, _},
    {_, b, o, o, o, b, _, _},
    {_, _, b, b, b, _, _, _},
};

const int r = pro2::red;
const int s = 0xecc49b;

const Sprite Game::lives_texture_ = {
    {_, _, _, r, r, r, r, r, _, _, _, _},
    {_, _, r, r, r, r, r, r, r, r, r, _},
    {_, _, b, b, b, s, s, b, s, _, _, _},
    {_, b, s, b, s, s, s, b, s, s, s, _},
    {_, b, s, b, b, s, s, s, b, s, s, s},
    {_, b, b, s, s, s, s, b, b, b, b, _},
    {_, _, _, s, s, s, s, s, s, s, _, _},
};