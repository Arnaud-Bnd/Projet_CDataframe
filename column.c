//
// Created by Arnaud Bernard on 28/03/2024.
//
#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COLUMN *create_column(char* title){
    COLUMN* column = (COLUMN*) malloc(sizeof * column);
    column->title = title;
    column->T_Logique = 0;
    column->T_Physique = 0;
    column->data = NULL;
    return column;
}

int insert_value(COLUMN* col, int value){
    if (col->data == NULL){
        col->data = (COLUMN*) malloc(256);
        col->T_Physique += 256;
        return 0;
    }
    else if (col->T_Physique == col->T_Logique){
        col->T_Physique += 256;
        realloc(col->data, col->T_Physique);
        return 0;
    }
    else{
        *(col->data + col->T_Logique++) = value;
        return 1;
    }
    return 0;
}