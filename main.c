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


    print_col(mycol);
    printf("Nombre d'occurence de 44 : %d", number_occ(mycol, 44));

    delete_column(mycol);

    print_col(mycol);

    return 0;
}

