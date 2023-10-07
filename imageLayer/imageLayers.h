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
     imageLayers(std::map<std::string, imageLayer *> layers);

     bool add_layer(const std::string& layer_name, imageLayer *layer);
     void delete_layer(const std::string& layer_name);
     bool modify_layer(const std::string& layer_name, const imageLayer *layer);
     void add_or_modify_layer(const std::string& layer_name, const imageLayer *layer);

     imageLayer* find_layer(const std::string& layer_name);
     bool has_layer (const std::string& layer_name);
     std::vector<std::string> enumerateLayers();

     RGBA get_rgba_pixel(int x, int y);
    void get_rgba_pixel_fast(int x, int y, unsigned char &out_r, unsigned char &out_g, unsigned char &out_b,
                             unsigned char &out_a);
    void rande_directly(int x, int y, int i, DWORD* pbWnd);
    void get_rgba_pixel_fast2(int x, int y);
private:
    // std::vector<imageLayer> layers;
    std::map<std::string, imageLayer*> layers;



};




#endif //BANKAENGINE_IMAGELAYERS_H
