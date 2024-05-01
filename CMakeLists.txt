cmake_minimum_required(VERSION 3.27)
project(Projet_CDataframe C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet_CDataframe main.c
        column.c
        column.h
        cdataframe.h
        cdataframe.c
        features.h
        features.c)
