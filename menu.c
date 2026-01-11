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
        printf("0. Wyjdz\n");
        printf("Wybierz opcje: ");
        scanf("%d", &wybor);
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