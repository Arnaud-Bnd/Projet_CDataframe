//
// Created by Arnaud Bernard on 28/03/2024.
//

#ifndef PROJET_CDATAFRAME_COLUMN_H
#define PROJET_CDATAFRAME_COLUMN_H

typedef struct {
    char *title;
    int T_Logique;
    int T_Physique;
    int *data;
} COLUMN;

COLUMN *create_column(char* title);
int insert_value(COLUMN* col, int value);


#endif //PROJET_CDATAFRAME_COLUMN_H
