#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char user[50], pass[50];
char session_us[50];
int session_log = 0;

void explode(char text[100], char data[5][100], char separator){
	int i, firstI = 0, secondI = 0;
	memset(data[0], 0, sizeof(data[0]));
	for(i=0; i<strlen(text); i++)
	{
		if(text[i] == separator)
		{
			firstI += 1; secondI = 0;
			memset(data[firstI], 0, sizeof(data[firstI]));
		}
		else if(text[i] != '\n' || text[i] != '\0')
		{
			data[firstI][secondI] = text[i];
			secondI++;
		}
	}
}

int firstMenu () {
	int pilih;
	printf("\n\n\n\n\n\n");
	printf("                 ___________________ TO MART _________________\n");
	printf("                 =============================================\n");
	printf("                                  1. Login          \n");
	printf("                                  2. Registrasi     \n");
	printf("                           ------------------------ \n");
	printf("                                 ---> "); scanf("%d", &pilih);
	return pilih;
}
int Menu () {
	int pilih;
	// admin menu
	if (session_log == 2) {
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
	// user menu
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
	char data[3][100];
	char buffer[255];
	bool isThere;
	FILE *fptr;
	
	system("cls");
	do
	{
		isThere = false;
		fflush(stdin);
		printf ("\n                 ____________________ TO MART ________________");
		printf ("\n                 =============================================");
		printf ("\n                                 Masukan Username : ");
		printf ("\n                             ------------------------");
		printf ("\n                                 ---> "); gets (username); fflush (stdin);
		printf ("\n                    ========================================");
		printf ("\n                                 Masukan Password : ");
		printf ("\n                            --------------------------");
		printf ("\n                                 ---> "); gets (password); fflush (stdin); 
		
		fptr = fopen("file/akun.dat", "r");
		while(!feof(fptr))
		{
			fgets(buffer, sizeof(buffer), fptr);
			explode(buffer, data, '|');
			if(strcmp(data[0], username) == 0 && strcmp(data[1], password) == 0)
			{
				isThere = true;
				strcpy(session_us, data[0]);
				session_log = atoi(data[2]);
			}
		}
		fclose(fptr);
		
		if(isThere == false)
		{
			system("cls");
			printf("\n                            Username dan Password Salah\n");
		}
	} while (isThere == false);
}

void registrasi () {
	system ("cls");
	printf ("\nREGISTRASI");
	printf ("\n=============================================\n");
	//operasi file
	char nama[50], rep_pass[50], join[50];
	bool isThere;
	char buffer[255];
	char data[3][100];
	FILE *fptr;
	
	do
	{
		isThere = false;
		fflush(stdin);
		printf(" Masukan Nama      : "); gets(nama); fflush(stdin);
		printf(" Masukan Username  : "); gets(user); fflush(stdin);
		printf(" Masukan Password  : "); gets(pass); fflush(stdin);
		printf(" Ulangi Password   : "); gets(rep_pass); fflush(stdin); 
		
		if(strcmp(pass, rep_pass) == 0)
		{
			fptr = fopen("file/akun.dat", "r");
			while(!feof(fptr))
			{
				fgets(buffer, sizeof(buffer), fptr);
				explode(buffer, data, '|');
				
				if(strcmp(data[0], user) == 0)
				{
					isThere = true;
					system("cls");
					printf("\n REGISTRASI \n");
					printf(" ============================================= \n");
					printf("\n Maaf, Username sudah terpakai! \n");
					printf(" Gunakan Username lainnya!!! \n\n");
				}
			}
			fclose(fptr);
			
			if(isThere == false)
			{
				char gabung[60] = "";
				fptr = fopen("file/akun.dat", "a");
				// menggabungkan string
				strcat(gabung, "\n"); strcat(gabung, user); strcat(gabung, "|"); strcat(gabung, pass); strcat(gabung, "|"); strcat(gabung, "1");
				fputs(gabung, fptr);
				fclose(fptr);
				
				fptr = fopen("file/saldo.dat", "a");
				memset(gabung, 0, sizeof(gabung));
				strcat(gabung, "\n"); strcat(gabung, user); strcat(gabung, "|"); strcat(gabung, nama); strcat(gabung, "|"); strcat(gabung, "0");
				fputs(gabung, fptr);
				fclose(fptr);
			}
		}
		else
		{
			system("cls");
			printf("\n REGISTRASI \n");
			printf(" ============================================= \n");
			printf(" Password tidak singkron!! \n\n");
			isThere = 1;
			continue;
		}
	} while (isThere == 1);
	system("cls");
	printf("\n\n                               Registrasi Berhasil");
}
void showList () {
	printf("List Barang [ TOMART ]\n\n");
	printf("=================================================================\n");
	printf("||=============================================================||\n");
	printf("||        Nama Barang       ||  Kode Barang  ||  Harga Barang  ||\n");
	printf("=================================================================\n");
}
void jualBarang () {
	printf ("\nNULL\n");
}
void troli () {
	printf ("\nNULL\n");
}
void addBarang(char *code, char *nm_barang, int *stok, int *harga) {
	char gabung[60] = "", str_stok[10], str_harga[10];
	FILE *fptr = fopen("file/data.dat", "a");
	itoa(*stok, str_stok, 10);
	itoa(*harga, str_harga, 10);
	strcat(gabung, "\n"); strcat(gabung, code); strcat(gabung, "|"); strcat(gabung, nm_barang); strcat(gabung, "|"); strcat(gabung, str_stok); strcat(gabung, "|"); strcat(gabung, str_harga);
	fputs(gabung, fptr);
	fclose(fptr);
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
	int pilih;
	char ulang;
	bool repeat = true;
	while (repeat == true) {
		pilih = firstMenu ();
		if (pilih == 1) {
			repeat = false;
			login();
		}
		else if (pilih == 2) {
			registrasi();
		}
		else {
			printf("\nNot Found!\n");
		}
	}
	
	if (strcmp(session_us, "") != 0 && session_log == 2) {
		do {
			showList ();
			pilih = Menu();
			if (pilih == 1) {
				jualBarang ();
				troli ();
			}
			else if (pilih == 2) {  // Tambah Barang
				printf("Tambah Data \n\n");
				char code[9], nm_barang[75];
				int stok, harga;
				char buffer[255], data[4][100];
				bool isThere = false;
				FILE *fptr;
				
				do
				{
					isThere = false;
					printf("Kode Barang   : "); scanf("%s", code); fflush(stdin);
					printf("Nama Barang   : "); gets(nm_barang); fflush(stdin);
					printf("Jumlah Barang : "); scanf("%d", &stok);
					printf("Harga         : Rp."); scanf("%d", &harga);
					
					fptr = fopen("file/data.dat", "r");
					while(!feof(fptr))
					{
						fgets(buffer, sizeof(buffer), fptr);
						explode(buffer, data, '|');
						
						if(strcmp(data[0], code) == 0)
						{
							isThere = true;
							system("cls");
							// showList();
							printf("Tambah Data Barang \n\n");
							printf("Kode Barang Sudah Terpakai!! \n");
							printf("Gunakan Kode lainnya!!! \n\n");
						}
					}
					fclose(fptr);
				} while (isThere == true);
				
				addBarang(&code[0], &nm_barang[0], &stok, &harga);
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
	else if (strcmp(session_us, "") != 0 && session_log == 1) {
		do {
			showList ();
			pilih = Menu();
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
//				showLaporan(session_us);
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
