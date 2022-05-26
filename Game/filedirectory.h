void open_progress(char *file_path){
    FILE *pointer = fopen(file_path,"r");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fscanf(pointer,"%d",(&matrix.puzzle[i][j]));
            matrix.puzzle[i][j]-=1;
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fscanf(pointer,"%d",&matrix.solution[i][j]);
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fscanf(pointer,"%d",&current.puzzle[i][j]);
        }
    }
    fclose(pointer);
    printbox(current.puzzle);

}
void save_progress(char *file_path){
    FILE *pointer = fopen(file_path,"w+");
    printparallel(matrix.puzzle,matrix.solution);
    if(!pointer){
        printf("Couldn't save the progress due to a file error\n");
    }
    else{
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(pointer,"%d ",matrix.puzzle[i][j]+1);
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(pointer,"%d ",matrix.solution[i][j]);
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(pointer,"%d ",current.puzzle[i][j]);
            }
        }
        fclose(pointer);
    }

}
