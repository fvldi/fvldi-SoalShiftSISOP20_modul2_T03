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
