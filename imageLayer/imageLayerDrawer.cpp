//
// Created by EinoPlasma on 2023/10/7.
//

#include <iostream>
#include "imageLayerDrawer.h"

namespace draw {
    bool imageLayerDrawer::add_layer(imageLayerInfo *layer_info, unsigned char *img_data) {
        if (layer_count > IMAGELAYER_CAPACITY) {
            std::cout<<"add layer failed, exceed the IMAGELAYER_CAPACITY"<<std::endl;
            return false;
        }

        layer_count += 1;
        int cur = layer_count - 1;
        image_layer_infos[cur] = layer_info;
        img_datas[cur] = img_data;
        return true;
    }

    int layers_x[IMAGELAYER_CAPACITY];
    int layers_y[IMAGELAYER_CAPACITY];
    int layers_w[IMAGELAYER_CAPACITY];
    int layers_h[IMAGELAYER_CAPACITY];
    int layer_x, layer_y, layer_h, layer_w;

    void
    imageLayerDrawer::render_directly_box(int x1, int y1, int x2, int y2, DWORD *pbWnd, int buffer_w, int buffer_h) {
        float a;
        float b;
        float g;
        float r;

        float tmp_a;
        float tmp_b;
        float tmp_g;
        float tmp_r;

        float tmp_a_float;

        int buffer_cur;
        int buffer_max_index = buffer_w * buffer_h - 1;

        for(int i=0; i<layer_count; i++){
            // 把this.image_layer_infos里需要的信息拷贝到本地数组备用，免得等下渲染时每个像素点都访问一次this.image_layer_infos这个object
            layers_x[i] = image_layer_infos[i]->x;
            layers_y[i] = image_layer_infos[i]->y;
            layers_w[i] = image_layer_infos[i]->get_w();
            layers_h[i] = image_layer_infos[i]->get_h();
        }


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

                for(int layer_index = begin_layer_index; layer_index < layer_count; layer_index++){
                    layer_x = layers_x[layer_index];
                    layer_y = layers_y[layer_index];
                    layer_w = layers_w[layer_index];
                    layer_h = layers_h[layer_index];
                    if(cur_x >= layer_x && cur_x < layer_x + layer_w && cur_y >= layer_y && cur_y < layer_y + layer_h){
                        // 欲求点在图片区域内
                        int local_x, local_y;
                        local_x = cur_x - layer_x;
                        local_y = cur_y - layer_y;
                        int pixel_index = local_y * layer_w + local_x;

                        tmp_a = img_datas[layer_index][pixel_index*4 + 3];
                        if(tmp_a == 0) continue;
                        tmp_b = img_datas[layer_index][pixel_index*4];
                        tmp_g = img_datas[layer_index][pixel_index*4 + 1];
                        tmp_r = img_datas[layer_index][pixel_index*4 + 2];


                        if (tmp_a == 255) {
                            a = 255;
                            r = tmp_r;
                            g = tmp_g;
                            b = tmp_b;
                        } else if (tmp_a != 0){
                            // alpha==0的话就不更新颜色值
                            a = (a * (1 - tmp_a/255)) + tmp_a/255 * tmp_a;
                            r = (r * (1 - tmp_a/255)) + tmp_a/255 * tmp_r;
                            g = (g * (1 - tmp_a/255)) + tmp_a/255 * tmp_g;
                            b = (b * (1 - tmp_a/255)) + tmp_a/255 * tmp_b;
                        }
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

    imageLayerDrawer::imageLayerDrawer() {
    }
} // draw