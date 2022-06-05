#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

char user[50], pass[50];
char session_us[50];
int session_log = 0;

struct Barang {
	char kode_brg[30], nama_brg[50];
	int stok_brg, harga_brg;
};
struct Barang Brg[255];

void explode(char text[100], char data[6][100], char separator){
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
			explode(buffer, data, '#');
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

void registrasi(){
	system ("cls");
	printf ("\nREGISTRASI");
	printf ("\n=============================================\n");
	
	//operasi file
	char nama[50], rep_pass[50], join[50];
	bool isThere;
	char buffer[255];
	char data[3][100];
	
	//FILE POINTER
	FILE *fptr;
	
	do{
		isThere = false; fflush(stdin);
		printf(" Masukan Nama      : "); gets(nama); fflush(stdin);
		printf(" Masukan Username  : "); gets(user); fflush(stdin);
		printf(" Masukan Password  : "); gets(pass); fflush(stdin);
		printf(" Ulangi Password   : "); gets(rep_pass); fflush(stdin); 
		
		if(strcmp(pass, rep_pass) == 0){
			fptr = fopen("file/akun.dat", "r");
			
			while(!feof(fptr)){
				fgets(buffer, sizeof(buffer), fptr);
				explode(buffer, data, '#');
				
				if(strcmp(data[0], user) == 0){
					isThere = true; system("cls");
					printf("\n REGISTRASI \n");
					printf(" ============================================= \n");
					printf("\n Maaf, Username sudah terpakai! \n");
					printf(" Gunakan Username lainnya!!! \n");
					printf(" ============================================= \n\n");
				}
			} fclose(fptr);
			
			if(isThere == false){
				char gabung[60] = "";
				fptr = fopen("file/akun.dat", "a");
				
				// menggabungkan string
				strcat(gabung, "\n"); strcat(gabung, user); strcat(gabung, "#"); strcat(gabung, pass); 
				strcat(gabung, "#"); strcat(gabung, "1");
				fputs(gabung, fptr);fclose(fptr);
				
				fptr = fopen("file/saldo.dat", "a");
				
				memset(gabung, 0, sizeof(gabung));
				strcat(gabung, "\n"); strcat(gabung, user); strcat(gabung, "#"); 
				strcat(gabung, nama); strcat(gabung, "#"); strcat(gabung, "0");
				
				fputs(gabung, fptr); fclose(fptr);
			}
		}
		else{
			system("cls");
			printf("\n REGISTRASI \n");
			printf(" ============================================= \n");
			printf(" Password tidak singkron!! \n\n");
			printf(" Masukkan Ulang!!! \n\n");
			printf(" ============================================= \n"); isThere = 1;
		}
	}while (isThere == 1);
	
	system("cls");
	printf("\n\n                               Registrasi Berhasil");
}

void showList () {
	printf("=======================================================\n");
	printf("                        TO MART\n");
	printf("=======================================================\n");
	printf("Kode Barang \tNama Barang \tStok \tHarga Barang \t\n");
	printf("=======================================================\n");
	
	char data[4][100];
	
	FILE *fptr = fopen("file/data.dat", "r");
			
	while(!feof(fptr)){
		char buffer[255] = "";
		fgets(buffer, sizeof(buffer), fptr);
		explode(buffer, data, '#');
		
		if(strcmp(buffer, "\n") != 0) printf("%s \t\t%s\t%s\tRp. %s \n", data[0], data[1], data[2], data[3]);
	} fclose(fptr);
}

void jualBarang() {
	system("cls");
	showList();
	printf("\n===============================================\n");
	printf("Penjualan Barang \n\n");
	
	char kode[30], nama_brg[60], nama_pembeli[60];
	int stok, harga, jml_beli;
	
	bool isThere = false, isStok = true;
	char buffer[255];
	char data[4][100];
	FILE *fptr;
	
	printf("Masukan Kode Barang\n=> "); scanf("%s", kode);
	fflush(stdin);
	
	fptr = fopen("file/data.dat", "r");
	int i = 0, baris = -1;
	while(!feof(fptr))
	{
		fgets(buffer, sizeof(buffer), fptr);
		explode(buffer, data, '#');
		if(strcmp(data[0], kode) == 0) {
			isThere = true;
			strcpy(nama_brg, data[1]);
			stok = atoi(data[2]);
			harga = atoi(data[3]);
			
			printf("Barang tersedia       : %d \n\n", stok);
			printf("Nama Pembeli          : "); gets(nama_pembeli); fflush(stdin);
			printf("Jumlah Barang dibeli  : "); scanf("%d", &jml_beli);
			
			if(stok < jml_beli) {
				isStok = false;
				printf("Maaf, stok kami tidak mencukupi \n");
				continue;
			} else baris = i;
		}
		
		strcpy(Brg[i].kode_brg, data[0]);
		strcpy(Brg[i].nama_brg, data[1]);
		Brg[i].stok_brg = atoi(data[2]);
		Brg[i].harga_brg = atoi(data[3]);
		i++;
	}
	fclose(fptr);
	
	if(isThere == true)
	{
		if(isStok == true)
		{
			int isEnough = true;
			int bayar, t_harga = harga * jml_beli;
			stok = stok - jml_beli;
			do
			{
				printf("==================================== \n");
				printf("Total Harga        = Rp. %d \n", t_harga);
				printf("Masukan Pembayaran = Rp. "); scanf("%d", &bayar);
				
				if(bayar >= t_harga)
				{
					int kembalian = bayar - t_harga;
					printf("==================================== \n");
					printf("Kembalian   = Rp. %d \n", kembalian);
					isEnough = true;
					
					Brg[baris].stok_brg = stok;
					
					fptr = fopen("file/data.dat", "w"); fclose(fptr);
					int j;
					fptr = fopen("file/data.dat", "a");
					for(j=0; j<i; j++) {
						char gabung[255] = "", str_stok[5], str_harga[30];
						itoa(Brg[j].stok_brg, str_stok, 10);
						itoa(Brg[j].harga_brg, str_harga, 10);
						if(j != 0) strcat(gabung, "\n");
						strcat(gabung, Brg[j].kode_brg); strcat(gabung, "#"); strcat(gabung, Brg[j].nama_brg); strcat(gabung, "#"); strcat(gabung, str_stok); strcat(gabung, "#"); strcat(gabung, str_harga);
						fputs(gabung, fptr);
					}
					fclose(fptr);
					
					fptr = fopen("file/laporan.dat", "a");
					
					// get Time
					time_t now;
					time(&now);
					struct tm *local = localtime(&now);
					
				    char gabung_t[15] = "", tgl[2], bln[2], thn[4], jam[2], men[2], det[2];
				    itoa(local->tm_mday, tgl, 10);
				    itoa(local->tm_mon + 1, bln, 10);
				    itoa(local->tm_year + 1900, thn, 10);
				    itoa(local->tm_hour, jam, 10);
				    itoa(local->tm_min, men, 10);
				    itoa(local->tm_sec, det, 10);
				    
					strcat(gabung_t, tgl); strcat(gabung_t, "-"); strcat(gabung_t, bln); strcat(gabung_t, "-"); strcat(gabung_t, thn); strcat(gabung_t, " "); 
					strcat(gabung_t, jam); strcat(gabung_t, ":"); strcat(gabung_t, men); strcat(gabung_t, ":"); strcat(gabung_t, det); 
					
					char gabung[255] = "", str_jml_beli[5], str_t_harga[10];
					itoa(jml_beli, str_jml_beli, 10);
					itoa(t_harga, str_t_harga, 10);
					strcat(gabung, "\n"); strcat(gabung, "1"); strcat(gabung, "#"); strcat(gabung, nama_pembeli); strcat(gabung, "#"); strcat(gabung, nama_brg); strcat(gabung, "#"); 
					strcat(gabung, str_jml_beli); strcat(gabung, "#"); strcat(gabung, str_t_harga); strcat(gabung, "#"); strcat(gabung, gabung_t); 
					
					fputs(gabung, fptr);
					fclose(fptr);
				}
				else {
					printf("\nMaaf, uang anda kurang! \n");
					isEnough = false;
				}
			} while(isEnough == false);
		} // isStok
	} // isThere
	else printf("Kode Penerbangan Tidak Ditemukan!! \n");
}
void troli () {
	printf ("\nNULL\n");
}
void addBarang(char *code, char *nm_barang, int *stok, int *harga) {
	char gabung[60] = "", str_stok[10], str_harga[10];
	FILE *fptr = fopen("file/data.dat", "a");
	itoa(*stok, str_stok, 10);
	itoa(*harga, str_harga, 10);
	strcat(gabung, "\n"); strcat(gabung, code); strcat(gabung, "#"); strcat(gabung, nm_barang); strcat(gabung, "#"); strcat(gabung, str_stok); strcat(gabung, "#"); strcat(gabung, str_harga);
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
	int cek_saldo;
	char cekUser[100], cekNama[100];
	//operasi file
	printf ("\nSaldo anda saat ini = Rp. %d");
	FILE *saldo = fopen ("file/saldo.dat", "r+");
	while (!feof (saldo)) {
		fscanf (saldo, "%s#%[^#]s%d, &cekUser, &cekNama, &cek_saldo);
		if (strcmp (cekUser, user) == 0) {
			printf ("\nSaldo anda saat ini = Rp. %d", cek_saldo);
			break;
		}
	}
	fclose (saldo);
	printf ("\nNULL\n");
}
void addSaldo () {
	system ("cls");
	printf ("SALDO\n");
	printf ("=======================\n");
	//operasi file
	printf ("Saldo Anda saat ini : Rp. %d\n\n");
	int cek_saldo;
	char cekUser[100], cekNama[100];
	//operasi file
	FILE *saldo = fopen ("file/saldo.dat", "r+");
	while (!feof (saldo)) {
		fscanf (saldo, "%s#%[^#]s%d, &cekUser, &cekNama, &cek_saldo);
		if (strcmp (cekUser, user) == 0) {
			printf ("\nSaldo anda saat ini = Rp. %d", cek_saldo);
			break;
		}
	}
	fclose (saldo);
	//opfile untuk tambah saldo lain lagi
	printf ("Masukkan Jumlah yang ingin ditambahkan : Rp. "); scanf ("%d");
	//proses dan operasi file
	printf ("Saldo berhasil ditambahkan\n");
}
void showLaporan (char user[60]) {
	system("cls");
	printf(" ========================================================================== \n");
	printf(" ||                           DAFTAR LAPORAN                             || \n");
	printf(" ========================================================================== \n\n");
	
	int i = 1, untung = 0, total_jual = 0;
	char buffer[255] = "";
	char data[6][100];
	
	printf(" Waktu \n");
	printf(" Nama Pembeli\t\tNama Barang \t\tJml. Beli \tT. Harga \t \n");
	printf(" ==========================================================================\n");
	int *ptr_untung = &untung, *ptr_jual = &total_jual;

	FILE *fptr = fopen("file/laporan.dat", "r");
	if(strcmp(user, "1") == 0) {
		while(!feof(fptr)){
			fgets(buffer, sizeof(buffer), fptr);
			explode(buffer, data, '#');
			
			if(strcmp(data[0], " ") != 0) {
				printf(" %s \n", data[5]);
				printf(" %d. %s \t%s \t\t %s \t\tRp. %s \n\n", i, data[1], data[2], data[3], data[4]);
				i++;
				*ptr_jual += atoi(data[3]);
				*ptr_untung += atoi(data[4]);
			}
		}
	}
	else {
		while(!feof(fptr)){
			fgets(buffer, sizeof(buffer), fptr);
			explode(buffer, data, '#');
			if(strcmp(data[0], user) == 0) {
				printf(" %s \n", data[5]);
				printf(" %d. %s \t%s \t\t %s \t\tRp. %s \n\n", i, data[1], data[2], data[3], data[4]);
				i++;
				*ptr_jual += atoi(data[3]);
				*ptr_untung += atoi(data[4]);
			}
		}
	}
	printf(" ========================================================================== \n");
	printf("\t\t\t\t\t\t %d \t\tRp. %d  \n", *ptr_jual, *ptr_untung);
	fclose(fptr);
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
			system("cls");
			showList();
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
						explode(buffer, data, '#');
						
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
				showLaporan("1");
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
			system("cls");
			showList();
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
				showLaporan(session_us);
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
