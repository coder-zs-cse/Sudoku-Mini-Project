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
