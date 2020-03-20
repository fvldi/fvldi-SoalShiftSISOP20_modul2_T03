# SoalShiftSISOP20_modul2_T03
Nama Anggota Kelompok T03 :
  1. Muhammad Rifaldi [05311840000022]
  2. Dimas Pramudya H. [05311840000037]

## Soal Shift Modul 2 dan Penyelesaiannya
### Soal 1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut: <br>
* #### Ketentuan Soal 1A
  A. Program menerima 4 argumen berupa : <br> 
    * #### Ketentuan Soal 1A (i, ii, iii dan iv)
      i. Detik: 0-59 atau * (any value) <br>
      ii. Menit: 0-59 atau * (any value) <br>
      iii. Jam: 0-23 atau * (any value) <br>
      iv. Path file .sh <br>
* #### Ketentuan Soal 1B
  B. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai 
* #### Ketentuan Soal 1C
  C. Program hanya menerima 1 config cron
* #### Ketentuan Soal 1D
  D. Program berjalan di background (daemon)
* #### Ketentuan Soal 1E
  E. Tidak boleh menggunakan fungsi system() <br>
  
Contoh ```./program \* 34 7 /home/somi/test.sh ``` <br>
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.
 #### Penyelesaian :
 ```bash
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main( int argc, char *argv[] ) {
  pid_t pid, sid;        // Variabel untuk menyimpan PID
  int detik, menit, jam;

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

if ((chdir("/root/sistem_operasi/")) < 0) {
    exit(EXIT_FAILURE);
  }

    //Pesan error jika argumen yang diberikan tidak sesuai
    if(argc != 5) {
        printf("Maaf, program hanya menerima 4 argumen yang terdiri atas: detik, menit, jam, dan path file bash script");
        return 0;
    }

  detik = 0;
  menit = 0;
  jam = 0;

    //Argument Detik
  if(argv[1][0] == '*'){
    detik = 0;
  }else if(isalpha(argv[1][0])){
    printf("Argument 1 harus berisi amgka");
  }else{
    detik = atoi(argv[1]);
  }
  //Argument Menit
  if(argv[2][0] == '*'){
    menit = 0;
  }else if(isalpha(argv[2][0])){
    printf("Argument 2 harus berisi angka");
  }else{
    menit = atoi(argv[2]);
  }
  //Argument Jam
  if(argv[3][0] == '*'){
    jam = 0;
  }else if(isalpha(argv[3][0])){
    printf("Argument 3 harus berisi angka");
  }else{
    jam = atoi(argv[3]);
  }

  while (1) {
    // Tulis program kalian di sini

    time_t t;
        struct tm* ptm;

        t = time(NULL);
        ptm = localtime(&t);

        if((jam == ptm->tm_hour || jam == 0) && (menit == ptm->tm_min || menit == 0) && (detik == ptm->tm_sec || detik == 0)) {
            if(fork()==0) {
                char *argx[] = {"bash",argv[4], NULL}; //Argumen 4: file bash script
                execv("/bin/bash", argx);
            }
        }
    sleep(1);
  }
}
```
### Penjelasan
```bash
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
```
Adalah beberapa jenis library yang digunakan untuk menjalankan program yang sudah kita buat sebelumnya

```c
int main( int argc, char *argv[] ) {

    pid_t pid, sid; // Variabel untuk menyimpan PID
    
    int detik, menit, jam;
    
    detik = 0;
    menit = 0;
    jam = 0;
    
    pid = fork();
```
Digunakan menyimpan PID dari child process, fungsi ```argc``` atau _Argument for count_ merupakan parameter bertipe int dan berfungsi untuk menunjukkan banyaknya parameter yang digunakan dalam eksekusi program. Fungsi ```argv``` atau _Argument for vector_ merupakan pointer ke string yang akan menyimpan parameter-parameter apa saja yang digunakan dalam eksekusi program. ```pid_t pid, sid;``` adalah variabel untuk menyimpan PID <br>

 ```c
/* Keluar saat fork gagal
     * (nilai variabel PID < 0) */

    if (pid <0) {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
     * (nilai variabel PID adalah PID dari child process) */

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
```
Digunakan untuk fork saat gagal & fork saat berhasil <br>

 ```c
umask (0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/media/sf_shared/sisop-modul-2/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
```
Dengan menggunakan template yang sudah disediakan sebelumnya didalam modul 2 <br>

 ```c
//Pesan error jika argumen yang diberikan tidak sesuai
    if(argc != 5) {
        printf("Maaf, program hanya menerima 4 argumen yang terdiri atas: detik, menit, jam, dan path file bash script");
    }
```
Jika argumen yang diberikan tidak sesuai, maka akan muncul pesan error <br>

 ```c
//Argumen 1: detik
    if(argv[1][0] == '*') {
        detik = 0;
    } else if(isalpha(argv[1][0])) {
        printf("Argument 1 harus berisi amgka");
    } else if(atoi(argv[1]) < 0 || atoi(argv[1]) > 59) {
        printf("Argument 1 harus berisi detik 0-59 atau * (any value)");
    } else {
        detik = atoi(argv[1]);
    }

    //Argumen 2: menit
    if(argv[2][0] == '*') {
        menit = 0;
    } else if(isalpha(argv[2])) {
        printf("Argument 2 harus berisi angka");
    } else if(atoi(argv[2]) < 0 || atoi(argv[2]) > 59) {
        printf("Argument 2 harus berisi menit 0-59 atau * (any value)");
    } else {
        menit = atoi(argv[2]);
    }

    //Argumen 3: jam
    if(argv[3][0] == '*') {
        jam = 0;
    } else if(isalpha(argv[3])) {
        printf("Argument 3 harus berisi angka");
    } else if(atoi(argv[3]) < 0 || atoi(argv[3]) > 23) {
        printf("Argument 3 harus berisi jam 0-23 atau * (any value)");
    } else {
        jam = atoi(argv[3]);
    }
```
Melakukan pengecheckan pada argumen, yang meliputi argumen detik, menit, jam <br>

```c
while (1) {
        // Program intinya
        time_t t;
        struct tm* ptm;

        t = time(NULL);
        ptm = localtime(&t);

        if((jam == ptm->tm_hour || jam == 0) && (menit == ptm->tm_min || menit == 0) && (detik == ptm->tm_sec || detik == 0)) {
            if(fork()==0) {
                char *argx[] = {"bash",argv[4], NULL}; //Argumen 4: file bash script
                execv("/bin/bash", argx);
            }
        }

        sleep(1);
    }
}
```
Daemon akan melakukan loop tiap detik untuk mengcheck apakah sudah sesuai dengan yang diinputkan <br> 



### Soal 2

# Belum

### Soal 3

# Belum


