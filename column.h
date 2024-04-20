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

#define REALLOC_SIZE 256

/* Create a column
 * @param1 : Column title
 * @return : Pointer to created column
 */
COLUMN *create_column(char* title);

/* Insert a value in a column
 * @param1 : Column in which we add the value
 * @param2 : Value to add
 * @return : Returns 1 if insertion successful otherwise 0
 */
int insert_value(COLUMN* col, int value);


#endif //PROJET_CDATAFRAME_COLUMN_H
