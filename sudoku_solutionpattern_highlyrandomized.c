#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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
int clash(int box[9][9],int i,int j,int num){
    if(rowclash(box,i,j,num)) return 1;
    if(columnclash(box,i,j,num)) return 1;
    if(boxclash(box,i,j,num)) return 1;
    return 0;
}
int solvesudoku(int box[9][9],int grid[82],int steps,int rowvisit[9][9],int colvisit[9][9]){
    if(steps==0){
        return 1;
    }
    srand(time(0));
    int pseudoindex = (rand() % steps) + 1;
    int count1=0,index;
    for(int it=1;it<=81;it++){
        if(grid[it]==1){
            count1++;
        }
        if(count1==pseudoindex){
            index =it;
            break;
        }
    }
    grid[index] = 0;
    int x = (index-1)/9;
    int y = (index-1)%9;

    int check[11];
    for(int i=0;i<=10;i++) check[i]=1;

    for(int it=9;it>=1;it--){
        srand(time(0));     
        int pseudonum = (rand() % it) +1;
        int count=0,num;
        for(int z=1;z<=9;z++){
            if(check[z]==1) {
                count++;
            }
            if(count==pseudonum) {
                num = z;
                break;
            }
        }
        if(rowvisit[x][num-1] && colvisit[y][num-1] && !boxclash(box,x,y,num)){
            box[x][y]=num;
            colvisit[y][num-1]=0;
            rowvisit[x][num-1]=0;
            if(solvesudoku(box,grid,steps-1,rowvisit,colvisit)){
                return 1;
            }
            box[x][y]=0;
            colvisit[y][num-1]=1;
            rowvisit[x][num-1]=1;
        }
        check[num] = 0;
    }
    grid[index]=1;
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
    int rowvisit[9][9];
    int colvisit[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            box[i][j]=0;
            rowvisit[i][j]=1;
            colvisit[i][j]=1;
        }
    }
    int check[82];
    for(int i=0;i<=81;i++){
        check[i]=1;
    }
    // printf("i am here");
    solvesudoku(box,check,81,rowvisit,colvisit);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            printf("%d ",box[i][j]);
            if(j!=8 && j%3==2) printf("| ");
        }
        if(i!=8 && i%3==2) {
    printf("\n");
            for(int x=0;x<21;x++) printf("-");
        }
    printf("\n");
    }
    printf("\n");
    
}
int main(){
    solve();
return 0;
}