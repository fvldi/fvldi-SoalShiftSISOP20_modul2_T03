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
 ```c
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
  pid_t pid, sid;        // Variabel untuk menyimpan PID
  int detik, menit, jam;
```

Fungsi ````argc```` atau _Argument for count_ pada ````int argc, char *argv[]```` merupakan parameter bertipe int dan berfungsi untuk menunjukkan banyaknya parameter yang digunakan dalam eksekusi program; Fungsi ```argv``` atau _Argument for vector_ merupakan pointer ke string yang akan menyimpan parameter-parameter apa saja yang digunakan dalam eksekusi program. Fungsi ```pid_t pid, sid``` Digunakan untuk menyimpan PID dan SID dari child process. Fungsi ````int detik, menit, jam```` untuk mendeklarasikan variabel dengan tipe data integer diantaranya detik, menit, dan jam.

 ```c
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
```

Fungsi daiatas digunakan untuk membuat sebuah parent process dan memunculkan child process dengan melakukan ````fork()````. Kemudian mematikan parent process agar sistem operasi mengira bahwa proses telah selesai.

```c
umask (0);
```

Setiap file dan directory memiliki permission atau izin yang mengatur siapa saja yang boleh melakukan read, write, dan execute pada file atau directory tersebut.

Dengan menggunakan umask kami mengatur permission dari suatu file pada saat file itu dibuat. Di sini kami mengatur nilai ````umask(0)```` agar kami mendapatkan akses full terhadap file yang dibuat oleh daemon.

````c
sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
````

Sebuah Child Process harus memiliki SID agar dapat berjalan. Tanpa adanya SID, Child Process yang Parent-nya sudah di-kill akan menjadi Orphan Process.

Untuk mendapatkan SID kami menggunakan perintah ````setsid()````. Perintah tersebut memiliki return type yang sama dengan perintah ````fork()````.

````c
if ((chdir("/root/sistem_operasi/")) < 0) {
    exit(EXIT_FAILURE);
  }
````

Pada fungsi diatas, kami mengubah working directory menjadi ````/root/sistem_operasi/````. Untuk mengubah Working Directory itu sendiri, kami menggunakan perintah ````chdir()````.

 ```c
//Pesan error jika argumen yang diberikan tidak sesuai
    if(argc != 5) {
        printf("Maaf, program hanya menerima 4 argumen yang terdiri atas: detik, menit, jam, dan path file bash script");
        return 0;
    }
```
Jika argumen yang diberikan tidak berjumlah 5, maka akan muncul pesan error yaitu _"Maaf, program hanya menerima 4 argumen yang terdiri atas: detik, menit, jam, dan path file bash script"_<br>

 ```c
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
```
Melakukan pengecheckan pada argumen, yang meliputi argumen detik, menit, dan jam. <br>

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

Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat sebuah program. <br />
- Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss]. <br />
- Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss]. <br />
- Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip). <br />
- Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri. <br />
- Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu di delete).<br />

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi. <br />
Buatlah program dalam mimpi Kiwa jadi nyata! <br />

Catatan: <br />
- Tidak boleh memakai system().
- Program utama harus ter-detach dari terminal <br />

Hint: <br />
- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran
tertentu
- Epoch Unix bisa didapatkan dari time()

### Penyelesaian :

### Penjelasan :

### Soal 3

Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan (multiprocessing). <br />
- Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
- Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.
- Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.
- Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”). <br />

Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat
program tersebut. <br />

Catatan : <br />
- Tidak boleh memakai system().
- Tidak boleh memakai function C mkdir() ataupun rename().
- Gunakan exec dan fork
- Direktori “.” dan “..” tidak termasuk

### Penyelesaian :
```bash
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main (){
    pid_t cid;
    int stat;
    cid=fork();

    if (cid < 0){
        exit(EXIT_FAILURE); }

    if(cid == 0){
        char *var[] = {"mkdir","-p","/home/dimas/modul2/indomie",(char *)NULL};

        execv("/bin/mkdir",var);}

    else{
        while(wait(&stat)>0);

    cid=fork();

    if (cid < 0){
        exit(EXIT_FAILURE); }

    if(cid==0){
        sleep(5);
        char *var[] = {"mkdir","-p","/home/dimas/modul2/sedaap",(char *)NULL};
        execv("/bin/mkdir",var);}

    else{
        while(wait(&stat)>0);

    cid=fork();

    if (cid < 0){
        exit(EXIT_FAILURE); }

    if(cid==0){
        char *var[] = {"unzip","/home/dimas/modul2/jpg.zip","-d","/home/dimas/modul2",(char *)NULL};

        execv("/usr/bin/unzip",var);}

    else{
        while(wait(&stat)>0);
    cid=fork();
    if (cid < 0){
        exit(EXIT_FAILURE); }

    if(cid==0){
        char *var[] = {"find","/home/dimas/modul2/jpg/","-type","f","-exec","/bin/mv","-t","/home/dimas/modul2/sedaap","{}",";",(char *)NULL};

        execv("/usr/bin/find",var);}

    else{
        while(wait(&stat)>0);

    cid=fork();

    if (cid < 0){
        exit(EXIT_FAILURE); }

    if(cid == 0){
        char *var[] = {"find","/home/dimas/modul2/jpg/","-mindepth","1","-type","d","-exec","/bin/mv","-t","/home/dimas/modul2/indomie","{}",";",(char *)NULL};
        execv("/usr/bin/find",var);}

    else{
        while(wait(&stat)>0);

    cid=fork();

    if (cid < 0){
        exit(EXIT_FAILURE); }

    if(cid==0){
        char *var[] = {"find","/home/dimas/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba1.txt","'\'",";",(char *)NULL};

        execv("/usr/bin/find",var);}

    else{
        while(wait(&stat)>0);
        sleep(3);

        char *var[] = {"find","/home/dimas/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba2.txt","'\'",";",(char *)NULL};
        execv("/usr/bin/find",var);}
        }
        }
      }
    }
  }
}
```

### Penjelasan :

```c
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
```
Library untuk menjalankan program, ```#include <stdlib.h>``` Merupakan file header yang berfungsi untuk operasi pembanding dan operasi konversi. ```#include <sys/types.h>``` & ```#include <wait.h>``` Agar proses induk bisa menunggu proses anaknya selesai, maka butuh system call wait(). Wait() akan memblok eksekusi program sampai salah satu proses anaknya mati. <br>

```cid=fork();``` digunakan untuk membuat proses baru <br>

```
if (cid < 0){
        exit(EXIT_FAILURE); }
```
Digunakan jika proses akan berhenti

```
if(cid == 0){
        char *var[] = {"mkdir","-p","/home/dimas/modul2/indomie",(char *)NULL};
```
Child process untuk membuat direktori baru

```
execv("/bin/mkdir",var);}
```
Agar proses sebelumnya dapat berjalan, ```execv``` fungsi dari sistem operasi yang menjalankan file yang dapat dieksekusi dalam konteks proses yang sudah ada, menggantikan executable sebelumnya

```
else{
        while(wait(&stat)>0);
```
Parent process sehingga child process dapat dijalankan terlebih dahulu

# Kendala :
- Soal terlalu panjang, rumit sehingga sulit dipahami.
- Susah banget pokoknya.
