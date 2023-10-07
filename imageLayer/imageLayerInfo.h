//
// Created by EinoPlasma on 2023/10/7.
//

#ifndef BANKAENGINE_IMAGELAYERINFO_H
#define BANKAENGINE_IMAGELAYERINFO_H

#include <string>

namespace draw{
    class imageLayerInfo {
    public:
        int x;
        int y;

        imageLayerInfo(const std::string &name, int x, int y, int w, int h, int unique_id);
        std::string get_name();
        int get_unique_id();
        int get_w();
        int get_h();
    private:
        std::string name;
        int unique_id;
        int w;
        int h;
    };
}



#endif //BANKAENGINE_IMAGELAYERINFO_H
