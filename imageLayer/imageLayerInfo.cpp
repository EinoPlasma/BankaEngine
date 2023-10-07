//
// Created by EinoPlasma on 2023/10/7.
//

#include "imageLayerInfo.h"

draw::imageLayerInfo::imageLayerInfo(const std::string &name, int x, int y, int w, int h, int unique_id) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->name = name;
    this->unique_id = unique_id;
}

std::string draw::imageLayerInfo::get_name() {
    return name;
}

int draw::imageLayerInfo::get_unique_id() {
    return unique_id;
}

int draw::imageLayerInfo::get_w() {
    return w;
}

int draw::imageLayerInfo::get_h() {
    return h;
}
