#include "utils.hh"
#include "globals.hh"
using namespace std;

namespace pro2 {

void paint_hline(pro2::Window& window, int xini, int xfin, int y, Color color) {
    for (int x = xini; x <= xfin; x++) {
        window.set_pixel({x, y}, color);
    }
}

void paint_vline(pro2::Window& window, int x, int yini, int yfin, Color color) {
    for (int y = yini; y <= yfin; y++) {
        window.set_pixel({x, y}, color);
    }
}

void paint_rect(pro2::Window& window, Rect rect, Color color) {
    for (int x = rect.left; x <= rect.right; ++x)
        for (int y = rect.top; y <= rect.bottom; ++y)
            window.set_pixel({x, y}, color);
}

void paint_sprite(pro2::Window&              window,
                  pro2::Pt                   orig,
                  const vector<vector<int>>& sprite,
                  bool                       mirror,
                  pro2::Color                col    ) {
    for (int i = 0; i < sprite.size(); i++) {
        const vector<int>& line = sprite[i];
        for (int j = 0; j < line.size(); j++) {
            const int _j = mirror ? line.size() - j - 1 : j;
            if (line[_j] >= 0) {
                window.set_pixel({orig.x + j, orig.y + i}, line[_j]);
            }
            else if (line[_j] == -2) {
                window.set_pixel({orig.x + j, orig.y + i}, col);
            }
        }
    }
}

void paint_sprite(pro2::Window&              window,
                  pro2::Pt                   orig,
                  const vector<vector<int>>& sprite,
                  pro2::Color                col    ) {
    paint_sprite(window, orig, sprite, false, col);          
}

int get_phrase_displacement(std::string phrase) {
    float n = phrase.size()/2;
    if (phrase.size() % 2 != 0) n += 0.5;
    return int(n*FONT_SIZE);
}


}  // namespace pro2