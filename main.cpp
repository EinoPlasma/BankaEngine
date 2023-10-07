#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "imageLayer/imageLayer.h"
#include "imageLayer/imageLayers.h"
#include "imageLayer/imageLayerDrawer.h"
#include "imageLayer/imageLayerInfo.h"


void _add_layer(draw::imageLayerDrawer *image_layer_drawer, std::string name, int unique_id, std::string file_path){
    int w, h, n;
    unsigned char *img_data = stbi_load(file_path.c_str(), &w, &h, &n, 0);
    draw::imageLayerInfo layer_info = draw::imageLayerInfo(name, 0, 0, w, h, unique_id);
    image_layer_drawer->add_layer(&layer_info, img_data);
}

int main()
{

    std::cout << "Hello, STB_Image" << std::endl;

    std::string inputPath = "C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/data/ev/14.png";
    int iw, ih, n;

    // 加载图片获取宽、高、颜色通道信息
    unsigned char *img_data = stbi_load(inputPath.c_str(), &iw, &ih, &n, 0);

    std::cout<<int(img_data[0])<<int(img_data[1])<<int(img_data[2])<<std::endl;







    // 初始化绘图窗口
    initgraph(1920, 1080);

    // 定义并加载图片
    IMAGE img;
    loadimage(&img, _T("C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/data/ev/14.png"));

    // 获取绘图窗口和 img 对象的显示缓冲区指针
    DWORD* pbWnd = GetImageBuffer();
    DWORD* pbImg = GetImageBuffer(&img);


    imageLayers image_layers = imageLayers({});

    // 先创建一个 imageLayer 对象
    imageLayer layer_cg("cg", 0, 0, 1920, 1080, img_data);



    inputPath = "C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/data/image/logo.png";
    unsigned char *img_logo_data = stbi_load(inputPath.c_str(), &iw, &ih, &n, 0);
    imageLayer layer_logo("logo", 0,0,1920,1080, img_logo_data);

    inputPath = "C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/data/image/transparent.png";
    unsigned char *img_transparent_data = stbi_load(inputPath.c_str(), &iw, &ih, &n, 0);
    imageLayer layer_transparent("transparent", 0,0,1920,1080, img_transparent_data);

    // load_from_file("C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/data/image/アイキャッチ_ロゴ.png", &layer_logo, 0, 0);
    std::cout<<layer_logo.get_rgba(0, 0).r<<std::endl;
    // 然后将其地址传递给 add_layer 函数

    image_layers.add_layer(&layer_cg);
    image_layers.add_layer(&layer_logo);
    image_layers.add_layer(&layer_transparent);
    image_layers.add_layer(&layer_transparent);
    image_layers.add_layer(&layer_transparent);
    image_layers.add_layer(&layer_transparent);
    image_layers.add_layer(&layer_transparent);
    image_layers.add_layer(&layer_transparent);
    image_layers.add_layer(&layer_transparent);





    std::cout<<"ready"<<std::endl;
    // 计算原图片每个点的颜色，实现逐渐变量的效果
    // int r, g, b;
    unsigned char r,g,b,a;
    int x, y;
    const int screen_w = 1920, screen_h = 1080;
    for (int offset = 0; offset < 1500; offset+=10){
        continue;
        //std::cout<<image_layers.find_layer("cg")->x<<std::endl;
        layer_cg.set_x(offset);
        Sleep(0);
        //std::cout<<"render"<<std::endl;

        //extern unsigned char extern_rgba[4];
        image_layers.rande_directly_box(0,0,1920,1080,pbWnd,1920,1080);
        for (int i = 0; i < screen_w * screen_h; i++)
        {
            /*
            r = GetRValue(pbImg[i]);;
            g = GetGValue(pbImg[i]);;
            b = GetBValue(pbImg[i]);;*/

            /*
            b = img_data[i*4];
            g = img_data[i*4 + 1];
            r = img_data[i*4 + 2];

            pbWnd[(i+offset)%(screen_w * screen_h)] = RGB(r, g, b);
            // 能跑53fps
             */

            //x = i % screen_w;
            //y = int(i / screen_w);
            //RGBA rgba = image_layers.get_rgba_pixel(x, y);

            /*
            // 能跑6.5fps
            image_layers.get_rgba_pixel_fast(x, y, r, g, b, a);

            pbWnd[i] = RGB(r, g, b);*/
            //pbWnd[i] = RGB(rgba.r, rgba.g, rgba.b);

            //image_layers.rande_directly_pixel(x, y, i, pbWnd);
            // 能跑6.5fps 27s

            //image_layers.get_rgba_pixel_fast2(x, y);
            //pbWnd[i] = RGB(extern_rgba[0], extern_rgba[1], extern_rgba[2]);

            //pbWnd[i] = 16775157;
            //4.2s 1500frames 能跑360fps

            //pbWnd[i] = RGB(255,0,0);
            //4.2s 1500frames 能跑360fps

            //int tmp_r = 255, tmp_g = 0, tmp_b = 0;
            //pbWnd[i] = RGB(tmp_r, tmp_g, tmp_b);
            // 7.5s 1500frames 200fps

            // r=255;g=0;b=0;
            // pbWnd[i] = RGB(r, g, b);
            // 8.2s 1500frames
        }
    }

    std::cout<<"render finished"<<std::endl;




    draw::imageLayerInfo layer_cg_info = draw::imageLayerInfo("cg", 0, 0, 1920, 1080, 0);
    draw::imageLayerInfo layer_logo_info = draw::imageLayerInfo("logo", 0, 0, 1920, 1080, 1);
    draw::imageLayerInfo layer_transparent_info = draw::imageLayerInfo("transparent", 0, 0, 1920, 1080, 2);

    draw::imageLayerDrawer image_layer_drawer = draw::imageLayerDrawer();
    image_layer_drawer.add_layer(&layer_cg_info, img_data);
    image_layer_drawer.add_layer(&layer_logo_info, img_logo_data);
    image_layer_drawer.add_layer(&layer_transparent_info, img_transparent_data);

    //_add_layer(&image_layer_drawer, "jizhongxian", 3, "C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/data/image/jzx.png");
    //_add_layer(&image_layer_drawer, "sd", 4, "C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/data/ev/SD/SD003DA.PNG");


    // std::cout<<image_layer_drawer.image_layer_infos[4]->get_w()<<std::endl;


    int w, h, in;
    std::string file_path = "C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/data/image/jzx.png";
    unsigned char *img_jizhongxian_data = stbi_load(file_path.c_str(), &w, &h, &in, 0);
    draw::imageLayerInfo layer_info = draw::imageLayerInfo("jzx", 0, 0, w, h, 3);
    image_layer_drawer.add_layer(&layer_info, img_jizhongxian_data);



    std::cout<<"ready2"<<std::endl;
    for(int i = 0; i < 1500; i+=10){
        image_layer_drawer.render_directly_box(0,0,1920,1080,pbWnd,1920,1080);
        image_layer_drawer.image_layer_infos[0]->x=i;
    }


    std::cout<<"render finished"<<std::endl;


    // 按任意键退出
    _getch();
    closegraph();
    return 0;




}