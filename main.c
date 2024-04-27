#include <stdio.h>
#include <string.h>
#include "column.h"
#include "cdataframe.h"

int main() {
    COLUMN *mycol = create_column("My column");

    do{
        insert_value(mycol, 52);
    } while (!insert_value(mycol, 52));
    insert_value(mycol, 44);
    insert_value(mycol, 15);
    insert_value(mycol, 12);
    insert_value(mycol, 13);
    insert_value(mycol, 44);
    insert_value(mycol, 0);


    print_col(mycol);
    printf("Nombre d'occurrence de 44 : %d\n", number_occ(mycol, 44));
    printf("Valeur à la position [6] : %d\n", val_at_pos(mycol, 6));
    printf("Nombre de valeurs supérieures à 44 : %d\n", greater_than(mycol, 44));
    printf("Nombre de valeurs supérieures à 44 : %d\n", less_than(mycol, 44));
    printf("Nombre de valeurs supérieures à 44 : %d\n\n", equal_to(mycol, 44));

    // delete_column(mycol);


    CDATAFRAME  *test = hard_filling();

    //print_cdt(test);
    print_lines(test, 1, 3);

    printf("Nombre de lignes : %d\n", number_of_lines(test));
    printf("Nombre de colonnes : %d\n", number_of_cols(test));
    printf("Nombre de cellules égales à 5 : %d\n", cell_equal_to(test, 5));
    printf("Nombre de cellules supérieures à 5 : %d\n", cell_greater_than(test, 5));
    printf("Nombre de cellules inférieures à 5 : %d\n", cell_less_than(test, 5));

    print_name_col(test);

    printf("%d\n", replace_cell(test, 0, 0, 18));
    print_lines(test, 1, 3);


    /*
    printf("%s\n", test->title);
    printf("\t\t%s \t\t%s\n", test->column[0]->title, test->column[1]->title);
    printf("[%d]\t\t%d\t\t\t\t%d\n", 0, test->column[0]->data[0], test->column[1]->data[0]);
    printf("[%d]\t\t%d\t\t\t\t%d\n", 1, test->column[0]->data[1], test->column[1]->data[1]);
    printf("[%d]\t\t%d\t\t\t\t%d\n", 2, test->column[0]->data[2], test->column[1]->data[2]);
    */

    /*
    CDATAFRAME *mycdt = create_cdataframe("Test");

    // Création d'une colonne
    COLUMN *col1 = create_column("Colonne 1");
    int verif;
    do{
        verif = insert_value(col1, 2);
    } while (verif == 0);
    do{
        verif = insert_value(col1, 4);
    } while (verif == 0);

    COLUMN *col2 = create_column("Colonne 2");
    do{
        verif = insert_value(col2, 3);
    } while (verif == 0);
    do{
        verif = insert_value(col2, 5);
    } while (verif == 0);

    // Insertion des colonnes dans le CDataframe
    do {
        verif = insert_column(mycdt, col1);
    } while (verif == 0);

    do {
        verif = insert_column(mycdt, col2);
    } while (verif == 0);

    print_cdt(mycdt);
    */


    // print_cdt(mycdt);

    /*
    for (int i = 0 ; i < mycdt->T_Logique ; i += sizeof (COLUMN*)){
        print_col(mycdt->column[i]);
    }
    */

    return 0;
}

 