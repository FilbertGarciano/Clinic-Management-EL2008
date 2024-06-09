#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct jumlah{ 
    char penyakit[100]; 
    int banyak; 
}jumlah; 

jumlah penyakit[9999]; 

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

// Pencarian bulan ataupun tahun pada masing-masing data
void Finder(char tanggal[], char TBulan[], char TTahun[]){
    char pTanggal[100]; 
    TanggalRemake(tanggal, pTanggal); 
    char *hari = strtok(pTanggal, " ");
    char *bulan = strtok(NULL, " ");
    char *tahun = strtok(NULL, "\n");  
    strcpy(TTahun, tahun); 
    strcpy(TBulan, bulan); 
}

// Mengurutkan data dari terbesar ke terkecil
void bubbleSort(jumlah arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Melakukan pengecekan terhadap jumlah yang paling banyak
            if (arr[j].banyak < arr[j + 1].banyak) {
                jumlah temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void DataPenyakit(char string[], int opsi){
    FILE*address; 
    int JPenyakit = 0; 
    char line[1000]; 
    char wabah[100]; 
    char *token;
    char tanggal[100]; 
    address = fopen("Riwayat Pasien.csv", "r");
    while (fgets(line, sizeof(line), address)) {
        token = strtok(line, ",");  // No
        token = strtok(NULL, ","); // Tanggal
        strcpy(tanggal,token); 
        token = strtok(NULL, ","); // ID
        token = strtok(NULL, ","); // Diagnosis
        strcpy(wabah, token);
        token = strtok(NULL, ","); // Tindakan
        token = strtok(NULL, ","); // Kontrol
        token = strtok(NULL, "/n"); // Biaya
        int i;
        int sudah_ada = 0;
        char bulan[100], tahun[100]; 
        Finder(tanggal, bulan, tahun);
        if(opsi == 1){
            if(strcmp(bulan, string) == 0){
                for (i = 0; i < JPenyakit; ++i) {
                    if (strcmp(penyakit[i].penyakit, wabah) == 0) {
                        sudah_ada = 1;
                        penyakit[i].banyak++;
                        break;
                    }
                }
                if (sudah_ada == 0) {
                    strcpy(penyakit[JPenyakit].penyakit, wabah);
                    penyakit[JPenyakit].banyak = 1;
                    JPenyakit++;
                }
            }
        }
        else{
            if(strcmp(tahun, string) == 0){
                for (i = 0; i < JPenyakit; ++i) {
                    if (strcmp(penyakit[i].penyakit, wabah) == 0) {
                        sudah_ada = 1;
                        penyakit[i].banyak++;
                        break;
                    }
                }
                if (sudah_ada == 0) {
                    strcpy(penyakit[JPenyakit].penyakit, wabah);
                    penyakit[JPenyakit].banyak = 1;
                    JPenyakit++;
                }
            }
        }
    }
    fclose(address);
    if (JPenyakit == 0){
        printf("Tidak ada penyakit pada Bulan ataupun Tahun Tersebut"); 
    }
    else{
        printf("Jumlah Penyakit yang terjadi Pada saat Itu:\n");
        bubbleSort(penyakit,JPenyakit); 
        for (int i = 0; i < JPenyakit; i++) {
            printf("%s %d \n", penyakit[i].penyakit, penyakit[i].banyak);
        }
    }
}

int main(){
    char string[10]; 
    int opsi;
    printf("=========== MENU  ===========\n");
    printf("1. Jumlah Derita Pasien per Bulan\n"); 
    printf("2. Jumlah Derita Pasien per Tahun\n");
    printf("==============================\n"); 
    printf("Menu: "); 
    scanf("%d", &opsi);
    if (opsi == 1){ 
        printf("Masukkan Nama Bulan : "); 
        scanf("%s", string); 
        DataPenyakit(string, opsi); 
    }
    else if(opsi == 2){
        printf("Masukkan Nama Tahun : "); 
        scanf("%s", string); 
        DataPenyakit(string, opsi); 
    }
    else{
        printf("Tidak Valid"); 
    }
}


