cmake_minimum_required(VERSION 3.22.2)

project(test_window)
# 	g++ -o test main.cpp -lglfw -lrt -lXrandr -lXinerama -lXi -lGL -lm -ldl -lXrender   -lX11 -lpthread


add_subdirectory(Libs)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} glad glfw rt Xrandr Xinerama Xi GL m dl Xrender X11 pthread)
