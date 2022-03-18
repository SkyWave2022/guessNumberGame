//
//  main.cpp
//  guessNumberGameOptimized(C++)
//
//  Created by SkyWave on 2022/2/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
FILE* fp;
int read_point;
char read_userName[10];
bool NoFile;//If player's save file doesn't exit,init the program

char path[50] = "save.dat";//change the path here
class read
{
public:
    int userName(void){
        fscanf(fp,"%s",read_userName);
        return 0;
        }
    int point(void){
        fscanf(fp,"%d\n",&read_point);
        return 0;
    }
private:
    
};
class write
{
public:
    int userName(void){
        fprintf(fp,"%s\n", read_userName);
        return 0;
    }
    int point(int addPoint){
        fprintf(fp,"%d\n",read_point+addPoint);
        return 0;
    }
private:
    
};
class scan
{
public:
    int userName(void){
        scanf("%s",read_userName);
        return 0;
    }
    //Don't ask me why there isn't scan.point()
private:
    
};

read read;
write write;
scan scan;

void setFilePoint(){
    fp = fopen(path,"r+");
    if (NULL == fp) {
        fp = fopen(path,"w+");
        NoFile = true;
    }
}
void init(){
    setFilePoint();
    read.point();
    if (NoFile) {
        printf("This is a guess number game created by SkyWave\n");
        printf("To start this game,simply input the range you want to guess\n");
        printf("I will pick a number for you in this range\n");
        printf("If you win,you will get some points according to your range and times\n");
        printf("By the way,could you tell me your name?\n");
        scan.userName();
        write.userName();
        printf("OK,%s,",read_userName);
    }else {
        read.userName();
        read.point();
        printf("Welcome back %s!\n",read_userName);
        printf("Your current point is: %d\n",read_point);
    }
}
int guessNumberMain() {
    init();
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
        }else if (pickedNumber > guessedNumber && guessedNumber>0){
            printf("Small\n");
            times++;
        }else if (guessedNumber < 0){
            printf("If you want to save the user profile and quit this game,input -1\nIf you want to restart,input -2\nor we will bring you back to game\n");
            scanf("%d",&guessedNumber);
            if (guessedNumber == -1) {
                fclose(fp);
                //Do we really need fclose here?
                exit(0);
            }else if (guessedNumber == -2){
                guessNumberMain();
            }else{
                printf("OK,guess my number:\n");
                continue;
            }
        }else {
            printf("Bingo!");
            pointAdded = range/times;
            printf("Point added:%d\n",pointAdded);
            fp = fopen(path,"w+");
            //erase the former point and write new points
            write.userName();
            write.point(pointAdded);
            fclose(fp);
            guessNumberMain();
        }
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    //why do I need main in this program XD
    guessNumberMain();
    return 0;
}
