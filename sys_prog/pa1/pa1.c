#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "pa1.h"

#define MAX_LINE_LENGTH 512

int main(int argc, char* argv[]){
    if (argc != 2){
        exit(1);
    }

    int fd;
    char txt_buffer[MAX_LINE_LENGTH];
    char stdin_buffer[MAX_LINE_LENGTH];
    int cnt = 0;
    int stdin_length;
    int i, j, k, l, n;
    int start_index = 0;
    //char temp_buffer[MAX_LINE_LENGTH];
    while(1) {
        int line_number = 1;
	fd = open(argv[1], O_RDONLY);
        n = read(STDIN_FILENO, &stdin_buffer, MAX_LINE_LENGTH);;
        if (stdin_buffer[0] == 'P' && stdin_buffer[1] == 'A' && stdin_buffer[2] == '1' && stdin_buffer[3] == 'E' && stdin_buffer[4] == 'X' && stdin_buffer[5] == 'I' && stdin_buffer[6] == 'T') {
            break;
        }
        //write(STDOUT_FILENO, &stdin_buffer[0], sizeof(stdin_buffer[0]));
        for(stdin_length=0; stdin_length<n; stdin_length++){
            if(stdin_buffer[stdin_length] == '\n')
                stdin_buffer[stdin_length] = '\0';
        }


        while ((n = read(fd, txt_buffer, MAX_LINE_LENGTH)) > 0) {

            for (i = 0; i < n; i++) { //0 ~ n-1
                
                
                if (txt_buffer[i] == '\n') {
                    txt_buffer[i] = '\0';
                    for(j = 0; j <= i; j++){
                        //printf("%c", txt_buffer[j]);
                        
                        if (txt_buffer[j] == stdin_buffer[0]) {

                            int match = 1;
                            for(l = 1, k = j+1; k<=i; k++, l++){
                                if(txt_buffer[k] == stdin_buffer[l]) {
                                    match++;
                                }
                                if(txt_buffer[k] == '\0' && stdin_buffer[l] == '\0')
                                    break;
                            }
                            
                            //printf("%d\n", cnt);
                            if(match == stdin_length)
                            {
                                // char ln = line_number + '0';
                                // j += 48;
                                // char idx = j + '0';
                                put_char(line_number);
                                
                                //write(STDOUT_FILENO, &ln, 1);
                                write(STDOUT_FILENO, ":", sizeof(char));
                                //write(STDOUT_FILENO, &idx, 1);
                                put_char(j);
                                write(STDOUT_FILENO, "\n", 1);
                            }
                        }   
                    }
		    int offset = -(n - (i + 1));
                    line_number++; //행 증   
                    lseek(fd, offset, SEEK_CUR);
                    break;
                }
            }
            txt_buffer[0] = '\0';
        }
    }
    close(fd);
}




