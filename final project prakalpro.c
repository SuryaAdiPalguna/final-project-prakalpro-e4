#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

char user[50], pass[50];
char session_us[50], session_name[60];
int session_log = 0;

struct Saldo {
	char user[50], nama[50];
	int t_saldo;
};
struct Saldo Kredit[255];
struct Troli {
	char user[50], kode_brg[30], nama_brg[50];
	int jml_brg, t_harga;
};
struct Troli Trol[255];
struct Barang {
	char kode_brg[30], nama_brg[50];
	int stok_brg, harga_brg;
};
struct Barang Brg[255];

void explode(char text[100], char data[6][100], char separator){
	int i, firstI = 0, secondI = 0;
	memset(data[0], 0, sizeof(data[0]));
	for(i=0; i<strlen(text); i++) {
		if(text[i] == separator) {
			firstI += 1; secondI = 0;
			memset(data[firstI], 0, sizeof(data[firstI]));
		}
		else if(text[i] != '\n' || text[i] != '\0') {
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
	return pilih;
}

void getNamaUser() {
	char buffer[255];
	char data[3][100];
	
	FILE *fptr = fopen("file/saldo.dat", "r");
	while(!feof(fptr)) {
		fgets(buffer, sizeof(buffer), fptr);
		explode(buffer, data, '#');
		if(strcmp(session_us, data[0]) == 0) {
			strcpy(session_name, data[1]);
		}
	}
	fclose(fptr);
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
				strcpy(session_name, data[0]);
				session_log = atoi(data[2]);
			}
		}
		fclose(fptr);
		
		getNamaUser();
		
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
				fputs(gabung, fptr); fclose(fptr);
				
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
	else printf("Kode Barang Tidak Ditemukan!! \n");
}

int cekSaldo() {
	bool isThere = false;
	char buffer[255] = "";
	char data[3][100];
	int saldo = 0;
	
	FILE *fptr = fopen("file/saldo.dat", "r");
	while(!feof(fptr)){
		fgets(buffer, sizeof(buffer), fptr);
		explode(buffer, data, '#');
		if(strcmp(data[0], session_us) == 0) {
			isThere = true;
			saldo = atoi(data[2]);
		}
	}
	fclose(fptr);
	return saldo;
}

void troli() {
	system("cls");
	int i = 0, total_harga = 0;
	char buffer[255] = "";
	char data[5][100];
	
	printf(" Kode Barang\tNama Barang \tJml. Beli \tT. Harga \t \n");
	printf(" ==========================================================================\n");
	int *ptr_harga = &total_harga;

	FILE *fptr = fopen("file/troli.dat", "r");
	while(!feof(fptr)){
		fgets(buffer, sizeof(buffer), fptr);
		explode(buffer, data, '#');
		if(strcmp(data[0], session_us) == 0) {
			strcpy(Trol[i].kode_brg, data[1]);
			strcpy(Trol[i].nama_brg, data[2]);
			Trol[i].jml_brg = atoi(data[3]);
			Trol[i].t_harga = atoi(data[4]);
			
			i++;
			printf(" %d. %s \t%s \t%s \t\tRp. %s \n", i, data[1], data[2], data[3], data[4]);
			*ptr_harga += atoi(data[4]);
		}
	}
	printf(" ========================================================================== \n");
	printf("\t\t\t\t\t\tRp. %d \n", *ptr_harga);
	fclose(fptr);
	
	int cek;
	printf("(1:bayar | 0:kembali) \n");
	printf("Ingin Membayar? => "); scanf("%d", &cek);
	
	if(cek == 1) {
		if(cekSaldo() > *ptr_harga) {
			fptr = fopen("file/data.dat", "r");
			int j = 0;
			while(!feof(fptr))
			{
				fgets(buffer, sizeof(buffer), fptr);
				explode(buffer, data, '#');
				
				strcpy(Brg[j].kode_brg, data[0]);
				strcpy(Brg[j].nama_brg, data[1]);
				Brg[j].stok_brg = atoi(data[2]);
				Brg[j].harga_brg = atoi(data[3]);
				j++;
			}
			fclose(fptr);
			
			int stok, total_bayar = 0;
			int troli = i;
			int in_data = j;
			for(i=0; i<troli; i++) {
				for(j=0; j<in_data; j++) {
					if(strcmp(Trol[i].kode_brg, Brg[j].kode_brg) == 0) {
						if(Trol[i].jml_brg <= Brg[j].stok_brg) {
							
							total_bayar = total_bayar + (Brg[j].harga_brg * Trol[i].jml_brg);
							
							fptr = fopen("file/data.dat", "w"); fclose(fptr);
							int k;
							fptr = fopen("file/data.dat", "a");
							for(k=0; k<in_data; k++) {
								char gabung[255] = "", str_stok[5], str_harga[30];
								if(j == k) Brg[j].stok_brg -= Trol[i].jml_brg;
								
								itoa(Brg[k].stok_brg, str_stok, 10);
								itoa(Brg[k].harga_brg, str_harga, 10);
								if(k != 0) strcat(gabung, "\n");
								strcat(gabung, Brg[k].kode_brg); strcat(gabung, "#"); strcat(gabung, Brg[k].nama_brg); strcat(gabung, "#"); strcat(gabung, str_stok); strcat(gabung, "#"); strcat(gabung, str_harga);
								fputs(gabung, fptr);
							}
							fclose(fptr);
							
							fptr = fopen("file/laporan.dat", "a");
							// get Time
							time_t now;
							time(&now);
							struct tm *local = localtime(&now);
							
						    char gabung_t[15] = "", tgl[2], bln[2], thn[4], jam[2], men[2], det[2];
						    itoa(local->tm_mday, tgl, 10); itoa(local->tm_mon + 1, bln, 10); itoa(local->tm_year + 1900, thn, 10); itoa(local->tm_hour, jam, 10); itoa(local->tm_min, men, 10); itoa(local->tm_sec, det, 10);
						    
							strcat(gabung_t, tgl); strcat(gabung_t, "-"); strcat(gabung_t, bln); strcat(gabung_t, "-"); strcat(gabung_t, thn); strcat(gabung_t, " "); 
							strcat(gabung_t, jam); strcat(gabung_t, ":"); strcat(gabung_t, men); strcat(gabung_t, ":"); strcat(gabung_t, det); 
							
							char gabung[255] = "", str_jml_beli[5], str_t_harga[10];
							itoa(Trol[i].jml_brg, str_jml_beli, 10);
							itoa(Trol[i].t_harga, str_t_harga, 10);
							strcat(gabung, "\n"); strcat(gabung, session_us); strcat(gabung, "#"); strcat(gabung, session_name); strcat(gabung, "#"); strcat(gabung, Brg[j].nama_brg); strcat(gabung, "#"); 
							strcat(gabung, str_jml_beli); strcat(gabung, "#"); strcat(gabung, str_t_harga); strcat(gabung, "#"); strcat(gabung, gabung_t); 
							
							fputs(gabung, fptr);
							fclose(fptr);
							
						} else {
							printf("Maaf '%s' Tidak memiliki Stok yang cukup (%d) \n", Brg[j].nama_brg, Trol[i].t_harga);
						}
						break;
					}
				}
			}
			
			printf("\nTotal Harga setelah di cek stok = %d\n", total_bayar);
			
			char data[5][100];
			fptr = fopen("file/troli.dat", "r");
			int i = 0, k;
			while(!feof(fptr)) {
				fgets(buffer, sizeof(buffer), fptr);
				explode(buffer, data, '#');
				
				if(strcmp(session_us, data[0]) != 0) {
					strcpy(Trol[i].user, data[0]);
					strcpy(Trol[i].kode_brg, data[1]);
					strcpy(Trol[i].nama_brg, data[2]);
					Trol[i].jml_brg = atoi(data[3]);
					Trol[i].t_harga = atoi(data[4]);
					i++;
				}
			}
			fclose(fptr);
			
			fptr = fopen("file/troli.dat", "w"); fclose(fptr);
			fptr = fopen("file/troli.dat", "a");
			for(k = 0; k<i; k++) {
				char gabung[255] = "", str_jml[5], str_harga[30];
				itoa(Trol[k].jml_brg, str_jml, 10);
				itoa(Trol[k].t_harga, str_harga, 10);
				if(k != 0) strcat(gabung, "\n");
				strcat(gabung, Trol[k].user); strcat(gabung, "#"); strcat(gabung, Trol[k].kode_brg); strcat(gabung, "#"); strcat(gabung, Trol[k].nama_brg); strcat(gabung, "#"); strcat(gabung, str_jml); strcat(gabung, "#"); strcat(gabung, str_harga);
				fputs(gabung, fptr);
			}
			fclose(fptr);
			
			fptr = fopen("file/saldo.dat", "r");
			i = 0;
			int baris = -1;
			while(!feof(fptr)) {
				fgets(buffer, sizeof(buffer), fptr);
				explode(buffer, data, '#');
				if(strcmp(session_us, data[0]) == 0) baris = i;
				
				strcpy(Kredit[i].user, data[0]);
				strcpy(Kredit[i].nama, data[1]);
				Kredit[i].t_saldo = atoi(data[2]);
				i++;
			}
			fclose(fptr);
			
			if(baris != -1) {
				fptr = fopen("file/saldo.dat", "w"); fclose(fptr);
				fptr = fopen("file/saldo.dat", "a");
				for(k = 0; k<i; k++) {
					char gabung[255] = "", str_saldo[30];
					if(baris == k) Kredit[k].t_saldo -= total_bayar;
					
					itoa(Kredit[k].t_saldo, str_saldo, 10);
					if(k != 0) strcat(gabung, "\n");
					strcat(gabung, Kredit[k].user); strcat(gabung, "#"); strcat(gabung, Kredit[k].nama); strcat(gabung, "#"); strcat(gabung, str_saldo);
					fputs(gabung, fptr);
				}
				fclose(fptr);
			}
			
		}
		else {
			printf("\nMaaf, saldo tidak mencukupi!!\n");
		}
	} 
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

void addStok(){
	// READ STUFF FROM DATA'
	FILE *read = fopen("file/data.dat" , "r");
	char detect[100]; char str[255]; char data[4][100]; int i = 0;
	int tempStock = 0;
	
	printf("Masukkan Kode Barang >> : "); 
	fflush(stdin); gets(detect);
	
	printf("\nKode Barang \t Nama Barang \t Stock \t Harga \n");
	while(!feof(read)){
		fgets(str , sizeof(str) , read);
		explode(str , data , '#');
		
		strcpy(Brg[i].kode_brg , data[0]); strcpy(Brg[i].nama_brg , data[1]);
		Brg[i].stok_brg = atoi(data[2]); Brg[i].harga_brg = atoi(data[3]);
		i++;
	}fclose(read);
	
	int j = 0; int BRG_STOCK;
	for(j; j < i; j++){
		if(strcmp(Brg[j].kode_brg , detect) == 0){
			printf("%s \t\t %s \t %d \t %d" , Brg[j].kode_brg , Brg[j].nama_brg , Brg[j].stok_brg , Brg[j].harga_brg);
			tempStock = Brg[j].stok_brg;
			
			printf("\n\nMasukkan Jumlah Stock >> : "); scanf("%d" , &BRG_STOCK);
			BRG_STOCK = BRG_STOCK + tempStock;
			break;
		}
		else{ printf("Data Tidak Ditemukan.\n"); }
	}
	
	// WRITE STUFF TO DATA
	FILE *write = fopen("file/data.dat" , "w");
	char str_stok[100]; char str_harga[1000];
	for(j = 0; j < i; j++){
		
		if(strcmp(Brg[j].kode_brg , detect) == 0){
			char gabung[255] = "";
			itoa(BRG_STOCK, str_stok , 10);
			itoa(Brg[j].harga_brg, str_harga, 10);
			
			if(j != 0) strcat(gabung, "\n");
			strcat(gabung, Brg[j].kode_brg); strcat(gabung, "#"); strcat(gabung, Brg[j].nama_brg); strcat(gabung, "#"); 
			strcat(gabung, str_stok); strcat(gabung, "#"); strcat(gabung, str_harga);
			
			fputs(gabung, write);
		}
		else{
			char gabung[255] = "";
			itoa(Brg[j].stok_brg, str_stok , 10);
			itoa(Brg[j].harga_brg, str_harga, 10);
			
			if(j != 0) strcat(gabung, "\n");
			strcat(gabung, Brg[j].kode_brg); strcat(gabung, "#"); strcat(gabung, Brg[j].nama_brg); strcat(gabung, "#"); 
			strcat(gabung, str_stok); strcat(gabung, "#"); strcat(gabung, str_harga);
			
			fputs(gabung, write);
		}
	}fclose(write);
}

void editProses(char *kode_brg, char *nama_brg, int *stok_brg, int *harga_brg, int baris) {
	char str_stok[20], str_harga[20];
	char buffer[255], data[4][100];

	FILE *fptr = fopen("file/data.dat", "r");
	int i = 0;
	while(fgets(buffer, sizeof(buffer), fptr) != NULL) {
		explode(buffer, data, '#');
		strcpy(Brg[i].kode_brg, data[0]);
		strcpy(Brg[i].nama_brg, data[1]);
		Brg[i].stok_brg = atoi(data[2]);
		Brg[i].harga_brg = atoi(data[3]);
		i++;
	}
	fclose(fptr);

	strcpy(Brg[baris].kode_brg, kode_brg);
	strcpy(Brg[baris].nama_brg, nama_brg);
	Brg[baris].stok_brg = *stok_brg;
	Brg[baris].harga_brg = *harga_brg;
	fptr = fopen("file/data.dat", "w"); fclose(fptr);
	int j;
	fptr = fopen("file/data.dat", "a");
	for(j=0; j<i; j++) {
		char gabung[255] = "";
		itoa(Brg[j].stok_brg, str_stok, 10);
		itoa(Brg[j].harga_brg, str_harga, 10);
		if(j != 0) strcat(gabung, "\n");
		strcat(gabung, Brg[j].kode_brg); strcat(gabung, "#"); strcat(gabung, Brg[j].nama_brg); strcat(gabung, "#"); strcat(gabung, str_stok); strcat(gabung, "#"); strcat(gabung, str_harga);
		fputs(gabung, fptr);
	}
	fclose(fptr);
}

void editBarang () {
	system("cls");
	showList();
	char kode_brg[30];
	char buffer[255], data[4][100];
	bool isThere = false;
	FILE *fptr = fopen("file/data.dat", "r");

	printf("\n============================================\n");
	printf("Edit Data \n");
	printf("Masukkan Kode data yang ingin Diedit : "); scanf("%s", &kode_brg);

	int i = 0;
	while(fgets(buffer, sizeof(buffer), fptr) != NULL) {
		explode(buffer, data, '#');
		i++;
		if(strcmp(data[0], kode_brg) == 0) {
			isThere = true;
			break;
		}
	}
	fclose(fptr);

	fflush(stdin);
	if(isThere == true) {
		char nama_brg[50];
		int stok_brg, harga_brg;

		printf("\nNama Barang : "); gets(nama_brg); fflush(stdin);
		printf("Jumlah        : "); scanf("%d", &stok_brg); fflush(stdin);
		printf("Harga         : "); scanf("%d", &harga_brg); fflush(stdin);

		editProses(&kode_brg[0], &nama_brg[0], &stok_brg, &harga_brg, (i-1));
	} else {
		printf("\nTidak terdapat barang dengan Kode tersebut!!!\n");
	}
}

void hapusBarang(){
	// READ STUFF FROM DATA
	FILE *read = fopen("file/data.dat" , "r");
	char detect[100]; char str[255]; char data[4][100]; int i = 0;
	int tempStock = 0;
	
	printf("Masukkan Kode Barang >> : "); 
	fflush(stdin); gets(detect);
	
	printf("\nKode Barang \t Nama Barang \t Stock \t Harga \n");
	while(!feof(read)){
		fgets(str , sizeof(str) , read);
		explode(str , data , '#');
		
		strcpy(Brg[i].kode_brg , data[0]); strcpy(Brg[i].nama_brg , data[1]);
		Brg[i].stok_brg = atoi(data[2]); Brg[i].harga_brg = atoi(data[3]);
		
		i++;
	}fclose(read);
	
	int j = 0; int z = 0;
	for(z; z < i; z++){
		if(strcmp(Brg[z].kode_brg , detect) == 0){
			printf("%s \t\t %s \t %d \t %d \n\n" , Brg[z].kode_brg , Brg[z].nama_brg , Brg[z].stok_brg , Brg[z].harga_brg);
			tempStock = Brg[z].stok_brg; 
			
			// WRITE STUFF TO DATA
			FILE *write = fopen("file/data.dat" , "w");
			char str_stok[100]; char str_harga[1000];
			for(j; j < i; j++){
				if(strcmp(Brg[j].kode_brg , detect) == 0) continue;
				
				else{
					char gabung[255] = "";
					itoa(Brg[j].stok_brg, str_stok , 10);
					itoa(Brg[j].harga_brg, str_harga, 10);
					
					if(j != 0) strcat(gabung, "\n");
					strcat(gabung, Brg[j].kode_brg); strcat(gabung, "#"); strcat(gabung, Brg[j].nama_brg); 
					strcat(gabung, "#"); strcat(gabung, str_stok); strcat(gabung, "#"); strcat(gabung, str_harga);
					
					fputs(gabung, write);
				}
			}fclose(write);
			break;
		}
	}
}

void beliBarang () {
	system("cls");
	showList();
	
	char kode[30], nama_brg[60];
	int stok, harga, jml_beli;
	
	bool isThere = false, isStok = true;
	char buffer[255];
	char data[4][100];
	FILE *fptr;
	
	printf("=====================================================\n");
	printf("Masukan Kode Barang\n=> "); scanf("%s", kode);
	fflush(stdin);
	
	fptr = fopen("file/data.dat", "r");
	int i = 0, baris = -1;
	while(!feof(fptr)) {
		fgets(buffer, sizeof(buffer), fptr);
		explode(buffer, data, '#');
		if(strcmp(data[0], kode) == 0) {
			isThere = true;
			strcpy(nama_brg, data[1]);
			stok = atoi(data[2]);
			harga = atoi(data[3]);
			
			printf("Barang tersedia : %d \n\n", stok);
			printf("Jumlah Barang   : "); scanf("%d", &jml_beli);
			
			if(stok < jml_beli) {
				isStok = false;
				printf("Maaf, stok kami tidak mencukupi \n");
				continue;
			} else baris = i;
			break;
		}
		i++;
	}
	fclose(fptr);
	
	if(isThere == true)
	{
		if(isStok == true)
		{
			int isEnough = true;
			int t_harga = harga * jml_beli;
			stok = stok - jml_beli;
			
			fptr = fopen("file/troli.dat", "a");
					
			char gabung[255] = "", str_jml_beli[5], str_t_harga[10];
			itoa(jml_beli, str_jml_beli, 10);
			itoa(t_harga, str_t_harga, 10);
			strcat(gabung, "\n"); strcat(gabung, session_us); strcat(gabung, "#"); strcat(gabung, kode); strcat(gabung, "#"); strcat(gabung, nama_brg); strcat(gabung, "#"); 
			strcat(gabung, str_jml_beli); strcat(gabung, "#"); strcat(gabung, str_t_harga); 
			
			fputs(gabung, fptr);
			fclose(fptr);
		} // isStok
	} // isThere
	else printf("Kode Barang Tidak Ditemukan!! \n");
	
}

void addSaldo () {
	system ("cls");
	printf ("SALDO\n");
	printf ("=======================\n");
	
	int tambah;
	
	printf ("Saldo Anda saat ini : Rp. %d\n\n", cekSaldo ());
	printf ("Masukkan Jumlah yang ingin ditambahkan : Rp. "); scanf ("%d", &tambah);
	
	//proses dan operasi file
	char buffer[255] = "";
	char data[3][100];
	
	FILE *fptr = fopen("file/saldo.dat", "r");
	int i = 0;
	while(!feof(fptr)){
		fgets(buffer, sizeof(buffer), fptr);
		explode(buffer, data, '#');
		
		Kredit[i].t_saldo = atoi(data[2]);
		if(strcmp(data[0], session_us) == 0) 
			Kredit[i].t_saldo += tambah;
		strcpy(Kredit[i].user, data[0]);
		strcpy(Kredit[i].nama, data[1]);
		i++;
	}
	fclose(fptr);
	
	int j;
	fptr = fopen("file/saldo.dat", "w"); fclose(fptr);
	fptr = fopen("file/saldo.dat", "a");
	for(j=0; j<i; j++) {
		char gabung[255] = "", str_saldo[30];
		itoa(Kredit[j].t_saldo, str_saldo, 10);
		if(j != 0) {strcat(gabung, "\n");}
		strcat(gabung, Kredit[j].user); strcat(gabung, "#"); strcat(gabung, Kredit[j].nama); strcat(gabung, "#"); strcat(gabung, str_saldo);
		fputs(gabung, fptr);
	}
	fclose(fptr);
	
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
				troli();
			}
			else if (pilih == 3) {
				printf("\nSaldo anda saat ini = Rp. %d\n", cekSaldo());
			}
			else if (pilih == 4) {
				addSaldo();
			}
			else if (pilih == 5) {
				showLaporan(session_us);
			}
			else {
				jualBarang();
			}
			printf ("\nTekan y untuk kembali ke MENU? "); scanf ("%s", &ulang);
		}
		while (ulang == 'y' || ulang == 'Y');
	}
	return 0;
}
