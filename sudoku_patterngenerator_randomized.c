#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define take(n) int n;scanf("%d",&n)
void printbox(int box[9][9]){
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
int unique(int box1[9][9],int box2[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(box1[i][j]!=box2[i][j]) return 0;
        }
    }
    return 1;
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


int solvesudoku(int box[9][9],int i,int j){
    if(i==8 && j==9)  return 1;
    if(j==9)  return solvesudoku(box,i+1,0);
    if(box[i][j]!=0) return solvesudoku(box,i,j+1);
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
        if(!rowclash(box,i,j,num) && !columnclash(box,i,j,num) && !boxclash(box,i,j,num)){
            box[i][j]=num;
            if(solvesudoku(box,i,j+1)){
                return 1;
            }
            box[i][j]=0;
        }
        check[num]=0;
    }
    return 0;
}
void diagonal_solve(int box[9][9]){
    
    for(int inc =0 ;inc<=6;inc+=3){
        int checknum[10];
        int checkcell[10];
        for(int i=0;i<10;i++){
            checknum[i] = checkcell[i] = 1;
        }
        for(int it=9;it>=1;it--){
            int cell = (rand()%it) +1;
            int count=0;
            for(int i=1;i<=9;i++){
                if(checkcell[i]==1){
                    count++;
                }
                if(count==cell){
                    cell = i;
                    break;
                }
            }
            checkcell[cell] = 0;
            // srand(time(0));
            int num = (rand()%it) +1;
            count=0;
            for(int i=1;i<=9;i++){
                if(checknum[i]==1){
                    count++;
                }
                if(count==num){
                    num = i;
                    break;
                }
            }
            checknum[num]=0;
            cell--;
            int x = cell/3;
            int y = cell%3;
            box[inc+x][inc+y] = num;
        }
    }
}
void solve(){
    int box[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            box[i][j]=0;
        }
    }
    diagonal_solve(box);
    solvesudoku(box,0,0);
    printbox(box);
    
}
int main(){
    solve();
return 0;
}