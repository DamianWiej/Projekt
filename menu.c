#include <stdio.h>
#include "menu.h"
#include "raport.h"
#include "archiwum.h"


void menu_glowne(Archiwum *a){
    int wybor;

    do {
        printf("=== Menu Glowne ===\n");
        printf("1. Dodaj nowy raport\n");
        printf("2. Wyswietl archiwum\n");
        printf("3. Edytuj raport\n");
        printf("4. Usun raport\n");
        printf("5. Wyszukaj raporty po nazwie\n");
        printf("6. Wyszukaj raporty po poziomie chaosu\n");
        printf("7. Usun wiele raportow (po nazwie)\n");
        printf("8. Sortuj raporty alfabetycznie\n");
        printf("9. Sortuj raporty po poziomie chaosu\n");
        printf("0. Wyjdz\n");
        printf("Wybierz opcje: ");
        
        if (scanf("%d", &wybor) != 1) {
            while (getchar() != '\n'); // Czyszczenie bufora wejścia
            printf("Nieprawidlowy wybor. Sprobuj ponownie.\n");
            continue;
        }

        while (getchar() != '\n'); // Czyszczenie bufora wejścia

        switch(wybor){
            case 1: {
                Raport r = menu_stworz_raport();
                archiwum_dodaj(a, r);
                break;
            }
            case 2:
                archiwum_wyswietl(a);
                break;
            case 3:
                menu_edytuj_raport(a);
                break;
            case 4:
                menu_usun_raport(a);
                break;
            case 5:
                menu_szukaj_nazwa(a);
                break;
            case 6:
                menu_szukaj_chaos(a);
                break;
            case 7:
                menu_usun_po_nazwie(a);
                break;
            case 8:
                menu_sortuj_nazwa(a);
                break;
            case 9:
                menu_sortuj_chaos(a);
                break;
        }
    } while (wybor != 0);

}


Raport menu_stworz_raport(void){
    Raport r;

    printf("Nazwa przedmiotu: ");
    wczytaj_linie(r.nazwa, MAX_NAZWA + 1);

    printf("Swiat Pochodzenia: ");
    wczytaj_linie(r.swiat_pochodzenia, MAX_SWIAT + 1);

    do {
        printf("Poziom Chaosu (0-10): ");
        scanf("%d", &r.poziom_chaosu);
        while (getchar() != '\n'); // Czyszczenie bufora wejścia
    } while (r.poziom_chaosu < 0 || r.poziom_chaosu > 10);
    
    printf("Opis Efektu: ");
    wczytaj_linie(r.opis_efektu, MAX_OPIS + 1);

    printf("Stabilnosc (0-Stabilny, 1-Chwiejny, 2-Niestabilny, 3-Nieklasyfikowany): ");
    scanf("%d", (int*)&r.stabilnosc);
    while (getchar() != '\n'); // Czyszczenie bufora wejścia
    return r;
}
void menu_edytuj_raport(Archiwum *a){
    int indeks;
    
    if (a->rozmiar == 0){
        printf("Archiwum jest puste. Brak raportow do edycji.\n");
        return;
    }
    archiwum_wyswietl(a);

    printf("Podaj numer raportu do edycji: ");
    if (scanf("%d",&indeks) != 1){
        while (getchar() != '\n'); // Czyszczenie bufora wejścia
        printf("Nieprawidlowy numer.\n");
        return;
    }
    while (getchar() != '\n'); // Czyszczenie bufora wejścia
    indeks--; // Konwersja na indeks 0-based
    if (!archiwum_edytuj(a, indeks)){
        printf("Nieprawidlowy numer raportu.\n");
    }

}

void menu_usun_raport(Archiwum *a){
    int indeks;
    
    if (a->rozmiar == 0){
        printf("Archiwum jest puste. Brak raportow do usuniecia.\n");
        return;
    }
    archiwum_wyswietl(a);

    printf("Podaj numer raportu do usuniecia: ");
    if (scanf("%d",&indeks) != 1){
        while (getchar() != '\n'); // Czyszczenie bufora wejścia
        printf("Nieprawidlowy numer.\n");
        return;
    }
    while (getchar() != '\n'); // Czyszczenie bufora wejścia
    indeks--; // Konwersja na indeks 0-based

    if (!archiwum_usun(a, indeks)){
        printf("Nieprawidlowy numer raportu lub raport nie moze byc usuniety (jest niestabilny).\n");
    }
    else {
        printf("Raport zostal usuniety pomyslnie.\n");
    }

}
void menu_szukaj_nazwa(const Archiwum *a){
    char prefiks[MAX_NAZWA + 1];

    if (a->rozmiar == 0){
        printf("Archiwum jest puste. Brak raportow do wyszukania.\n");
        return;
    }
    printf("Podaj nazwe lub prefiks do wyszukania: ");
    wczytaj_linie(prefiks, MAX_NAZWA + 1);

    archiwum_szukaj_nazwa(a, prefiks);

}
void menu_szukaj_chaos(const Archiwum *a){
    int max;

    if (a->rozmiar == 0){
        printf("Archiwum jest puste. Brak raportow do wyszukania.\n");
        return;
    }

    printf("Podaj maksymalny poziom chaosu do wyszukania: ");
    if (scanf("%d",&max) != 1 || max < 0 || max > 10){
        while (getchar() != '\n'); // Czyszczenie bufora wejścia
        printf("Nieprawidlowy poziom chaosu.\n");
        return;
    }
    while (getchar() != '\n'); // Czyszczenie bufora wejścia

    archiwum_szukaj_chaos(a, max);

}
void menu_usun_po_nazwie(Archiwum *a){
    char prefiks[MAX_NAZWA + 1];
    int usuniete;

    if (a->rozmiar == 0){
        printf("Archiwum jest puste. Brak raportow do usuniecia.\n");
        return;
    }
    printf("Podaj nazwe lub prefiks raportow do usuniecia: ");
    wczytaj_linie(prefiks, MAX_NAZWA + 1);

    usuniete = archiwum_usun_po_nazwie(a, prefiks);

    if (usuniete == 0){
        printf("Brak raportow spelniajacych kryterium usuniecia.\n");
    }
    else {
        printf("Usunieto %d raport(ow) spelniajacych kryterium.\n", usuniete);
    }
    
}
void menu_sortuj_nazwa(const Archiwum *a){
    if (a->rozmiar == 0){
        printf("Archiwum jest puste. Brak raportow do sortowania.\n");
        return;
    }

    Archiwum posortowane = archiwum_sortuj_po_nazwie(a);
    archiwum_wyswietl(&posortowane);
    archiwum_zwolnij(&posortowane); 
}
void menu_sortuj_chaos(const Archiwum *a){
    if (a->rozmiar == 0){
        printf("Archiwum jest puste. Brak raportow do sortowania.\n");
        return;
    }

    Archiwum posortowane = archiwum_sortuj_po_chaosie(a);
    archiwum_wyswietl(&posortowane);
    archiwum_zwolnij(&posortowane); 
}