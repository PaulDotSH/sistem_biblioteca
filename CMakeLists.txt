cmake_minimum_required(VERSION 3.21)
project(sistem_biblioteca_l C)

set(CMAKE_C_STANDARD 23)

add_executable(sistem_biblioteca_l main.c cjson/cJSON.c cjson/cJSON.h linkedLists.c linkedLists.h carte.c carte.h io.c io.h utils.c utils.h)
