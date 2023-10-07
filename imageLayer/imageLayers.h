//
// Created by EinoPlasma on 2023/10/6.
//
#include <vector>
#include <map>
#include <conio.h>
#include <graphics.h>
#include "imageLayer.h"
#include "../color/RGBA.h"

#ifndef BANKAENGINE_IMAGELAYERS_H
#define BANKAENGINE_IMAGELAYERS_H


extern unsigned char extern_rgba[4];

class imageLayers {
public:
     imageLayers(std::vector<imageLayer> layers);

     bool add_layer(const imageLayer *layer);
     void delete_layer_by_name(const std::string& layer_name);
     void delete_layer_by_index(const int index);
     bool modify_layer(const std::string& layer_name, const imageLayer *layer);
     void add_or_modify_layer(const std::string& layer_name, imageLayer *layer);

     imageLayer* find_layer(const std::string& layer_name);
     bool has_layer (const std::string& layer_name);
     std::vector<std::string> enumerateLayers();

     RGBA get_rgba_pixel(int x, int y);
    void get_rgba_pixel_fast(int x, int y, unsigned char &out_r, unsigned char &out_g, unsigned char &out_b,
                             unsigned char &out_a);
    void rande_directly_pixel(int x, int y, int i, DWORD* pbWnd);
    void rande_directly_box(int x1, int y1, int x2, int y2, DWORD *pbWnd, int buffer_w, int buffer_h);
    void get_rgba_pixel_fast2(int x, int y);

    bool add_layer(imageLayer *layer);

private:
    std::vector<imageLayer> layers;
    // imageLayer layers_fast[100];
    // std::map<std::string, imageLayer*> layers;



};




#endif //BANKAENGINE_IMAGELAYERS_H
