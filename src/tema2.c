#include "tema.h"

int main(const int argc, const char *argv[]){
    if(argc < 3){
        return 1;
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if(in == NULL || out == NULL){
        return 1;
    }
    S *stacktop1 = NULL, *stacktop2 = NULL, *stacktop3 = NULL;
    char s[256], s1[256] = "", s2[256] = "", s3[256] = "";
    int i = 0;
    Queue *q = createQueue();
    while(fgets(s, 256, in)){
        s[strcspn(s, "\r\n")] = 0;
        if(isalpha(s[0])){
            i++;
            if(i == 1)
                strcpy(s1, s);
            if(i == 2)
                strcpy(s2, s);
            if(i == 3)
                strcpy(s3, s);
        }
        else{
            double nr = atof(s);
            if(i == 1){
                push(&stacktop1, nr);
            }
            if(i == 2){
                push(&stacktop2, nr);
            }
            if(i == 3){
                push(&stacktop3, nr);
            }
        }
    }
    i = 0; //ziua
    while(!isEmptyS(stacktop1) && !isEmptyS(stacktop2) && !isEmptyS(stacktop3)){
        i++;
        double val1 = pop(&stacktop1), val2 = pop(&stacktop2), val3 = pop(&stacktop3);
        char rasp[256] = "ziua ";
        if(val1 == val2 && val1 != val3){
            createString(val1, val2, val3, rasp, i, s3);
            enQueue(q, rasp);
        }
        if(val2 == val3 && val2 != val1){
            createString(val2, val3, val1, rasp, i, s1);
            enQueue(q, rasp);
        }
        if(val1 == val3 && val1 != val2){
            createString(val1, val3, val2, rasp, i, s2);
            enQueue(q, rasp);
        }
    }
    printQueue(q, out);
    deleteStack(&stacktop1);
    deleteStack(&stacktop2);
    deleteStack(&stacktop3);
    fclose(in);
    fclose(out);
    return 0;
}