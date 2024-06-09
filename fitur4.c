#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 1000
#define MAX_DATE_LEN 30

typedef struct {
    char date[MAX_DATE_LEN];
    int cost;
} Record;

Record records[MAX_RECORDS];
int record_count = 0;

// Fungsi untuk menyamakan format bulan
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

// Fungsi untuk menyamakan format tanggal
void parseDate(const char *date_str, int *day, int *month, int *year) {
    char month_str[10];
    if (sscanf(date_str, "%d-%3s-%2d", day, month_str, year) == 3 ||
        sscanf(date_str, "%d %s %d", day, month_str, year) == 3) {
        *month = getMonthFromString(month_str);
        if (*year < 100) {
            if (*year <= 24) *year += 2000; // Adjust two-digit year to four-digit year
            else *year += 1900; // Adjust two-digit year to four-digit year
        }
    } else if (sscanf(date_str, "%d-%d-%d", day, month, year) == 3) {
    } else if (sscanf(date_str, "%d %d %d", day, month, year) == 3) {
    }
}

// Fungsi untuk membaca file CSV 
void readCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Tidak dapat membuka file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char dummy[20];
        int cost;
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d", dummy, records[record_count].date, dummy, dummy, dummy, dummy, &cost) == 7) {
            records[record_count].cost = cost;
            record_count++;
        } 
    }

    fclose(file);
}

// Fungsi untuk mendapatkan data pendapatan bulanan
void getMonthlyRevenueReport(int month, int year) {
    int total = 0;
    int found = 0;
    for (int i = 0; i < record_count; i++) {
        int rec_day, rec_month, rec_year;
        parseDate(records[i].date, &rec_day, &rec_month, &rec_year);

        if (rec_year == year && rec_month == month) {
            total += records[i].cost;
            found = 1;
        }
    }
    if (found) {
        printf("Pendapatan bulan %d-%d: Rp %d\n", month, year, total);
    } else {
        printf("Data pendapatan untuk bulan %d-%d tidak tersedia.\n", month, year);
    }
}

// Fungsi untuk mendapatkan data pendapatan tahunan
void getAnnualRevenueReport(int year) {
    int total = 0;
    int found = 0;
    for (int i = 0; i < record_count; i++) {
        int rec_day, rec_month, rec_year;
        parseDate(records[i].date, &rec_day, &rec_month, &rec_year);

        if (rec_year == year) {
            total += records[i].cost;
            found = 1;
        }
    }
    if (found) {
        printf("Pendapatan tahun %d: Rp %d\n", year, total);
    } else {
        printf("Data pendapatan untuk tahun %d tidak tersedia.\n", year);
    }
}

// Fungsi untuk mendapatkan rata-rata dari data pendapatan tahunan
void getAverageAnnualRevenue() {
    int year;
    printf("\nMasukkan tahun (YYYY): ");
    scanf("%d", &year);

    int total_revenue = 0;
    int total_records = 0;

    for (int i = 0; i < record_count; i++) {
        int rec_day, rec_month, rec_year;
        parseDate(records[i].date, &rec_day, &rec_month, &rec_year);

        if (rec_year == year) {
            total_revenue += records[i].cost;
            total_records++;
        }
    }

    if (total_records > 0) {
        printf("Rata-rata pendapatan untuk tahun %d: Rp %d\n", year, total_revenue / total_records);
    } else {
        printf("Tidak ada data pendapatan untuk tahun %d.\n", year);
    }
}

// Fungsi main
int main() {
    int choice, month, year;
    readCSV("RiwayatPasien.csv");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Pendapatan bulanan\n");
        printf("2. Pendapatan tahunan\n");
        printf("3. Rata-rata pendapatan per tahun\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                do {
                    printf("\nMasukkan bulan (1-12): ");
                    scanf("%d", &month);
                    if (month < 1 || month > 12) {
                        printf("Bulan tidak valid. Silahkan masukkan bulan antara 1-12.\n");
                    }
                } while (month < 1 || month > 12);
                
                printf("Masukkan tahun (YYYY): ");
                scanf("%d", &year);
                getMonthlyRevenueReport(month, year);
                break;
            case 2:
                printf("\nMasukkan tahun (YYYY): ");
                scanf("%d", &year);
                getAnnualRevenueReport(year);
                break;
            case 3:
                getAverageAnnualRevenue();
                break;
            case 4:
                printf("\nKeluar dari program.\n");
                exit(0);
            default:
                printf("Opsi tidak valid. Silakan coba lagi.\n");
        }
    }

    return 0;
}
