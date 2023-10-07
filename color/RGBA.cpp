//
// Created by EinoPlasma on 2023/10/6.
//

#include "RGBA.h"
#include <vector>

RGBA::RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}


struct RGBA rgba_blend(std::vector<RGBA> rgbas){
    if(rgbas.size() == 1){
        // 列表里只有一个颜色就直接返回
        return rgbas[0];
    }
    struct RGBA background = rgbas[0];
    unsigned char a = background.a;
    unsigned char r = background.r;
    unsigned char g = background.g;
    unsigned char b = background.b;
    for (int i = 1; i < rgbas.size(); i++){
        a = (a * (1 - rgbas[i].a/255)) + (rgbas[i].a/255 * rgbas[i].a);
        r = (r * (1 - rgbas[i].a/255)) + (rgbas[i].a/255 * rgbas[i].r);
        g = (g * (1 - rgbas[i].a/255)) + (rgbas[i].a/255 * rgbas[i].g);
        b = (b * (1 - rgbas[i].a/255)) + (rgbas[i].a/255 * rgbas[i].b);
    }
    rgbas.clear();
    return {r, g, b, a};
}


