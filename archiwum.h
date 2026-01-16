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
bool archiwum_usun(Archiwum *a, int indeks);
void archiwum_szukaj_nazwa(const Archiwum *a, const char *prefiks);
void archiwum_szukaj_chaos(const Archiwum *a, int max_chaos);
#endif // ARCHIWUM_H