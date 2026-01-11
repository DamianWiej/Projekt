#ifndef ARCHIWUM_H
#define ARCHIWUM_H
#include "raport.h"

typedef struct {
    Raport *raporty;
    int rozmiar;
    int pojemnosc;
} Archiwum;

void archiwum_init(Archiwum *a);
void archiwum_zwolnij(Archiwum *a);
bool archiwum_dodaj(Archiwum *a, Raport r);
void archiwum_wyswietl(const Archiwum *a);
bool archiwum_edytuj(Archiwum *a, int indeks);
#endif // ARCHIWUM_H