//
// Created by EinoPlasma on 2023/10/6.
//

#include <iostream>
#include "imageLayers.h"
#include <graphics.h>
#include <conio.h>
/*
imageLayer* imageLayers::get_layer(std::string layer_name) {
    if(layers.find(layer_name) == layers.end()){
        // key doesn't exist
        return nullptr;
    }
    return *layers[layer_name];
}
*/
imageLayers::imageLayers(std::map<std::basic_string<char>, imageLayer *> layers) {
    this->layers = layers;
}

imageLayer* imageLayers::find_layer(const std::string &layer_name) {
    auto it = layers.find(layer_name);
    if (it != layers.end()){
        // key found
        return reinterpret_cast<imageLayer *>(&it->second);
    } else {
        return nullptr;
    }
}

bool imageLayers::has_layer(const std::string &layer_name) {
    return layers.find(layer_name) != layers.end();
}

void imageLayers::delete_layer(const std::string &layer_name) {
    auto it = layers.find(layer_name);
    if (it != layers.end()) {
        layers.erase(it);
    }
}

bool imageLayers::modify_layer(const std::string &layer_name, const imageLayer *new_layer) {
    // Check if the layer exists
    auto it = layers.find(layer_name);
    if (it == layers.end()) {
        return false;  // Layer does not exist
    }

    // Update the layer
    it->second = const_cast<imageLayer*>(new_layer);
    return true;
}

std::vector<std::string> imageLayers::enumerateLayers() {
    std::vector<std::string> layer_names;
    for (const auto& pair : layers) {
        layer_names.push_back(pair.first);
    }
    return layer_names;
}

void imageLayers::add_or_modify_layer(const std::string &layer_name, const imageLayer *new_layer) {
    layers[layer_name] = const_cast<imageLayer*>(new_layer);
}

bool imageLayers::add_layer(const std::string &layer_name, imageLayer *layer) {
    if (has_layer(layer_name)) {
        return false;
    }

    layers[layer_name] = const_cast<imageLayer*>(layer);
    return true;
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
        std::string key = iter->first;
        return iter->second->get_rgba(x, y);
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
        std::string key = iter->first;
        iter->second->get_rgba_fast(x, y, out_r, out_g, out_b, out_a);
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
void imageLayers::rande_directly(int x, int y, int i, DWORD* pbWnd) {
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
    /*
    for(auto iter = layers.begin(); iter != layers.end(); iter++){
        std::string key = iter->first;
        iter->second->get_rgba_fast(x, y, r, g, b, a);
    }*/

    //layers["cg"]->get_rgba_fast(x, y, r, g, b, a);
    layers["cg"];
    r = 255;
    g = 255;
    b = 255;
    pbWnd[i] = RGB(r, g, b);

    //std::cout<<r<<g<<b<<a<<std::endl;

}