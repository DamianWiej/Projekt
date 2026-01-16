#include "archiwum.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STARTOWA_POJEMNOSC 10

void archiwum_init(Archiwum *a)
{
    a->rozmiar = 0;
    a->pojemnosc = STARTOWA_POJEMNOSC;
    a->raporty = malloc(sizeof(Raport) * a->pojemnosc);
    if (!a->raporty) {
        a->pojemnosc = 0;
    }
}

void archiwum_zwolnij(Archiwum *a)
{
    free(a->raporty);
    a->raporty = NULL;
    a->rozmiar = 0;
    a->pojemnosc = 0;
}

bool archiwum_dodaj(Archiwum *a, Raport r){
    if (!raport_poprawny(&r)){
        return false;
    }

    if (a->rozmiar >= a->pojemnosc){
        int nowa = a->pojemnosc * 2;
        Raport *tmp = realloc(a->raporty, sizeof(Raport) * nowa);
        if (!tmp){
            return false;
        }
        a->raporty = tmp;
        a->pojemnosc = nowa;
    }
    a->raporty[a->rozmiar++] = r;
    return true;
}

void archiwum_wyswietl(const Archiwum *a){
    if (a->rozmiar == 0){
        printf("Archiwum jest puste.\n");
        return;
    }
    for (int i = 0; i < a->rozmiar; i++){
        printf("Raport #%d:\n", i + 1);
        raport_wyswietl(&a->raporty[i]);
    }
}
bool archiwum_edytuj(Archiwum *a, int indeks){
    if (!a || indeks < 0 || indeks >= a->rozmiar){
        return false;
    }
    raport_edytuj(&a->raporty[indeks]);
    return true;
    
}
bool archiwum_usun(Archiwum *a, int indeks){
    if (!a || indeks < 0 || indeks >= a->rozmiar)
        return false;

    Raport *r = &a->raporty[indeks];

    if (!raport_mozna_usunac(r)) {
        return false;
    }

    for (int i = indeks; i < a->rozmiar - 1; i++) {
        a->raporty[i] = a->raporty[i + 1];
    }

    a->rozmiar--;
    return true;
    
}
void archiwum_szukaj_nazwa(const Archiwum *a, const char *prefiks){
    int znalezione = 0;
    size_t len = strlen(prefiks);

    for (int i = 0; i < a->rozmiar; i++){
        if (strncmp(a->raporty[i].nazwa, prefiks, len) == 0){
            raport_wyswietl(&a->raporty[i]);
            znalezione++;
        }
    }
    if (znalezione == 0){
        printf("Brak raportow spelniajacych kryterium wyszukiwania.\n");
    }
}
void archiwum_szukaj_chaos(const Archiwum *a, int max_chaos){
    int znalezione = 0;

    for (int i = 0; i < a->rozmiar; i++){
        if (a->raporty[i].poziom_chaosu <= max_chaos){
            raport_wyswietl(&a->raporty[i]);
            znalezione++;
        }
    }
    if (znalezione == 0){
        printf("Brak raportow spelniajacych kryterium wyszukiwania.\n");
    }
}