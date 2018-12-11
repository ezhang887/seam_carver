#ifndef STRUCTS_H
#define STRUCTS_H

struct Color{
    int r;
    int g;
    int b;

    Color(int _r = 0, int _g = 0, int _b = 0){
        r = _r;
        g = _g;
        b = _b;
    }
};

struct FaceBounds{
    int x;
    int y;
    int upper_x;
    int upper_y;

    FaceBounds(int _x = 0, int _y = 0, int _upper_x = 0, int _upper_y = 0){
        x = _x;
        y = _y;
        upper_x = _upper_x;
        upper_y = _upper_y;
    }
};

#endif
