//
//  main.c
//  guessNumberGame
//
//  Created by SkyWave on 2022/1/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
FILE* fp;
int guessNumberMain(void) {
    fp = fopen("save.dat","r+");
    if (NULL == fp) {
        fp = fopen("save.dat","w+");
    }
    int point = -1;
    char userName[10];
    fscanf(fp,"%s",userName);
    fscanf(fp,"\n%d",&point);
    if (point == -1) {
        point = 0;
        printf("This is a guess number game created by SkyWave\n");
        printf("To start this game,simply input the range you want to guess\n");
        printf("I will pick a number for you in this range\n");
        printf("If you win,you will get some points according to your range and times\n");
        printf("By the way,could you tell me your name?\n");
        scanf("%s",userName);
        fprintf(fp,"%s\n",userName);
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
        printf("Please re-input:S");
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
            fp = fopen("/users/skywavesun/desktop/games/guessnumbergame/save.dat","w+");
            fprintf(fp,"%s\n",userName);
            fprintf(fp,"%d",point+pointAdded);
            fclose(fp);
            guessNumberMain();
        }
    }
}

int main(int argc, const char * argv[]) {
    guessNumberMain();
    return 0;
}
