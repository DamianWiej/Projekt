#include <stdio.h>
#include "menu.h"
#include "archiwum.h"

int main(void)
{
    Archiwum archiwum;
    archiwum_init(&archiwum);
    menu_glowne(&archiwum);
    archiwum_zwolnij(&archiwum);

    
    return 0;
}
