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
    // Saisie du nombre de colonnes souhaitées
    int nbr_col;
    printf("Saisir le nombre de colonnes que vous souhaitez : ");
    do {
        scanf("%d", &nbr_col);
    } while (nbr_col <= 0);
    printf("\n");

    // Boucle pour ajout d'une colonne
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
            printf("Bonjour");
            // Insertion de la valeur
            insert_value((COLUMN *) &new_col->data[i], value);
            // printf("%d", cdt->column[i]->data[j]);
            printf("\n");
        }

        // Insertion de la colonne
        insert_column(cdt, new_col);
    }
}


CDATAFRAME *hard_filling(){
    // Création d'un CDataframe
    CDATAFRAME *hfd = create_cdataframe("Hard Filling Dataframe");

    int verif; // Variable qui vérifie qu'une colonne a bien été insérée

    // 1ère colonne
    COLUMN *col1 = create_column("Colonne 1");
    col1->T_Physique = 3;
    col1->T_Logique = 3;
    col1->data = (int *) malloc(3 * sizeof (int));

    col1->data[0] = 1;
    col1->data[1] = 4;
    col1->data[2] = 7;

    do {
        verif = insert_column(hfd, col1);
    } while (verif == 0);

    // 2ème colonne
    COLUMN *col2 = create_column("Colonne 2");
    col2->T_Physique = 3;
    col2->T_Logique = 3;
    col2->data = (int *) malloc(3 * sizeof (int));

    col2->data[0] = 2;
    col2->data[1] = 5;
    col2->data[2] = 8;

    do {
        verif = insert_column(hfd, col2);
    } while (verif == 0);

    // 3ème colonne
    COLUMN *col3 = create_column("Colonne 3");
    col3->T_Physique = 3;
    col3->T_Logique = 3;
    col3->data = (int *) malloc(3 * sizeof (int));

    col3->data[0] = 3;
    col3->data[1] = 6;
    col3->data[2] = 9;

    /*
    printf("Nombre de colonne : %d\n", hfd->num_columns);
    do {
        verif = insert_column(hfd, col3);
    } while (verif == 0);
    printf("Nombre de colonne : %d\n", hfd->num_columns);
    */

    return hfd;
}


void print_cdt(CDATAFRAME *cdt){
    /* Afficher le titre du CDataframe */
    printf("%s\n", cdt->title);

    /* Boucle pour les titres des colonnes */
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        // Afficher le titre de la colonne
        printf("\t\t%s", cdt->column[i]->title);
    }
    printf("\n");

    /* Boucle pour les valeurs des colonnes */
    for (int j = 0 ; j < cdt->column[0]->T_Logique ; j++){ // Variation de la ligne
        /* Afficher le numéro de la ligne */
        printf("[%d]\t\t", j);

        /* Afficher les valeurs */
        for (int i = 0; i < cdt->num_columns; i++) {    // Variation de la colonne
            // Afficher la valeur
            printf("%d\t\t\t\t", cdt->column[i]->data[j]);
        }
        printf("\n"); // Passage à la ligne suivante
    }
    printf("\n");
}


void print_lines(CDATAFRAME *cdt, int x, int y){
    /* Afficher le titre du CDataframe */
    printf("%s\n", cdt->title);

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

    /* Si la colonne n'a pas encore été utilisé, faire une allocation */
    if (cdt->column == NULL) {
        cdt->column = (COLUMN **) malloc(sizeof (COLUMN *));
        return 0;
    }

    /* Sinon faire une réallocation (toujours à la bonne taille) */
    realloc(cdt->column, (cdt->num_columns + 1) * sizeof (COLUMN *));

    /* Insertion de la valeur */
    cdt->column[(cdt->num_columns)++] = column;

    return 1;
}



int replace_cell(CDATAFRAME* cdt, int index_l, int index_c, int value) {
    /* Si la case n'existe pas retourner 0 */
    if (index_c < 1 || index_c > cdt->num_columns || index_l < 1 || index_l > cdt->column[index_c])
        return 0;

    /* Sinon remplacer la valeur et retourner 1 */
    cdt->column[index_c - 1]->data[index_l - 1] = value;

    return 1;
}


void print_name_col(CDATAFRAME *cdt) {
    /* Boucle pour les titres des colonnes */
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        // Afficher le titre de la colonne
        printf("%s\t\t", cdt->column[i]->title);
    }
    printf("\n\n");
}


int number_of_lines(CDATAFRAME *cdt) {
    int max = 0;

    /* Recherche de la colonne avec le plus de lignes */
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        if (max < cdt->column[i]->T_Logique)
            max = cdt->column[i]->T_Logique;
    }

    return max;
}


int number_of_cols(CDATAFRAME *cdt) {
    return cdt->num_columns;
}


int cell_equal_to(CDATAFRAME *cdt, int x) {
    /* Initialisation du compteur à 0 */
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
    /* Initialisation du compteur à 0 */
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
    /* Initialisation du compteur à 0 */
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