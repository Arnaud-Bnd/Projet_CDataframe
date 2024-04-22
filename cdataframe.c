//
// Created by Arnaud Bernard on 20/04/2024.
//
#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>

CDATAFRAME *create_cdataframe(char* title) {
    CDATAFRAME* cdataframe = (CDATAFRAME*) malloc(sizeof (CDATAFRAME));
    cdataframe->title = title;
    cdataframe->T_Logique = 0;
    cdataframe->T_Physique = 0;
    cdataframe->column = NULL;

    return cdataframe;
}

int insert_column(CDATAFRAME* cdt, COLUMN** column) {
    /* Si la colonne n'a pas encore été utilisé, faire une allocation */
    if (cdt->column == NULL) {
        /* Allocation */
        cdt->column = (COLUMN**) malloc(sizeof(COLUMN*));
        cdt->T_Physique += sizeof (COLUMN*);
        /* Insertion de la valeur */
        cdt->column[cdt->T_Logique] = (COLUMN*) &column;
        cdt->T_Logique += sizeof (COLUMN*);
        return 1;
    }

    /* S'il n'y a plus de place, faire une réallocation */
    else if (cdt->T_Physique == cdt->T_Logique) {
        /* Réallocation */
        cdt->T_Physique += sizeof (COLUMN*);
        realloc(cdt->column, cdt->T_Physique);
        /* Insertion de la valeur */
        cdt->column[cdt->T_Logique] = (COLUMN*) &column;
        cdt->T_Logique += sizeof (COLUMN*);
        return 1;
    }

    /* Insertion de la valeur */
    else if (cdt->T_Physique != cdt->T_Logique) {
        cdt->column[(cdt->T_Logique)++] = (COLUMN*) &column;
        return 1;
    }

    /* Retourner 0 si l'insertion n'a pas été faite */
    else {
        return 0;
    }
}

