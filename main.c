#include <stdio.h>
#include "menu.h"
#include "archiwum.h"

int main(int argc, char **argv)
{
    Archiwum archiwum;
    archiwum_init(&archiwum);

    if (argc >= 2){
        if (!archiwum_wczytaj_z_pliku(&archiwum, argv[1])){
            printf("Nie udalo sie wczytac archiwum z pliku: %s\n", argv[1]);
        }
    }

    menu_glowne(&archiwum);

    if (argc >= 3){
        if (!archiwum_zapisz_do_pliku(&archiwum, argv[2])){
            printf("Nie udalo sie zapisac archiwum do pliku: %s\n", argv[2]);
        }
    }
    
    archiwum_zwolnij(&archiwum);
    return 0;
}
