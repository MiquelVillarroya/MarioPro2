#ifndef FINDER_HH
#define FINDER_HH

#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "geometry.hh"

//Idea: Given the problem condition, we can create a grid and check which rectangles intersect in each cell.
//The condition of maximum rectangles of 2000x2000 and a max position of 20000x20000 allows us to create a 10x10 grid.
//When querying a big rectangle we can avoid of checking all the inner cells and only check for the borders.
//We also require a map to relate pointers to rectangles, for implementing the remove function, if not, we would need to check all cells to find the rectangle to remove.

template <class T>
class Finder {
 private:

    static const int SIZE = 40000;
    static const int CELL_SIZE = 4000;
    //make sure that SIZE and CELL_SIZE are always perfectly divisible
    static const int CELL_NUM = SIZE/CELL_SIZE;

    typedef std::vector<std::unordered_set<const T*>> Row;
    std::vector<Row> grid; //Pointers are not required to be ordered, so an unordered_set is used for efficiency.

    std::unordered_map<const T*, pro2::Rect> idRect; //Map pointers-rectangles (doesn't require order)

    /**
    * @brief Check if two rectangles are intersecting. 
    * 
    * @param r1 First rectangle
    * @param r2 Second rectangle
    * 
    * @returns `true` if the rectangles intersect, `false` otherwise.
    */
    static bool checkCollision(const pro2::Rect& a, const pro2::Rect& b) {
    return (a.left <= b.right and b.left <= a.right
            and a.top <= b.bottom and b.top <= a.bottom);
    }

    /**
    * @brief Normalizes a rectangle according to `CELL_SIZE`, giving the index cell of it's position. 
    * The far right and bottom border are included in the last cell.
    * 
    * @param a Rectangle
    * 
    * @returns `a` normalized
    */
    static pro2::Rect normalize(pro2::Rect a) {
        if (a.right == SIZE) --a.right;
        if (a.bottom == SIZE) --a.bottom;
        a.left /= CELL_SIZE;
        a.top /= CELL_SIZE;
        a.right /= CELL_SIZE;
        a.bottom /= CELL_SIZE;
        return a;
    }

 public:
    Finder() : grid(CELL_NUM, Row(CELL_NUM)) {}
    Finder(const std::list<T>& v) : grid(CELL_NUM, Row(CELL_NUM)) {
        for (const auto& obj: v) {
            add(&obj);
        }
    }
    Finder(const std::list<T*>& v) : grid(CELL_NUM, Row(CELL_NUM)) {
        for (const auto& obj: v) {
            add(obj);
        }
    }

    void add(const T *t) {
        idRect[t] = t->get_rect();
        pro2::Rect r = normalize(t->get_rect());

        //We check for the 3 options of a rectangle: all in one cell, intersecting 2 cells, or intersecting 4 cells.
        grid[r.top][r.left].insert(t);
        if (r.left != r.right and r.top != r.bottom) {
            grid[r.top][r.right].insert(t);
            grid[r.bottom][r.left].insert(t);
            grid[r.bottom][r.right].insert(t);
        }
        else if (r.left != r.right) grid[r.top][r.right].insert(t);
        else if (r.top != r.bottom) grid[r.bottom][r.left].insert(t);
    }
    
    void update(const T *t) {
        remove(t);
        add(t);
    }

    void remove(const T *t) {
        auto it = idRect.find(t);
        if (it == idRect.end()) return; //Check that element exists
        pro2::Rect r = normalize(it->second);

        grid[r.top][r.left].erase(t);
        if (r.left != r.right and r.top != r.bottom) {
            grid[r.top][r.right].erase(t);
            grid[r.bottom][r.left].erase(t);
            grid[r.bottom][r.right].erase(t);
        }
        else if (r.left != r.right) grid[r.top][r.right].erase(t);
        else if (r.top != r.bottom) grid[r.bottom][r.left].erase(t);
        idRect.erase(it);
    }

    std::set<const T*> query(pro2::Rect qrect) const {
        pro2::Rect r = normalize(qrect);
        std::set<const T*> s;

        //Horizontal borders check (including corners)
        for (int x = r.left; x <= r.right; ++x) {
            for (const T* obj : grid[r.top][x]) {
                if (checkCollision(obj->get_rect(), qrect)) s.insert(obj);
            }
            for (const T* obj : grid[r.bottom][x]) {
                if (checkCollision(obj->get_rect(), qrect)) s.insert(obj);
            }
        }

        //Vertical borders check (no corners)
        for (int y = r.top + 1; y < r.bottom; ++y) {
            for (const T* obj : grid[y][r.left]) {
                if (checkCollision(obj->get_rect(), qrect)) s.insert(obj);
            }
            for (const T* obj : grid[y][r.right]) {
                if (checkCollision(obj->get_rect(), qrect)) s.insert(obj);
            }
        }

        //Interior cells (no collision check necessary)
        for (int x = r.left + 1; x < r.right; ++x) {
            for (int y = r.top + 1; y < r.bottom; ++y) {
                s.insert(grid[y][x].begin(), grid[y][x].end());
            }
        }
        
        return s;
    }
};

#endif