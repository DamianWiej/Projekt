#include "raport.h"
#include <stdio.h>
#include <string.h>

bool wczytaj_linie(char *bufor, int rozmiar)
{
    if (fgets(bufor, rozmiar, stdin) == NULL) {
        return false;
    }
    bufor[strcspn(bufor, "\n")] = '\0'; // Usuwa znak nowej linii
    return true;
}

const char *stabilnosc_na_tekst(Stabilnosc s)
{
    switch (s) {
        case STABILNY: return "Stabilny";
        case CHWIEJNY: return "Chwiejny";
        case NIESTABILNY: return "Niestabilny";
        case NIEKLASYFIKOWANY: return "Nieklasyfikowany";
        default: return "Nieznany";
    }
}

Stabilnosc stabilnosc_z_tekstu(const char *tekst)
{
    if (!tekst) 
        return NIEKLASYFIKOWANY;
    if (strcmp(tekst, "Stabilny") == 0)
         return STABILNY;
    if (strcmp(tekst, "Chwiejny") == 0) 
        return CHWIEJNY;
    if (strcmp(tekst, "Niestabilny") == 0) 
        return NIESTABILNY;
    return NIEKLASYFIKOWANY; 
}

void raport_wyswietl(const Raport *r)
{
    if (!r) return;
    printf("===================================\n");
    printf("Nazwa: %s\n", r->nazwa);
    printf("Swiat Pochodzenia: %s\n", r->swiat_pochodzenia);
    printf("Poziom Chaosu: %d\n", r->poziom_chaosu);
    printf("Stabilnosc: %s\n", stabilnosc_na_tekst(r->stabilnosc));
    printf("Opis Efektu: %s\n", r->opis_efektu);
    printf("===================================\n");
}

void raport_edytuj(Raport *r){
    char bufor[300];
    int wybor;

    if (!r) return;
    do{
        printf("Edycja raportu:\n",r->nazwa);
        printf("1. Swiat Pochodzenia\n");
        printf("2. Poziom Chaosu\n");
        printf("3. Opis Efektu\n");
        printf("4. Stabilnosc\n");
        printf("0. Zakoncz edycje\n");
        printf("Wybierz opcje: ");

        if (scanf("%d", &wybor) != 1) {
            while (getchar() != '\n'); // Czyszczenie bufora wejścia
            printf("Nieprawidlowy wybor. Sprobuj ponownie.\n");
            continue;
        }
        while (getchar() != '\n'); // Czyszczenie bufora wejścia

        switch (wybor){
            case 1:
                printf("Nowy Swiat Pochodzenia: ");
                if (wczytaj_linie(bufor, MAX_SWIAT + 1)) {
                    strncpy(r->swiat_pochodzenia, bufor, MAX_SWIAT);
                }
                break;
            case 2:
                printf("Nowy Poziom Chaosu (0-10): ");
                if (scanf("%d",&r->poziom_chaosu) != 1 || r->poziom_chaosu < 0 || r->poziom_chaosu > 10) {
                    printf("Nieprawidlowy poziom chaosu. Powinien byc w zakresie 0-10.\n");
                }
                while (getchar() != '\n'); // Czyszczenie bufora wejścia
                break;
            case 3:
                printf("Nowy Opis Efektu: ");
                if (wczytaj_linie(bufor, MAX_OPIS + 1)) {
                    strncpy(r->opis_efektu, bufor, MAX_OPIS);
                }
                break;
            case 4:
                printf("0-Stabilny, 1-Chwiejny, 2-Niestabilny, 3-Nieklasyfikowany\n");
                printf("Nowa Stabilnosc: ");
                if (scanf("%d",&wybor) == 1 && wybor >= 0 && wybor <= 3) {
                    r->stabilnosc = (Stabilnosc)wybor;
                } else {
                    printf("Nieprawidlowy wybor stabilnosci.\n");
                }
                while (getchar() != '\n'); // Czyszczenie bufora wejścia
                break;
            case 0:
                printf("Zakonczono edycje raportu.\n");
                break;
            default:
                printf("Nieprawidlowy wybor. Sprobuj ponownie.\n");

        }
        
    } while (wybor != 0);
}

bool raport_poprawny(const Raport *r){
    if (!r) return false;

    if (strlen(r->nazwa) == 0)
        return false;
    
    if (r->poziom_chaosu < 0 || r->poziom_chaosu > 10)
        return false;

    return true;
}

bool raport_mozna_usunac(const Raport *r){
    if (!r) return false;

    return r->stabilnosc != NIESTABILNY;
}