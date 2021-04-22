#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

struct data{
    char nama[50];
    char telepon[20];
    int kamar;
    int hari;
    int biaya;
    struct data *next;
}*head, *tail, *current, *save, *temp;

struct history{
    char hist[100];
    struct history *lanjut;
}*pala, *ekor, *now;

COORD coord={0,0};
void gotoxy(int x, int y){
    coord.X=x;coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void password(char *temp){
    int key=0,index=0;
    do{
        key=getch();
        switch(key){
            case 0:
            case 224:
                getch();
                break;
            case '\b':
                if(index>0){
                    index--;
                    temp[index]=0;
                    printf("\b \b");
                }
                break;
            default:
                if(key>31 && key<127){
                    temp[index]=key;
                    index++;
                    printf("*");
                }
        }
    }while(key!=13);
    temp[index]='\0';
}

void historyy(char kalimat[100]){
    now = (struct history*)malloc(sizeof(struct history));
    strcpy(now->hist,kalimat);
    if(pala==NULL){
        pala=ekor=now;
        pala->lanjut=NULL;
    }else{
        ekor->lanjut=now;
        ekor=now;
    }
    ekor->lanjut=NULL;
    ekor=now;
}

void insert(int room, char name[50], char telp[50], int days, int harga){
    current = (struct data*)malloc(sizeof(struct data));
    current->kamar=room;
    strcpy(current->nama,name);
    strcpy(current->telepon,telp);
    current->hari=days;
    current->biaya=harga;
    if(head==NULL){
        head=tail=current;
        head->next=NULL;
    }else{
        tail->next=current;
        tail=current;
    }
    tail->next=NULL;
    tail=current;
}

void tampil(){
    system("cls");
    int a=11;

    gotoxy(23,3);printf("+============================================================================+");
    gotoxy(23,10);printf("+----------------------------------------------------------------------------+");
    gotoxy(23,8);printf("+============================================================================+");
    gotoxy(50,5);printf("DATA PENGUNJUNG HOTEL ROSE");
    gotoxy(46,6);printf("Data pengunjung yang telah diinput");
    gotoxy(23,9);printf("NO. KAMAR\tNAMA\t\tNO. TELP\t\tJUMLAH HARI\tBIAYA");
    current = head;
    if(head==NULL){
        gotoxy(56,a);printf("Tidak Ada Data");a++;
    }
    while(current!=NULL){
        gotoxy(23,a);printf("%i\t\t%s\t\t%s\t\t%i\t\t%i",current->kamar,current->nama,current->telepon,current->hari,current->biaya);a++;
        current=current->next;
    }
    gotoxy(23,a);printf("+----------------------------------------------------------------------------+");a+=2;
    gotoxy(50,a);printf("Klik terserah untuk lanjut");

}

int searchKamar(int room){
    current = head;
    while(current!=NULL){
        if(current->kamar==room){
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int aa=19;
void tampilSearch(){
    gotoxy(23,16);printf("+----------------------------------------------------------------------------+");
    gotoxy(23,18);printf("+----------------------------------------------------------------------------+");
    gotoxy(23,17);printf("NO. KAMAR\tNAMA\t\tNO. TELP\t\tJUMLAH HARI\tBIAYA");
    gotoxy(23,aa);printf("%i\t\t%s\t\t%s\t\t%i\t\t%i",current->kamar,current->nama,current->telepon,current->hari,current->biaya);aa++;
}

int searchRoom(int room){
    int a=0;
    current = head;
    while(current!=NULL){
        if(current->kamar==room){
            tampilSearch();
            a++;
        }
        current = current->next;
    }aa=19;
    if(a==0){
        return 0;
    }else{
        return 1;
    }
}

int searchNama(char name[50]){
    int a=0;
    current = head;
    while(current!=NULL){
        if(strcmp(current->nama,name)==0){
            tampilSearch();
            a++;
        }
        current = current->next;
    }aa=19;
    if(a==0){
        return 0;
    }else{
        return 1;
    }
}

int searchNomor(char telp[20]){
    int a=0;
    current = head;
    while(current!=NULL){
        if(strcmp(current->telepon,telp)==0){
            tampilSearch();
            a++;
        }
        current = current->next;
    }aa=19;
    if(a==0){
        return 0;
    }else{
        return 1;
    }
}

int searchHari(int days){
    int a=0;
    current = head;
    while(current!=NULL){
        if(current->hari==days){
            tampilSearch();
            a++;
        }
        current = current->next;
    }aa=19;
    if(a==0){
        return 0;
    }else{
        return 1;
    }
}

int searchBiaya(int harga){
    int a=0;
    current = head;
    while(current!=NULL){
        if(current->biaya==harga){
            tampilSearch();
            a++;
        }
        current = current->next;
    }aa=19;
    if(a==0){
        return 0;
    }else{
        return 1;
    }
}

void hapusKepala(){
    current = head;
    if(head==tail){
        head = tail = NULL;
        free(current);
    }else{
        head = head->next;
        free(current);
    }
}

void hapusAkhir(){
    if(head==tail){
        head = tail = NULL;
        free(current);
    }else{
        struct data *temp = head;
        while(temp->next!=tail){
            temp = temp->next;
        }
        current = tail;
        tail = temp;
        free(current);
        tail->next = NULL;
    }
}

void hapusKamar(int hapus){
    if(head->kamar==hapus){
        hapusKepala();
    }else if(tail->kamar==hapus){
        hapusAkhir();
    }else {
        struct data *temp = head;
        while(temp->next->kamar!=hapus && temp!=tail){
            temp = temp->next;
        }
        current = temp->next;
        temp->next = temp->next->next;
        free(current);
    }
}

void editNama(int room){
    char namaBaru[50];
    gotoxy(45,16);printf("UBAH DATA NAMA");
    gotoxy(45,17);printf("Data semula\t: %s",current->nama);fflush(stdin);
    gotoxy(45,18);printf("Data diubah\t: ");gets(namaBaru);
    strcpy(current->nama, namaBaru);
    char kalimat[50];
    sprintf(kalimat,"Nama pengunjung kamar nomor %i diubah menjadi %s",room,current->nama);
    historyy(kalimat);
}

void editNomor(int room){
    char nomorBaru[20];
    gotoxy(45,16);printf("UBAH DATA NOMOR");
    gotoxy(45,17);printf("Data semula\t: %s",current->telepon);fflush(stdin);
    gotoxy(45,18);printf("Data diubah\t: ");gets(nomorBaru);
    strcpy(current->telepon, nomorBaru);
    char kalimat[50];
    sprintf(kalimat,"Nomor telepon pengunjung kamar nomor %i diubah menjadi %s",room,current->telepon);
    historyy(kalimat);
}

void editHari(int room){
    int hariBaru;
    gotoxy(45,16);printf("UBAH DATA JUMLAH HARI");
    gotoxy(45,17);printf("Data semula\t: %i",current->hari);fflush(stdin);
    gotoxy(45,18);printf("Data diubah\t: ");scanf("%i",&hariBaru);
    current->hari=hariBaru;
    char kalimat[50];
    sprintf(kalimat,"Jumlah hari pengunjung kamar nomor %i diubah menjadi %i",room,current->hari);
    historyy(kalimat);
}

void editBiaya(int room){
    int biayaBaru;
    gotoxy(45,16);printf("UBAH DATA BIAYA");
    gotoxy(45,17);printf("Data semula\t: %i",current->biaya);fflush(stdin);
    gotoxy(45,18);printf("Data diubah\t: ");scanf("%i",&biayaBaru);
    current->biaya=biayaBaru;
    char kalimat[50];
    sprintf(kalimat,"Jumlah hari pengunjung kamar nomor %i diubah menjadi %i",room,current->biaya);
    historyy(kalimat);
}

void sortNama(){
    struct data *x,*y;
    char name[50],telp[20];
    int room,harga,days;
    if(head==NULL){}
    else{
        save=head;
        for(x=save;x->next!=NULL;x=x->next){
            for(y=x->next;y!=NULL;y=y->next){
                if(strcmp(x->nama, y->nama)>0){
                    strcpy(name,x->nama);
                    strcpy(telp,x->telepon);
                    room=x->kamar;
                    days=x->hari;
                    harga=x->biaya;

                    strcpy(x->nama,y->nama);
                    strcpy(x->telepon,y->telepon);
                    x->kamar=y->kamar;
                    x->hari=y->hari;
                    x->biaya=y->biaya;

                    strcpy(y->nama,name);
                    strcpy(y->telepon,telp);
                    y->kamar=room;
                    y->hari=days;
                    y->biaya=harga;
                }
            }
        }
    }
}

void sortNomor(){
    struct data *x,*y;
    char name[50],telp[20];
    int room,harga,days;
    if(head==NULL){}
    else{
        save=head;
        for(x=save;x->next!=NULL;x=x->next){
            for(y=x->next;y!=NULL;y=y->next){
                if(strcmp(x->telepon, y->telepon)>0){
                    strcpy(name,x->nama);
                    strcpy(telp,x->telepon);
                    room=x->kamar;
                    days=x->hari;
                    harga=x->biaya;

                    strcpy(x->nama,y->nama);
                    strcpy(x->telepon,y->telepon);
                    x->kamar=y->kamar;
                    x->hari=y->hari;
                    x->biaya=y->biaya;

                    strcpy(y->nama,name);
                    strcpy(y->telepon,telp);
                    y->kamar=room;
                    y->hari=days;
                    y->biaya=harga;
                }
            }
        }
    }
}

void sortKamar(){
    struct data *x,*y;
    char name[50],telp[20];
    int room,harga,days;
    if(head==NULL){}
    else{
        save=head;
        for(x=save;x->next!=NULL;x=x->next){
            for(y=x->next;y!=NULL;y=y->next){
                if(x->kamar > y->kamar){
                    strcpy(name,x->nama);
                    strcpy(telp,x->telepon);
                    room=x->kamar;
                    days=x->hari;
                    harga=x->biaya;

                    strcpy(x->nama,y->nama);
                    strcpy(x->telepon,y->telepon);
                    x->kamar=y->kamar;
                    x->hari=y->hari;
                    x->biaya=y->biaya;

                    strcpy(y->nama,name);
                    strcpy(y->telepon,telp);
                    y->kamar=room;
                    y->hari=days;
                    y->biaya=harga;
                }
            }
        }
    }
}

void sortHari(){
    struct data *x,*y;
    char name[50],telp[20];
    int room,harga,days;
    if(head==NULL){}
    else{
        save=head;
        for(x=save;x->next!=NULL;x=x->next){
            for(y=x->next;y!=NULL;y=y->next){
                if(x->hari > y->hari){
                    strcpy(name,x->nama);
                    strcpy(telp,x->telepon);
                    room=x->kamar;
                    days=x->hari;
                    harga=x->biaya;

                    strcpy(x->nama,y->nama);
                    strcpy(x->telepon,y->telepon);
                    x->kamar=y->kamar;
                    x->hari=y->hari;
                    x->biaya=y->biaya;

                    strcpy(y->nama,name);
                    strcpy(y->telepon,telp);
                    y->kamar=room;
                    y->hari=days;
                    y->biaya=harga;
                }
            }
        }
    }
}

void sortBiaya(){
    struct data *x,*y;
    char name[50],telp[20];
    int room,harga,days;
    if(head==NULL){}
    else{
        save=head;
        for(x=save;x->next!=NULL;x=x->next){
            for(y=x->next;y!=NULL;y=y->next){
                if(x->biaya > y->biaya){
                    strcpy(name,x->nama);
                    strcpy(telp,x->telepon);
                    room=x->kamar;
                    days=x->hari;
                    harga=x->biaya;

                    strcpy(x->nama,y->nama);
                    strcpy(x->telepon,y->telepon);
                    x->kamar=y->kamar;
                    x->hari=y->hari;
                    x->biaya=y->biaya;

                    strcpy(y->nama,name);
                    strcpy(y->telepon,telp);
                    y->kamar=room;
                    y->hari=days;
                    y->biaya=harga;
                }
            }
        }
    }
}

void kotakMenu(){
    system("color 1F");
    int x=36,b=12,a=11,c=11;
    char selamat[]={"SELAMAT DATANG DI DATABASE HOTEL"};

    gotoxy(30,4);printf("+==========================================================+");
    gotoxy(30,24);printf("+==========================================================+");
    gotoxy(30,9);printf("+----------------------------------------------------------+");
    gotoxy(44,6);for(int i=0;selamat[i]!='\0';i++){
                    printf("%c",selamat[i]);
                    for(double j=0;j<=4000000;j++){}
                }
    gotoxy(48,7);printf("=== DATA HOTEL ROSE ===");
    for(int i=0;i<b;i++){
        gotoxy(30,a);printf("|");
        a++;
    }
    for(int i=0;i<b;i++){
        gotoxy(89,c);printf("|");
        c++;
    }
    gotoxy(x,12);printf("Tekan 1. Membuat database hotel");
    gotoxy(x,13);printf("Tekan 2. Menampilkan isi database hotel");
    gotoxy(x,14);printf("Tekan 3. Menambahkan data baru ke database hotel");
    gotoxy(x,15);printf("Tekan 4. Menghapus data di database hotel");
    gotoxy(x,16);printf("Tekan 5. Mengedit data di database hotel");
    gotoxy(x,17);printf("Tekan 6. Mencari data di database hotel");
    gotoxy(x,18);printf("Tekan 7. Riwayat Pencarian database hotel");
    gotoxy(x,19);printf("Tekan 8. Mengurutkan data di database hotel");
    gotoxy(x,20);printf("Tekan 9. Keluar dari program");

}

int ke=1;
void menuSatu(){
    system("cls");
    system("color 0E");
    int input,room,harga,days,a=12;
    char name[50],telp[20];

    if(head==NULL){}
    else{
        for(int m=1;m<=9;m++){
            hapusKepala();
        }
    }

    gotoxy(28,3);printf("+================================================================+");
    gotoxy(28,8);printf("+----------------------------------------------------------------+");
    gotoxy(28,11);printf("+================================================================+");
    gotoxy(58,5);printf("DATABASE");
    gotoxy(47,6);printf("=== Membuat Database Hotel ===");
    gotoxy(41,9);printf("Data maksimum yang bisa diinput\t: 5");
    gotoxy(41,10);printf("Banyak data yang ingin diinput\t\t: ");scanf("%i",&input);
    if(input<=5){
        ke=1;
        for(int i=1;i<=input;i++){
            gotoxy(40,a);printf("::DATA PENGUNJUNG HOTEL KE-%i\n",ke);a++;ke++;
            gotoxy(40,a);printf("::Nomor Kamar\t\t: ");scanf("%i",&room);fflush(stdin);a++;
            gotoxy(40,a);printf("::Nama Pengunjung\t: ");gets(name);fflush(stdin);a++;
            gotoxy(40,a);printf("::Nomor Telepon\t\t: ");gets(telp);fflush(stdin);a++;
            gotoxy(40,a);printf("::Jumlah Hari\t\t: ");scanf("%i",&days);a++;
            gotoxy(40,a);printf("::Biaya\t\t\t: ");scanf("%i",&harga);a+=2;
            insert(room, name, telp, days, harga);
        }
        char kalimat[100];
        sprintf(kalimat,"Admin membuat %i data baru",input);
        historyy(kalimat);
    }else{
        gotoxy(48,a);printf("Maaf, data maksimal adalah 5.");a+=2;
    }

    gotoxy(49,a);printf("Klik terserah untuk lanjut");
    system("pause>null");
    system("cls");
}

void menuDua(){
    system("cls");
    system("color 0A");
    tampil();
    historyy("Admin melihat data");
    system("pause>null");
    system("cls");
}

void menuTiga(){
    system("cls");
    system("color 0D");
    int input,room,harga,days,a=12;
    char name[50],telp[20];

    gotoxy(28,3);printf("+================================================================+");
    gotoxy(28,8);printf("+----------------------------------------------------------------+");
    gotoxy(28,11);printf("+================================================================+");
    gotoxy(58,5);printf("DATABASE");
    gotoxy(46,6);printf("=== Menambah Database Hotel ===");
    gotoxy(41,9);printf("Data maksimum yang bisa diinput\t: 4");
    gotoxy(41,10);printf("Banyak data yang ingin diinput\t\t: ");scanf("%i",&input);
    if(input<=5){
        for(int i=1;i<=input;i++){
            gotoxy(40,a);printf("::DATA PENGUNJUNG HOTEL KE-%i\n",ke);a++;ke++;
            gotoxy(40,a);printf("::Nomor Kamar\t\t: ");scanf("%i",&room);fflush(stdin);a++;
            gotoxy(40,a);printf("::Nama Pengunjung\t: ");gets(name);fflush(stdin);a++;
            gotoxy(40,a);printf("::Nomor Telepon\t\t: ");gets(telp);fflush(stdin);a++;
            gotoxy(40,a);printf("::Jumlah Hari\t\t: ");scanf("%i",&days);a++;
            gotoxy(40,a);printf("::Biaya\t\t\t: ");scanf("%i",&harga);a+=2;
            insert(room, name, telp, days, harga);
        }
        char kalimat[100];
        sprintf(kalimat,"Admin menambah %i data baru",input);
        historyy(kalimat);
    }else{
        gotoxy(48,a);printf("Maaf, data maksimal adalah 4.");a+=2;
    }
    gotoxy(49,a);printf("Klik terserah untuk lanjut");
    system("pause>null");
    system("cls");
}

void menuEmpat(){
    system("cls");
    system("color 0B");
    int hapus;
    char yakin;

    gotoxy(28,3);printf("+================================================================+");
    gotoxy(28,8);printf("+----------------------------------------------------------------+");
    gotoxy(28,10);printf("+----------------------------------------------------------------+");
    gotoxy(57,5);printf("DATABASE");
    gotoxy(42,6);printf("=== Menghapus data pengunjung hotel ===");
    gotoxy(40,9);printf("Masukkan nomor kamar yang ingin dihapus\t: ");scanf("%i",&hapus);
    if((searchKamar(hapus))==0){
        gotoxy(52,12);printf("Data tidak ditemukan.");
        gotoxy(49,13);printf("Klik terserah untuk lanjut");
    }else{
        gotoxy(45,11);printf("::DATA");
        gotoxy(45,12);printf("::Nomor Kamar\t: %i",current->kamar);
        gotoxy(45,13);printf("::Nama\t\t: %s",current->nama);
        gotoxy(45,14);printf("::No. Telp\t\t: %s",current->telepon);
        gotoxy(45,15);printf("::Jumlah Hari\t: %i",current->hari);
        gotoxy(45,16);printf("::Biaya\t\t: %i",current->biaya);fflush(stdin);
        gotoxy(45,18);printf("Yakin ingin menghapus data ini?(y/n)");yakin=getch();
        if(yakin=='Y' || yakin=='y'){
            hapusKamar(hapus);
            char kalimat[100];
            sprintf(kalimat,"Admin menghapus data dari kamar nomor %i",hapus);
            historyy(kalimat);
            gotoxy(45,19);printf("Data berhasil dihapus");
            gotoxy(45,20);printf("Klik terserah untuk lanjut");
        }else if(yakin=='N' || yakin=='n'){
            gotoxy(45,19);printf("Data batal dihapus");
            gotoxy(45,20);printf("Klik terserah untuk lanjut");
        }
    }
    system("pause>null");
    system("cls");
}

void menuLima(){
    system("cls");
    system("color 0C");
    int edit,room;

    gotoxy(28,3);printf("+================================================================+");
    gotoxy(28,8);printf("+----------------------------------------------------------------+");
    gotoxy(28,15);printf("+----------------------------------------------------------------+");
    gotoxy(57,5);printf("DATABASE");
    gotoxy(42,6);printf("=== Mengubah data pengunjung hotel ===");
    gotoxy(40,9);printf("Apa yang ingin Anda edit?");
    gotoxy(40,10);printf("1. Nama pengunjung hotel\t3. Jumlah hari");
    gotoxy(40,11);printf("2. Nomor telepon\t\t4. Biaya");
    gotoxy(40,13);printf("Pilihan Anda\t\t: ");scanf("%i",&edit);
    gotoxy(40,14);printf("Masukkan nomor kamar\t: ");scanf("%i",&room);
    if(head==NULL){
        gotoxy(54,16);printf("Tidak ada data");
        gotoxy(48,17);printf("Klik terserah untuk lanjut");
    }else if(searchKamar(room)==0){
        gotoxy(54,16);printf("Tidak ada data");
        gotoxy(48,17);printf("Klik terserah untuk lanjut");
    }else{
        switch(edit){
        case 1:
            editNama(room);
            break;
        case 2:
            editNomor(room);
            break;
        case 3:
            editHari(room);
            break;
        case 4:
            editBiaya(room);
            break;
        }
        gotoxy(45,20);printf("Data berhasil diubah");
        gotoxy(45,21);printf("Klik terserah untuk lanjut");
    }
    system("pause>null");
    system("cls");
}

void menuEnam(){
    system("cls");
    system("color 80");
    int cari,room,harga,days;
    char name[50],telp[20],kalimat[100];

    gotoxy(28,3);printf("+================================================================+");
    gotoxy(28,8);printf("+----------------------------------------------------------------+");
    gotoxy(28,16);printf("+----------------------------------------------------------------+");
    gotoxy(57,5);printf("DATABASE");
    gotoxy(43,6);printf("=== Mencari data pengunjung hotel ===");
    gotoxy(40,9);printf("Apa yang ingin Anda cari?");
    gotoxy(40,10);printf("1. Nama pengunjung hotel\t3. Jumlah hari");
    gotoxy(40,11);printf("2. Nomor telepon\t\t4. Biaya");
    gotoxy(40,12);printf("5. Nomor kamar");
    gotoxy(40,14);printf("Pilihan Anda\t\t\t: ");scanf("%i",&cari);fflush(stdin);
    switch(cari){
        case 1:
            gotoxy(40,15);printf("Nama pengunjung yang dicari\t: ");gets(name);
            searchNama(name);
            if(searchNama(name)==0){
                gotoxy(50,17);printf("Tidak ada data");
            }
            sprintf(kalimat,"Admin mencari nama pengunjung : %s",name);
            historyy(kalimat);
            break;
        case 2:
            gotoxy(40,15);printf("Nomor telepon yang dicari\t: ");gets(telp);
            searchNomor(telp);
            if(searchNomor(telp)==0){
                gotoxy(50,17);printf("Tidak ada data");
            }
            sprintf(kalimat,"Admin mencari pengunjung dengan nomor telepon : %s",telp);
            historyy(kalimat);
            break;
        case 3:
            gotoxy(40,15);printf("Jumlah hari yang dicari\t\t: ");scanf("%i",&days);
            searchHari(days);
            if(searchHari(days)==0){
                gotoxy(50,17);printf("Tidak ada data");
            }
            sprintf(kalimat,"Admin mencari pengunjung dengan jumlah hari : %i",days);
            historyy(kalimat);
            break;
        case 4:
            gotoxy(40,15);printf("Biaya yang dicari\t\t: ");scanf("%i",&harga);
            searchBiaya(harga);
            if(searchBiaya(harga)==0){
                gotoxy(50,17);printf("Tidak ada data");
            }
            sprintf(kalimat,"Admin mencari pengunjung dengan biaya : %i",harga);
            historyy(kalimat);
            break;
        case 5:
            gotoxy(40,15);printf("Nomor kamar yang dicari\t\t: ");scanf("%i",&room);
            searchRoom(room);
            if(searchRoom(room)==0){
                gotoxy(50,17);printf("Tidak ada data");
            }
            sprintf(kalimat,"Admin mencari nomor kamar pengunjung : %i",room);
            historyy(kalimat);
            break;
        default:
            gotoxy(50,17);printf("Pilihan tidak ada");
    }
    system("pause>null");
    system("cls");
}

void menuTujuh(){
    system("cls");
    system("color 0F");
    int a=11,i=0;

    gotoxy(23,3);printf("+=====================================================================+");
    gotoxy(23,8);printf("+---------------------------------------------------------------------+");
    gotoxy(23,10);printf("+=====================================================================+");
    gotoxy(52,5);printf("DATA HOTEL ROSE");
    gotoxy(39,6);printf("=== RIWAYAT AKTIVITAS YANG DILAKUKAN ===");
    gotoxy(28,9);printf("NO.\t AKTIVITAS");
    now=pala;
    if(pala==NULL){
        gotoxy(53,a);printf("Tidak Ada Data");a++;
    }
    while(now!=NULL){
        gotoxy(28,a);printf("%i.\t %s",i+1,now->hist);i++;a++;
        now=now->lanjut;
    }
    a++;
    gotoxy(47,a);printf("Klik terserah untuk lanjut");
    system("pause>null");
    system("cls");
}

void menuDelapan(){
    system("cls");
    system("color 0E");
    int sort;

    gotoxy(28,3);printf("+================================================================+");
    gotoxy(28,8);printf("+----------------------------------------------------------------+");
    gotoxy(28,16);printf("+----------------------------------------------------------------+");
    gotoxy(57,5);printf("DATABASE");
    gotoxy(43,6);printf("=== Urutkan data pengunjung hotel ===");
    gotoxy(40,9);printf("Apa yang ingin Anda cari?");
    gotoxy(40,10);printf("1. Nama pengunjung hotel\t3. Jumlah hari");
    gotoxy(40,11);printf("2. Nomor telepon\t\t4. Biaya");
    gotoxy(40,12);printf("5. Nomor kamar");
    gotoxy(40,14);printf("Pilihan Anda\t\t\t: ");scanf("%i",&sort);fflush(stdin);
    switch(sort){
        case 1:
            sortNama();
            tampil();
            historyy("Admin mengurutkan data berdasarkan nama");
            break;
        case 2:
            sortNomor();
            tampil();
            historyy("Admin mengurutkan data berdasarkan nomor telepon");
            break;
        case 3:
            sortHari();
            tampil();
            historyy("Admin mengurutkan data berdasarkan jumlah hari");
            break;
        case 4:
            sortBiaya();
            tampil();
            historyy("Admin mengurutkan data berdasarkan biaya");
            break;
        case 5:
            sortKamar();
            tampil();
            historyy("Admin mengurutkan data berdasarkan nomor kamar");
            break;
        default:
            gotoxy(50,17);printf("Pilihan tidak ada");
    }
    system("pause>null");
    system("cls");
}

void menuSembilan(){
    system("cls");
    system("color 1F");
    int i;
    double j;

    char denis[]="DENIS ADITYA FERNANDA";
    char nim[]="672019245";
    gotoxy(30,9);printf("AUTHOR");
    gotoxy(30,10);for(i=0;denis[i]!='\0';i++){
                    printf("%c",denis[i]);
                    for(j=0;j<=15000000;j++){}
                }
    gotoxy(30,11);for(i=0;nim[i]!='\0';i++){
                    printf("%c",nim[i]);
                    for(j=0;j<=15000000;j++){}
                }
    Sleep(1000);
    system("cls");
    gotoxy(51,9);printf(" ");
    Sleep(1000);
    gotoxy(52,9);printf("****  *   * *****");
    gotoxy(51,10);printf(" ");
    Sleep(1000);
    gotoxy(52,10);printf("*   *  * *  *");
    gotoxy(51,11);printf(" ");
    Sleep(1000);
    gotoxy(52,11);printf("****    *   *****");
    gotoxy(51,12);printf(" ");
    Sleep(1000);
    gotoxy(52,12);printf("*   *   *   *");
    gotoxy(51,13);printf(" ");
    Sleep(1000);
    gotoxy(52,13);printf("****    *   *****");
    Sleep(1000);
    system("cls");
    gotoxy(48,9);printf("Thanks for using this database");
    Sleep(1000);
    system("cls");
    for(int i=3;i>0;i--){
        gotoxy(0,0);printf("This program will close in %i...",i);
        Sleep(1000);
    }
    exit(0);
}

int main(){
    char username[50],pass[50];
    struct tm *waktu;
    time_t tval;
    tval = time(NULL);
    waktu=localtime(&tval);
    const char * bulan[13]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

    start:
    system("color CF");
    gotoxy(41,8);printf("SELAMAT DATANG DI DATABASE HOTEL ROSE");
    gotoxy(40,10);printf("=======================================");
    gotoxy(40,14);printf("=======================================");
    gotoxy(41,15);printf("%s %02d %d",bulan[waktu->tm_mon],waktu->tm_mday,waktu->tm_year+1900);
    gotoxy(70,15);printf("%02i:%02i:%02i", waktu->tm_hour,waktu->tm_min,waktu->tm_sec);
    gotoxy(45,11);printf("Masukkan username\t: ");gets(username);fflush(stdin);
    gotoxy(45,13);printf("Masukkan password\t: ");password(pass);
    if(strcmp(username,"admin")==0 && strcmp(pass,"admin")==0){
        gotoxy(53,16);printf("Login Success!");
        gotoxy(47,18);printf("Klik terserah untuk lanjut");
        system("pause>null");
        system("cls");
    }else if(strcmp(username,"admin")!=0){
        gotoxy(53,16);printf("Username salah!");
        system("pause>null");
        system("cls");
        goto start;
    }else if(strcmp(pass,"admin")!=0){
        gotoxy(53,16);printf("Password salah!");
        system("pause>null");
        system("cls");
        goto start;
    }
    int menu;
    while(menu!=9){
        kotakMenu();
        gotoxy(36,23);printf("Masukkan pilihan anda : ");scanf("%i",&menu);fflush(stdin);
        switch(menu){
        case 1:
            menuSatu();
            break;
        case 2:
            menuDua();
            break;
        case 3:
            menuTiga();
            break;
        case 4:
            menuEmpat();
            break;
        case 5:
            menuLima();
            break;
        case 6:
            menuEnam();
            break;
        case 7:
            menuTujuh();
            break;
        case 8:
            menuDelapan();
            break;
        case 9:
            menuSembilan();
            break;
        default:
            gotoxy(52,25);printf("Pilihan tidak ada");
            gotoxy(47,26);printf("Klik terserah untuk lanjut");
            system("pause>null");
            system("cls");
        }
    }
    return 0;
}
