#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<dirent.h>


typedef struct {
    int puzzle[9][9];
    int solution[9][9];
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

void init(sudoku *puzzle){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            puzzle->puzzle[i][j]=0;
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            puzzle->solution[i][j]=0;
        }
    }
}
void copy_box1_to_box2(int box1[9][9],int box2[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            box2[i][j]=box1[i][j];
        }
    }
}

void generate_puzzle(sudoku *matrix){
    int visited[82];
    for(int i=0;i<=81;i++){
        visited[i]=1;
    }
    puzzle_generator(matrix,visited,81);
}

void difficulty_mode(sudoku *matrix){
    int k;
    while(1){
        int choice;
        printf("Press 1 to play a easy mode sudoku game\n");
        printf("Press 2 to play a medium mode sudoku game\n");
        printf("Press 3 to play a hard mode sudoku game\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1: k = rand() % 10 + 20;
            goto out;
        case 2: k = rand() % 10 + 10;
            goto out;
        case 3: 
            return;
        default:
        printf("Invalid entry!, please check the menu and try again\n");
        }
    }
    out:
    fill_k_empty_boxes(matrix,k);
}

void play_sudoku(sudoku *matrix,sudoku *current,int numberofhints){
    
    while(!is_box1_equal_to_box2(current->puzzle,matrix->solution)){
        int choice;
        printf("Press 1 to enter your next input\n");
        printf("Press 2 to get a hint\n");
        printf("Press 3 to undo a move\n");
        printf("Press 4 to save the current progress for later and close\n");
        printf("Press 5 to get the solution of this puzzle\n");
        printf("Press -1 to quit the game\n");
        printf("\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: takeinput(current->puzzle);
            break;
            case 2: get_a_hint(current,matrix);
                    numberofhints++;
            break;
            case 3: undo_move(current->puzzle,matrix->puzzle);
            break;
            case 4: save_progress(matrix,current,numberofhints);
                    return;
            case 5: printparallel(current->puzzle,matrix->solution);
                    return;
            break;
            case -1: return;
            break;
            default: printf("Invalid entry, Please check menu\n");
        }
        printbox(current->puzzle);
        printf("Hints taken so far : %d\n",numberofhints);
    }
    printf("Congratulations!\nYou have solved the puzzle with %d hints\n",numberofhints);
}

void load_and_play_sudoku(sudoku *matrix){
    difficulty_mode(matrix);
    printbox(matrix->puzzle);
    sudoku current;
    copy_box1_to_box2(matrix->puzzle,current.puzzle);
    int numberofhints=0;
    play_sudoku(matrix,&current,numberofhints);
}
void play(){
    sudoku matrix;
    init(&matrix);
    diagonal_solve(&matrix);
    solve_sudoku(&matrix,0,0,1,9,1);
    copy_box1_to_box2(matrix.solution,matrix.puzzle);
    generate_puzzle(&matrix);
    load_and_play_sudoku(&matrix);
}

void input(){
    sudoku matrix;
    printf("Enter the values of the sudoku cells from left to right up to down\n");
    printf("Enter 0 to indicate a blank space\n\n");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            scanf("%d",&matrix.puzzle[i][j]);
        }
    }
    if(!isvalidsudoku(matrix.puzzle)){
        printf("\nInputted sudoku is incorrect\n");
        return;
    }
    copy_box1_to_box2(matrix.puzzle,matrix.solution);
    solve_sudoku(&matrix,0,0,1,9,1);
    sudoku current;
    copy_box1_to_box2(matrix.puzzle,current.puzzle);
    while(1){
        int choice;
        printf("Press 1 if you want to solve the inputted puzzle yourself\n");
        printf("Press 2 to get the solution of this puzzle\n");
        printf("Press -1 to exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: 
                    printbox(current.puzzle);
                    play_sudoku(&matrix,&current,0);
            case 2: printbox(matrix.solution);
            case -1: return;
            default : 
            printf("Invalid entry, please check the menu and retry again\n");
        }
    }
}
#include "printfunctions.h"
#include "helperfunctions.h"
#include "algorithms.h"
#include "filedirectory.h"
int main(){
    system("clear");
    system("cls");
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
            case 3: open_progress();
            break;
            case -1: goto out;
            default:
            printf("Invalid entry!, please check the menu and try again\n");
        }
    }
    out:

return 0;
}