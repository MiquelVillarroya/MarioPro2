#ifndef TEXT_HH
#define TEXT_HH

#include <vector>
#include <string>
#include "window.hh"
#include "globals.hh"

/**
 * @brief A text class that manages alphanumeric characters drawing.
 * It allows character from a-z, A-Z and 0-9 and both character, number and phrase drawing.
 */

class Text {
    private:
        /**
         * @brief Converts a string into an integer
         * 
         * @param n int to convert
         * 
         * @return An string corresponding to the input `n`
         */
        static std::string stoi(int n);

    public:
        Text() {};
    
        /**
         * @brief Paints a character in the screen
         * 
         * @param window window where to paint
         * @param pos top-left position of the sprite
         * @param c character to draw, between a-z or A-Z
         * @param col color of the character, black by default
         */
        void paint_char(pro2::Window& window, pro2::Pt pos, const char c, pro2::Color col = pro2::black) const;

        /**
         * @brief Paints a phrase in the screen
         * 
         * @param window window where to paint
         * @param pos top-left position of the sprite
         * @param c phrase to draw, characters between a-z or A-Z
         * @param col color of the characters, black by default
         */
        void paint_phrase(pro2::Window& window, pro2::Pt pos, const std::string word, pro2::Color col = pro2::black) const;

        /**
         * @brief Paints a number in the screen
         * 
         * @param window window where to paint
         * @param pos top-left position of the sprite
         * @param c number to draw, between 0-9
         * @param col color of the number, black by default
         */
        void paint_number(pro2::Window& window, pro2::Pt pos, const int n, pro2::Color col = pro2::black) const;

    private:
        static const std::vector<Sprite> alphabet_;
        static const std::vector<Sprite> numbers_;
};

#endif