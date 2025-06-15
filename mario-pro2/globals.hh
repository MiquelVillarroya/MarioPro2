#ifndef GLOBALS_HH
#define GLOBALS_HH

#include <vector>

#define FPS     48
#define FONT_SIZE 8
typedef std::vector<std::vector<int>> Sprite;

enum class movType {
   NONE, LINEAR, CIRCULAR
};

enum class PartType {
    COIN, JUMP
};

#endif