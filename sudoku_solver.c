#include<stdio.h>
#include<stdlib.h>
#define take(n) int n;scanf("%d",&n)
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
    int xll =  2 - i%3 ;
    int xul =  4 - i%3 ;
    int yll =  2 - j%3 ;
    int yul =  4 - j%3 ;
    
    for(int x = xll ; x <= xul;x++){
        int xnew = i + xcor[x];
        for(int y = yll ; y <= yul;y++){
            int ynew = j + ycor[y];
            if(!(xnew==i && ynew==j)&& box[xnew][ynew]==num) return 1;
        }
    }
    return 0;
}
int solvesudoku(int box[9][9],int i,int j,int S,int E,int X){

    if(i==8 && j==9)  {
        return 1;
    }
    if(j==9)  return solvesudoku(box,i+1,0,S,E,X);
    if(box[i][j]!=0) return solvesudoku(box,i,j+1,S,E,X);
    
    for(int num = S;num != E + X;num = num + X){
        if(!rowclash(box,i,j,num) && !columnclash(box,i,j,num) && !boxclash(box,i,j,num)){
            box[i][j]=num;
            if(solvesudoku(box,i,j+1,S,E,X)){
                return 1;
            }
            box[i][j]=0;
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
int unique(int box1[9][9],int box2[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(box1[i][j]!=box2[i][j]) return 0;
        }
    }
    return 1;
}
void solve(){
    int box[9][9];
    printf("Enter the sudoku puzzle\nEnter 0 in blank spaces\n");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            scanf("%d",&box[i][j]);
        }
    }
    printf("\n");
    if(!isvalidsudoku(box)){
        printf("Given sudoku is invalid\n");
    }
    else{
        int box2[9][9];
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                box2[i][j] = box[i][j];
            }
        }
        solvesudoku(box,0,0,1,9,1);
       
        solvesudoku(box2,0,0,9,1,-1);
           
        if(unique(box,box2)){
            for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                    printf("%d ",box[i][j]);
                }
            printf("\n");
            }
            printf("\n");
        }   
        else{
            printf("No unique solution exists to this sudoku, hence unsolvable\n");
            int choice;
            printf("Do you want to print any two solution to this sudoku?\n");
            printf("Press 1 to get any two solution\nPress 0 to exit\n");
            scanf("%d",&choice);
            if(choice==1){
                for(int i=0;i<9;i++){
                    for(int j=0;j<9;j++){
                        printf("%d ",box[i][j]);
                    }
                    printf(" ");
                    for(int j=0;j<9;j++){
                        printf("%d ",box2[i][j]);
                    }
                printf("\n");
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}
int main(){
    solve();
return 0;
}