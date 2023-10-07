//
// Created by EinoPlasma on 2023/10/7.
//

#include <string>
#include <vector>
#include <graphics.h>
#include "imageLayerInfo.h"

#ifndef BANKAENGINE_IMAGELAYERDRAWER_H
#define BANKAENGINE_IMAGELAYERDRAWER_H

#define IMAGELAYER_CAPACITY 255

namespace draw {

    class imageLayerDrawer {
    public:
        imageLayerDrawer();
        void render_directly_box(int x1, int y1, int x2, int y2, DWORD* pbWnd, int buffer_w, int buffer_h);
        bool add_layer(imageLayerInfo *layer_info, unsigned char *img_data);
        imageLayerInfo *image_layer_infos[IMAGELAYER_CAPACITY]{};
    private:
        int layer_count = 0;
        unsigned char *img_datas[IMAGELAYER_CAPACITY]{};

    };

} // draw

#endif //BANKAENGINE_IMAGELAYERDRAWER_H
