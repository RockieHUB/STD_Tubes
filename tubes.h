#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED

#include <string>
#include <iostream>

#define Rinfo(P)  P->Rinfo
#define Pinfo(P)  P->Pinfo//
#define Rnext(P)  P->Rnext// pointer ruangan
#define next_pas(P)  P->next_pas//
#define first(L) L.first
#define kolom(L)  L->kolom // first (L) dari Child

using namespace std;

struct Ruang{
    string tipe;
    int nomor;
};

struct Pasien{
    string nama;
    string penyakit;
};

typedef struct ElmPasien *adrPasien;
struct ElmPasien{
    Pasien Pinfo;
    adrPasien next_pas;
};

typedef struct ElmRuang *adrRuang;
struct ElmRuang {
    Ruang Rinfo;
    adrPasien kolom;
    adrRuang Rnext;
};

struct List {
    adrRuang first;
};

void createList(List &L);
adrRuang alokasiRuang(Ruang x);
adrPasien alokasiPasien(Pasien x);

int CountElementRuang(List L);
int CountElementPasienRuangan(adrRuang L);

void dealokasiRuang(adrRuang &P);
void dealokasiPasien(adrPasien &P);

void insertFirstRuang(List &L, adrRuang P);
void insertFirstPasien(adrRuang &L, adrPasien P);

void insertLastRuang(List &L, adrRuang P);
void insertLastPasien(adrRuang &L, adrPasien P);

void deleteFirstRuang(List &L, adrRuang &P);
void deleteFirstPasien(adrRuang &L, adrPasien P);

void deleteLastRuang(List &L);
void deleteLastPasien(adrRuang &L);

void insertAfterRuang(List &L, adrRuang Prec, adrRuang P);
void insertAfterPasien(adrPasien Prec, adrPasien P);
void printsemuaruangan(List &L,adrPasien q);

void deleteAfterRuang(List &L, adrRuang Prec, adrRuang &P);
void deleteAfterPasien(adrRuang &L, adrPasien &Prec, adrPasien &P);

adrRuang findElmRuang(List L, string x);
adrRuang findElmRuangNomor(List L, int x);

adrRuang findElmRuangdariPasien(List L, Pasien x);

adrPasien findElmPasien(adrRuang &L, Pasien x);
adrPasien findElmPasienList(List L, Pasien x, adrRuang P);

void printall(List L);

#endif // TUBES_H_INCLUDED
