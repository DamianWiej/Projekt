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
int archiwum_usun_po_nazwie(Archiwum *a, const char *prefiks){
    int usuniete = 0;
    size_t len = strlen(prefiks);

    if (!a || len == 0)
        return 0;
    
    // usuwamy od konca, bo jakby bylo od poczatku to rejestry sie przeciez przesuwaja w lewo i indeks sie przesunie
    for (int i = a->rozmiar - 1; i >= 0; i--){
        if (strncmp(a->raporty[i].nazwa, prefiks, len) == 0){
            if (!raport_mozna_usunac(&a->raporty[i]))
                continue;
            
            archiwum_usun(a, i);
            usuniete++;
            
        }
    }
    return usuniete;
}
static int cmp_nazwa(const void *a, const void *b){
    const Raport *r1 = a;
    const Raport *r2 = b;
    return strcmp(r1->nazwa, r2->nazwa);
}
static int cmp_chaos(const void *a, const void *b){
    const Raport *r1 = a;
    const Raport *r2 = b;
    return r1->poziom_chaosu - r2->poziom_chaosu;
}
Archiwum archiwum_sortuj_po_nazwie(const Archiwum *a){
    Archiwum kopia;
    archiwum_init(&kopia);

    if (!a || a->rozmiar == 0)
        return kopia;
    kopia.raporty = malloc(sizeof(Raport) * a->rozmiar);
    if (!kopia.raporty)
        return kopia;
    
    memcpy(kopia.raporty, a->raporty, sizeof(Raport) * a->rozmiar);
    kopia.rozmiar = a->rozmiar;
    kopia.pojemnosc = a->rozmiar;

    qsort(kopia.raporty, kopia.rozmiar, sizeof(Raport), cmp_nazwa);

    return kopia;

}
Archiwum archiwum_sortuj_po_chaosie(const Archiwum *a){
    Archiwum kopia;
    archiwum_init(&kopia);

    if (!a || a->rozmiar == 0)
        return kopia;
    kopia.raporty = malloc(sizeof(Raport) * a->rozmiar);
    if (!kopia.raporty)
        return kopia;
    
    memcpy(kopia.raporty, a->raporty, sizeof(Raport) * a->rozmiar);
    kopia.rozmiar = a->rozmiar;
    kopia.pojemnosc = a->rozmiar;

    qsort(kopia.raporty, kopia.rozmiar, sizeof(Raport), cmp_chaos);

    return kopia;

}
int archiwum_zapisz_do_pliku(const Archiwum *a, const char *sciezka){
    FILE *f = fopen(sciezka, "w");
    if (!f)
        return -1;
    
    if (!a || !sciezka)
        return 0;
    
    fprintf(f, "%d\n", a->rozmiar);
    for (int i = 0; i < a->rozmiar; i++){
        Raport *r = &a->raporty[i];
        fprintf(f, "%s|%s|%d|%s|%s\n", r->nazwa, r->swiat_pochodzenia, r->poziom_chaosu, r->opis_efektu, stabilnosc_na_tekst(r->stabilnosc));
    }

    fclose(f);
    return 1;
}
int archiwum_wczytaj_z_pliku(Archiwum *a, const char *sciezka){
    FILE *f = fopen(sciezka,"r");
    if (!f)
        return -1;

    Archiwum tmp;
    int liczba;
    char bufor[512];

    if (!a || !sciezka)
        return 0;
    
    archiwum_init(&tmp);

    if (fscanf(f, "%d\n", &liczba) != 1 || liczba < 0){
        fclose(f);
        return 0;
    }
    for (int i = 0; i < liczba; i++){
        Raport r;
        if (!fgets(bufor, sizeof(bufor), f)){
            goto blad;
        }
        bufor[strcspn(bufor, "\n")] = '\0'; // Usuwa znak nowej linii

        char *token = strtok(bufor, "|");
        if (!token) goto blad;
        strncpy(r.nazwa, token, MAX_NAZWA);

        token = strtok(NULL, "|");
        if (!token) goto blad;
        strncpy(r.swiat_pochodzenia, token, MAX_SWIAT);

        token = strtok(NULL, "|");
        if (!token) goto blad;
        r.poziom_chaosu = atoi(token);

        token = strtok(NULL, "|");
        if (!token) goto blad;
        strncpy(r.opis_efektu, token, MAX_OPIS);

        token = strtok(NULL, "|");
        if (!token) goto blad;
        r.stabilnosc = stabilnosc_z_tekstu(token);

        archiwum_dodaj(&tmp, r);
    }
    fclose(f);
    
    archiwum_zwolnij(a);
    *a = tmp;
    return 1;

blad:
    fclose(f);
    archiwum_zwolnij(&tmp);
    return 0;
    
}