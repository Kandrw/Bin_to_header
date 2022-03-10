#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

char *to_hex(int a){
    int r, i = 0;
    char *strh;
    strh = malloc(sizeof(char) * (pow(a, 1./16.)+1));
    sprintf(strh, "0x%2x", a);
    if(strh[2] == ' '){
        strh[2] = '0';
    }
    return strh;
}
char *to_str(int a){
    char *stri;
    stri = malloc(sizeof(char) * (pow(a, 0.1)+1));
    sprintf(stri, "%d", a);
    return stri;
}

int Read(char *file_read, char *file_write, int sf, char *d_n){
    FILE *fr;
    FILE *fw;
    int count = 0;
    fr = fopen(file_read,"rb");
    fw = fopen(file_write,"wb");
    if(fr == NULL){
        printf("Error: file not found\n");
        return 1;
    }
    fputs("int size = ",fw);
    fputs(to_str(sf), fw);
    fputs(";\n", fw);
    fputs("static const unsigned int ",fw);
    fputs(d_n,fw);
    fputs("[] = {",fw);
    unsigned int var;
    while((var = getc(fr)) != EOF){
        if(count != 0){
            fputs(", ",fw);
        }
        if(count % 12 == 0){
            fputs("\n\t", fw);
        }
        fputs(to_hex(var), fw);
        ++count;
    }
    fputs(" };\n",fw);
    fclose(fw);
    fclose(fr);
    printf("Write file\n");
    return 0;
}

int main(int argc, char **argv){
    if(argc > 1){
        int var, size = 0, i;
        int len = 0;
        while(argv[1][len] != '\0'){
            ++len;
        }
        int k = 0, k2 = 0;
        if(argc > 2){
             while(argv[1][k] != '\0'){
            ++k;
            }       
        }
        else{
            k = len;
            k2 = 2;
        }
        char f_write[k+k2], data_n[len], f_read[len];
        if(argc > 2){
            for(i = 0; i < k; ++i){
                f_write[i] = argv[2][i];
            }
            f_write[i] = '\0';
        }
        for(i = 0; i < len; ++i){
            if(argv[1][i] == ' ' || argv[1][i] == '.' ){
                data_n[i] = '_';
            }
            else{
                data_n[i] = argv[1][i];
            }
            f_read[i] = argv[1][i];
            if(argc == 2){
                f_write[i] = argv[1][i];
            }
        }
        data_n[i] = '\0';
        f_read[i] = '\0';
        if(argc == 2){
            f_write[i] = '.';
            f_write[i+1] = 'h';
            f_write[i+2] = '\0';
        }

        FILE *f_size = fopen(f_read,"rb");
        if(f_size != NULL){
            while ((var = getc(f_size)) != EOF){
                ++size;
            }
            fclose(f_size);
            printf("size %s = %d\n", f_read, size);
            Read(f_read,f_write, size, data_n);
        }
        else{
            printf("Error: file not found\n");
        }

    }
    else{
        printf("Error: file name not entered\n");
    }
}


