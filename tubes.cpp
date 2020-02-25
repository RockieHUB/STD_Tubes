#include "tubes.h"

void createList(List &L) {
    first(L) = NULL;
}

adrRuang alokasiRuang(Ruang x) {
    adrRuang P = new ElmRuang;
    Rinfo(P) = x;
    Rnext(P) = NULL;
    kolom(P) = NULL;

    return P;
}

adrPasien alokasiPasien(Pasien x) {//menambahakan data pasien
    adrPasien P = new ElmPasien;
    Pinfo(P) = x;
    next_pas(P) = NULL;

    return P;
}

void dealokasiRuang(adrRuang &P) {//delete ruangan
    Rnext(P) = NULL;
    delete P;
}

void dealokasiPasien(adrPasien &P) {
    next_pas(P) = NULL;
    delete P;
}

int CountElementRuang(List L){
    adrRuang P = first(L);
    int i = 1;
    while(Rnext(P) != NULL){
        P = Rnext(P);
        i++;
    }
    return i;
}

int CountElementPasienRuangan(adrRuang L){
    adrPasien P = kolom(L);
    int i = 0;
    while(P != NULL){
        i++;
        P = next_pas(P);
    }
    return i;
}

void insertFirstRuang(List &L, adrRuang P) {
    Rnext(P) = first(L);
    first(L) = P;
}

void insertFirstPasien(adrRuang &L, adrPasien P) {
    if(kolom(L) == NULL){
        next_pas(P) = NULL;
    }
    else{
        next_pas(P) = kolom(L);
    }
    kolom(L) = P;
}

void insertLastRuang(List &L, adrRuang P) {
    if(first(L) != NULL) {
        adrRuang Q = first(L);
        while(Rnext(Q) != NULL) {
            Q = Rnext(Q);
        }
        /* Rnext(Q) == NULL */
        Rnext(Q) = P;
        Rnext(P) = NULL;
    } else {
        insertFirstRuang(L,P);
    }
}

void insertLastPasien(adrRuang &L, adrPasien P) {
    if(kolom(L) != NULL) {
        adrPasien Q = kolom(L);
        while(next_pas(Q) != NULL) {
            Q = next_pas(Q);
        }
        /* next_pas(Q) == NULL */
        next_pas(Q) = P;
        next_pas(P) = NULL;
    } else { //jika kosong
        insertFirstPasien(L,P);
    }
}

void deleteFirstRuang(List &L, adrRuang &P) {
    if(first(L) != NULL) {
        P = first(L);
        first(L) = Rnext(P);
        dealokasiRuang(P);
    } else {
        cout << "List Kosong" << endl;
    }
}

void deleteFirstPasien(adrRuang &L, adrPasien P) {
    if(kolom(L) != NULL) {
        P = kolom(L);

        if(CountElementPasienRuangan(L) == 1){
            kolom(L) = NULL;
        }
        else{
            kolom(L) = next_pas(kolom(L));
        }
        next_pas(P) = NULL;
        dealokasiPasien(P);
    } else {
        cout << "List Kosong" << endl;
    }
}

void deleteLastRuang(List &L) {
    if(first(L) != NULL) {
        adrRuang P = first(L);
        if(Rnext(P) == NULL) {
            deleteFirstRuang(L,P);
        }
        else{
            while(Rnext(Rnext(P)) != NULL) {
                P = Rnext(P);
            }
            /* Rnext(RNext(P)) == NULL , P adalah address yang menunjuk element yang berada dibelakang element terakhir dari lsit */
            dealokasiRuang(Rnext(P)); //dealokasi element terakhir
            Rnext(P) = NULL;
        }
    }
    else{
        cout << "List Kosong" << endl;
    }
}

void deleteLastPasien(adrRuang &L) {
    adrPasien P = kolom(L);
    if(P != NULL) {
        if(CountElementPasienRuangan(L) == 1){
            deleteFirstPasien(L,P);
        }
        else{
            while(next_pas(next_pas(P)) != NULL) {
                P = next_pas(P);
            }
            /* next_pas(next_pas(P)) == NULL , P adalah address yang menunjuk element yang berada dibelakang element terakhir dari lsit */
            dealokasiPasien(next_pas(P)); //dealokasi element terakhir
        }
    }
}

void insertAfterRuang(List &L, adrRuang Prec, adrRuang P) {
    /* Yang dimasukkan adalah element yang ditunjuk oleh P dan ditaruh didepan element yang ditunjuk oleh Prec */
    Rnext(P) = Rnext(Prec);
    Rnext(Prec) = P;
}

void insertAfterPasien(adrRuang &L, adrPasien Prec, adrPasien P) {
    /* Yang dimasukkan adalah element yang ditunjuk oleh P dan ditaruh didepan element yang ditunjuk oleh Prec */
    next_pas(P) = next_pas(Prec);
    next_pas(Prec) = P;
}

void deleteAfterRuang(List &L, adrRuang Prec, adrRuang &P) {
    /* Menghapus Element(ditunjuk oleh P) yang berada didepan Element yang ditunjuk Prec  */
    if(Rnext(Prec) != NULL)  {
        P = Rnext(Prec);
        Rnext(Prec) = Rnext(P);
        dealokasiRuang(P);
    } else {
        /* Mendelete Element setelah Element terakhir, impossible */
        cout << "Tidak ada Element yang bisa dihapus" << endl;
    }
}

void deleteAfterPasien(adrRuang &L , adrPasien &Prec, adrPasien &P) {
    /* Menghapus Element(ditunjuk oleh P) yang berada didepan Element yang ditunjuk Prec  */
    if(next_pas(Prec) != NULL)  {
        P = next_pas(Prec);
        next_pas(Prec) = next_pas(P);
        dealokasiPasien(P);
    }else {
        /* Mendelete Element setelah Element terakhir, impossible */
        cout << "Tidak ada Element yang bisa dihapus" << endl;
    }
}

adrRuang findElmRuang(List L, string x) {
    if(first(L) != NULL) {
        adrRuang Q = first(L);
        while((Rnext(Q) != NULL) && (Rinfo(Q).tipe != x)) {
            Q = Rnext(Q);
        }
        /* next(Q) == NULL  || info(Q).tipe == x.tipe*/
        if(Rinfo(Q).tipe == x) {
            return Q;
        }
        else{
            /* Not Found */
            return NULL;
        }
    }
    else{
        /* List Kosong */
        return NULL;
    }
}

adrRuang findElmRuangNomor(List L, int x) {
    if(first(L) != NULL) {
        adrRuang Q = first(L);
        while((Rnext(Q) != NULL) && (Rinfo(Q).nomor != x)) {
            Q = Rnext(Q);
        }
        /* next(Q) == NULL  || info(Q).angka == x.angka*/
        if(Rinfo(Q).nomor == x) {
            return Q;
        }
        else{
            /* Not Found */
            return NULL;
        }
    }
    else{
        /* List Kosong */
        return NULL;
    }
}

adrPasien findElmPasien(adrRuang &L, Pasien x) {
    if(kolom(L) != NULL) {
        adrPasien Q = kolom(L);
        while((next_pas(Q) != NULL) && (Pinfo(Q).nama != x.nama)) {
            Q = next_pas(Q);
        }
        /* next_pas(Q) == NULL  || Pinfo(Q).nama == x.nama*/
        if(Pinfo(Q).nama == x.nama) {
            return Q;
        }
        else{
            /* Not Found */
            return NULL;
        }
    }
    else{
        /* List Kosong */
        return NULL;
    }
}

adrRuang findElmRuangdariPasien(List L, Pasien x){
    adrRuang Y = new ElmRuang;
    Y = first(L);
    adrPasien Z = findElmPasien(Y,x);
    while((Z == NULL) && (Rnext(Y) != NULL)) { // looping berhenti saat pasien ketemu (Z != NULL) atau Y sebagai address ruangan mentok
            Y = Rnext(Y);
            Z = findElmPasien(Y,x);
    }
    return Y;
}

adrPasien findElmPasienList(List L, Pasien x, adrRuang P) {
    adrRuang Y = new ElmRuang;
    Y = first(L);
    adrPasien Z = findElmPasien(Y,x);
    while((Z == NULL) && (Rnext(Y) != NULL)) { // looping berhenti saat pasien ketemu (Z != NULL) atau Y sebagai address ruangan mentok
            Y = Rnext(Y);
            Z = findElmPasien(Y,x);
    }
    return Z;
}

void printsemuaruangan(List &L,adrPasien q){
    adrRuang P = first(L);
    while(P != NULL){
        cout<<Rinfo(P).nomor<<"."<<Rinfo(P).tipe<<endl;
        P = Rnext(P);
    }
}

void printall(List L) {
    adrRuang Y = first(L);
    while (Y != NULL) {
        cout << "Ruang " << Rinfo(Y).tipe << "\t" ;
        cout << "Nomor " << Rinfo(Y).nomor<< endl ;
        adrPasien Z = kolom(Y);
        while(Z != NULL) {
            cout << "Nama Pasien : " << Pinfo(Z).nama<< endl ;
            cout << "Jenis Penyakit : " << Pinfo(Z).penyakit<< endl ;
            Z = next_pas(Z);
        }
    Y = Rnext(Y);
    }
}
