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
int archiwum_usun_po_nazwie(Archiwum *a, const char *prefiks); //int bo zwraca liczbe usunietych raportow
Archiwum archiwum_sortuj_po_nazwie(const Archiwum *a);
Archiwum archiwum_sortuj_po_chaosie(const Archiwum *a);
int archiwum_zapisz_do_pliku(const Archiwum *a, const char *sciezka);
int archiwum_wczytaj_z_pliku(Archiwum *a, const char *sciezka);
#endif // ARCHIWUM_H