int get_all_files(){
    int total_num_files=0,file_number=0;
    struct dirent *dir;
    
    DIR *d = opendir(save_sudoku.folderpath);
    if(d==NULL) return 0;
    else{
        while((dir=readdir(d))!=NULL){
            file_number++;
            if(file_number>2) printf("%d. %s\n",file_number-2,dir->d_name);
        }
        closedir(d);
        total_num_files = file_number-2;
    }
    return total_num_files;
}
void get_file_location(char *file_path,int choice,int total_num_files){
    DIR *d = opendir(save_sudoku.folderpath);
    struct dirent *dir;
    while((dir=readdir(d))!=NULL){
        choice--;
        if(choice==-2){
            strcat(file_path,save_sudoku.folderpath);
            strcat(file_path,dir->d_name);
            closedir(d);
            return;
        }
    }
    closedir(d);
}
int get_saved_progress_file(char *file_path,int total_num_files){
    
    if(total_num_files==0){
        return 0;
    }
    int choice;
    while(1){
        printf("Enter the sudoku saved progress file number you want to load\n");
        scanf("%d",&choice);
        if(choice<1 || choice>total_num_files){
            printf("Invalid entry please enter the correct file number\n");
        }
        else  break;
    }
    get_file_location(file_path,choice,total_num_files);

}
int take_new_file_name_from_user(char *file_path,Folder save_sudoku){

    char name[50];
    printf("Please enter a label to save your progress file with\n");
    scanf("%s",name);
    strcat(name,".txt");
    file_path[0]='\0';
    strcat(file_path,save_sudoku.folderpath);
    strcat(file_path,name);
    FILE *temp = fopen(file_path,"r");
    if(temp!=NULL) return 1;
    return 0;
}
void open_progress(int total_num_of_files){
    if(total_num_of_files==0){
        printf("No files available\n");
        return;
    }
    char file_path[50]="\0";
    get_saved_progress_file(file_path,total_num_of_files);
    
    sudoku matrix,current;
    int numberofhints=0;
    FILE *pointer = fopen(file_path,"r");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fscanf(pointer,"%d",&matrix.puzzle[i][j]);
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
    fscanf(pointer,"%d",&numberofhints);
    fclose(pointer);
    printbox(current.puzzle);
    play_sudoku(&matrix,&current,numberofhints);
    
}
void save_progress(sudoku *matrix,sudoku *current,int numberofhints){
    DIR *d = opendir(save_sudoku.folderpath);
    if(d==NULL){
        int check = mkdir(save_sudoku.foldername);
        d = opendir(save_sudoku.folderpath);
    }
    FILE *pointer;
    char file_path[50];
    int file_already_present;
    do{
        file_already_present =take_new_file_name_from_user(file_path,save_sudoku);
        if(file_already_present==1){
            printf("There already exists a file with this name\n");
            printf("Please enter a new label\n");
        }
    }while(file_already_present!=0);
    pointer = fopen(file_path,"w+");

    if(!pointer){
        printf("Couldn't save the progress due to a file error\n");
    }
    else{
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(pointer,"%d ",matrix->puzzle[i][j]);
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(pointer,"%d ",matrix->solution[i][j]);
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                fprintf(pointer,"%d ",current->puzzle[i][j]);
            }
        }
        fprintf(pointer,"%d ",numberofhints);
        fclose(pointer);
    }
    fclose(pointer);
    closedir(d);
}

void delete_saved_file(int total_num_file){
    if(total_num_file==0){
        printf("There are no saved sudoku files\n");
    }
    else{
        int choice;
        while(1){
            choice;
            printf("Enter the number of file you want to delete\n");
            scanf("%d",&choice);
            if(choice>0 && choice<=total_num_file) break;
            printf("Invalid file number\n");
        }
        char file_path[50]="\0";
        get_file_location(file_path,choice,total_num_file);
        remove(file_path);
    }
}

void open_file_directory(){
    int choice;
    while(1){
    int num_of_files = get_all_files();
        printf("Press 1 : To Load and play any sudoku from this list\n");
        printf("Press 2 : Delete any progress record from this list\n");
        printf("Press -1: To exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: 
                    open_progress(num_of_files);
                    goto out;
            break;
            case 2: 
                    delete_saved_file(num_of_files);
            break;
            case -1: 
                    goto out;
            default :
                    printf("Invalid input, please check the menu and try again \n");
        }

    }
    out:
    return;
}