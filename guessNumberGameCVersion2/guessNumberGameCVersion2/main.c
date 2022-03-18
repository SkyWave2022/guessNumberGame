//
//  main.c
//  guessNumberGame
//
//  Created by SkyWave on 2022/1/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
FILE* fp;
bool NoFile;
char path[50] = "save.dat";
int point;
char userName[10];
void read_userName(void){
    fscanf(fp,"%s",userName);
}
void read_point(void){
    fscanf(fp,"\n%d",&point);
}
void write_userName(void){
    fprintf(fp,"%s\n",userName);
}
void write_point(int addpoint){
    fprintf(fp,"%d",point+addpoint);
}
void setFilePoint(void){
    fp = fopen("save.dat","r+");
    NoFile = false;
    if (NULL == fp) {
        fp = fopen("save.dat","w+");
        NoFile = true;
    }
}
void init(void){
    setFilePoint();
    read_userName();
    read_point();
}
void guessNumberMain(void) {
    init();
    if (NoFile) {
        printf("This is a guess number game created by SkyWave\n");
        printf("To start this game,simply input the range you want to guess\n");
        printf("I will pick a number for you in this range\n");
        printf("If you win,you will get some points according to your range and times\n");
        printf("By the way,could you tell me your name?\n");
        scanf("%s",userName);
        write_userName();
        printf("OK,%s,",userName);
    }else {
        printf("Welcome back %s!\n",userName);
        printf("Your current point is: %d\n",point);
    }
    int range;
    printf("Input the range you want to guess:");
    scanf("%d",&range);
    if (range<2) {
        printf("Oops,range can only larger than 1!\n");
        printf("Please re-input:");
        scanf("%d",&range);
    }
    srand((unsigned)time(NULL));
    int pickedNumber = rand()%range+1;
    int guessedNumber;
    int times = 0;
    int pointAdded = 0;
    printf("I already picked a number,guess it!\n");
    while (1) {
        scanf("%d",&guessedNumber);
        if (pickedNumber < guessedNumber) {
            printf("Big\n");
            times++;
        }else if (pickedNumber > guessedNumber){
            printf("Small\n");
            times++;
        }else {
            printf("Bingo!");
            pointAdded = range/times;
            printf("Point added:%d\n",pointAdded);
            setFilePoint();
            write_userName();
            write_point(pointAdded);
            fclose(fp);
            guessNumberMain();
        }
    }
}

int main(int argc, const char * argv[]) {
    guessNumberMain();
    return 0;
}
