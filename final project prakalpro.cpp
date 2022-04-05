#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int firstMenu () {
	int pilih;
	system ("cls");
	printf ("\n___________________ TO MART ___________________");
	printf ("\n===============================================");
	printf ("\n                 1. Login");
	printf ("\n                 2. Registrasi");
	printf ("\n          ---------------------------");
	printf ("\n                ---> "); scanf ("%d", &pilih);
	return pilih;
}
int adminMenu () {
	int pilih;
	if (/*anda admin dan bukan user*/) {
		system ("cls");
		printf ("=======================================================\n");
		printf ("                        TO MART\n");
		printf ("=======================================================\n");
		//operasi file
		printf ("=======================================================\n");
		printf ("1. Penjualan\n");
		printf ("2. Tambah Barang Baru\n");
		printf ("3. Tambah Stok\n");
		printf ("4. Ubah Data Barang\n");
		printf ("5. Hapus Data Barang\n");
		printf ("6. Laporan\n");
		printf ("==========================================\n");
		printf ("Masukkan Pilihan : "); scanf ("%d", &pilih);
	}
	else {
		system ("cls");
		printf ("==========================================\n");
		printf ("1. Beli Barang\n");
		printf ("2. Troli - Bayar\n");
		printf ("3. Cek Saldo\n");
		printf ("4. Tambah Saldo\n");
		printf ("5. Laporan\n");
		printf ("==========================================\n");
		printf ("Masukkan Pilihan : "); scanf ("%d", &pilih);
	}
	printf ("\nNULL\n");
	return pilih;
}
void login () {
	char username[50], password[50];
	system ("cls");
	printf ("\n___________________ TO MART ___________________");
	printf ("\n===============================================");
	printf ("\n                Masukkan Username :");
	printf ("\n            ---------------------------");
	printf ("\n                ---> "); fflush (stdin); gets (username);
	printf ("\n                Masukkan Password :");
	printf ("\n            ---------------------------");
	printf ("\n                ---> "); fflush (stdin); gets (password);
	//proses dan operasi file
}
void registrasi () {
	system ("cls");
	printf ("\nREGISTRASI");
	printf ("\n=============================================")
	//operasi file
	printf ("\nMasukkan Nama      : "); fflush (stdin); gets ();
	printf ("\nMasukkan Username  : "); fflush (stdin); gets ();
	printf ("\nMasukkan Password  : "); fflush (stdin); gets ();
	printf ("\nUlangi Password    : "); fflush (stdin); gets ();
}
void showList () {
	printf ("\nNULL\n");
}
void jualBarang () {
	printf ("\nNULL\n");
}
void troli () {
	printf ("\nNULL\n");
}
void addBarang () {
	printf ("\nNULL\n");
}
void addStok () {
	printf ("\nNULL\n");
}
void editBarang () {
	printf ("\nNULL\n");
}
void hapusBarang () {
	printf ("\nNULL\n");
}
void beliBarang () {
	printf ("\nNULL\n");
}
void cekSaldo () {
	//operasi file
	printf ("\nSaldo anda saat ini = Rp. %d");
	printf ("\nNULL\n");
}
void addSaldo () {
	system ("cls");
	printf ("SALDO\n");
	printf ("=======================\n");
	//operasi file
	printf ("Saldo Anda saat ini : Rp. %d\n\n");
	printf ("Masukkan Jumlah yang ingin ditambahkan : Rp. "); scanf ("%d");
	//proses dan operasi file
	printf ("Saldo berhasil ditambahkan\n");
}
void showLaporan (int session_us) {
	printf ("\nNULL\n");
}

int main () {
	int pilih, session_us, session_log;
	char ulang;
	bool repeat = true;
	while (repeat == true) {
		pilih = firstMenu ();
		if (pilih == 1) {
			repeat = false;
			login ();
		}
		else if (pilih == 2) {
			registrasi ();
		}
		else {
			printf ("\nNot Found!\n");
		}
	}
	if (session_us != NULL && session_log == 2) {
		do {
			showList ();
			pilih = adminMenu ();
			if (pilih == 1) {
				jualBarang ();
				troli ();
			}
			else if (pilih == 2) {
				addBarang ();
			}
			else if (pilih == 3) {
				addStok ();
			}
			else if (pilih == 4) {
				editBarang ();
			}
			else if (pilih == 5) {
				hapusBarang ();
			}
			else if (pilih == 6) {
				showLaporan (1);
			}
			else {
				jualBarang ();
			}
			printf ("Tekan y untuk kembali ke MENU? "); scanf ("%s", &ulang);
		}
		while (ulang == 'y' || ulang == 'Y');
	}
	else if (session_us != NULL && session_log == 1) {
		do {
			showList ();
			pilih = adminMenu ();
			if (pilih == 1) {
				beliBarang ();
			}
			else if (pilih == 2) {
				troli ();
			}
			else if (pilih == 3) {
				cekSaldo ();
			}
			else if (pilih == 4) {
				addSaldo ();
			}
			else if (pilih == 5) {
				showLaporan (session_us);
			}
			else {
				jualBarang ();
			}
			printf ("\nTekan y untuk kembali ke MENU? "); scanf ("%s", &ulang);
		}
		while (ulang == 'y' || ulang == 'Y');
	}
	return 0;
}
