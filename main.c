#include <stdio.h>
#include <string.h>
#include "column.h"
#include "cdataframe.h"

int main() {
    CDATAFRAME *cdt = create_cdataframe("Test");

    user_input(cdt);

    print_cdt(cdt);

    return 0;
}

 