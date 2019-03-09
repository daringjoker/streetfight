cmake_minimum_required(VERSION 3.13)
project(streetfight)

set(CMAKE_CXX_STANDARD 14)

add_executable(streetfight main.cpp player.cpp player.h AI.h AI.cpp network.cpp network.h ipgrab.cpp ipgrab.h)
target_link_libraries(streetfight SDL2 SDL2main pthread)