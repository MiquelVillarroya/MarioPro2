#ifndef TEXT_HH
#define TEXT_HH

#include <vector>
#include <string>
#include "window.hh"

typedef std::vector<std::vector<int>> Sprite;

class Text {
    private:

    static const int width = 8;

    static const std::vector<Sprite> alphabet;
    static const std::vector<Sprite> numbers;

    static std::string stoi(int n);
    public:
        Text() {};
        
        void paint_char(pro2::Window& window, int x, int y, char c, pro2::Color col = pro2::black) const;
        void paint_phrase(pro2::Window& window, int x, int y, std::string phrase, pro2::Color col = pro2::black) const;
        void paint_number(pro2::Window& window, int x, int y, int n, pro2::Color col = pro2::black) const;
        
        int get_width() {
            return width;
        }
};

#endif