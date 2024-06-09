#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data {
    char nama[100];
    char alamat[100];
    char kota[100];
    char tempat_lahir[100];
    char tanggal_lahir[100];
    int umur;
    int BPJS;
    char ID_pasien[100];
    struct Data *next;
} Data;

// Fungsi untuk menambahkan data pasien baru
void addPatient(Data **head_ref, char *nama, char *alamat, char *kota, char *tempat_lahir, char *tanggal_lahir, int umur, int BPJS, char *ID_pasien) {
    // Inisialisasi
    Data *newdata = (Data*) malloc(sizeof(Data));
    Data *last = *head_ref;
    // Input data
    strcpy(newdata->nama, nama);
    strcpy(newdata->alamat, alamat);
    strcpy(newdata->kota, kota);
    strcpy(newdata->tempat_lahir, tempat_lahir);
    strcpy(newdata->tanggal_lahir, tanggal_lahir);
    newdata->umur = umur;
    newdata->BPJS = BPJS;
    strcpy(newdata->ID_pasien, ID_pasien);
    // Assign next sebagai NULL
    newdata->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = newdata;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newdata;
    return;
}

// Fungsi untuk mengupdate data lama dengan data baru berdasarkan ID pasien
void updatePatient(Data **head_ref, char *nama, char *alamat, char *kota, char *tempat_lahir, char *tanggal_lahir, int umur, int BPJS, char *ID_pasien) {
    Data *current = *head_ref;
    while (current != NULL) {
        // Mencari data dengan ID yang sesuai
        if (strcmp(current->ID_pasien, ID_pasien) == 0) {
            // Mengubah keseluruhan data, kecuali ID
            strcpy(current->nama, nama);
            strcpy(current->alamat, alamat);
            strcpy(current->kota, kota);
            strcpy(current->tempat_lahir, tempat_lahir);
            strcpy(current->tanggal_lahir, tanggal_lahir);
            current->umur = umur;
            current->BPJS = BPJS;
            return;
        }
        current = current->next;
    }
    // Jika data tidak ditemukan
    printf("\nID Pasien tidak ditemukan.\n");
}

// Fungsi untuk menghapus data berdasarkan ID pasien
void deletePatient(Data **head_ref, char *ID_pasien) {
    Data *temp = *head_ref, *prev = NULL;

    if (temp != NULL && strcmp(temp->ID_pasien, ID_pasien) == 0) {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    // Mencari data yang perlu di-delete
    while (temp != NULL && strcmp(temp->ID_pasien, ID_pasien) != 0) {
        prev = temp;
        temp = temp->next;
    }
    // Jika ID tidak ditemukan
    if (temp == NULL) {
        printf("\nID Pasien tidak ditemukan.\n");
        return;
    }
    // Remove node
    prev->next = temp->next;
    free(temp);
}

// Fungsi untuk mencari data pasien berdasarkan ID pasien
void searchPatient(Data **head_ref, char *ID_pasien) {
    Data *current = *head_ref;
    while (current != NULL) {
        if (!strcmp(current->ID_pasien, ID_pasien)) {
            printf("\nData Pasien:\n");
            printf("Nama: %s\n", current->nama);
            printf("Alamat: %s\n", current->alamat);
            printf("Kota: %s\n", current->kota);
            printf("Tempat Lahir: %s\n", current->tempat_lahir);
            printf("Tanggal Lahir: %s\n", current->tanggal_lahir);
            printf("Umur: %d\n", current->umur);
            printf("Nomor BPJS: %d\n", current->BPJS);
            printf("ID Pasien: %s\n", current->ID_pasien);
            return;
        }
        current = current->next;
    }
    // Jika data tidak ditemukan
    printf("\nID Pasien tidak ditemukan.\n");
}

// Fungsi untuk mengecek apakah ID masukan sama dengan yang sudah ada di database
int cekID(Data **head, char *ID_pasien) {
    Data *current = *head;
    while (current != NULL) {
        if (!strcmp(current->ID_pasien, ID_pasien)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Fungsi untuk menyamakan format bulan
int getMonthFromString(char *month_str) {
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

// Fungsi untuk mem-format string tanggal_lahir ke DD-MM-YYY
void formatDate(char *tanggal_lahir) {
    int day, year;
    char month[20];
    int month_num; // menyimpan bulan dalam integer
    // Cek apakah format sudah DD-MM-YYYY
    if (sscanf(tanggal_lahir, "%d-%d-%d", &day, &month_num, &year) == 3) {
        sprintf(tanggal_lahir, "%02d-%02d-%d", day, month_num, year);
        return;
    }
    // Cek untuk format DD Month YYYY
    if (sscanf(tanggal_lahir, "%d %s %d", &day, month, &year) == 3) {
        month_num = getMonthFromString(month);
        sprintf(tanggal_lahir, "%02d-%02d-%d", day, month_num, year);
    }
    // Cek untuk format DD-Month-YY
    else if (sscanf(tanggal_lahir, "%d-%[^-]-%d", &day, month, &year) == 3) {
        month_num = getMonthFromString(month);
        // Ubah format YY ke YYYY
        year += (year < 50) ? 2000 : 1900;
        sprintf(tanggal_lahir, "%02d-%02d-%d", day, month_num, year);
    }
}

// Fungsi untuk membaca file csv Data Pasien
void readCSV(Data **head_ref, char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File tidak bisa dibuka.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char tempNama[100], tempAlamat[100], tempKota[100], tempKotaLahir[100], tempTanggalLahir[100], tempID[100];
        int tempUmur, tempBPJS; 
        int dummy; // untuk variabel number
        if (sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%[^\n]", &dummy, tempNama, tempAlamat, tempKota, tempKotaLahir, tempTanggalLahir, &tempUmur, &tempBPJS, tempID) == 9) {
            formatDate(tempTanggalLahir);
            addPatient(head_ref, tempNama, tempAlamat, tempKota, tempKotaLahir, tempTanggalLahir, tempUmur, tempBPJS, tempID);
        } 
    }
    fclose(file);
}

// Fungsi untuk menulis linked list ke file csv Data Pasien
void writeCSV(Data **head_ref, char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("File tidak bisa dibuka.\n");
        return;
    }

    Data *current = *head_ref;
    int id = 1;  // Penomoran data di csv
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%s,%s,%s,%d,%d,%s\n", id++, current->nama, current->alamat, current->kota, current->tempat_lahir, current->tanggal_lahir, current->umur, current->BPJS, current->ID_pasien);
        current = current->next;
    }
    fclose(file);
}

// Fungsi untuk display data pasien (untuk keperluan testing)
void display(Data **head) {
    Data *current = *head;
    if (current == NULL) {
        printf("Data Pasien Kosong.\n");
        return;
    }
    else {
        while (current != NULL) {
            printf("Nama            : %s\n", current->nama);
            printf("Alamat          : %s\n", current->alamat);
            printf("Kota            : %s\n", current->kota);
            printf("Tempat Lahir    : %s\n", current->tempat_lahir);
            printf("Tanggal Lahir   : %s\n", current->tanggal_lahir);
            printf("Umur            : %d\n", current->umur);
            printf("Nomor BPJS      : %d\n", current->BPJS);
            printf("ID Pasien       : %s\n\n", current->ID_pasien);
            current = current->next;
        }
    }
}

// Fungsi untuk free linked list
void freeList(Data **head) {
    Data *current = *head;
    Data *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Fungsi untuk menu utama, asumsi input selalu benar (testing)
void menu(Data **head) {
    // Membaca file awal
    readCSV(head, "Data Pasien.csv");
    int choice;
    char nama[100], alamat[100], kota[100], tempat_lahir[100], tanggal_lahir[100], ID_pasien[100];
    int umur, BPJS;

    do {
        printf("\n=============================================\n");
        printf("              PROGRAM DATA PASIEN\n");
        printf("Menu:\n");
        printf("1. Tambah Pasien\n");
        printf("2. Update Data Pasien\n");
        printf("3. Hapus Data Pasien\n");
        printf("4. Cari Data Pasien\n");
        printf("5. Tampilkan Data\n"); // testing
        printf("6. Keluar Program\n");
        printf("=============================================\n");
        printf("Masukkan pilihan (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan nama pasien: ");
                scanf(" %[^\n]", nama);
                printf("Masukkan alamat pasien: ");
                scanf(" %[^\n]", alamat);
                printf("Masukkan kota asal pasien: ");
                scanf(" %[^\n]", kota);
                printf("Masukkan tempat lahir pasien: ");
                scanf(" %[^\n]", tempat_lahir);
                printf("Masukkan tanggal lahir pasien (DD-MM-YYYY): ");
                scanf(" %[^\n]", tanggal_lahir);
                printf("Masukkan umur pasien: ");
                scanf("%d", &umur);
                printf("Masukkan nomor BPJS pasien: ");
                scanf("%d", &BPJS);
                printf("Masukkan nomor ID pasien: ");
                scanf(" %[^\n]", ID_pasien);
                if (cekID(head, ID_pasien)) {
                    printf("ID pasien sudah digunakan!\n");
                }
                else addPatient(head, nama, alamat, kota, tempat_lahir, tanggal_lahir, umur, BPJS, ID_pasien);
                break;
            case 2:
                printf("Masukkan ID pasien: ");
                scanf(" %[^\n]", ID_pasien);
                printf("Masukkan nama perbaikan: ");
                scanf(" %[^\n]", nama);
                printf("Masukkan alamat perbaikan: ");
                scanf(" %[^\n]", alamat);
                printf("Masukkan kota asal perbaikan: ");
                scanf(" %[^\n]", kota);
                printf("Masukkan tempat lahir perbaikan: ");
                scanf(" %[^\n]", tempat_lahir);
                printf("Masukkan tanggal lahir perbaikan (DD-MM-YYYY): ");
                scanf(" %[^\n]", tanggal_lahir);
                printf("Masukkan umur perbaikan: ");
                scanf("%d", &umur);
                printf("Masukkan nomor BPJS perbaikan: ");
                scanf("%d", &BPJS);
                updatePatient(head, nama, alamat, kota, tempat_lahir, tanggal_lahir, umur, BPJS, ID_pasien);
                break;
            case 3:
                printf("Masukkan ID pasien untuk menghapus data: ");
                scanf(" %[^\n]", ID_pasien);
                deletePatient(head, ID_pasien);
                break;
            case 4:
                printf("Masukkan ID pasien untuk mencari data: ");
                scanf(" %[^\n]", ID_pasien);
                searchPatient(head, ID_pasien);
                break;
            case 5:
                printf("DATA PASIEN\n");
                display(head);
                break;
            case 6:
                printf("MENUTUP PROGRAM...\n");
                writeCSV(head, "Data Pasien.csv"); // Update file csv
                freeList(head);
                printf("PROGRAM BERHASIL DITUTUP.\n");
                break;
            default:
                printf("Masukkan pilihan yang valid!\n");
                break;
        }
    } while (choice != 6);
}

int main() {
    Data *head = NULL;
    menu(&head);
    return 0;
}
