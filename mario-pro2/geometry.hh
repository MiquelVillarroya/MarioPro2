#ifndef GEOMETRY_HH
#define GEOMETRY_HH
#include <cmath>

namespace pro2 {

struct Pt {
    int x = 0, y = 0;
};

/**
 * @brief Compara dos punts del pla
 * 
 * La comparació és necessària per poder fer servir `Pt` com la clau d'un `map`.
 * La comparació utilitza primer la coordenada `x` (com si fos més "important"), 
 * i, quan les `x`s són iguals, la coordenada `y`.
 */
inline bool operator<(const Pt& a, const Pt& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

struct Rect {
    int left, top, right, bottom;
};

}

/**
 * @brief Check if two rectangles are intersecting. 
 * 
 * @param r1 First rectangle
 * @param r2 Second rectangle
 * 
 * @returns `true` if the rectangles intersect, `false` otherwise.
 */
inline bool checkCollision(const pro2::Rect& a, const pro2::Rect& b) {
    return (a.left <= b.right and b.left <= a.right
            and a.top <= b.bottom and b.top <= a.bottom);
}

/**
 * @brief Returns the euclidian norm (length) of a vector
 * 
 * @param p1 Point treated as a vector (origin point does not matter as we only compute the distance)
 * 
 * @returns Distance from (0,0) to the point, that corresponds to the length of the vector
 */
inline float vecNorm(const pro2::Pt& vec) {
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

#endif