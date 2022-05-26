#include<gtk/gtk.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define N 9
#define M 3
enum difficulty{EASY=1,MEDIUM, HARD};

typedef struct {
    int **puzzle;
    int **solution;
}sudoku;

sudoku matrix,current;
GtkWidget *gmatrix[N][N];
GtkWidget *window;

int rowclash(int **box,int row,int col,int num);
int columnclash(int **box,int row,int col,int num);
int boxclash(int **box,int row,int col,int num);
int clash(int **box,int row,int col,int num);
void nullify_sudoku(sudoku *matrix);
void open_progress(char *file_path);
void save_progress(char *file_path);
void generate_puzzle(sudoku* matrix);
void get_a_hint(sudoku* current);
void fill_k_empty_boxes(sudoku* matrix,int k);
void diagonal_solve(sudoku* matrix);
void copy_box1_to_box2(int **box1,int **box2);
void init(sudoku* matrix);
int validinput(int **box,int,int,int);
void printparallel(int **box1,int **box2);
void printbox(int **box);
int is_box1_equal_to_box2(int **box1,int **box2);
int solve_sudoku(int **box,int xstart,int ystart,int xll,int yll,int incre_flag);
int isvalidsudoku(int **box);
void difficulty_mode(sudoku*,int);
int select_random_grid(int visited[N*N+1],int no_of_grids_left);
int select_random_number(int numvisited[N+1],int no_of_num_left);
void puzzle_generator(sudoku *matrix,int visited[N*N+1],int steps);
void play(int);

#include "printfunctions.h"
#include "helperfunctions.h"
#include "sudoku_algorithms.h"
#include "filedirectory.h"
#include "gtk_callback_functions.h"

void open_dialog(const char* str){
    GtkWidget *label, *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons("Sudoku",GTK_WINDOW(window),flags,"_Ok",GTK_RESPONSE_NONE,NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label = gtk_label_new(str);
    g_signal_connect_swapped(dialog,"response",G_CALLBACK(gtk_widget_destroy),dialog);
    gtk_container_add(GTK_CONTAINER(content_area),label);
    gtk_widget_show_all(dialog);
}
void set_color(int i,int j){
    int a = i/3;
    int b = j/3;
    if((a+b)%2!=0){
        const GdkRGBA blue =  {0, 0x00FF, 0x00FF, 0x0099};
        gtk_widget_override_background_color(gmatrix[i][j], GTK_STATE_NORMAL, &blue);
    }
    else{
        const GdkRGBA pink =  {0, 0x00DD, 0x00D7, 0x0000};
        gtk_widget_override_background_color(gmatrix[i][j], GTK_STATE_NORMAL, &pink);
    }
}
void load_puzzle(int **puzzle){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            const char *data = gtk_entry_get_text(GTK_ENTRY(gmatrix[i][j]));
            if(strcmp(data," ")==0){
                puzzle[i][j] = 0;
            }
            else{
                puzzle[i][j] = atoi(data);
            }
        }
    }
}
void load_gpuzzle(int **puzzle){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(puzzle[i][j]!=0){
                char data[2];
                strcpy(data,"0");
                sprintf(data,"%d",puzzle[i][j]);
                gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]),data);
            }
            else gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j])," ");
        }
    }

}

int main(int argc,char *argv[]){

    srand(time(0));
    init(&matrix);
    init(&current);

    static char *File[4] = {"New","Save","Open","Quit"};
    static char *New_File[3] = {"Easy","Medium","Hard"};
    static char *Help[2] = {"Rules","About"};

    gtk_init(&argc,&argv);
    GtkWidget *vbox, *hbox, *file_menu, *help_menu, *new_menu, *menu_item, *menu_bar, *sep, *button;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window),"Sudoku");

    menu_bar = gtk_menu_bar_new();

    menu_item = gtk_menu_item_new_with_label("FILE");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);
    file_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),file_menu);

    menu_item = gtk_menu_item_new_with_label("HELP");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);
    help_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),help_menu);

    for(int i=0;i<4;i++){
        menu_item = gtk_menu_item_new_with_label(File[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
        if(i==0){
            new_menu = gtk_menu_new();
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),new_menu);
        }
        else if(i==3) g_signal_connect(menu_item,"activate",G_CALLBACK(gtk_main_quit),NULL);
        else g_signal_connect(menu_item,"activate",G_CALLBACK(menu_event),NULL);
    }
    for(int i=0;i<3;i++){
        menu_item = gtk_menu_item_new_with_label(New_File[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(new_menu),menu_item);
        g_signal_connect(menu_item,"activate",G_CALLBACK(menu_event),NULL);
    }
    for(int i=0;i<2;i++){
        menu_item = gtk_menu_item_new_with_label(Help[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),menu_item);
        g_signal_connect(menu_item,"activate",G_CALLBACK(menu_event),NULL);
    }

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_box_pack_start(GTK_BOX(vbox),menu_bar,0,0,0);

    for(int i=0;i<N;i++){
        hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
        for(int j=0;j<N;j++){
            gmatrix[i][j] = gtk_entry_new();
            set_color(i,j);
            gtk_entry_set_max_length(GTK_ENTRY(gmatrix[i][j]),2);
            gtk_entry_set_width_chars(GTK_ENTRY(gmatrix[i][j]),2);
            gtk_box_pack_start(GTK_BOX(hbox),gmatrix[i][j],0,0,0);
            if(!(j+1)%M){
                sep = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
                gtk_box_pack_start(GTK_BOX(hbox),sep,0,0,1);
            }
        }
        if(!(i+1)%M){
                sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
                gtk_box_pack_start(GTK_BOX(vbox),sep,0,0,1);
        }
        gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j])," ");
        }
    }

    button = gtk_button_new_with_label("Show solution");
    g_signal_connect(button,"clicked",G_CALLBACK(solve_gtk_sudoku),NULL);
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);

    button = gtk_button_new_with_label("Reset");
    g_signal_connect(button,"clicked",G_CALLBACK(reset),NULL);
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);

    button = gtk_button_new_with_label("Get a hint");
    g_signal_connect(button,"clicked",G_CALLBACK(hint_gtk_sudoku),NULL);
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);

    button = gtk_button_new_with_label("Check if correct");
    g_signal_connect(button,"clicked",G_CALLBACK(check_gtk_sudoku),NULL);
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);

    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);
    gtk_main();

return 0;
}
