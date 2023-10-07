//
// Created by EinoPlasma on 2023/10/6.
//

#include "../color/RGBA.h"
#include <string>

#ifndef BANKAENGINE_IMAGELAYER_H
#define BANKAENGINE_IMAGELAYER_H


extern unsigned char extern_rgba[4];

class imageLayer {
public:
    int x;
    int y;
    unsigned char *img_data; //一维数组，顺序为bgra

    imageLayer(const std::string& name, int x, int y, int w, int h, unsigned char *img_data);
    std::string get_name();

    RGBA get_rgba(int x, int y);
    bool set_rgba(int x, int y, RGBA rgba);
    void set_x(int x);
    void set_y(int y);

    void get_rgba_fast(int x, int y, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a);
    void get_rgba_fast2(int x, int y) const;

private:
    std::string name;
    int w;
    int h;



};
/*
bool load_from_file(const std::string& path, imageLayer *layer, int x=0, int y=0) {
    int w, h, n;
    unsigned char *img_data = stbi_load(path.c_str(), &w, &h, &n, 0);
    if (img_data == nullptr){
        return false;
    }

    if (layer == nullptr) {
        return false;
    }

    layer = new imageLayer(x, y, w, h, img_data);

    if (layer == nullptr) {
        return false;
    }

    return true;
}*/
// bool load_from_file(const std::string& path, imageLayer *layer, int x=0, int y=0);
#endif //BANKAENGINE_IMAGELAYER_H
