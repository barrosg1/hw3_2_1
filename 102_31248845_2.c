#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

int numOfProcesses;

int main(int argc, char **argv)
{
    
    if(argc < 3)
    {
        puts("Insufficient arguments");
        return 0;
    }
    else
    {
        int i, pid, status;
        
        int opt;
        while((opt = getopt(argc, argv, "n:")) != -1) {
            switch(opt) {
                case 'n':
                    numOfProcesses = atoi(optarg);
                    break;
                case ':':
                    printf("option needs a value\n"); break;
                case '?':
                    printf("unknown option: %c\n", optopt); break;
            }
            
        }
        
        int sum = 0;
        unsigned int seed = (unsigned int)time(NULL); // create seed for each process
        
        for(i = 0; i < numOfProcesses; i++) {
            int randomNum = rand_r(&seed) % 201 + (-100); // generate random numbers between -100 to 100
            
            pid = fork(); // spawning processes
            
            if(pid < 0) {
                printf("Fork Failure");
                exit(1);
            } else if (pid == 0) { // child process
                printf("%d\n", randomNum);
                
                exit(42);
            } else  {  // parent process
                sum += randomNum;
                wait(&status);
            }
        }
        
        printf("%d\n", sum);
    }
    
    return 0;
}


