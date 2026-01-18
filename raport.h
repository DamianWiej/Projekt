#ifndef RAPORT_H
#define RAPORT_H
#include <stdbool.h>

#define MAX_NAZWA 100
#define MAX_SWIAT 100
#define MAX_OPIS 256

typedef enum {
    STABILNY,
    CHWIEJNY,
    NIESTABILNY,
    NIEKLASYFIKOWANY
} Stabilnosc;

typedef struct {
    char nazwa[MAX_NAZWA + 1];
    char swiat_pochodzenia[MAX_SWIAT + 1];
    int poziom_chaosu;
    char opis_efektu[MAX_OPIS + 1];
    Stabilnosc stabilnosc;
} Raport;

void raport_wyswietl(const Raport *r);
void raport_edytuj(Raport *r);
bool raport_poprawny(const Raport *r);
bool raport_mozna_usunac(const Raport *r);
const char *stabilnosc_na_tekst(Stabilnosc s);
Stabilnosc stabilnosc_z_tekstu(const char *tekst);
bool wczytaj_linie(char *bufor, int rozmiar);

#endif // RAPORT_H