#include "tubes.h"
#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include <windows.h>
#include <dos.h>
#include <direct.h>
#include <conio.h>
using namespace std;

int nomor = 0;
adrRuang getInput(string s) {
    Ruang x;
    x.tipe = s;
    x.nomor = ++nomor;
    return alokasiRuang(x);
}

adrPasien getPasien(){
    Pasien S;
    cout<<"Nama Pasien: ";
    cin>>S.nama;
    cout<<"Penyakit: ";
    cin>>S.penyakit;
    return alokasiPasien(S);
}
void SetColor(int ForgC)
 {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }

 void ClearConsoleToColors(int ForgC, int BackC)
 {
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleTextAttribute(hStdOut, wColor);
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          SetConsoleCursorPosition(hStdOut, coord);
     }
    return;
}

void starter(){
    cout<<"__________________________________________________________________"<<endl;
    cout<<"                           KELOMPOK 3"<<endl;
    cout<<"                                                                  "<<endl;
    cout<<"                  Dewa Made Aditya Wirasakananda (1301180266)     "<<endl;
    cout<<"                  Muhammad Rizki Irsyad (1301180347)"<<endl;
    cout<<" "<<endl;
    cout<<"                          Program Version             "<<endl;
    cout<<"                            Version 0.99                        "<<endl;
    cout<<"__________________________________________________________________"<<endl;
}

void mainMenu(Ruang &R) {
    int g;
    Pasien cari;
    adrRuang p,k,tumbal;
    List L;
    string sl,he;
    createList(L);
    adrPasien q,r;
    int pil;
    int mini = 9999;
    sl="ICU"; /// membuat
    p = getInput(sl); /// icu
    insertLastRuang(L,p); /// sebagai ruangan default
    do {
        cout << "1. Tambah Ruangan" << endl;
        cout << "2. Tambah Pasien" << endl;
        cout << "3. Hapus Ruangan" << endl;
        cout << "4. Hapus Pasien" << endl;
        cout << "5. Lihat Isi" << endl;
        cout << "6. Cari Pasien" << endl;
        cout << "7. Cari Ruang dengan 4 Pasien" << endl;
        cout << "8. Cari Ruang dengan Pasien terkecil" << endl;
        cout << "0. Exit" << endl;
        cout << "Masukkan Pilihan : ";
        cin >> pil;
        cout << endl;
        switch(pil) {
        case 1 :
            he="INAP";
            p = getInput(he);
            insertLastRuang(L,p);
            cout<<"Ruang INAP sudah terbuat "<<endl;
            break;
        case 2 :
            // penambahan nama pasien
            q = getPasien();
            cout<<"1. ICU"<<endl;
            cout<<"2. INAP"<<endl;
            cout<<"3. ICU DAN INAP"<<endl;
            cout<<"Pilihan Anda : ";
            cin >> g;
            if (g == 1){
                k = findElmRuangNomor(L,g);
                if(CountElementPasienRuangan(k) != 4){
                    insertLastPasien(k,q);
                }
                else{
                    cout << "Icu sudah Penuh" << endl;
                }
            }else if (g == 2){
                k = findElmRuang(L,"INAP");
                while(CountElementPasienRuangan(k) == 4){
                    k = Rnext(k);
                }
                insertLastPasien(k,q);
            }else {
                g = 1;
                k = findElmRuangNomor(L,g);
                insertLastPasien(k,q);
                k = findElmRuang(L,"INAP");
                while(CountElementPasienRuangan(k) == 4){
                    k = Rnext(k);
                }
                insertLastPasien(k,q);
            }
            break;
        case 3 :
            deleteLastRuang(L);
            break;
        case 4 :
            // belom bisa berfungsi
            cout<<"Nama Pasien yang ingin dihapus : ";
            cin>>cari.nama;
            q = findElmPasienList(L,cari,tumbal);
            tumbal = findElmRuangdariPasien(L,cari);
            r = kolom(tumbal);
            if(r == q){
                deleteFirstPasien(tumbal,q);
            }
            else{
                while(next_pas(r) != q){
                    r = next_pas(r);
                }
                deleteAfterPasien(tumbal,r,q);
            }
            break;
        case 5 :
            printall(L);
            break;
        case 6 :
            cout<<"Nama Pasien yang ingin dicari : ";
            cin>>cari.nama;
            q = findElmPasienList(L,cari,p);
            p = findElmRuangdariPasien(L,cari);
            // ICU belum bisa ditampilkan mohon di cek ulang
            cout << "Tipe Ruangan : " << Rinfo(p).tipe << endl ;
            cout << "Nomor Ruangan : " << Rinfo(p).nomor << endl ;
            cout << "Nama Pasien : " << Pinfo(q).nama << endl ;
            cout << "Penyakit : " << Pinfo(q).penyakit << endl ;
            break;
        case 7 :
            p = first(L);
            while(Rnext(p) != NULL){
                if(CountElementPasienRuangan(p) == 4){
                    cout << "Tipe Ruangan : " << Rinfo(p).tipe << endl ;
                    cout << "Nomor Ruangan : " << Rinfo(p).nomor << endl ;
                    q = kolom(p);
                    while(q != NULL){
                        cout << "Nama Pasien : " << Pinfo(q).nama << endl ;
                        cout << "Penyakit : " << Pinfo(q).penyakit << endl ;
                        q = next_pas(q);
                    }
                }
                p = Rnext(p);
            }
            break;
        case 8 :
            p = first(L);
            while(Rnext(p) != NULL){
                if(CountElementPasienRuangan(p) < mini){
                    mini = CountElementPasienRuangan(p);
                    tumbal = p;
                }
                p = Rnext(p);
            }
            r = kolom(tumbal);
            if(CountElementPasienRuangan(tumbal) < 1){
                cout << "Tipe Ruangan : " << Rinfo(tumbal).tipe << endl ;
                cout << "Nomor Ruangan : " << Rinfo(tumbal).nomor << endl ;
                cout << "Kosong" << endl;
            }else{
                cout << "Tipe Ruangan : " << Rinfo(tumbal).tipe << endl ;
                cout << "Nomor Ruangan : " << Rinfo(tumbal).nomor << endl ;
                cout << "Nama Pasien : " << Pinfo(r).nama << endl ;
                cout << "Penyakit : " << Pinfo(r).penyakit << endl ;
            }
            break;
        case 0 :
            break;
        default :
            cout << "Invalid Input!" << endl;
            break;
        }
        cout << endl;
    } while(pil != 0);
}


int main()
{
    cout << "Checking Requirement Program" << endl;
    cout << "Press enter to continue....." << endl;
    getch();
    system("CLS");
    Ruang R;
    ClearConsoleToColors(15,4);
    cout<<"You Are Using Trial Mode Please Buy the Full Version"<<endl;
    starter();
    mainMenu(R);
    return 0;
}
