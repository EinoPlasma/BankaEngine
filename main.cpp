#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "imageLayer/imageLayer.h"
#include "imageLayer/imageLayers.h"


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
    loadimage(&img, _T("C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/data/ev/14.png"));	// 请确保该图片是 640x480 像素

    // 获取绘图窗口和 img 对象的显示缓冲区指针
    DWORD* pbWnd = GetImageBuffer();
    DWORD* pbImg = GetImageBuffer(&img);


    imageLayers image_layers = imageLayers({});

    // 先创建一个 imageLayer 对象
    imageLayer layer_cg(0, 0, 1920, 1080, img_data);
    imageLayer layer_logo(0,0,0,0, nullptr);

    // load_from_file("C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/data/image/アイキャッチ_ロゴ.png", &layer_logo, 0, 0);
    // 然后将其地址传递给 add_layer 函数
    image_layers.add_layer("cg", &layer_cg);
    //image_layers.add_layer("logo", &layer_logo);

    std::cout<<"ready"<<std::endl;
    // 计算原图片每个点的颜色，实现逐渐变量的效果
    // int r, g, b;
    unsigned char r,g,b,a;
    int x, y;
    const int screen_w = 1920, screen_h = 1080;
    for (int offset = 0; offset < 1500; offset+=10){
        //std::cout<<image_layers.find_layer("cg")->x<<std::endl;
        layer_cg.set_x(offset);
        Sleep(0);
        //std::cout<<"render"<<std::endl;

        //extern unsigned char extern_rgba[4];
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

            x = i % screen_w;
            y = int(i / screen_w);
            //RGBA rgba = image_layers.get_rgba_pixel(x, y);

            /*
            // 能跑6.5fps
            image_layers.get_rgba_pixel_fast(x, y, r, g, b, a);

            pbWnd[i] = RGB(r, g, b);*/
            //pbWnd[i] = RGB(rgba.r, rgba.g, rgba.b);

            image_layers.rande_directly(x, y, i, pbWnd);
            // 能跑6.5fps

            //image_layers.get_rgba_pixel_fast2(x, y);
            //pbWnd[i] = RGB(extern_rgba[0], extern_rgba[1], extern_rgba[2]);
        }
    }

    std::cout<<"rander finished"<<std::endl;



    // 按任意键退出
    _getch();
    closegraph();
    return 0;




}