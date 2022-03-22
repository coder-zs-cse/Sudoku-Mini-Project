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

int get_file_location(char *file_path){
    
    int total_num_files = get_all_files();
    if(total_num_files==0){
        return 0;
    }
    int choice;
    while(1){
        printf("\n\n");
        printf("Enter the sudoku saved progress file number you want to load\n");
        scanf("%d",&choice);
        if(choice<1 || choice>total_num_files){
            printf("Invalid entry please enter the correct file number\n");
        }
        else{
            break;
        }
    }
    DIR *d = opendir(save_sudoku.folderpath);
    struct dirent *dir;
    while((dir=readdir(d))!=NULL){
        choice--;
        if(choice==-2){
            strcat(file_path,save_sudoku.folderpath);
            strcat(file_path,dir->d_name);
            closedir(d);
            return 1;
        }
    }
    closedir(d);
    return 0;
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
void open_progress(){
    char file_path[50]="\0";
    int is_file_path_fetched = get_file_location(file_path);
    if(is_file_path_fetched==0){
        printf("There are no saved files\n");
    }
    else{
        sudoku matrix,current;
        int numberofhints=0;
        FILE *pointer = fopen(file_path,"r");
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                fscanf(pointer,"%d",&matrix.puzzle[i][j]);
            }
        }
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                fscanf(pointer,"%d",&matrix.solution[i][j]);
            }
        }
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                fscanf(pointer,"%d",&current.puzzle[i][j]);
            }
        }
        fscanf(pointer,"%d",&numberofhints);
        fclose(pointer);
        printbox(current.puzzle);
        play_sudoku(&matrix,&current,numberofhints);
    }
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
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                fprintf(pointer,"%d ",matrix->puzzle[i][j]);
            }
        }
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                fprintf(pointer,"%d ",matrix->solution[i][j]);
            }
        }
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                fprintf(pointer,"%d ",current->puzzle[i][j]);
            }
        }
        fprintf(pointer,"%d ",numberofhints);
        fclose(pointer);
    }
    fclose(pointer);
    closedir(d);
}

// void delete_saved_file(FILE *pointer){
//     int total_num_file = get_all_files();
//     if(total_num_file==0){
//         printf("There are no saved sudoku files\n");
//     }
//     else{
//         int choice;
//         while(1){
//             choice;
//             printf("Enter the number of file you want to delete\n");
//             scanf("%d",&choice);
//             if(choice>0 && choice<=total_num_file) break;
//             printf("Please check the menu and try a valid entry to delete\n");
//         }
//         int count_of_file=0;
//         DIR *dir = opendir(save_sudoku.folderpath);
//         struct dirent *d;
//         while((d=readdir(dir))!=NULL){
//             count_of_file++;
//             if(count_of_file==choice){
//                 char file_name[50]="\n";
//                 strcat(file_name)

//                 remove
//             }

//         }
//     }
// }
