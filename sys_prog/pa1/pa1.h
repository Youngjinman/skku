#include <unistd.h>
#include <stdlib.h>
int temp;
int quotient = 1;

void put_char(int cnt) {

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
                                write(STDOUT_FILENO, &quotient, sizeof(quotient));
                            }
                            temp = cnt/1000;
                            if(temp>=10){
                                temp%=10;
                            }
                            quotient = '0' + temp;
                            write(STDOUT_FILENO, &quotient, sizeof(quotient));
                        }
                        temp = cnt/100;
                        if(temp>=10){
                            temp%=10;
                        }
                        quotient = '0' + temp;
                        write(STDOUT_FILENO, &quotient, sizeof(quotient));
                    }
                    temp = cnt/10;
                    if(temp>=10){
                        temp%=10;
                    }
                    quotient = '0' + temp;
                    write(STDOUT_FILENO, &quotient, sizeof(quotient));
                    temp = cnt%10;
                    quotient = '0' + temp;
                    write(STDOUT_FILENO, &quotient, sizeof(quotient));
                }

    else{
        quotient = '0' + cnt;
        write(STDOUT_FILENO, &quotient, sizeof(quotient));
    }

}
