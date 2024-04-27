#include <stdio.h>
#include <string.h>
#include "column.h"
#include "cdataframe.h"

int main() {
    CDATAFRAME *cdt = hard_filling();

    print_cdt(cdt);

    replace_cell(cdt, 1, 1, 18);

    print_cdt(cdt);

    return 0;
}

 