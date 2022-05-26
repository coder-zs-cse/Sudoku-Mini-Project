void difficulty_mode(sudoku *matrix,int DIFFICULTY_LEVEL){
    int k;
    switch(DIFFICULTY_LEVEL){
        case 1: k = rand() % 5 + 18;
            break;
        case 2: k = rand() % 5 + 10;
            break;
        case 3:
            k=0;
    }
    fill_k_empty_boxes(matrix,k);
}
void play(int DIFFICULTY_LEVEL){
    zero_sudoku(&matrix);
    diagonal_solve(&matrix);
    solve_sudoku(matrix.solution,0,0,1,N,1);
    copy_box1_to_box2(matrix.solution,matrix.puzzle);
    generate_puzzle(&matrix);
    printbox(matrix.puzzle);
    difficulty_mode(&matrix,DIFFICULTY_LEVEL);
    printbox(matrix.puzzle);
}

void diagonal_solve(sudoku *matrix){
    for(int diag =0;diag<N;diag+=M){
        int numvisited[N+1];
        int cellvisited[N+1];
        for(int i=0;i<=N;i++){
            numvisited[i] = cellvisited[i] = 1;
        }
        for(int emptyboxes=N;emptyboxes>=1;emptyboxes--){
            int cell = select_random_number(cellvisited,emptyboxes);
            int num = select_random_number(numvisited,emptyboxes);
            int x = (cell-1)/M;
            int y = (cell-1)%M;
            matrix->solution[diag+x][diag+y] = num;
        }
    }
}
int solve_sudoku(int **solution,int i,int j,int S,int E,int T){
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
void get_a_hint(sudoku *box){
    int count=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(box->puzzle[i][j]==0) count++;
        }
    }
    if(count==0) return;
    int pos = rand()%count+1;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(box->puzzle[i][j]==0) pos--;
            if(pos==0){
                char data[2];
                strcpy(data,"0");
                sprintf(data,"%d",matrix.solution[i][j]);
                gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]),data);
                current.puzzle[i][j] = matrix.solution[i][j];
            }
        }
    }
}

void generate_puzzle(sudoku *matrix){
    int visited[N*N+1];
    for(int i=0;i<=N*N;i++){
        visited[i]=1;
    }
    puzzle_generator(matrix,visited,N*N);
}

