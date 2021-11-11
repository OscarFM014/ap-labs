#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <ftw.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int wd, inotifyFd;
char *myPath; 

#define BUF_LEN (10 * (sizeof(struct inotify_event) + 32 + 1))
#define MAXLEVEL  2

char *currentDir[60000];

static int display_info(const char *fpath, const struct stat *sb,
            int tflag, struct FTW *ftwbuf)
{
   // if the depth is above the max sub dirs, continue to next file
   if (ftwbuf->level > MAXLEVEL) {
       return 0; 
   }

    if(tflag == FTW_D){

        wd = inotify_add_watch(inotifyFd, fpath, IN_ALL_EVENTS);

        currentDir[wd] = malloc (sizeof(char) * 1024);
        strncpy(currentDir[wd], fpath, strlen(fpath));
        currentDir[wd][strlen(fpath)] = 0;
    }
   return 0;           /* To tell nftw() to continue */
}

static void             /* Display information from inotify_event structure */
displayInotifyEvent(struct inotify_event *i)
{
    if (i->mask & IN_CREATE){
        if(strcmp(currentDir[i->wd], myPath) != 0){
            char *myDir;
            myDir = malloc (sizeof(char) * (strlen(currentDir[i->wd]) - strlen(myPath)));
            strncpy(myDir, currentDir[i->wd] + strlen(myPath) , strlen(currentDir[i->wd]) - strlen(myPath));
            myDir[strlen(currentDir[i->wd]) - strlen(myPath)] = 0;
            if (i->mask & IN_ISDIR){
                printf("- [Directory - Create] - %s/%s" , myDir, i->name);
            }else{
                printf("- [File - Create] - %s/%s" , myDir, i->name);
            }
            printf("\n");   
        }else{
            if (i->mask & IN_ISDIR){
                printf("- [Directory - Create] - %s ", i->name);
                int flags = 0;
                if (nftw((1 < 2) ? myPath : myPath, display_info, 20, flags) == -1) {
                    perror("nftw");
                    exit(EXIT_FAILURE);
                }
            }else{
                printf("- [File - Create] - %s" , i->name);
            }
            printf("\n");  
        }

    }  
    if (i->mask & IN_DELETE){
        if(strcmp(currentDir[i->wd], myPath) != 0){
            char *myDir;
            myDir = malloc (sizeof(char) * (strlen(currentDir[i->wd]) - strlen(myPath)));
            strncpy(myDir, currentDir[i->wd] + strlen(myPath) , strlen(currentDir[i->wd]) - strlen(myPath));
            myDir[strlen(currentDir[i->wd]) - strlen(myPath)] = 0;
            if (i->mask & IN_ISDIR){
                printf("- [Directory - Removal] - %s/%s" , myDir, i->name);
            }else{
                printf("- [File - Removal] - %s/%s" , myDir, i->name);
            }
            printf("\n");   
        }else{
             if (i->mask & IN_ISDIR){
            printf("- [Directory - Removal] - %s ", i->name);
            }else{
                printf("- [File - Removal] - %s ", i->name);
            } 
            printf("\n");   
        }           
    } 
    if (i->mask & IN_MOVED_FROM){
        if(strcmp(currentDir[i->wd], myPath) != 0){
            char *myDir;
            myDir = malloc (sizeof(char) * (strlen(currentDir[i->wd]) - strlen(myPath)));
            strncpy(myDir, currentDir[i->wd] + strlen(myPath) , strlen(currentDir[i->wd]) - strlen(myPath));
            myDir[strlen(currentDir[i->wd]) - strlen(myPath)] = 0;
            if (i->mask & IN_ISDIR){
                printf("- [Directory - Rename] - %s /%s " , myDir, i->name);
            }else{
                printf("- [File - Rename] - %s/%s " , myDir, i->name);
            }
        }else{
            if (i->mask & IN_ISDIR){
            printf("- [Directory - Rename] - %s ", i->name);
            }else{
                printf("- [File - Rename] - %s ", i->name);
            } 
        }

    }      
    if (i->mask & IN_MOVED_TO){
        if(strcmp(currentDir[i->wd], myPath) != 0){
            char *myDir;
            myDir = malloc (sizeof(char) * (strlen(currentDir[i->wd]) - strlen(myPath)));
            strncpy(myDir, currentDir[i->wd] + strlen(myPath) , strlen(currentDir[i->wd]) - strlen(myPath));
            myDir[strlen(currentDir[i->wd]) - strlen(myPath)] = 0;
            if (i->mask & IN_ISDIR){
                printf("-> %s/%s" , myDir, i->name);
            }else{
                printf("-> %s/%s" , myDir, i->name);
            }
            printf("\n");   
        }else{
            if (i->mask & IN_ISDIR){
                printf("-> %s ", i->name);
                int flags = 0;
                if (nftw((1 < 2) ? myPath : myPath, display_info, 20, flags) == -1) {
                    perror("nftw");
                    exit(EXIT_FAILURE);
                }
            }else{
                printf("-> %s ", i->name);
            }
            printf("\n");     
        }  
    } 
}

int
main(int argc, char *argv[])
{
    int j;
    char buf[BUF_LEN] __attribute__ ((aligned(8)));
    ssize_t numRead;
    char *p;
    struct inotify_event *event;


    if(argc == 1){
        printf("Error: Path not added \n");
        printf("./monitor $HOME\n");
        return -1;
    }

    myPath = argv[1];
    inotifyFd = inotify_init();

    wd = inotify_add_watch(inotifyFd, myPath, IN_ALL_EVENTS);

    if(wd == -1){
        printf("Error 404: Path not found \n");
        printf("./monitor $HOME\n");
        return -1;
    }

    printf("Starting File/Directory Monitor on %s \n", myPath);
    printf("-------------------------------------------------------------------------------------\n");

    //nftw()
    int flags = 0;
    if (nftw((argc < 2) ? myPath : myPath, display_info, 20, flags) == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }

    for (;;) {                                  /* Read events forever */
        numRead = read(inotifyFd, buf, BUF_LEN);
        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *) p;
            displayInotifyEvent(event);
            p += sizeof(struct inotify_event) + event->len;
        } 
    }
}

//Oscar