void difficulty_mode(sudoku *matrix){
    int k;
    while(1){
        int choice;
        printf("Press 1 to play a easy mode sudoku game\n");
        printf("Press 2 to play a medium mode sudoku game\n");
        printf("Press 3 to play a hard mode sudoku game\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1: k = rand() % 10 + 20;
            goto out;
        case 2: k = rand() % 10 + 10;
            goto out;
        case 3: 
            return;
        default:
        printf("Invalid entry!, please check the menu and try again\n");
        }
    }
    out:
    fill_k_empty_boxes(matrix,k);
}

void play_sudoku(sudoku *matrix,sudoku *current,int numberofhints){
    
    while(!is_box1_equal_to_box2(current->puzzle,matrix->solution)){
        int choice;
        printf("Press 1 to enter your next input\n");
        printf("Press 2 to get a hint\n");
        printf("Press 3 to erase an input\n");
        printf("Press 4 to save the current progress for later and close\n");
        printf("Press 5 to get the solution of this puzzle\n");
        printf("Press -1 to quit the game\n");
        printf("\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: takeinput(current->puzzle);
            break;
            case 2: get_a_hint(current,matrix);
                    numberofhints++;
            break;
            case 3: erase_input(current->puzzle,matrix->puzzle);
            break;
            case 4: save_progress(matrix,current,numberofhints);
                    return;
            case 5: printparallel(current->puzzle,matrix->solution);
                    return;
            break;
            case -1: return;
            break;
            default: printf("Invalid entry, Please check menu\n");
        }
        printbox(current->puzzle);
        printf("Hints taken so far : %d\n",numberofhints);
    }
    printf("Congratulations!\nYou have solved the puzzle with %d hints\n",numberofhints);
}

void load_and_play_sudoku(sudoku *matrix){
    difficulty_mode(matrix);
    printbox(matrix->puzzle);
    sudoku current;
    copy_box1_to_box2(matrix->puzzle,current.puzzle);
    int numberofhints=0;
    play_sudoku(matrix,&current,numberofhints);
}
void play(){
    sudoku matrix;
    init(&matrix);
    diagonal_solve(&matrix);
    solve_sudoku(&matrix,0,0,1,N,1);
    copy_box1_to_box2(matrix.solution,matrix.puzzle);
    generate_puzzle(&matrix);
    load_and_play_sudoku(&matrix);
}

void input(){
    sudoku matrix;
    printf("Enter the values of the sudoku cells from left to right up to down\n");
    printf("Enter 0 to indicate a blank space\n\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&matrix.puzzle[i][j]);
        }
    }
    if(!isvalidsudoku(matrix.puzzle)){
        printf("\nInputted sudoku is incorrect\n");
        return;
    }
    copy_box1_to_box2(matrix.puzzle,matrix.solution);
    solve_sudoku(&matrix,0,0,1,N,1);
    sudoku current;
    copy_box1_to_box2(matrix.puzzle,current.puzzle);
    while(1){
        int choice;
        printf("Press 1 if you want to solve the inputted puzzle yourself\n");
        printf("Press 2 to get the solution of this puzzle\n");
        printf("Press -1 to exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: 
                    printbox(current.puzzle);
                    play_sudoku(&matrix,&current,0);
            case 2: printbox(matrix.solution);
            case -1: return;
            default : 
            printf("Invalid entry, please check the menu and retry again\n");
        }
    }
}