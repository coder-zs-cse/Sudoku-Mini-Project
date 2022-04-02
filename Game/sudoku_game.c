#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<dirent.h>
#define N 9
#define M 3
typedef struct {
    int puzzle[N][N];
    int solution[N][N];
}sudoku;

typedef struct{
    char foldername[50];
    char folderpath[50];
}Folder;
Folder save_sudoku;

void Folder_init(){
    save_sudoku.foldername[0]='\0';
    save_sudoku.folderpath[0]='\0';
    strcat(save_sudoku.foldername,"Progress_Reports");
    strcat(save_sudoku.folderpath,"Progress_Reports\\");

    DIR *dir = opendir(save_sudoku.folderpath);
    if(dir==NULL){
        mkdir(save_sudoku.foldername);
    }
}

void save_progress(sudoku*,sudoku*,int);
void generate_puzzle(sudoku*);
void erase_input(int box[N][N],int puzzle[N][N]);
void get_a_hint(sudoku*,sudoku*);
void fill_k_empty_boxes(sudoku*,int);
void diagonal_solve(sudoku*);
void copy_box1_to_box2(int box1[N][N],int box2[N][N]);
void init(sudoku*);
int validinput(int box[N][N],int,int,int);
void takeinput(int box[N][N]);
void printparallel(int box1[N][N],int box2[N][N]);
void printbox(int box[N][N]);
int is_box1_equal_to_box2(int box1[N][N],int box2[N][N]);
int solve_sudoku(sudoku*,int,int,int,int,int);
int isvalidsudoku(int box[N][N]);
void difficulty_mode(sudoku*);
void play_sudoku(sudoku*,sudoku*,int);
void load_and_play_sudoku(sudoku*);
void play();
void input();

#include "printfunctions.h"
#include "helperfunctions.h"
#include "algorithms.h"
#include "filedirectory.h"
#include "menu.h"


int main(){
    Folder_init();
    srand(time(0));
    int choice;
    while(1){
        printf("Press 1 to play a random sudoku game\n");
        printf("Press 2 to input a sudoku\n");
        printf("Press 3 to open a previously saved sudoku\n");
        printf("Press -1 to exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: play();
            break;
            case 2: input();
            break;
            case 3: open_file_directory();
            break;
            case -1: goto out;
            default:
            printf("Invalid entry!, please check the menu and try again\n");
        }
    }
    out:

return 0;
}