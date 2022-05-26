int rowclash(int box[N][N],int i,int j,int num){
    for(int col=0; col<N;col++){
        if(col!=j && box[i][col]==num) return 1;
    }
    return 0;
}
int columnclash(int box[N][N],int i,int j,int num){
    for(int row=0; row<N;row++){
        if(row!=i && box[row][j]==num) return 1;
    }
    return 0;
}
int boxclash(int box[N][N],int i,int j,int num){
    int xcor[2*M-1],ycor[2*M-1];
    for(int i=0;i<2*M-1;i++){
        xcor[i] = i - M + 1;
        ycor[i] = i - M + 1;
    }
    int xll =  M-1 - i%M ; // x lower limit
    int xul =  2*(M-1) - i%M; // x upper limit
    int yll =  M-1 - j%M ; // y lower limit
    int yul =  2*(M-1) - j%M ; // y upper limit
    
    for(int x = xll ; x <= xul;x++){
        int xnew = i + xcor[x];
        for(int y = yll ; y <= yul;y++){
            int ynew = j + ycor[y];
            if(!(xnew==i && ynew==j)&& box[xnew][ynew]==num) return 1;
        }
    }
    return 0;
}
int clash(int box[N][N],int i,int j,int num){
    if(rowclash(box,i,j,num)) return 1;
    if(columnclash(box,i,j,num)) return 1;
    if(boxclash(box,i,j,num)) return 1;
    return 0;
}
int is_box1_equal_to_box2(int box1[N][N],int box2[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(box1[i][j]!=box2[i][j]) return 0;
        }
    }
    return 1; //if all elements are equal then both are duplicates
}
int isvalidsudoku(int box[N][N]){

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(box[i][j]!=0){
                if(box[i][j]<0 || box[i][j]>N) return 0;
                if(clash(box,i,j,box[i][j])){
                    return 0;
                }
            }
        }
    }
    return 1;
}
int select_random_number(int box[N][N],int numvisited[N+1],int no_of_num_left){
    int n=no_of_num_left;
    int num = (rand()%n) +1;
    int count=0;
    for(int i=1;i<=N;i++){
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
int unique_solution(int box[N][N]){
    sudoku tempbox;
    copy_box1_to_box2(box,tempbox.puzzle);
    copy_box1_to_box2(box,tempbox.solution);
    solve_sudoku(tempbox.puzzle,0,0,1,N,1);
    solve_sudoku(tempbox.solution,0,0,N,1,-1);
    if(is_box1_equal_to_box2(tempbox.puzzle,tempbox.solution)) return 1;
    else return 0;
}
int validinput(int box[N][N],int i,int j,int num){
    if(num<1 || num>N) return 0;
    if(box[i][j]!=0) return 0;
    if(clash(box,i,j,num)) return 0;
    return 1;
}
void init(sudoku *puzzle){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            puzzle->puzzle[i][j]=0;
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            puzzle->solution[i][j]=0;
        }
    }
}
void copy_box1_to_box2(int box1[N][N],int box2[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            box2[i][j]=box1[i][j];
        }
    }
}
