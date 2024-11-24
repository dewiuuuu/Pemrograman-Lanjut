#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char npm[15];
    char nama[50];
    char prodi[30];
    float ipk;
} Mahasiswa;

int i;
int j;
	
Mahasiswa data[MAX];
int n;

// Fungsi untuk menampilkan data mahasiswa
void tampilData() {
	
    printf("\nData Mahasiswa:\n");
    printf("%-15s %-30s %-20s %-5s\n", "NPM", "Nama", "Prodi", "IPK");
    for ( i = 0; i < n; i++) {
        printf("%-15s %-30s %-20s %.2f\n", data[i].npm, data[i].nama, data[i].prodi, data[i].ipk);
    }
}

// Fungsi Bubble Sort
void bubbleSort(int mode) {
    for ( i = 0; i < n - 1; i++) {
        for ( j = 0; j < n - i - 1; j++) {
            int swapNeeded = 0;
            if (mode == 1 && strcmp(data[j].npm, data[j + 1].npm) > 0) swapNeeded = 1; // NPM
            else if (mode == 2 && strcmp(data[j].nama, data[j + 1].nama) > 0) swapNeeded = 1; // Nama
            else if (mode == 3 && strcmp(data[j].prodi, data[j + 1].prodi) > 0) swapNeeded = 1; // Prodi
            else if (mode == 4 && data[j].ipk > data[j + 1].ipk) swapNeeded = 1; // IPK
            
            if (swapNeeded) {
                Mahasiswa temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

// Fungsi Insertion Sort
void insertionSort(int mode) {
    for ( i = 1; i < n; i++) {
        Mahasiswa key = data[i];
        int j = i - 1;

        while (j >= 0) {
            int shouldInsert = 0;
            if (mode == 1 && strcmp(data[j].npm, key.npm) > 0) shouldInsert = 1; // NPM
            else if (mode == 2 && strcmp(data[j].nama, key.nama) > 0) shouldInsert = 1; // Nama
            else if (mode == 3 && strcmp(data[j].prodi, key.prodi) > 0) shouldInsert = 1; // Prodi
            else if (mode == 4 && data[j].ipk > key.ipk) shouldInsert = 1; // IPK
            
            if (!shouldInsert) break;

            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

// Fungsi Merge untuk Merge Sort
void merge(int left, int mid, int right, int mode) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Mahasiswa L[n1], R[n2];

    for (i = 0; i < n1; i++) L[i] = data[left + i];
    for (j = 0; j < n2; j++) R[j] = data[mid + 1 + j];

    i = 0; j = 0; k = left;

    while (i < n1 && j < n2) {
        int shouldMerge = 0;
        if (mode == 1 && strcmp(L[i].npm, R[j].npm) <= 0) shouldMerge = 1; // NPM
        else if (mode == 2 && strcmp(L[i].nama, R[j].nama) <= 0) shouldMerge = 1; // Nama
        else if (mode == 3 && strcmp(L[i].prodi, R[j].prodi) <= 0) shouldMerge = 1; // Prodi
        else if (mode == 4 && L[i].ipk <= R[j].ipk) shouldMerge = 1; // IPK

        if (shouldMerge) data[k++] = L[i++];
        else data[k++] = R[j++];
    }

    while (i < n1) data[k++] = L[i++];
    while (j < n2) data[k++] = R[j++];
}

void mergeSort(int left, int right, int mode) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid, mode);
        mergeSort(mid + 1, right, mode);
        merge(left, mid, right, mode);
    }
}

// Menu utama untuk pengurutan
void menuSorting() {
    int pilihan;
    printf("\nPilih Metode Pengurutan:\n");
    printf("1. Bubble Sort\n2. Insertion Sort\n3. Merge Sort\nPilihan: ");
    scanf("%d", &pilihan);

    int mode;
    printf("\nPilih Kriteria Pengurutan:\n");
    printf("1. NPM\n2. Nama\n3. Prodi\n4. IPK\nPilihan: ");
    scanf("%d", &mode);

    switch (pilihan) {
        case 1: bubbleSort(mode); break;
        case 2: insertionSort(mode); break;
        case 3: mergeSort(0, n - 1, mode); break;
        default: printf("Pilihan tidak valid!\n"); return;
    }

    printf("\nData setelah pengurutan:\n");
    tampilData();
}

int main() {
    printf("Masukkan jumlah mahasiswa: ");
    scanf("%d", &n);

    for ( i = 0; i < n; i++) {
        printf("\nData Mahasiswa ke-%d:\n", i + 1);
        printf("NPM: "); scanf("%s", data[i].npm);
        printf("Nama: "); getchar(); fgets(data[i].nama, sizeof(data[i].nama), stdin);
        data[i].nama[strcspn(data[i].nama, "\n")] = 0; // Hapus newline
        printf("Prodi: "); fgets(data[i].prodi, sizeof(data[i].prodi), stdin);
        data[i].prodi[strcspn(data[i].prodi, "\n")] = 0; // Hapus newline
        printf("IPK: "); scanf("%f", &data[i].ipk);
    }

    int pilihan;
    do {
        printf("\nMenu:\n");
        printf("1. Tampilkan Data\n2. Urutkan Data\n3. Keluar\nPilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tampilData(); break;
            case 2: menuSorting(); break;
            case 3: printf("Keluar dari program.\n"); break;
            default: printf("Pilihan tidak valid!\n"); break;
        }
    } while (pilihan != 3);

    return 0;
}
