#ifndef COIN_HH
#define COIN_HH

#include <vector>
#include "geometry.hh"
#include "window.hh"

enum class movType {
   NONE, LINEAR, CIRCULAR
};

class Coin {
 private:
    //Position logic
    static const int width = 12;
    static const int height = 16;
    pro2::Pt centre_; //centre (bot_right)

    //Spin logic
    static const int spin_vel_ = 8*5;
    static int spin_counter_;

    //Although some coins don't move, they will have to contain this move-related members
    //This could be avoided and possibly better implemented with class inheritance. 

    //Movement
    bool it_moves_;
    movType mov_type_ = movType::NONE;
    float mov_speed_ = 0;

    float dist_ = 0;

    //Circular movement
    pro2::Pt mov_point_ = {0,0}; //centre of rotation in circular mov
    float angle_ = 0.0;

    //Linear movement
    pro2::Pt init_pos_ = {0,0};
    pro2::Pt dir_ = {0,0};
    bool forward_ = true;
    

 public:
    Coin(pro2::Pt pos);
    Coin(pro2::Pt pos, movType type, pro2::Pt mov_point, float mov_speed_ = 0.1);

    /**
   * @brief Updates the `spin_counter_` that controls the spin aimation of all coins.
   * Invariant: `1 <= spin_counter_ <= spin_vel_`
   */
    static void update_spin();

    /**
     * @brief Updates the logic of the coin according to its `mov_type_`
     * If `mov_type_ == movType::NONE` the object is still so no update is needed.
     * If `mov_type_ == movType::CIRCULAR` the `angle_` of rotation is incresed and the position `centre_` is updated according to it.
     * If `mov_type_ == movType::LINEAR` the `dist_` updated (`0 <= dist_ <= 1`) that determines the position of the coin between
     * the inital and final position, and the coin position `centre_` is updated according to it.
     */
    void update();

   /**
    * @brief Paints in the screen the coin sprite.
    * Depending on the `spin_counter` parametere a different state of the coin will be painted. 
    *
    * @param window Window where the coin is painted.
    */
    void paint(pro2::Window& window) const;

    /**
     * @brief Gets the rectangle of the coin.
     * 
     * @return The rectangle of the coin object.
     */
    pro2::Rect get_rect() const {
        return {centre_.x-width/2, centre_.y-height/2, centre_.x+width/2-1, centre_.y+height/2-1};
    }

 private:
    static const std::vector<std::vector<int>> coin_texture_1_;
    static const std::vector<std::vector<int>> coin_texture_2_;
    static const std::vector<std::vector<int>> coin_texture_3_;
    static const std::vector<std::vector<int>> coin_texture_4_;
    static const std::vector<std::vector<int>> coin_texture_5_;
};

#endif