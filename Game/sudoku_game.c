#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct {
    int puzzle[9][9];
    int solution[9][9];
}sudoku;

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


#define take(n) int n;scanf("%d",&n)
void printbox(int box[9][9]){
    for(int i=0;i<3;i++)printf(" ");
    for(int i=0;i<9;i++){
        if(i%3==0) printf("  ");
        printf("%d ",i);
    }
    printf("\n");
    for(int i=0;i<15;i++) {
        printf("_ ");
    }
    printf("\n");
    for(int i=0;i<9;i++){
        printf("%d |  ",i);
        for(int j=0;j<9;j++){
            if(box[i][j]!=0)
            printf("%d ",box[i][j]);
            else printf("_ ");
            if(j!=8 && j%3==2) printf("| ");
        }
        if(i!=8 && i%3==2) {
        printf("\n");
            for(int x=0;x<26;x++) printf("-");
        }
        printf("\n");
    }
    printf("\n");
}
void printparallel(int box1[9][9],int box2[9][9]){
    for(int i=0;i<3;i++)printf(" ");
    for(int i=0;i<9;i++){
        if(i%3==0) printf("  ");
        printf("%d ",i);
    }
    printf("    ");
    for(int i=0;i<3;i++)printf(" ");
    for(int i=0;i<9;i++){
        if(i%3==0) printf("  ");
        printf("%d ",i);
    }
    printf("\n");
    for(int i=0;i<14;i++) {
        printf("_ ");
    }
    printf("   ");
    for(int i=0;i<15;i++) {
        printf("_ ");
    }
    printf("\n");
    for(int i=0;i<9;i++){
        printf("%d |  ",i);
        for(int j=0;j<9;j++){
            if(box1[i][j]!=0)
            printf("%d ",box1[i][j]);
            else printf("_ ");
            if(j!=8 && j%3==2) printf("| ");
        }
        printf("    ");
        printf("%d |  ",i);
        for(int j=0;j<9;j++){
            if(box2[i][j]!=0)
            printf("%d ",box2[i][j]);
            else printf("_ ");
            if(j!=8 && j%3==2) printf("| ");
        }
        if(i!=8 && i%3==2) {
        printf("\n");
            for(int x=0;x<26;x++) printf("-");
            printf("    ");
            for(int x=0;x<26;x++) printf("-");
        }
        printf("\n");
    }
    printf("\n");
}
int rowclash(int box[9][9],int i,int j,int num){
    for(int col=0; col<9;col++){
        if(col!=j && box[i][col]==num) return 1;
    }
    return 0;
}
int columnclash(int box[9][9],int i,int j,int num){
    for(int row=0; row<9;row++){
        if(row!=i && box[row][j]==num) return 1;
    }
    return 0;
}
int boxclash(int box[9][9],int i,int j,int num){
    int xcor[5] = {-2,-1,0,1,2};
    int ycor[5] = {-2,-1,0,1,2};
    int xll =  2 - i%3 ; // x lower limit
    int xul =  4 - i%3 ; // x upper limit
    int yll =  2 - j%3 ; // y lower limit
    int yul =  4 - j%3 ; // y upper limit
    
    for(int x = xll ; x <= xul;x++){
        int xnew = i + xcor[x];
        for(int y = yll ; y <= yul;y++){
            int ynew = j + ycor[y];
            if(!(xnew==i && ynew==j)&& box[xnew][ynew]==num) return 1;
        }
    }
    return 0;
}
int clash(int box[9][9],int i,int j,int num){
    if(rowclash(box,i,j,num)) return 1;
    if(columnclash(box,i,j,num)) return 1;
    if(boxclash(box,i,j,num)) return 1;
    return 0;
}
int is_box1_equal_to_box2(int box1[9][9],int box2[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(box1[i][j]!=box2[i][j]) return 0;
        }
    }
    return 1; //if all elements are equal then both are duplicates
}
int isvalidsudoku(int box[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(box[i][j]!=0){
                if(clash(box,i,j,box[i][j])){
                    return 0;
                }
            }
        }
    }
    return 1;
}
int select_random_number(int box[9][9],int numvisited[10],int no_of_num_left){
    int n=no_of_num_left;
    int num = (rand()%n) +1;
    int count=0;
    for(int i=1;i<=9;i++){
        if(numvisited[i]==1){
            count++;
        }
        if(count==num){
            num = i;
            break;
        }
    }
    numvisited[num]=0;
    return num;
}
int select_random_grid(int visited[82],int no_of_grids_left){
    int n=no_of_grids_left;
    int number = (rand() % n) + 1;
    int count1=0,index;
    for(int it=1;it<=81;it++){
        if(visited[it]==1){
            count1++;
        }
        if(count1==number){
            index =it;
            break;
        }
    }
    visited[index] = 0;
    return index;
}
int solve_sudoku(sudoku *matrix,int i,int j,int S,int E,int X){
    if(i==8 && j==9)  {
        return 1;
    }
    if(j==9)  return solve_sudoku(matrix,i+1,0,S,E,X);
    if(matrix->solution[i][j]!=0) return solve_sudoku(matrix,i,j+1,S,E,X);
    
    for(int num = S;num != E + X;num = num + X){
        if(!clash(matrix->solution,i,j,num)){
            matrix->solution[i][j]=num;
            if(solve_sudoku(matrix,i,j+1,S,E,X)){
                return 1;
            }
            matrix->solution[i][j]=0;
        }
    }
    return 0;
}
int unique_solution(int box[9][9]){
    sudoku tempbox1;
    sudoku tempbox2;
    copy_box1_to_box2(box,tempbox1.solution);
    copy_box1_to_box2(box,tempbox2.solution);
    solve_sudoku(&tempbox1,0,0,1,9,1);
    solve_sudoku(&tempbox2,0,0,9,1,-1);
    if(is_box1_equal_to_box2(tempbox1.solution,tempbox2.solution)) return 1; //if both solutions are equal, that means unique solution
    return 0;
}
void puzzle_generator(sudoku *matrix,int visited[82],int steps){
    if(steps==0) return ;
    int index = select_random_grid(visited,steps);
    int x = (index-1)/9;
    int y = (index-1)%9;
    int store = matrix->puzzle[x][y];
    matrix->puzzle[x][y] = 0;
    if(!unique_solution(matrix->puzzle)){
        matrix->puzzle[x][y]=store;    //restore 
    }
    puzzle_generator(matrix,visited,steps-1);
}
void generate_puzzle(sudoku *matrix){
    int visited[82];
    for(int i=0;i<=81;i++){
        visited[i]=1;
    }
    puzzle_generator(matrix,visited,81);
}
void diagonal_solve(sudoku *puzzle){
    for(int diag =0 ;diag<=6;diag+=3){
        int numvisited[10];
        int cellvisited[10];
        for(int i=0;i<10;i++){
            numvisited[i] = cellvisited[i] = 1;
        }
        for(int emptyboxes=9;emptyboxes>=1;emptyboxes--){
            int cell = select_random_number(puzzle->solution,cellvisited,emptyboxes);
            int num = select_random_number(puzzle->solution,numvisited,emptyboxes);
            int x = (cell-1)/3;
            int y = (cell-1)%3;
            puzzle->solution[diag+x][diag+y] = num;
        }
    }
}
int validinput(int box[9][9],int i,int j,int num){
    if(num<1 || num>9) return 0;
    if(box[i][j]!=0) return 0;
    if(clash(box,i,j,num)) return 0;
    return 1;
}
void get_a_hint(sudoku *current,sudoku *matrix){
    int count=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(current->puzzle[i][j]==0) count++;
        }
    }  
    int number = rand()%count +1;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(current->puzzle[i][j]==0) number--;
            if(number==0){
                printf("At (%d,%d) the number is %d\n",i,j,matrix->solution[i][j]);
                current->puzzle[i][j] = matrix->solution[i][j];
                return;
            }
        }
    }

}
void undo_move(int box[9][9],int puzzle[9][9]){
    printparallel(box,puzzle);
    printf("Sudoku given on right side is the puzzle question\n");
    int i,j;
    printf("Enter the coordinates of your input where you want to erase\n");
    scanf("%d%d",&i,&j);
    if(puzzle[i][j]!=0){
        printf("Invalid coordinates!\n Chosen coordinates are not inputted by user by are part of puzzle\n");
    }
    else if(box[i][j]==0){
        printf("Chosen coordinates is already blank\n");
    }
    else{
        box[i][j] = 0;
    }
}
void takeinput(int box[9][9]){
    printf("Enter coordinates and number in format: row col num\n");
    int i,j,num;
    scanf("%d%d %d",&i,&j,&num);
    if(validinput(box,i,j,num)){
        box[i][j]=num;
    }
    else{
        printf("Invalid entry! Try again\n");
    }
}
void fill_k_empty_boxes(sudoku *matrix,int k){
    int total_empty_boxes=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(matrix->puzzle[i][j]==0) total_empty_boxes++;
        }
    }  
    while(k--){
        int number = rand()%total_empty_boxes +1;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(matrix->puzzle[i][j]==0) number--;
                if(number==0){
                    matrix->puzzle[i][j] = matrix->solution[i][j];
                    goto out;
                }
            }
        }
        out:
        total_empty_boxes--;
    }
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
void play_sudoku(sudoku *matrix){
    difficulty_mode(matrix);
    printbox(matrix->puzzle);
    sudoku current;
    copy_box1_to_box2(matrix->puzzle,current.puzzle);
    while(!is_box1_equal_to_box2(current.puzzle,matrix->solution)){
        int choice;
        printf("Press 1 to enter your next input\n");
        printf("Press 2 to get a hint\n");
        printf("Press 3 to undo a move\n");
        printf("Press 4 to get the solution of this puzzle\n");
        printf("Press -1 to quit the game\n");
        printf("\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: takeinput(current.puzzle);
            break;
            case 2: get_a_hint(&current,matrix);
            break;
            case 3: undo_move(current.puzzle,matrix->puzzle);
            break;
            case 4: printparallel(current.puzzle,matrix->solution);
                    return;
            break;
            case -1: return;
            break;
            defult: printf("Invalid entry, Please check menu\n");
        }
        printbox(current.puzzle);
    }
    printf("Congratulations!\n You have solved the puzzle.\n");
}
void play(){
    sudoku matrix;
    init(&matrix);
    diagonal_solve(&matrix);
    solve_sudoku(&matrix,0,0,1,9,1);
    copy_box1_to_box2(matrix.solution,matrix.puzzle);
    generate_puzzle(&matrix);
    play_sudoku(&matrix);
}
void input(){
    sudoku matrix;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            scanf("%d",&matrix.puzzle[i][j]);
        }
    }

    while(1){
        int choice;
        printf("Press 1 if you want to solve the inputted puzzle yourself\n");
        printf("Press 2 to get the solution of this puzzle\n");
        printf("Press -1 to exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: play_sudoku(&matrix);
            break; 
            case 2: solve_sudoku(&matrix,0,0,1,9,1);
                    printbox(matrix.solution);
            break;
            case -1: return;
            default : 
            printf("Invalid entry, please check the menu and retry again\n");
        }
    }
}
int main(){
    srand(time(0));
    int choice;
    while(1){
        printf("Press 1 to play a random sudoku game\n");
        printf("Press 2 to input a sudoku\n");
        printf("Press -1 to exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: play();
            break;
            case 2: input();
            break;
            case -1: goto out;
            default:
            printf("Invalid entry!, please check the menu and try again\n");
        }
    }
    out:

return 0;
}