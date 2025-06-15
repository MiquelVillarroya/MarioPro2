#include "jutge.hh"


const int _ = -1;
const int b = pro2::black;
const int w = pro2::white;
const int m = 0x00ecdcc9;
const int d = 0x008e908f;
const int g = 0x00d5d5d5;
const int s = 0x00eeeeee;

const Sprite Jutge::jutge_texture_ = {
    {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
    {_,d,d,d,d,g,g,g,g,s,s,s,s,s,s,_},
    {d,d,d,g,g,g,g,g,g,g,g,g,s,s,s,s},
    {d,g,g,g,g,m,m,m,m,m,m,g,g,g,g,s},
    {_,g,g,m,m,m,m,m,m,m,m,m,m,g,g,_},
    {d,g,g,m,m,m,b,m,m,b,m,m,m,g,g,s},
    {d,g,g,m,m,m,b,m,m,b,m,m,m,g,g,s},
    {_,g,g,m,m,m,b,m,m,b,m,m,m,g,g,_},
    {d,g,g,m,m,m,m,m,m,m,m,m,m,g,g,s},
    {d,g,g,m,m,b,m,m,m,m,b,m,m,g,g,s},
    {_,d,d,m,m,m,b,b,b,b,m,m,m,s,s,_},
    {_,_,_,m,m,m,m,m,m,m,m,m,m,_,_,_},
    {_,_,b,b,b,b,b,w,w,b,b,b,b,b,_,_},
    {_,_,b,b,b,b,b,w,w,b,b,b,b,b,_,_},
    {_,b,b,b,b,b,w,w,w,w,b,b,b,b,b,_},
    {_,b,b,b,b,b,w,w,w,w,b,b,b,b,b,_},

};
