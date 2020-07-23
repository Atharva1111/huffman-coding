#include<stdio.h>
#include<string.h>

void main(){
    FILE *file;
    file = fopen("text.txt", "r");
    char *p, buff[1000];
    int i=1;
    while(fgets(buff, sizeof(buff), file)){
        printf("%d", i);
        printf("s");
        strcat(p, buff);
    }
    printf("%s", p);
}