#include "game.hh"
#include "utils.hh"
#include <vector>
using namespace pro2;
using namespace std;

Game::Game(int width, int height)
    : mario_({width / 2, 150}, Keys::Left, Keys::Right, Keys::Space),
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          //Platform(250, 400, 150, 161),
      },
      coins_{
      },
      finished_(false),
      paused_(false) {
    for (int i = 0; i < 20; i++) {
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
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if(window.was_key_pressed('P')) {
        paused_ = !paused_;
    }
    else if (window.was_key_pressed('R')) {
        mario_.set_pos({window.width()/2, 150});
        window.set_camera_topleft({0,0});
    }
}

void Game::update_objects(pro2::Window& window) {    //While the platform-player logic is managed inside player, other logic will be managed here
    //Update objects
    mario_.update(window, platforms_);
    for (Coin* c : coins_) {
        c->update();
    }
    Coin::update_spin();
    

    //Check for collisions
    Rect mario_rect = mario_.get_rect();
    auto it = coins_.begin();
    while (it != coins_.end()) {
        if (checkCollision((*it)->get_rect(), mario_rect)) {
            mario_.update_score();
            std::cout << "Mario score: "<< mario_.get_score() << endl;
            delete *it;
            it = coins_.erase(it);
        }
        else ++it;
    }
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
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
    if(!is_paused()) {
        update_objects(window);
        update_camera(window);
    }
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);
    for (const Platform& p : platforms_) {
        p.paint(window);
    }
    for (const Coin* c : coins_) {
        c->paint(window);
    }
    mario_.paint(window);

    //print score
    int score = mario_.get_score();
    Pt cam_topleft = window.topleft();
    for (int i = 0; i < score; ++i) {
        paint_sprite(window, {cam_topleft.x + 10*i + 5, cam_topleft.y + 5}, mini_coin_texture_);
    }
}

const int _ = -1; //transparent
const int b = 0x000000; //black
const int w = 0xffffff; //white
const int g = 0xfff93d; //gold
const int y = 0xfadd00; //yellow
const int o = 0xe0ac12; //orange

const vector<vector<int>> Game::mini_coin_texture_ = {
    {_, _, b, b, _, _},
    {_, b, w, w, b, _},
    {b, w, y, g, o, b},
    {b, w, y, g, o, b},
    {b, w, y, g, o, b},
    {b, w, y, g, o, b},
    {_, b, y, o, b, _},
    {_, _, b, b, _, _},
};