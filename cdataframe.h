//
// Created by Arnaud Bernard on 20/04/2024.
//

#ifndef PROJET_CDATAFRAME_CDATAFRAME_H
#define PROJET_CDATAFRAME_CDATAFRAME_H

#include "column.h"

typedef struct {
    char *title;
    int T_Logique;
    int T_Physique;
    COLUMN **column;
} CDATAFRAME;

/* Create a CDataframe
 * @param1 : CDataframe title
 * @return : Pointer to created column
 */
CDATAFRAME *create_cdataframe(char* title);

/* Add a new column to a CDataframe
 * @param1 : Pointer to a CDataframe
 * @param2 : Pointer to a column to be added
 * @return : 1 if the column is added 0 otherwise
 */
int insert_column(CDATAFRAME* cdt, COLUMN** column);


#endif //PROJET_CDATAFRAME_CDATAFRAME_H
