
void diagonal_solve(sudoku *puzzle){
    for(int diag =0;diag<N;diag+=M){
        int numvisited[N+1];
        int cellvisited[N+1];
        for(int i=0;i<=N;i++){
            numvisited[i] = cellvisited[i] = 1;
        }
        for(int emptyboxes=N;emptyboxes>=1;emptyboxes--){
            int cell = select_random_number(puzzle->solution,cellvisited,emptyboxes);
            int num = select_random_number(puzzle->solution,numvisited,emptyboxes);
            int x = (cell-1)/M;
            int y = (cell-1)%M;
            puzzle->solution[diag+x][diag+y] = num;
        }
    }
}
int solve_sudoku(int solution[N][N],int i,int j,int S,int E,int T){
    if(i==N)  return 1;
    if(j==N)  return solve_sudoku(solution,i+1,0,S,E,T);
    if(solution[i][j]!=0) return solve_sudoku(solution,i,j+1,S,E,T);
    for(int num = S;num != E + T;num = num + T){
        if(!clash(solution,i,j,num)){
            solution[i][j]=num;
            if(solve_sudoku(solution,i,j+1,S,E,T)){
                return 1;
            }
            solution[i][j]=0;
        }
    }
    return 0;
}
int select_random_grid(int visited[N*N+1],int no_of_grids_left){
    int n=no_of_grids_left;
    int number = (rand() % n) + 1;
    int count1=0,index;
    for(int it=1;it<=N*N;it++){
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
void puzzle_generator(sudoku *matrix,int visited[N*N+1],int steps){
    if(steps==0) return ;
    int index = select_random_grid(visited,steps);
    int x = (index-1)/N;
    int y = (index-1)%N;
    int store = matrix->puzzle[x][y];
    matrix->puzzle[x][y] = 0;
    if(!unique_solution(matrix->puzzle)){
        matrix->puzzle[x][y]=store;    //restore 
    }
    puzzle_generator(matrix,visited,steps-1);
}
void fill_k_empty_boxes(sudoku *matrix,int k){
    int total_empty_boxes=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(matrix->puzzle[i][j]==0) total_empty_boxes++;
        }
    }  
    while(k--){
        int number = rand()%total_empty_boxes +1;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
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
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(current->puzzle[i][j]==0) count++;
        }
    }  
    int number = rand()%count +1;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(current->puzzle[i][j]==0) number--;
            if(number==0){
                printf("At (%d,%d) the number is %d\n",i,j,matrix->solution[i][j]);
                current->puzzle[i][j] = matrix->solution[i][j];
                return;
            }
        }
    }

}
void erase_input(int box[N][N],int puzzle[N][N]){
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

void generate_puzzle(sudoku *matrix){
    int visited[N*N+1];
    for(int i=0;i<=N*N;i++){
        visited[i]=1;
    }
    puzzle_generator(matrix,visited,N*N);
}

