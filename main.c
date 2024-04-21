#include <stdio.h>
#include "column.h"
#include "cdataframe.h"

int main() {
    COLUMN *mycol = create_column("My column");
    insert_value(mycol, 52);
    insert_value(mycol, 44);
    insert_value(mycol, 15);
    insert_value(mycol, 12);
    insert_value(mycol, 13);
    insert_value(mycol, 44);
    insert_value(mycol, 0);

    print_col(mycol);
    printf("Nombre d'occurrence de 44 : %d\n", number_occ(mycol, 44));
    printf("Valeur à la position [6] : %d\n", val_at_pos(mycol, 6));
    printf("Nombre de valeurs supérieur à 44 : %d\n", greater_than(mycol, 44));
    printf("Nombre de valeurs supérieur à 44 : %d\n", less_than(mycol, 44));
    printf("Nombre de valeurs supérieur à 44 : %d\n\n", equal_to(mycol, 44));

    CDATAFRAME *mycdt = create_cdataframe("My CDataframe");
    insert_column(mycdt, &mycol);

    printf("%s\n", mycdt->title);
    printf("%s\n", mycdt->column[0]->title);
    for(int j = 0 ; j < mycdt->column[0]->T_Logique ; j++){
        printf("[%d]\t %d\n", j, mycdt->column[0]->data[j]);
    }
    printf("\n");


    for (int i = 0 ; i < mycdt->T_Logique ; i += sizeof (COLUMN*)){
        print_col(mycdt->column[i]);
    }

    return 0;
}

