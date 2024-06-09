#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int tempNomor = 0;
int prevNomor = 0;
int tempTanggal;
int tempBulan;
int tempTahun;
char tempID[20];
char tempDiagnosis[50];
char tempTindakan[50];
int tempTanggalKontrol;
int tempBulanKontrol;
int tempTahunKontrol;
int tempBiaya;


char namafile[255];
char line[255];
char tempLine[255];
char *token;
char tokenTanggal[255];
char Vessel[255];
char tokenKontrol[255];

struct riwayat
{
    int nomor;
    int Tanggal; //format tanggal entry DD
    int Bulan;
    int Tahun;
    char ID[20];
    char Diagnosis[50];
    char Tindakan[50];
    int TanggalKontrol; //format tanggal entry DD
    int BulanKontrol;
    int TahunKontrol;
    int biaya;
    struct riwayat* next;

};

void printList(struct riwayat* node)
{
    while (node != NULL) {
        printf("No: %d\n", node->nomor);
        printf("Tanggal %d ", node->Tanggal);
        printf("%d ", node->Bulan);
        printf("%d\n", node->Tahun);
        printf("ID: %s\n", node->ID);
        printf("Diagnosis: %s\n", node->Diagnosis);
        printf("Tindakan: %s\n", node->Tindakan);
        printf("Kontrol: %d ", node->TanggalKontrol);
        printf("%d ", node->BulanKontrol);
        printf("%d\n", node->TahunKontrol);
        printf("Biaya: %d\n\n", node->biaya);

        node = node->next;
    }
    printf("\n");
}

int getMonthFromString(const char *month_str) {
    if (strcmp(month_str, "Januari") == 0 || strcmp(month_str, "Jan") == 0) return 1;
    else if (strcmp(month_str, "Februari") == 0 || strcmp(month_str, "Feb") == 0) return 2;
    else if (strcmp(month_str, "Maret") == 0 || strcmp(month_str, "Mar") == 0) return 3;
    else if (strcmp(month_str, "April") == 0 || strcmp(month_str, "Apr") == 0) return 4;
    else if (strcmp(month_str, "Mei") == 0 || strcmp(month_str, "Mei") == 0) return 5;
    else if (strcmp(month_str, "Juni") == 0 || strcmp(month_str, "Jun") == 0) return 6;
    else if (strcmp(month_str, "Juli") == 0 || strcmp(month_str, "Jul") == 0) return 7;
    else if (strcmp(month_str, "Agustus") == 0 || strcmp(month_str, "Agu") == 0) return 8;
    else if (strcmp(month_str, "September") == 0 || strcmp(month_str, "Sep") == 0) return 9;
    else if (strcmp(month_str, "Oktober") == 0 || strcmp(month_str, "Okt") == 0) return 10;
    else if (strcmp(month_str, "November") == 0 || strcmp(month_str, "Nov") == 0) return 11;
    else if (strcmp(month_str, "Desember") == 0 || strcmp(month_str, "Des") == 0) return 12;
    else return -1; // Invalid month
}

void parseDate(const char *date_str, int *day, int *month, int *year) {
    char month_str[10];
    if (sscanf(date_str, "%d-%3s-%2d", day, month_str, year) == 3 ||
        sscanf(date_str, "%d %s %d", day, month_str, year) == 3) {
        *month = getMonthFromString(month_str);
        *year += (*year < 100) ? 2000 : 0; // Adjust two-digit year to four-digit year
    } 
    else if (sscanf(date_str, "%d-%d-%d", day, month, year) == 3) {
    } 
    else if (sscanf(date_str, "%d %d %d", day, month, year) == 3) {
    }
}

int Biaya(char Tindakan[] , int Pendaftaran, int Pemeriksaan , int Vaksinasi , int Gula , int Infus , int Obat){
    int tempBiaya = Pendaftaran + Pemeriksaan;

    if (strcmp(Tindakan , "Vaksinasi") == 0){
        tempBiaya += Vaksinasi;
    }
    else if(strcmp(Tindakan , "Cek gula darah") == 0){
        tempBiaya += Gula;
    }
    else if(strcmp(Tindakan , "Pemasangan infus") == 0){
        tempBiaya += Infus;
    }
    else if(strcmp(Tindakan , "Pengobatan") == 0){
        tempBiaya += Obat;
    }
    return tempBiaya;
}

void tambahRiwayat(int nomor ,int Tanggal , int Bulan , int Tahun,char ID[20],char Diagnosis[50],char Tindakan[50],int TanggalKontrol , int BulanKontrol , int TahunKontrol  , struct riwayat** head , int Pendaftaran , int Pemeriksaan , int Vaksinasi , int Gula , int Infus , int Obat) 
{
    struct riwayat *RiwayatBaru = (struct riwayat *)malloc(sizeof(struct riwayat));
    RiwayatBaru -> nomor = nomor; 
    RiwayatBaru -> Tanggal = Tanggal;
    RiwayatBaru -> Bulan = Bulan;
    RiwayatBaru -> Tahun = Tahun;
    strcpy(RiwayatBaru -> ID , ID);
    strcpy(RiwayatBaru -> Diagnosis , Diagnosis);
    strcpy(RiwayatBaru -> Tindakan , Tindakan);
    RiwayatBaru -> TanggalKontrol = TanggalKontrol;
    RiwayatBaru -> BulanKontrol =BulanKontrol;
    RiwayatBaru -> TahunKontrol = TahunKontrol;
    RiwayatBaru -> biaya = Biaya(RiwayatBaru -> Tindakan , Pendaftaran , Pemeriksaan , Vaksinasi , Gula , Infus , Obat);

    struct riwayat* last = *head;
    RiwayatBaru->next = NULL;

    if (*head == NULL)
    {
        *head = RiwayatBaru;
        return;
    }

    while (last->next != NULL)
    {
        last = last->next;
    }

    last->next = RiwayatBaru;


}

void ubahRiwayat(struct riwayat **head, char ID[] , int Tanggal , int Bulan , int Tahun , int Pendaftaran , int Pemeriksaan , int Vaksinasi , int Gula , int Infus , int Obat) {
    struct riwayat *tinjau = *head;
    struct riwayat *prev = NULL;

    while (tinjau != NULL) {
        if ((strcmp(tinjau->ID, ID) == 0) && (tinjau->Tanggal == Tanggal) && (tinjau->Bulan == Bulan) && (tinjau->Tahun == Tahun)){
            printf("Masukkan data baru!\n");

            printf("Diagnosis: ");
            scanf(" %[^\n]s", tempDiagnosis);
            strcpy(tinjau->Diagnosis , tempDiagnosis);

            printf("Tindakan: ");
            scanf(" %[^\n]s", tempTindakan);
            while ((strcmp(tempTindakan , "Vaksinasi") != 0) && (strcmp(tempTindakan , "Cek gula darah") != 0) && (strcmp(tempTindakan , "Pemasangan infus") != 0) && (strcmp(tempTindakan , "Pengobatan") != 0)){
                printf("Tindakan tidak valid!\n");
                printf("Tindakan yang valid: Vaksinasi , Cek gula darah , Pemasangan infus , atau Pengobatan\n");
                printf("Tindakan: ");
                scanf(" %[^\n]s", tempTindakan);
            }
            strcpy(tinjau->Tindakan , tempTindakan);

            tinjau->biaya = Biaya(tinjau->Tindakan , Pendaftaran , Pemeriksaan , Vaksinasi , Gula , Infus , Obat);

            
            printf("Data pada tanggal %.2d-%.2d-%d dengan ID %s berhasil dimodifikasi\n",Tanggal , Bulan , Tahun , ID);
            return;
        }
        prev = tinjau;
        tinjau = tinjau->next;
    
    }
    printf("Data pada tanggal %.2d-%.2d-%d dengan ID %s tidak ditemukan\n",Tanggal , Bulan , Tahun , ID);
    return;
}

void hapusRiwayat(struct riwayat **head, char ID[] , int Tanggal , int Bulan , int Tahun) {
    struct riwayat *tinjau = *head;
    struct riwayat *prev = NULL;

    while (tinjau != NULL) {
        if ((strcmp(tinjau->ID, ID) == 0) && (tinjau->Tanggal == Tanggal) && (tinjau->Bulan == Bulan) && (tinjau->Tahun == Tahun)) {
            if (prev == NULL) {
                *head = tinjau->next;
            } else {
                prev->next = tinjau->next;
            }
            while (tinjau -> next != NULL){
                tinjau -> next -> nomor -= 1;
                tinjau = tinjau -> next;
            }
            
            free(tinjau);
            printf("Data pada tanggal %.2d-%.2d-%d dengan ID %s berhasil dihapus\n",Tanggal , Bulan , Tahun , ID);

            

            return;
        }
        prev = tinjau;
        tinjau = tinjau->next;
    }

    printf("Data pada tanggal %.2d-%.2d-%d dengan ID %s tidak ditemukan\n",Tanggal , Bulan , Tahun , ID);
    return;
}

void cariRiwayat(struct riwayat **head, char ID[] , int Tanggal , int Bulan , int Tahun){
    struct riwayat *tinjau = *head;
    struct riwayat *prev = NULL;

    while (tinjau != NULL) {
        if ((strcmp(tinjau->ID, ID) == 0) && (tinjau->Tanggal == Tanggal) && (tinjau->Bulan == Bulan) && (tinjau->Tahun == Tahun)){
            printf("\nNo: %d\n", tinjau->nomor);
            printf("Tanggal %d ", tinjau->Tanggal);
            printf("%d ", tinjau->Bulan);
            printf("%d\n", tinjau->Tahun);
            printf("ID: %s\n", tinjau->ID);
            printf("Diagnosis: %s\n", tinjau->Diagnosis);
            printf("Tindakan: %s\n", tinjau->Tindakan);
            printf("Kontrol: %d ", tinjau->TanggalKontrol);
            printf("%d ", tinjau->BulanKontrol);
            printf("%d\n", tinjau->TahunKontrol);
            printf("Biaya: %d\n\n", tinjau->biaya);
            return;
        }
        prev = tinjau;
        tinjau = tinjau->next;
    }

    printf("Data pada tanggal %.2d-%.2d-%d dengan ID %s tidak ditemukan\n",Tanggal , Bulan , Tahun , ID);
    return;
}


int main(){
    
int tempNomor = 0;
int prevNomor = 0;
int tempTanggal;
int tempBulan;
int tempTahun;
char tempID[20];
char tempDiagnosis[50];
char tempTindakan[50];
int tempTanggalKontrol;
int tempBulanKontrol;
int tempTahunKontrol;
int tempBiaya;


char namafile[255];
char line[255];
char tempLine[255];
char *token;
char tokenTanggal[255];
char Vessel[255];
char tokenKontrol[255];
int Pendaftaran , Pemeriksaan , Vaksinasi , Gula , Infus , Obat;

    FILE* stream = fopen("BiayaTindakan.csv", "r");
    for (int j = 0 ; j < 6 ; j++){
        fgets(line, 255, stream);
        token = strtok(line , ",");
        token = strtok(NULL , ",");
        token = strtok(NULL , "\n");

        if(j == 0){
            Pendaftaran = atoi(token);
        }
        else if(j == 1){
            Pemeriksaan = atoi(token);
        }
        else if(j == 2){
            Vaksinasi = atoi(token);   
        }
        else if(j == 3){
            Gula = atoi(token);
        }
        else if(j == 4){
            Infus = atoi(token);
        }
        else{
            Obat = atoi(token);
        }
    }
    fclose(stream);

    stream = fopen("RiwayatPasien.csv", "r");
    if (stream == NULL){
        printf("File tidak ditemukan");
        return 0;
    }

    //Parsing
    int i = 0;
    struct riwayat* head = NULL;
    while(fgets(line, 255, stream)){
        i++;
        while (i > 0){
        strcpy(tempLine, line);
        token = strtok(tempLine, ",");
        tempNomor = atoi(token);
    //printf("No: %d\n" , tempNomor);
    //printf("Nomor sebelumnya: %d " , prevNomor);
    //printf("Nomor saat ini: %d\n" , tempNomor);
        if(tempNomor == prevNomor){
            break;
        }
        prevNomor = tempNomor;
    
        token = strtok(NULL, ",");
        strcpy(tokenTanggal , token);
        parseDate(tokenTanggal , &tempTanggal , &tempBulan , &tempTahun);
        //printf("Tanggal: %d\n" , tempTanggal);
        //printf("Bulan: %d\n" , tempBulan);
        //printf("Tahun: %d\n" , tempTahun);

        token = strtok(NULL, ",");
        strcpy(tempID , token);
    //printf("ID: %s\n" , tempID);

        token = strtok(NULL, ",");
        strcpy(tempDiagnosis , token);
    //printf("Diagnosis: %s\n" , tempDiagnosis);

        token = strtok(NULL, ",");
        strcpy(tempTindakan , token);
    //printf("Tindakan: %s\n" , tempTindakan);

        token = strtok(NULL, ",");
        strcpy(tokenKontrol , token);
        parseDate(tokenKontrol , &tempTanggalKontrol , &tempBulanKontrol , &tempTahunKontrol);
        //printf("TanggalKontrol: %d\n" , tempTanggalKontrol);
        //printf("BulanKontrol: %d\n" , tempBulanKontrol);
        //printf("TahunKontrol: %d\n" , tempTahunKontrol);

        tambahRiwayat(tempNomor , tempTanggal , tempBulan , tempTahun , tempID , tempDiagnosis , tempTindakan , tempTanggalKontrol, tempBulanKontrol , tempTahunKontrol , &head , Pendaftaran , Pemeriksaan , Vaksinasi , Gula , Infus , Obat);

        fgets(line, 255, stream);
        }
    }
    int pilihanfitur = 6;

    printf("=============MENU=============\n");
    printf("0.Keluar\n");
    printf("1.Menambah riwayat kedatangan\n");
    printf("2.Mengubah riwayat kedatangan\n");
    printf("3.Menghapus riwayat kedatangan\n");
    printf("4.Mencari riwayat kedatangan\n");
    printf("5.Tampilkan semua riwayat kedatangan\n");
    printf("Masukkan pilihan: ");

    scanf("%d" , &pilihanfitur);

    while(pilihanfitur != 0){
            char IDUBAH[255];
            char TanggalUbah[255];
            int Tanggal;
            int Bulan;
            int Tahun;

        if (pilihanfitur == 1){
            strcpy(tokenTanggal , "");
            tempTanggal = 0;
            tempBulan = 0;
            tempTahun = 0;

            strcpy(tokenKontrol , "");
            tempTanggalKontrol = 0;
            tempBulanKontrol = 0;
            tempTahunKontrol = 0;

            tempNomor ++;
            printf("Tanggal(Format : DD-MM-YYYY): ");
            scanf("%s" , tokenTanggal);
            parseDate(tokenTanggal , &tempTanggal , &tempBulan , &tempTahun);

            printf("ID: ");
            scanf("%s" , tempID);
            strcat(tempID , " ");
            scanf("%s" , Vessel);
            strcat(tempID , Vessel);

            printf("Diagnosis: ");
            scanf(" %[^\n]s", tempDiagnosis);

            printf("Tindakan: ");
            scanf(" %[^\n]s", tempTindakan);
            while ((strcmp(tempTindakan , "Vaksinasi") != 0) && (strcmp(tempTindakan , "Cek gula darah") != 0) && (strcmp(tempTindakan , "Pemasangan infus") != 0) && (strcmp(tempTindakan , "Pengobatan") != 0)){
                printf("Tindakan tidak valid!\n");
                printf("Tindakan yang valid: Vaksinasi , Cek gula darah , Pemasangan infus , atau Pengobatan\n");
                printf("Tindakan: ");
                scanf(" %[^\n]s", tempTindakan);
            }

            printf("Tanggal kontrol(Format : DD-MM-YYYY): ");
            scanf("%s" , tokenKontrol);
            parseDate(tokenKontrol , &tempTanggalKontrol , &tempBulanKontrol , &tempTahunKontrol);
            
            tambahRiwayat(tempNomor , tempTanggal , tempBulan , tempTahun , tempID , tempDiagnosis , tempTindakan , tempTanggalKontrol, tempBulanKontrol , tempTahunKontrol , &head , Pendaftaran , Pemeriksaan , Vaksinasi , Gula , Infus , Obat);

        }
        else if(pilihanfitur == 2){
            printf("Tanggal Input Data yang ingin diubah (Format : DD-MM-YYYY): ");
            scanf("%s" , TanggalUbah);
            parseDate(TanggalUbah , &Tanggal , &Bulan , &Tahun);

            printf("ID Data yang ingin diubah: ");
            scanf("%s" , IDUBAH);
            scanf("%s" , Vessel);
            strcat(IDUBAH , " ");
            strcat(IDUBAH , Vessel);

            ubahRiwayat(&head , IDUBAH , Tanggal , Bulan , Tahun , Pendaftaran , Pemeriksaan , Vaksinasi , Gula , Infus , Obat);
            
        }
        else if(pilihanfitur == 3){
            printf("Tanggal Input Data yang ingin dihapus (Format : DD-MM-YYYY): ");
            scanf("%s" , TanggalUbah);
            parseDate(TanggalUbah , &Tanggal , &Bulan , &Tahun);

            printf("ID Data yang ingin dihapus: ");
            scanf("%s" , IDUBAH);
            scanf("%s" , Vessel);
            strcat(IDUBAH , " ");
            strcat(IDUBAH , Vessel);

            hapusRiwayat(&head , IDUBAH , Tanggal , Bulan , Tahun);
        }
        else if(pilihanfitur == 4){
            printf("Tanggal Input Data yang ingin dicari (Format : DD-MM-YYYY): ");
            scanf("%s" , TanggalUbah);
            parseDate(TanggalUbah , &Tanggal , &Bulan , &Tahun);

            printf("ID Data yang ingin dicari: ");
            scanf("%s" , IDUBAH);
            scanf("%s" , Vessel);
            strcat(IDUBAH , " ");
            strcat(IDUBAH , Vessel);

            cariRiwayat(&head , IDUBAH , Tanggal , Bulan , Tahun);
        }
        else if(pilihanfitur == 5){
            printList(head);
        }

        printf("\n=============MENU=============\n");
        printf("0.Keluar\n");
        printf("1.Menambah riwayat kedatangan\n");
        printf("2.Mengubah riwayat kedatangan\n");
        printf("3.Menghapus riwayat kedatangan\n");
        printf("4.Mencari riwayat kedatangan\n");
        printf("5.Tampilkan semua riwayat kedatangan\n");

        printf("Masukkan pilihan selanjutnya: ");

        scanf("%d" , &pilihanfitur);
    }
    fclose(stream);

    stream = fopen("RiwayatPasien.csv", "w");

    while (head != NULL) {
        fprintf(stream , "%d,%.2d-%.2d-%.4d,%s,%s,%s,%.2d-%.2d-%.4d,%d" , head -> nomor , head -> Tanggal , head -> Bulan , head ->Tahun , head -> ID , head-> Diagnosis , head -> Tindakan , head-> TanggalKontrol , head->BulanKontrol , head->TahunKontrol , head->biaya);
        fprintf(stream , "\n");
        head = head->next;
    }
    printf("\n");

    fclose(stream);
}
