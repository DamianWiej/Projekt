#ifndef MENU_H
#define MENU_H
#include "archiwum.h"

void menu_glowne(Archiwum *archiwum);

Raport menu_stworz_raport(void);

void menu_edytuj_raport(Archiwum *a);

void menu_usun_raport(Archiwum *a);

void menu_szukaj_nazwa(const Archiwum *a);

void menu_szukaj_chaos(const Archiwum *a);

void menu_usun_po_nazwie(Archiwum *a);

void menu_sortuj_nazwa(const Archiwum *a);

void menu_sortuj_chaos(const Archiwum *a);
#endif 