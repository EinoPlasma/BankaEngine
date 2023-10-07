cmake_minimum_required(VERSION 3.25)
project(BankaEngine)

set(CMAKE_CXX_STANDARD 14)

if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
endif()

set(EasyX_DIR C:/Users/EinoPlasma/Desktop/ComputerScience/GameEngine/BankaEngine/Easyx)
include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib64)
link_libraries(libEasyX.a libgdi32.a libole32.a)




add_executable(BankaEngine main.cpp Easyx/include/graphics.h stb_image.h color/RGBA.cpp color/RGBA.h imageLayer/imageLayer.cpp imageLayer/imageLayer.h imageLayer/imageLayers.cpp imageLayer/imageLayers.h imageLayer/imageLayerDrawer.cpp imageLayer/imageLayerDrawer.h imageLayer/imageLayerInfo.cpp imageLayer/imageLayerInfo.h)
