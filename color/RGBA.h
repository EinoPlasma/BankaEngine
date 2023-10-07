//
// Created by EinoPlasma on 2023/10/6.
//
#include <vector>
#ifndef BANKAENGINE_RGBA_H
#define BANKAENGINE_RGBA_H


class RGBA {
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

     RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
};

struct RGBA rgba_blend(std::vector<RGBA> rgbas);





#endif //BANKAENGINE_RGBA_H
