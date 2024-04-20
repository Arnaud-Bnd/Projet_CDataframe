#include <stdio.h>
#include "column.h"

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
    printf("Nombre de valeurs supérieur à 44 : %d\n", equal_to(mycol, 44));

    delete_column(mycol);

    print_col(mycol);

    return 0;
}

