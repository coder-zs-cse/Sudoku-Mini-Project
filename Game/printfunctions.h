void printbox(int **box){
    for(int i=0;i<M;i++)printf(" ");
    for(int i=0;i<N;i++){
        if(i%M==0) printf(" ");
        printf("%d ",i);
    }
    printf("\n");
    for(int i=0;i<28;i++) {
        printf("_");
    }
    printf("\n");
    for(int i=0;i<N;i++){
        printf("%d |  ",i);
        for(int j=0;j<N;j++){
            if(box[i][j]!=0)
            printf("%d ",box[i][j]);
            else printf("_ ");
            if(j!=N-1 && j%M==M-1) printf("| ");
        }
        if(i!=N-1 && i%M==M-1) {
        printf("\n");
            for(int x=0;x<26;x++) printf("-");
        }
        printf("\n");
    }
    printf("\n");
}
void printparallel(int **box1,int **box2){
    for(int i=0;i<M;i++)printf(" ");
    for(int i=0;i<N;i++){
        if(i%M==0) printf("  ");
        printf("%d ",i);
    }
    printf("    ");
    for(int i=0;i<M;i++)printf(" ");
    for(int i=0;i<N;i++){
        if(i%M==0) printf("  ");
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
    for(int i=0;i<N;i++){
        printf("%d |  ",i);
        for(int j=0;j<N;j++){
            if(box1[i][j]!=0)
            printf("%d ",box1[i][j]);
            else printf("_ ");
            if(j!=N-1 && j%M==M-1) printf("| ");
        }
        printf("    ");
        printf("%d |  ",i);
        for(int j=0;j<N;j++){
            if(box2[i][j]!=0)
            printf("%d ",box2[i][j]);
            else printf("_ ");
            if(j!=N-1 && j%M==M-1) printf("| ");
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