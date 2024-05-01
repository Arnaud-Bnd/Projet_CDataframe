//
// Created by Arnaud Bernard on 20/04/2024.
//
#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>


#include <string.h>


CDATAFRAME *create_cdataframe(char* title) {
    CDATAFRAME *cdataframe = (CDATAFRAME *) malloc(sizeof (CDATAFRAME));
    cdataframe->title = title;
    cdataframe->num_columns = 0;
    cdataframe->column = NULL;

    return cdataframe;
}


void user_input(CDATAFRAME* cdt) {
    /* Vérification de la taille du CDataframe */
    if (cdt == NULL) {
        printf("Le pointeur CDataframe est NULL.\n");
        return;
    }

    /* Initialisation de la variable qui vérifie les insertions */
    int verif;

    // Saisie du nombre de colonnes souhaitées
    int nbr_col;
    printf("Saisir le nombre de colonnes que vous souhaitez : ");
    do {
        scanf("%d", &nbr_col);
    } while (nbr_col <= 0);
    printf("\n");

    // Boucle pour ajouter une colonne
    for (int i = 0; i < nbr_col; i++) {
        // Saisie du nom de la colonne
        char name_col[50];
        printf("Saisir le nom de la %d-ième colonne : ", i + 1);
        scanf("%s", name_col);

        // Création de la colonne portant le nom
        COLUMN *new_col = create_column(name_col);

        // Saisie du nombre de valeurs qu'il veut rentrer
        int nbr_value;
        printf("Saisir le nombre de valeurs que vous souhaitez entrer : ");
        do {
            scanf("%d", &nbr_value);
        } while (nbr_value <= 0);
        printf("\n");

        // Boucle pour d'une valeur
        for (int j = 0; j < nbr_value; j++) {
            // Saisie de la valeur
            int value;
            printf("Saisir la %d-ième valeur : ", j + 1);
            scanf("%d", &value);

            // Insertion de la valeur
            do {
                verif = insert_value(new_col, value);
            } while (verif == 0);

            printf("\n");
        }

        // Insertion de la colonne
        do {
            verif = insert_column(cdt, new_col);
        } while (verif == 0);
    }
}


CDATAFRAME *hard_filling(){
    // Création d'un CDataframe
    CDATAFRAME *cdt = create_cdataframe("Hard Filling Dataframe");

    COLUMN *col1 = create_column("Colonne 1");
    insert_value(col1, 1);
    insert_value(col1, 2);
    insert_value(col1, 3);
    insert_column(cdt, col1);

    COLUMN *col2 = create_column("Colonne 2");
    insert_value(col2, 4);
    insert_value(col2, 5);
    insert_value(col2, 6);
    insert_column(cdt, col2);

    COLUMN *col3 = create_column("Colonne 3");
    insert_value(col3, 7);
    insert_value(col3, 8);
    insert_value(col3, 9);
    insert_column(cdt, col3);

    return cdt;
}


void print_cdt(CDATAFRAME *cdt){
    /* Vérification de la taille du CDataframe */
    if (cdt == NULL) {
        printf("Le pointeur CDataframe est NULL.\n");
        return;
    }

    /* Afficher le titre du CDataframe */
    printf("%s\n", cdt->title);

    /* Vérification du nombre de colonnes */
    if (cdt->num_columns == 0) {
        printf("Le CDataframe n'a pas de colonnes.\n");
        return;
    }

    /* Boucle pour les titres des colonnes */
    printf("\t\t");
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        // Afficher le titre de la colonne
        printf("%s\t\t", (char *) cdt->column[i]->title);
    }
    printf("\n");

    /* Trouver la colonne avec le plus de lignes */
    int max_rows = number_of_lines(cdt);

    /* Boucle pour les valeurs des colonnes */
    for (int j = 0 ; j < max_rows ; j++){   // Variation de la ligne
        /* Afficher le numéro de la ligne */
        printf("[%d]\t\t", j + 1);

        /* Afficher les valeurs */
        for (int i = 0 ; i < cdt->num_columns ; i++) {    // Variation de la colonne
                // Afficher la valeur
                printf("%d\t\t\t\t", cdt->column[i]->data[j]);
        }
        printf("\n"); // Passage à la ligne suivante
    }
    printf("\n");
}


void print_lines(CDATAFRAME *cdt, int x, int y){
    /* Afficher le titre du CDataframe */
    printf("%s\n", (char *) cdt->title);

    /* Vérification du nombre de colonnes */
    if (cdt->num_columns == 0) {
        printf("Le CDataframe n'a pas de colonnes.\n");
        return;
    }

    /* Boucle pour les titres des colonnes */
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        // Afficher le titre de la colonne
        printf("\t\t%s", cdt->column[i]->title);
    }
    printf("\n");

    /* Boucle pour les valeurs des colonnes */
    for (int j = x - 1 ; j < y; j++){ // Variation de la ligne
        /* Afficher le numéro de la ligne */
        printf("[%d]\t\t", j + 1);

        /* Afficher les valeurs */
        for (int i = 0; i < cdt->num_columns; i++) {    // Variation de la colonne
            // Afficher la valeur
            printf("%d\t\t\t\t", cdt->column[i]->data[j]);
        }
        printf("\n"); // Passage à la ligne suivante
    }
    printf("\n");
}













int insert_column(CDATAFRAME* cdt, COLUMN* column) {
    /* Vérification de la taille du CDataframe et de la colonne */
    if (cdt == NULL || column == NULL) {
        fprintf(stderr, "Le pointeur CDataframe ou colonne est NULL.\n");
        return 0;
    }

    /* Si la colonne n'a pas encore été utilisée, faire une allocation */
    if (cdt->column == NULL) {
        cdt->column = (COLUMN **) malloc(sizeof (COLUMN *));
        if (cdt->column == NULL) {
            printf("Échec de la réallocation de la mémoire.\n");
            return 0;
        }
    }

    /* Sinon faire une réallocation (toujours à la bonne taille) */
    else {
        cdt->column = realloc(cdt->column, (cdt->num_columns + 1) * sizeof (COLUMN *));
    }

    // Dupliquer le titre de la colonne avant de l'insérer
    char *col_title = (char *) malloc(strlen(column->title) + 1);
    strcpy(col_title, column->title);
    column->title = col_title;

    // Insertion de la colonne dans le CDataframe
    cdt->column[cdt->num_columns++] = column;

    return 1;
}


int replace_cell(CDATAFRAME* cdt, int index_l, int index_c, int value) {
    /* Vérification de la taille du CDataframe */
    if (cdt == NULL) {
        printf("Le pointeur CDataframe est NULL.\n");
        return 0;
    }

    /* Si la case n'existe pas retourner 0 */
    if (index_c < 1 || index_c > cdt->num_columns || index_l < 1 || index_l > number_of_lines(cdt))
        return 0;

    /* Sinon remplacer la valeur et retourner 1 */
    cdt->column[index_c - 1]->data[index_l - 1] = value;

    return 1;
}


void print_name_col(CDATAFRAME *cdt) {
    /* Vérification de la taille du CDataframe */
    if (cdt == NULL) {
        printf("Le pointeur CDataframe est NULL.\n");
        return;
    }

    /* Boucle pour les titres des colonnes */
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        // Afficher le titre de la colonne
        printf("%s\t\t", cdt->column[i]->title);
    }
    printf("\n\n");
}


int number_of_lines(CDATAFRAME *cdt) {
    /* Vérification de la taille du CDataframe */
    if (cdt == NULL) {
        printf("Le pointeur CDataframe est NULL.\n");
        return 0;
    }

    int max = 0;

    /* Recherche de la colonne avec le plus de lignes */
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        if (max < cdt->column[i]->T_Logique)
            max = cdt->column[i]->T_Logique;
    }

    return max;
}


int number_of_cols(CDATAFRAME *cdt) {
    /* Vérification de la taille du CDataframe */
    if (cdt == NULL) {
        printf("Le pointeur CDataframe est NULL.\n");
        return 0;
    }

    return cdt->num_columns;
}


int cell_equal_to(CDATAFRAME *cdt, int x) {
    /* Vérification de la taille du CDataframe */
    if (cdt == NULL) {
        printf("Le pointeur CDataframe est NULL.\n");
        return 0;
    }

    /* Initialisation du compteur à 0. */
    int cpt = 0;

    /* Parcours des valeurs */
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        for (int j = 0 ; j < cdt->column[i]->T_Logique ; j++) {
            if (cdt->column[i]->data[j] == x)
                cpt++;
        }
    }

    return cpt;
}


int cell_greater_than(CDATAFRAME *cdt, int x) {
    /* Vérification de la taille du CDataframe */
    if (cdt == NULL) {
        printf("Le pointeur CDataframe est NULL.\n");
        return 0;
    }

    /* Initialisation du compteur à 0. */
    int cpt = 0;

    /* Parcours des valeurs */
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        for (int j = 0 ; j < cdt->column[i]->T_Logique ; j++) {
            if (cdt->column[i]->data[j] > x)
                cpt++;
        }
    }

    return cpt;
}


int cell_less_than(CDATAFRAME *cdt, int x) {
    /* Vérification de la taille du CDataframe */
    if (cdt == NULL) {
        printf("Le pointeur CDataframe est NULL.\n");
        return 0;
    }

    /* Initialisation du compteur à 0. */
    int cpt = 0;

    /* Parcours des valeurs */
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        for (int j = 0 ; j < cdt->column[i]->T_Logique ; j++) {
            if (cdt->column[i]->data[j] < x)
                cpt++;
        }
    }

    return cpt;
}
