#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc != 2){
        exit(1);
    }

    char* inputfile;
    inputfile = argv[1];

    int rfd, wfd;
    char c;
    int cnt = 1;
    int temp;
    int quotient = 1;
    char one = '0';
    char *sen = " | ";



    rfd = open(inputfile, O_RDONLY);
    wfd = open("Aladdin_num.txt", O_RDWR | O_CREAT, 0755);
    
    one += 1;
    write(wfd, &one, 1);
    write(wfd, sen, 3);

    while(read(rfd, &c, 1) > 0){
        write(wfd, &c, 1);
        if(c=='\n'){
            one ++;
            cnt++;
            if (one>57){
                one = '0';
            }
            
            if(cnt/10>0){ //10~99
                if(cnt/10>=10)//100~999
                { 
                    if(cnt/10>=100)//1000~9999
                    {
                        if(cnt/10>=1000)//10000~
                        {
                            temp = cnt/10000;
                            if(temp>=10){
                                temp%=10;
                            }
                            quotient = '0' + temp;
                            write(wfd, &quotient, sizeof(quotient));
                        }
                        temp = cnt/1000;
                        if(temp>=10){
                            temp%=10;
                        }
                        quotient = '0' + temp;
                        write(wfd, &quotient, sizeof(quotient));
                    }
                    temp = cnt/100;
                    if(temp>=10){
                        temp%=10;
                    }
                    quotient = '0' + temp;
                    write(wfd, &quotient, sizeof(quotient));
                }
                temp = cnt/10;
                if(temp>=10){
                    temp%=10;
                }
                quotient = '0' + temp;
                write(wfd, &quotient, sizeof(quotient));
            }
            write(wfd, &one, sizeof(one));
            write(wfd, sen, 3); 
        }
    }

    close(rfd);
    close(wfd);


    return 0;
}
