#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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
int duplicate_grid(int box1[9][9],int box2[9][9]){
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
int select_random_grid(int box[9][9],int grid[82],int no_of_grids_left){
    int n=no_of_grids_left;
    int number = (rand() % n) + 1;
    int count1=0,index;
    for(int it=1;it<=81;it++){
        if(grid[it]==1){
            count1++;
        }
        if(count1==number){
            index =it;
            break;
        }
    }
    grid[index] = 0;
    return index;
}
int solve_sudoku(int box[9][9],int i,int j,int S,int E,int X){
    if(i==8 && j==9)  {
        return 1;
    }
    if(j==9)  return solve_sudoku(box,i+1,0,S,E,X);
    if(box[i][j]!=0) return solve_sudoku(box,i,j+1,S,E,X);
    
    for(int num = S;num != E + X;num = num + X){
        if(!clash(box,i,j,num)){
            box[i][j]=num;
            if(solve_sudoku(box,i,j+1,S,E,X)){
                return 1;
            }
            box[i][j]=0;
        }
    }
    return 0;
}
int unique_solution(int box[9][9]){
    int tempbox1[9][9];
    int tempbox2[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            tempbox1[i][j]=box[i][j];
            tempbox2[i][j]=box[i][j];
        }
    }
    solve_sudoku(tempbox1,0,0,1,9,1);
    solve_sudoku(tempbox2,0,0,9,1,-1);
    if(duplicate_grid(tempbox1,tempbox2)) return 1; //if both solutions are equal, that means unique solution
    return 0;
}
void puzzle_generator(int box[9][9],int grid[82],int steps){
    if(steps==0) return ;
    int index = select_random_grid(box,grid,steps);
    int x = (index-1)/9;
    int y = (index-1)%9;
    int store = box[x][y];
    box[x][y] = 0;
    if(!unique_solution(box)){
        box[x][y]=store;    //restore 
    }
    puzzle_generator(box,grid,steps-1);
}
void generate_puzzle(int box[9][9]){
    int check[82];
    for(int i=0;i<=81;i++){
        check[i]=1;
    }
    puzzle_generator(box,check,81);
}
void diagonal_solve(int box[9][9]){
    for(int diag =0 ;diag<=6;diag+=3){
        int numvisited[10];
        int cellvisited[10];
        for(int i=0;i<10;i++){
            numvisited[i] = cellvisited[i] = 1;
        }
        for(int emptyboxes=9;emptyboxes>=1;emptyboxes--){
            int cell = select_random_number(box,cellvisited,emptyboxes);
            int num = select_random_number(box,numvisited,emptyboxes);
            int x = (cell-1)/3;
            int y = (cell-1)%3;
            box[diag+x][diag+y] = num;
        }
    }
}
int validinput(int box[9][9],int i,int j,int num){
    if(num<1 || num>9) return 0;
    if(box[i][j]!=0) return 0;
    if(clash(box,i,j,num)) return 0;
    return 1;
}
void get_a_hint(int box[9][9],int solution[9][9]){
    int count=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(box[i][j]==0) count++;
        }
    }  
    int number = rand()%count +1;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(box[i][j]==0) number--;
            if(number==0){
                printf("At (%d,%d) the number is %d\n",i,j,solution[i][j]);
                box[i][j] = solution[i][j];
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
void play(int puzzle[9][9]){
    int box[9][9];
    int solution[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            solution[i][j] = box[i][j] = puzzle[i][j];
        }
    }
    solve_sudoku(solution,0,0,1,9,1);
    while(!duplicate_grid(box,solution)){
        int choice;
        printf("Press 1 to enter your next input\n");
        printf("Press 2 to get a hint\n");
        printf("Press 3 to undo a move\n");
        printf("Press 4 to get the solution of this puzzle\n");
        printf("Press -1 to quit the game\n");
        printf("\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: takeinput(box);
            break;
            case 2: get_a_hint(box,solution);
            break;
            case 3: undo_move(box,puzzle);
            break;
            case -1: return;
            break;
            case 4: printparallel(box,solution);
            break;
            defult: printf("Invalid entry, Please check menu\n");
        }
        printbox(box);
    }
    printf("Congratulations!\n You have solved the puzzle.\n");
}
void solve(){
    int box[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            box[i][j]=0;
        }
    }
    diagonal_solve(box);
    solve_sudoku(box,0,0,1,9,1);
    generate_puzzle(box);
    printbox(box);
    play(box);
}
void input(){
    int puzzle[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            scanf("%d",&puzzle[i][j]);
        }
    }
    while(1){
        int choice;
        printf("Press 1 if you want to solve the inputted puzzle yourself\n");
        printf("Press 2 to get the solution of this puzzle\n");
        printf("Press -1 to exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: play(puzzle);
            break; 
            case 2: solve_sudoku(puzzle,0,0,1,9,1);
                    printbox(puzzle);
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
            case 1: solve();
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