#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct DataPasien {
    int No;
    char Nama_Lengkap[100];
    char Alamat[100];
    char Kota[100];
    char Tempat_Lahir[100];
    char Tanggal_Lahir[100];
    int Umur;
    char BPJS[100];
    char ID[100]; 
    struct DataPasien *next; 
} DataPasien; 

void Pasien(DataPasien **head){
    char line[1000];
    char *token;
    int count = 0; 
    // Sesuaikan ini dengan data csv yang digunakan untuk data pasien
    FILE* address = fopen("Data Pasien.csv", "r");
    while (fgets(line, 1000, address)) {
        DataPasien *data = (DataPasien*) malloc(sizeof(DataPasien));
        token = strtok(line, ","); 
        data->No = atoi(token); 
        token = strtok(NULL, ",");
        strcpy(data->Nama_Lengkap, token);
        token = strtok(NULL, ",");
        strcpy(data->Alamat, token);
        token = strtok(NULL, ",");
        strcpy(data->Kota, token);
        token = strtok(NULL, ",");
        strcpy(data->Tempat_Lahir, token);
        token = strtok(NULL, ",");
        strcpy(data->Tanggal_Lahir, token);
        token = strtok(NULL, ",");
        data->Umur = atoi(token); 
        token = strtok(NULL, ",");
        strcpy(data->BPJS, token);
        token = strtok(NULL, ",");
        strcpy(data->ID, token);
        data->next = NULL;
        if (*head == NULL) {
            *head = data;
        } else {
            DataPasien *tail = *head;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = data;
        }
    }
    fclose(address);
}

typedef struct DataTindakan {
    int No;
    char Tanggal[100];
    char ID[100];
    char Diagnosis[100];
    char Tindakan[100];
    char Kontrol[100];
    int Biaya;
    struct DataTindakan *next;
} DataTindakan;

void Tindakan(DataTindakan **head) {
    char line[1000];
    char *token;
    int count = 0; 
    // Sesuaikan ini dengan data csv yang digunakan untuk data riwayat
    FILE* address = fopen("Riwayat Pasien.csv", "r");
    while (fgets(line, 1000, address)) {
        DataTindakan *data = (DataTindakan*) malloc(sizeof(DataTindakan));
        token = strtok(line, ","); 
        data->No = atoi(token); 
        token = strtok(NULL, ",");
        strcpy(data->Tanggal, token);
        token = strtok(NULL, ",");
        strcpy(data->ID, token);
        token = strtok(NULL, ",");
        strcpy(data->Diagnosis, token);
        token = strtok(NULL, ",");
        strcpy(data->Tindakan, token);
        token = strtok(NULL, ",");
        strcpy(data->Kontrol, token);
        token = strtok(NULL, ",");
        data->Biaya = atoi(token);
        data->next = NULL;
        if (*head == NULL) {
            *head = data;
        } else {
            DataTindakan *tail = *head;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = data;
        } 
    } 
    fclose(address);
}

// Konversi dari format tanggal "DD-MM-YY" ke "DD MM YYYY"
void TanggalRemake(char tanggal[], char p_tanggal[]){
    if (strchr(tanggal, '-')!= NULL) {
        char *hari = strtok(tanggal, "-");
        char *bulan = strtok(NULL, "-");
        char *tahun = strtok(NULL, "-");
        char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        char *l_bulan[] = {"Januari", "Febuari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
        int index = -1;
        for (int i = 0; i < 12; i++) {
            if (strcmp(bulan, months[i]) == 0) {
                index = i;
                break;
            }
        }
        int tahun_int = atoi(tahun);
        if (tahun_int < 25) {
            tahun_int += 2000;
        }
        else if(tahun_int > 25 && tahun_int <100){
            tahun_int += 1900;
        }
        // untuk hari bisa %02d ataupun %d 
        // apabila %02d maka inputnya apabila angka kurang dari perlu diberi 0 didepan
        sprintf(p_tanggal, "%d %s %04d", atoi(hari), l_bulan[index], tahun_int); 
    }
    else{
        strcpy(p_tanggal, tanggal); 
    }
}


// Permasalahan Nomor 3
void search(DataPasien*data, char ID[]){
    char nama[100]; 
    printf("Masukkan Nama Pasien yang ingin dicari : "); 
    scanf(" %[^\n]s", nama);
    // Konversi dari nama ke ID untuk mengakses secara lebih apa saja yang telah dilakukan
    while(data != NULL){ 
        if(strcasecmp(data->Nama_Lengkap, nama) == 0){
            strcpy(ID, data->ID);
            printf("Nama Lengkap : %s\n", data->Nama_Lengkap);
            printf("ID : %s", data-> ID);
            printf("Alamat : %s\n", data->Alamat);
            printf("No BPJS : %s\n", data->BPJS);
        }
        data = data->next; 
    }
}

// Pembuatan Sub Fungsi untuk melakukan pencetakan riwayat penyakit berdasarkan tanggal
typedef struct {
    int hari;
    int bulan;
    int tahun;
    char Diagnosa[100]; 
} Date;

Date dates[9999];

int monthToNumber(char* month) {
    if (strcasecmp(month, "Januari") == 0) return 1;
    else if (strcasecmp(month, "Februari") == 0) return 2;
    else if (strcasecmp(month, "Maret") == 0) return 3;
    else if (strcasecmp(month, "April") == 0) return 4;
    else if (strcasecmp(month, "Mei") == 0) return 5;
    else if (strcasecmp(month, "Juni") == 0) return 6;
    else if (strcasecmp(month, "Juli") == 0) return 7;
    else if (strcasecmp(month, "Agustus") == 0) return 8;
    else if (strcasecmp(month, "September") == 0) return 9;
    else if (strcasecmp(month, "Oktober") == 0) return 10;
    else if (strcasecmp(month, "November") == 0) return 11;
    else if (strcasecmp(month, "Desember") == 0) return 12;
    else return -1;
}

void swap(Date* a, Date* b) {
    Date temp = *a;
    *a = *b;
    *b = temp;
}

void add(char tanggal[], char diagnosa[], int i){
    char* token = strtok(tanggal, " ");
    dates[i].hari = atoi(token);    
    token = strtok(NULL, " ");
    dates[i].bulan = monthToNumber(token);
    token = strtok(NULL, " ");
    dates[i].tahun = atoi(token);
    strcpy(dates[i].Diagnosa, diagnosa);
}

void sortPrint(int n){
    // Bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (dates[j].tahun > dates[j + 1].tahun ||
                (dates[j].tahun == dates[j + 1].tahun && dates[j].bulan > dates[j + 1].bulan) ||
                (dates[j].tahun == dates[j + 1].tahun && dates[j].bulan == dates[j + 1].bulan && dates[j].hari > dates[j + 1].hari)) {
                swap(&dates[j], &dates[j + 1]);
            }
        }
    }
    char *l_bulan[] = {"Januari", "Febuari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"}; 
    for (int i = 0; i < n; i++) {
        printf("%d. %d %s %d - %s\n", i+1, dates[i].hari, l_bulan[dates[i].bulan-1],dates[i].tahun, dates[i].Diagnosa);
    }
}

void riwayat(DataTindakan**data_T, char ID[]){
    DataTindakan *head = *data_T;
    printf("Riwayat yang dialami pengguna :\n");
    int i = 0; 
    while (head != NULL) {
        if (strcmp(head->ID, ID) == -10) {
            char ptanggal[100]; 
            TanggalRemake(head->Tanggal, ptanggal);
            add(ptanggal,head->Diagnosis, i); 
            i++; 
        }
        head = head->next;
    } 
    sortPrint(i); 
} 

// Permasalahan No 6
void kontrol(DataPasien **data1, DataTindakan**data2){
    char input[100], ID[100]; 
    printf("Masukkan Tanggal Kontrol dalam Format(Hari Bulan Tahun): ");
    scanf(" %[^\n]s", input);
    printf("Pasien yang perlu untuk dikontrol pada tanggal %s : \n\n", input); 
    DataTindakan *head = *data2;
    int jumlah = 1; 
    while(head != NULL){
        char p_tanggal[100];
        TanggalRemake(head->Kontrol,p_tanggal);
        if (strcasecmp(p_tanggal, input) == 0) {
            strcpy(ID, head->ID);
            DataPasien *body = *data1;
            while(body != NULL){
                if (strcmp(body->ID, ID) == 10) {
                    printf("%d. \n", jumlah); 
                    printf("Nama : %s\n", body->Nama_Lengkap);
                    char ntanggal[100]; 
                    TanggalRemake(body->Tanggal_Lahir, ntanggal); 
                    printf("Tanggal Lahir : %s\n", ntanggal);
                    printf("Umur : %d\n", body->Umur); 
                    printf("ID : %s", body -> ID);
                    printf("Diagnosis : %s\n", head->Diagnosis);
                    printf("Tindakan : %s\n", head -> Tindakan);
                    printf("\n");
                    jumlah ++; 
                }
                body = body ->next;
            }
        }
        head = head->next;
    }
}

int main(){
    DataPasien* head1 = NULL;
    DataTindakan* head2 = NULL;
    char ID[100]; 
    Pasien(&head1);
    Tindakan(&head2);
    // Fitur no 3
    search(head1, ID);
    riwayat(&head2, ID);
    // Fitur no 6
    kontrol(&head1, &head2); 
}
