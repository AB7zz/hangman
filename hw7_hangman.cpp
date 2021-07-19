#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>   // for call to time() in srand(time(NULL))

#define DEBUG 1  // 1-development mode, prints more info; 0 - user mode, prints less
#define MAX_WRONG 6

int wins=0;
int totalgames=0;
int play_session(int level);
void drawman(int wrong, char str1[100], char str2[]);

int main(){
    int level;
    char enter;
    if (DEBUG == 1) {
        srand(1);  // the same sequence of random numbers will be generated for each run
    }
    else {
        srand(time(NULL));  // a different sequence of random numbers will be generated with each run
    }

    printf("Choose difficulty level (exit the game: 0, easy: 1, medium: 2, hard: 3): ");
    scanf("%d%c", &level, &enter);
    while (level!=0){
        int returnval =0;
        returnval = play_session(level);
            while(returnval == 5){
              printf("Choose difficulty level (exit the game: 0, easy: 1, medium: 2, hard: 3): ");
              scanf("%d%c", &level, &enter);
              if(level == 0){
                 printf("\nThank you for playing our game! Goodbye!");
              }
              returnval = play_session(level);
            }
    }
  printf("\nThank you for playing our game! Goodbye!");

}
int play_session(int level){
    totalgames++;
    int i=0;
    char buff[1000];
    FILE * fp = NULL;
    if(level==1){fp=fopen("easy.txt", "r");}

    if(level==2){fp=fopen("medium.txt", "r");}

    if(level==3){fp=fopen("hard.txt", "r");}

    if(fp != NULL && level ==1)
    {
        printf("Loading file: easy.txt\n");
    }
    else if(fp != NULL && level ==2)
    {
        printf("Loading file: medium.txt\n");
    }
    else if(fp != NULL && level ==3)
    {
        printf("Loading file: hard.txt\n");
    }

    int N;
    fscanf(fp, "%d", &N);
    N++;
    int r = 1+rand()%N;
    int ct = 0;
    while((!feof(fp))&&(ct<r))
    {
        fscanf(fp,"%s",&buff);
        ct++;
    }
    printf("-----hidden word: |%s|\n\n\n\n\n",buff);
    int correct =0;
    int mistake = 0;
    int number = 0 ;
    char guess;
    char usedwords[100];
    int z;
    char name[20];
    int buffy = strlen(buff);
    char guessStatus[buffy+1];
    for (z=0;z<buffy+1;z++)
    {
        if(buff[z]!=NULL)
        {
            guessStatus[z]= '-';
        }else
        {
            guessStatus[z]= NULL;
        }
        guessStatus[buffy+1] = '\0';
    }
    printf("\n\n\n\n\n\n\n\n\n");
    printf("Level: %d\n\n\n",level);
    drawman(mistake,usedwords,guessStatus);
    int fullcorrect = 0;
    while (mistake<6 && fullcorrect != 55)
    {
        printf("Enter a letter: ");
        char enter; // this will be used just to get read of the ENTER
        scanf("%c%c", &guess, &enter);  // to read one char (one letter) and remove the ENTER that is after it (from the user hitting the ENTER key)
        printf("\n\n\n\n\n\n\n\n\n");
        correct = 0;
        strncat(usedwords, &guess, 1);
        for (int search=0; search<buffy; search++)
        {
            if (guess == buff[search]){
                number++;
                guessStatus[search] = buff[search];
                correct = 1;
            }
        }
        if (correct == 0){
            mistake++;
        }
        printf("Level: %d\n\n\n",level);
        drawman(mistake,usedwords,guessStatus);
        printf("\n");
        if(strcmp(guessStatus, buff) == 0){
            printf("You won!\n");
            fullcorrect = 55;
        }
    }

    if(strcmp(guessStatus, buff) == 0)
    {
        wins++;
    }
    else
    {
        printf("Sorry. You lost. Better luck next time. \n");
        printf("The word was: %s \n\n", buff);
    }
    int choi=3;
    char enter;
    printf("Do you want to play again? (0-no, 1-yes) ");
    scanf("%d%c",&choi,&enter);
    if(choi==0){
        printf("\n");
        printf("****************************\n");
        printf("*  Session score:   %d/  %d  *\n", wins, totalgames);
        printf("****************************\n");
        wins = 0;
        totalgames = 0;
        for(int q=0;q<strlen(usedwords);q++)
        {
        usedwords[q] = 0;
        }
        return 5;
    }
    else if(choi==1)
    {
        for(int q=0;q<strlen(usedwords);q++)
        {
        usedwords[q] = 0;
        }
        play_session(level);
    }
}
void drawman(int wrong, char str1[100], char str2[]){
    if(wrong==0){
    printf("------|\n");
    printf("|     |\n");
    printf("|\n");
    printf("|\n");
    printf("|\n");
    printf("|\n");
    printf("|\n");
    printf("-------------\n");
    }
    else if(wrong==1){
    printf("------|\n");
    printf("|     |\n");
    printf("|     O\n");
    printf("|\n");
    printf("|\n");
    printf("|\n");
    printf("|\n");
    printf("-------------\n");
    }
    else if(wrong==2){
    printf("------|\n");
    printf("|     |\n");
    printf("|     O\n");
    printf("|     |\n");
    printf("|     |\n");
    printf("|     |\n");
    printf("|\n");
    printf("-------------\n");
    }
    else if(wrong==3){
    printf("------|\n");
    printf("|     |\n");
    printf("|     O\n");
    printf("|     |\n");
    printf("|    /|\n");
    printf("|     |\n");
    printf("|\n");
    printf("-------------\n");
    }
    else if (wrong==4){
    printf("------|\n");
    printf("|     |\n");
    printf("|     O\n");
    printf("|     |\n");
    printf("|    /|\\\n");
    printf("|     |\n");
    printf("|\n");
    printf("-------------\n");
    }
    else if(wrong==5){
    printf("------|\n");
    printf("|     |\n");
    printf("|     O\n");
    printf("|     |\n");
    printf("|    /|\\\n");
    printf("|     |\n");
    printf("|    /\n");
    printf("-------------\n");
    }
    else if(wrong==6){
    printf("------|\n");
    printf("|     |\n");
    printf("|     O\n");
    printf("|     |\n");
    printf("|    /|\\\n");
    printf("|     |\n");
    printf("|    / \\\n");
    printf("-------------\n");
    }
    printf("Used letters: %s\n", str1);
    printf("Number of bad guesses: %i (out of 6)\n",wrong);
    printf("%s\n\n",str2);
}
