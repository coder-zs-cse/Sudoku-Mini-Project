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
                if(box[i][j]<0 || box[i][j]>9) return 0;
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
int validinput(int box[9][9],int i,int j,int num){
    if(num<1 || num>9) return 0;
    if(box[i][j]!=0) return 0;
    if(clash(box,i,j,num)) return 0;
    return 1;
}
