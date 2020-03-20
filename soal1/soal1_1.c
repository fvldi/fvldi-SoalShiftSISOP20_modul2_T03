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