#include "game.hh"
#include "utils.hh"
#include "text.hh"
#include "boo.hh"
#include "terrain.hh"
#include "globals.hh"

#include <vector>
#include <iostream>

using namespace pro2;
using namespace std;

Game::Game(int width, int height)
    : mario_({width / 2, 160}, Keys::Left, Keys::Right, Keys::Space),
      finished_(false), paused_(false), part_manager_(new ParticleManager),
      text_(new Text), timer_(text_), jutge_(0,0,0,0) {
    
    level_initiation();
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if(window.was_key_pressed('P')) {
        paused_ = !paused_;
    }
    else if (window.was_key_pressed('R') and (!mario_.is_alive() or win_)) {
        mario_.set_pos({window.width()/2, 150});
        window.set_camera_topleft({0,0});
        mario_.set_lives(3);
        level_initiation();
    }
    else if (window.was_key_pressed(Keys::Space)) {
        intro_ = false;
    }
}

void Game::update_objects(pro2::Window& window) {    //While the platform-player logic is managed inside player, other logic will be managed here
    //Update objects
    Rect camera_rect = window.camera_rect_extra(extra_);

    auto nearby_plat = plat_finder_.query(camera_rect);
    auto nearby_hard_blocks = hard_block_finder_.query(camera_rect);
    auto nearby_terrain = terrain_finder_.query(camera_rect);
    mario_.update(window, nearby_plat, nearby_hard_blocks, nearby_terrain);

    //all coins are updated (not only those in the window) because if not, the coin circles will desynchronize
    for (Coin* c : coins_) {
        c->update();
        coin_finder_.update(c);
    }
    Coin::update_spin();
    

    //Check for collisions between mario and coins
    const Rect mario_rect = mario_.get_rect();
    auto nearby_coins = coin_finder_.query(camera_rect);
    auto itc = nearby_coins.begin();
    while (itc != nearby_coins.end()) {
        if (checkCollision((*itc)->get_rect(), mario_rect)) {
            part_manager_->enqueue((*itc)->get_pos(), PartType::COIN);

            coin_finder_.remove(*itc);
            coins_.remove(const_cast<Coin*>(*itc)); //Only instance of needing a non-const Finder, not worth changing for only this occasion
            delete *itc;

            mario_.update_score();
        }
        ++itc;
    }

    //Update boos according to mario behaviour, also check for collision
    const Pt mario_pos = mario_.pos() - Pt{0, 8};
    auto nearby_boos = boo_finder_.query(camera_rect);
    for (auto b : nearby_boos) {
        if (mario_.is_looking_left() and mario_pos.x < b->pos().x
        or mario_.is_looking_right() and mario_pos.x > b->pos().x) {
            b->update(mario_pos);
        }
        else b->set_being_looked(true);
        if (!mario_.isInvincible() and checkCollision(mario_rect, b->get_rect())) {
            mario_.get_hurt_();
            mario_.set_pos_init();
            window.set_camera_topleft({0,0});
        }
    }

    if (checkCollision(mario_rect, jutge_.get_rect())) {
        win_ = true;
        cout << "a";
    }

}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos() - Pt {0, 10};
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    float camera_speed = 0.75;

    int dx = 0, dy = 0;
    if (pos.x > right) {
        dx = (pos.x - right)*camera_speed;
    } else if (pos.x < left) {
        dx = (pos.x - left)*camera_speed;
    }
    if (pos.y < top) {
        dy = (pos.y - top)*camera_speed;
    } else if (pos.y > bottom) {
        dy = (pos.y - bottom)*camera_speed;
    }
    
    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    if (!win_ and !intro_ and !is_paused() and mario_.is_alive()) {
        update_objects(window);
        update_camera(window);
        timer_.update();
        part_manager_->update();
    }
}

void Game::paint(pro2::Window& window) {
    if (intro_) {
        window.clear(black);
        Pt camera_center = window.camera_center();

        string phrase1 = "Els coordinadors de pro2 han segrestat el jutge";
        int displ1 = get_phrase_displacement(phrase1);
        Pt pos_1 = camera_center - Pt{0, FONT_SIZE+2};
        pos_1 -= Pt{displ1, 0};
        text_->paint_phrase(window, pos_1, phrase1, white);

        string phrase2 = "Prem space per jugar";
        int displ2 = get_phrase_displacement(phrase2);
        Pt pos_2 = camera_center + Pt{0, FONT_SIZE+2};
        pos_2 -= Pt{displ2, 0};
        text_->paint_phrase(window, pos_2, phrase2, white);
    }
    else if (win_) {
                window.clear(black);
        Pt camera_center = window.camera_center();

        string phrase1 = "Has rescatat al jutge";
        int displ1 = get_phrase_displacement(phrase1);
        Pt pos_1 = camera_center - Pt{0, FONT_SIZE+2};
        pos_1 -= Pt{displ1, 0};
        text_->paint_phrase(window, pos_1, phrase1, white);

        string phrase2 = "Felicitats";
        int displ2 = get_phrase_displacement(phrase2);
        Pt pos_2 = camera_center + Pt{0, FONT_SIZE+2};
        pos_2 -= Pt{displ2, 0};
        text_->paint_phrase(window, pos_2, phrase2, white);
    }
    else if (mario_.is_alive()) {
        window.clear(sky_blue);
        Rect camera_rect = window.camera_rect_extra(extra_);
        auto nearby_plat = plat_finder_.query(camera_rect);
        for (auto p : nearby_plat) {
            p->paint(window);
        }

        auto nearby_coin = coin_finder_.query(camera_rect);
        for (auto c : nearby_coin) {
            c->paint(window);
        }

        auto nearby_hard_blocks = hard_block_finder_.query(camera_rect);
        for (auto hb : nearby_hard_blocks) {
            hb->paint(window);
        }

        auto nearby_terrain = terrain_finder_.query(camera_rect);
        for (auto t : nearby_terrain) {
            t->paint(window);
        }

        auto nearby_boos = boo_finder_.query(camera_rect);
        for (auto b : nearby_boos) {
            b->paint(window);
        }

        jutge_.paint(window);
        mario_.paint(window);

        //print score
        int score = mario_.get_score();
        Pt cam_topleft = window.topleft();
        int space = 5;

        paint_sprite(window, cam_topleft + Pt{space, top_margin_-2}, mini_coin_texture_);
        space += mini_coin_texture_width_;
        text_->paint_char(window, cam_topleft + Pt{space, top_margin_}, 'x');
        space += FONT_SIZE+1;
        text_->paint_number(window, cam_topleft + Pt{space, top_margin_}, score);

        space = 40;
        timer_.paint(window, cam_topleft + Pt{window.width()-space, 3});

        space += 40;
        paint_sprite(window, cam_topleft + Pt{window.width()-space, 5}, lives_texture_);
        space -= lives_texture_width_;
        text_->paint_char(window, cam_topleft + Pt{window.width()-space, 5}, 'x');
        space -= FONT_SIZE+2;
        text_->paint_number(window, cam_topleft + Pt{window.width()-space, 5}, mario_.get_lives()); 
        part_manager_->paint(window);   
    }
    else {
        window.clear(black);

        Pt camera_center = window.camera_center();

        string phrase1 = "Game Over";
        int displ1 = get_phrase_displacement(phrase1);
        Pt pos_1 = camera_center - Pt{0, FONT_SIZE+2};
        pos_1 -= Pt{displ1, 0};
        text_->paint_phrase(window, pos_1, phrase1, white);

        string phrase2 = "Press r to restart";
        int displ2 = get_phrase_displacement(phrase2);
        Pt pos_2 = camera_center + Pt{0, FONT_SIZE+2};
        pos_2 -= Pt{displ2, 0};
        text_->paint_phrase(window, pos_2, phrase2, white);
    }
    if (is_paused()) {
        Pt cam_top_centre = window.top_centre() + Pt{0, top_margin_};
        string phrase = "Game paused";
        int displ = get_phrase_displacement(phrase);
        cam_top_centre -= Pt{displ, 0};
        text_->paint_phrase(window, cam_top_centre, phrase, white);
    }
}

void Game::level_initiation() {
    clear_level();

    //Map based on blocks of 16x16 pixel (or 8x8)
    const int i = 16; //16x16 block
    const int j = 10; //for smaller platforms
    const int a = 6;  //coin displacement
    const int b = 8;  //coin displacement

    //Section 1: Fall
    platforms_.push_back(Platform(11*i,18*i,12*i,12*i+j));
    platforms_.push_back(Platform(18*i,25*i,15*i,15*i+j));
    platforms_.push_back(Platform(11*i,18*i,18*i,18*i+j));
    boos_.push_back(Boo({28*i,12*i}));
    coins_.push_back(new Coin({21*i+a,13*i+b}));
    coins_.push_back(new Coin({14*i+a,16*i+b}));
    for (int k = 0; k < 12; k += 2) {
        coins_.push_back(new Coin({21*i, (20+k)*i}));
    }

    //Section 2: Horizontal
    terrain_.push_back(Terrain(0*i,39*i,34*i,50*i));
    terrain_.push_back(Terrain(39*i,53*i,37*i,53*i));
    terrain_.push_back(Terrain(56*i,85*i-1,37*i,53*i));
    for(int k = 0; k < 5; ++k) {
        hard_blocks_.push_back(HardBlock((47+k)*i,53*i-1,(36-k)*i,(37-k)*i));
        hard_blocks_.push_back(HardBlock(56*i,(62-k)*i-1,(36-k)*i,(37-k)*i));
    }
    boos_.push_back(Boo({53*i,36*i}));
    coins_.push_back(new Coin({54*i+a,27*i+b}, movType::LINEAR, {54*i+a,34*i+b}));
    platforms_.push_back(Platform(60*i,64*i,29*i,29*i+j));
    platforms_.push_back(Platform(60*i,64*i,23*i,23*i+j));
    platforms_.push_back(Platform(54*i,59*i,26*i,26*i+j));
    coins_.push_back(new Coin({56*i+a,23*i+b}));
    coins_.push_back(new Coin({62*i+a,26*i+b}));

    for(int k = 0; k < 12; k += 3) {
        coins_.push_back(new Coin({68*i+a,(24+k)*i+b}));
    }
    boos_.push_back(Boo({73*i,25*i}));
    coins_.push_back(new Coin({76*i+a,32*i+b}, movType::LINEAR, {81*i+a,32*i+b}));
    Pt spin_center = {62*i+a,19*i+b};
    coins_.push_back(new Coin({60*i+a-1,19*i+b}, movType::CIRCULAR, spin_center));
    coins_.push_back(new Coin({64*i+a,19*i+b}, movType::CIRCULAR, spin_center));
    coins_.push_back(new Coin({62*i+a,17*i+b-1}, movType::CIRCULAR, spin_center));
    coins_.push_back(new Coin({62*i+a,21*i+b}, movType::CIRCULAR, spin_center));

    //Section 3: Platformer
    platforms_.push_back(Platform(86*i,91*i,34*i,34*i+j));
    platforms_.push_back(Platform(93*i,99*i,35*i,35*i+j));
    platforms_.push_back(Platform(99*i,104*i,32*i,32*i+j));
    platforms_.push_back(Platform(94*i,100*i,29*i,29*i+j));
    platforms_.push_back(Platform(100*i,106*i,26*i,26*i+j));
    platforms_.push_back(Platform(108*i,113*i,27*i,27*i+j));
    boos_.push_back(Boo({107*i,15*i}));
    coins_.push_back(new Coin({111*i+a,23*i+b}));
    

    //Section 4: Cave
    terrain_.push_back(Terrain(115*i,130*i,29*i,50*i));
    hard_blocks_.push_back(HardBlock(130*i,131*i-1,29*i,41*i));
    hard_blocks_.push_back(HardBlock(134*i,135*i-1,0*i,37*i));
    for (int k = 0; k < 12; k += 3) {
        coins_.push_back(new Coin({132*i, (28+k)*i}));
    }
    hard_blocks_.push_back(HardBlock(130*i,148*i-1,40*i,41*i));
    hard_blocks_.push_back(HardBlock(134*i,148*i-1,36*i,37*i));
    hard_blocks_.push_back(HardBlock(147*i,148*i-1,36*i,41*i));

    jutge_ = Jutge(145*i,146*i,38*i,39*i);
    //Add to finders
    plat_finder_ = Finder<Platform>(platforms_);
    hard_block_finder_ = Finder<HardBlock>(hard_blocks_);
    terrain_finder_ = Finder<Terrain>(terrain_);
    coin_finder_ = Finder<Coin> (coins_);
    boo_finder_ = Finder<Boo> (boos_);
}

void Game::clear_level() {
    win_ = false;
    intro_ = true;
    mario_.set_score(0);

    plat_finder_.clear(platforms_);
    hard_block_finder_.clear(hard_blocks_);
    terrain_finder_.clear(terrain_);
    coin_finder_ .clear(coins_);
    boo_finder_.clear(boos_);

    platforms_.clear();
    hard_blocks_.clear();
    terrain_.clear();
    coins_.clear();
    boos_.clear();
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