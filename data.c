//
// Created by Arnaud Bernard on 28/03/2024.
//
#include "data.h"
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