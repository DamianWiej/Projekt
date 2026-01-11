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
        printf("Nieprawidlowy indeks raportu.\n");
        return false;
    }
    raport_edytuj(&a->raporty[indeks]);
    return true;
    
}