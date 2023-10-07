//
// Created by EinoPlasma on 2023/10/6.
//

#include "imageLayer.h"
#include "../stb_image.h"

imageLayer::imageLayer(const std::string &name, int x, int y, int w, int h, unsigned char *img_data) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->img_data = img_data;
    this->
}

RGBA imageLayer::get_rgba(int x, int y) {
    if(x >= this->x && x < this->x + this->w && y >= this->y && y < this->y + this->h){
        // 欲求点在图片区域内
        int local_x, local_y;
        local_x = x - this->x;
        local_y = y - this->y;
        int pixel_index = local_y * this->w + local_x;
        unsigned char b,g,r,a;
        b = img_data[pixel_index*4];
        g = img_data[pixel_index*4 + 1];
        r = img_data[pixel_index*4 + 2];
        a = img_data[pixel_index*4 + 3];
        return {r, g, b, a};
    } else {
        return {0, 0, 0, 0};
    }
}

void imageLayer::get_rgba_fast(int x, int y, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a) {

    if(x >= this->x && x < this->x + this->w && y >= this->y && y < this->y + this->h){
        // 欲求点在图片区域内
        int local_x, local_y;
        local_x = x - this->x;
        local_y = y - this->y;
        int pixel_index = local_y * this->w + local_x;
        b = img_data[pixel_index*4];
        g = img_data[pixel_index*4 + 1];
        r = img_data[pixel_index*4 + 2];
        a = img_data[pixel_index*4 + 3];
    } else {
        r = 0;
        g = 0;
        b = 0;
        a = 0;
    }
}
/*
extern unsigned char extern_rgba[4];
void imageLayer::get_rgba_fast2(int x, int y) const {
    if(x >= this->x && x < this->x + this->w && y >= this->y && y < this->y + this->h){
        // 欲求点在图片区域内
        int local_x, local_y;
        local_x = x - this->x;
        local_y = y - this->y;
        int pixel_index = local_y * this->w + local_x;
        extern_rgba[2] = img_data[pixel_index*4];
        extern_rgba[1] = img_data[pixel_index*4 + 1];
        extern_rgba[0] = img_data[pixel_index*4 + 2];
        extern_rgba[3] = img_data[pixel_index*4 + 3];
    } else {
        extern_rgba[2] = 0;
        extern_rgba[1] = 0;
        extern_rgba[0] = 0;
        extern_rgba[3] = 0;
    }
}*/
bool imageLayer::set_rgba(int x, int y, RGBA rgba) {
    /* 已废弃：传入坐标为绝对坐标
     *
    if(x >= this->x && x < this->x + this->w && y >= this->y && y < this->y + this->h){
        // 欲设点在图片区域内
        int local_x, local_y;
        local_x = x - this->x;
        local_y = y - this->y;
        int pixel_index = local_y * this->w + local_x;

        img_data[pixel_index*4] = rgba.b;
        img_data[pixel_index*4 + 1] = rgba.g;
        img_data[pixel_index*4 + 2] = rgba.r;
        img_data[pixel_index*4 + 3] = rgba.a;
        return true;
    } else {
        return false;
    }
     */
    if(x < this->w &&y < this->h){
        // 欲设点在图片区域内
        int pixel_index = y * this->w + x;

        img_data[pixel_index*4] = rgba.b;
        img_data[pixel_index*4 + 1] = rgba.g;
        img_data[pixel_index*4 + 2] = rgba.r;
        img_data[pixel_index*4 + 3] = rgba.a;
        return true;
    } else {
        return false;
    }
}

void imageLayer::set_x(int x) {
    this->x = x;
}

void imageLayer::set_y(int y) {
    this->y = y;
}

std::string imageLayer::get_name() {
    return name;
}




