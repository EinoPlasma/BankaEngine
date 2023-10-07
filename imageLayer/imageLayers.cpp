//
// Created by EinoPlasma on 2023/10/6.
//

#include <iostream>
#include <utility>
#include "imageLayers.h"
#include <graphics.h>
#include <conio.h>
// Initialize extern_rgba
unsigned char extern_rgba[4];

imageLayers::imageLayers(std::vector<imageLayer> layers) : layers(layers) {}

bool imageLayers::add_layer(imageLayer *layer) {
    // Add a layer to the vector
    layers.push_back(*layer);
    return true;
}

void imageLayers::delete_layer_by_name(const std::string &layer_name) {
    // Iterate through layers to find and delete by name
    for (auto it = layers.begin(); it != layers.end(); ++it) {
        if (it->get_name() == layer_name) {
            layers.erase(it);
            break;  // Exit loop after deleting the layer
        }
    }
}

void imageLayers::delete_layer_by_index(const int index) {
    // Check if the index is valid before deleting
    if (index >= 0 && index < layers.size()) {
        layers.erase(layers.begin() + index);
    }
}

bool imageLayers::modify_layer(const std::string &layer_name, const imageLayer *layer) {
    // Iterate through layers to find and modify by name
    for (auto &l : layers) {
        if (l.get_name() == layer_name) {
            l = *layer;
            return true;
        }
    }
    return false;  // Layer not found
}
/*
void imageLayers::add_or_modify_layer(const std::string &layer_name, const imageLayer *layer) {
    // Check if the layer already exists, if not, add it
    for (auto &l : layers) {
        if (l.get_name() == layer_name) {
            l = *layer;
            return;
        }
    }
    // If not found, add a new layer
    add_layer(layer);
}*/

imageLayer *imageLayers::find_layer(const std::string &layer_name) {
    // Iterate through layers to find and return by name
    for (auto &l : layers) {
        if (l.get_name() == layer_name) {
            return &l;
        }
    }
    return nullptr;  // Layer not found
}

bool imageLayers::has_layer(const std::string &layer_name) {
    // Check if a layer with the given name exists
    for (auto &l : layers) {
        if (l.get_name() == layer_name) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> imageLayers::enumerateLayers() {
    std::vector<std::string> layerNames;
    // Extract layer names from the layers vector
    for (imageLayer l : layers) {
        layerNames.push_back(l.get_name());
    }
    return layerNames;
}


RGBA imageLayers::get_rgba_pixel(int x, int y) {
    /*
    std::vector<RGBA> rgbas;
    for(auto iter = layers.begin(); iter != layers.end(); iter++){
        std::string key = iter->first;
        rgbas.push_back(iter->second->get_rgba(x, y));
    }
    return rgba_blend(rgbas);*/

    //std::cout<<"少一层抽象快很多"<<std::endl;
    for(auto iter = layers.begin(); iter != layers.end(); iter++){
        return iter->get_rgba(x, y);
    }
}


void imageLayers::get_rgba_pixel_fast(int x, int y, unsigned char &out_r, unsigned char &out_g, unsigned char &out_b, unsigned char &out_a) {
    /*
    std::vector<RGBA> rgbas;
    for(auto iter = layers.begin(); iter != layers.end(); iter++){
        std::string key = iter->first;
        rgbas.push_back(iter->second->get_rgba(x, y));
    }
    return rgba_blend(rgbas);*/

    //std::cout<<"少一层抽象快很多"<<std::endl;
    unsigned char a;
    unsigned char b;
    unsigned char g;
    unsigned char r;
    for(auto iter = layers.begin(); iter != layers.end(); iter++){
        iter->get_rgba_fast(x, y, out_r, out_g, out_b, out_a);
    }
    //std::cout<<r<<g<<b<<a<<std::endl;

}
/*
extern unsigned char extern_rgba[4];
void imageLayers::get_rgba_pixel_fast2(int x, int y) {


    //std::cout<<"少一层抽象快很多"<<std::endl;
    for(auto iter = layers.begin(); iter != layers.end(); iter++){
        std::string key = iter->first;
        iter->second->get_rgba_fast2(x, y);
    }
    std::cout<<r<<g<<b<<a<<std::endl;

}*/
void imageLayers::rande_directly_pixel(int x, int y, int i, DWORD* pbWnd) {
    /*
    std::vector<RGBA> rgbas;
    for(auto iter = layers.begin(); iter != layers.end(); iter++){
        std::string key = iter->first;
        rgbas.push_back(iter->second->get_rgba(x, y));
    }
    return rgba_blend(rgbas);*/

    //std::cout<<"少一层抽象快很多"<<std::endl;
    float a;
    float b;
    float g;
    float r;

    unsigned char tmp_a;
    unsigned char tmp_b;
    unsigned char tmp_g;
    unsigned char tmp_r;

    float tmp_a_float;

    /*
     * 然而实测并不一定能加速
    int begin_layer_index; // （忽略被遮挡后的像素）从array最后一个元素开始找，把最先找到的那个alpha==255的layer_index作为混合颜色的起始index，忽略再往后的像素点
    for(begin_layer_index = layers.size() - 1; begin_layer_index>=0; begin_layer_index--){
        if (layers[begin_layer_index].is_opaque(x, y)) {
            break;
        }
    }*/

    layers[0].get_rgba_fast(x, y, tmp_r, tmp_g, tmp_b, tmp_a);
    a = float(tmp_a);
    r = float(tmp_r);
    g = float(tmp_g);
    b = float(tmp_b);
    for(int j=1; j<layers.size(); j++){
        layers[j].get_rgba_fast(x, y, tmp_r, tmp_g, tmp_b, tmp_a);
        if (tmp_a == 255){
            a = 255;
            r = tmp_r;
            g = tmp_g;
            b = tmp_b;
        } else if (tmp_a != 0) {
            // alpha==0的话就不更新颜色值
            tmp_a_float = float(tmp_a);
            a = (a * (1 - tmp_a_float/255)) + tmp_a_float/255 * tmp_a_float;
            r = (r * (1 - tmp_a_float/255)) + tmp_a_float/255 * float(tmp_r);
            g = (g * (1 - tmp_a_float/255)) + tmp_a_float/255 * float(tmp_g);
            b = (b * (1 - tmp_a_float/255)) + tmp_a_float/255 * float(tmp_b);
        }
    }


    pbWnd[i] = RGB(r, g, b);

    //std::cout<<RGB(r, g, b)<<std::endl;

    //std::cout<<r<<g<<b<<a<<std::endl;

}
void imageLayers::rande_directly_box(int x1, int y1, int x2, int y2, DWORD* pbWnd, int buffer_w, int buffer_h) {
    float a;
    float b;
    float g;
    float r;

    unsigned char tmp_a;
    unsigned char tmp_b;
    unsigned char tmp_g;
    unsigned char tmp_r;

    float tmp_a_float;

    int buffer_cur;
    int buffer_max_index = buffer_w * buffer_h - 1;
    int layer_count = layers.size();

    for(int cur_y=y1; cur_y<=y2; cur_y++){
        for(int cur_x=x1; cur_x<=x2; cur_x++){


            int begin_layer_index = 0;
            /*
            // （忽略被遮挡后的像素）从array最后一个元素开始找，把最先找到的那个alpha==255的layer_index作为混合颜色的起始index，忽略再往后的像素点
            // 然而实测并不一定能加速
            for(begin_layer_index = layers.size() - 1; begin_layer_index>=0; begin_layer_index--){
                if (layers[begin_layer_index].is_opaque(cur_x, cur_y)) {
                    break;
                }
            }*/

            layers[begin_layer_index].get_rgba_fast(cur_x, cur_y, tmp_r, tmp_g, tmp_b, tmp_a);
            a = float(tmp_a);
            r = float(tmp_r);
            g = float(tmp_g);
            b = float(tmp_b);
            for(int j=begin_layer_index + 1; j<layer_count; j++){
                layers[j].get_rgba_fast(cur_x, cur_y, tmp_r, tmp_g, tmp_b, tmp_a);
                if (tmp_a == 255){
                    a = 255;
                    r = tmp_r;
                    g = tmp_g;
                    b = tmp_b;
                } else if (tmp_a != 0) {
                    // alpha==0的话就不更新颜色值
                    tmp_a_float = float(tmp_a);
                    a = (a * (1 - tmp_a_float/255)) + tmp_a_float/255 * tmp_a_float;
                    r = (r * (1 - tmp_a_float/255)) + tmp_a_float/255 * float(tmp_r);
                    g = (g * (1 - tmp_a_float/255)) + tmp_a_float/255 * float(tmp_g);
                    b = (b * (1 - tmp_a_float/255)) + tmp_a_float/255 * float(tmp_b);
                }
            }

            buffer_cur = cur_x + cur_y * buffer_w;
            if(buffer_cur > buffer_max_index) break;
            pbWnd[buffer_cur] = RGB(r, g, b);

            //std::cout<<RGB(r, g, b)<<" "<<buffer_cur<<std::endl;

            //std::cout<<r<<g<<b<<a<<std::endl;
        }
    }

    // std::cout<<" draw finished "<<buffer_cur<<std::endl;
}