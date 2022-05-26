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

void save_progress(sudoku*,sudoku*,char *);
void generate_puzzle(sudoku*);
void get_a_hint(sudoku*);
void fill_k_empty_boxes(sudoku*,int);
void diagonal_solve(sudoku*);
void copy_box1_to_box2(int **box1,int **box2);
void init(sudoku*);
int validinput(int **box,int,int,int);
void printparallel(int **box1,int **box2);
void printbox(int **box);
int is_box1_equal_to_box2(int **box1,int **box2);
int solve_sudoku(int **box,int,int,int,int,int);
int isvalidsudoku(int **box);
void difficulty_mode(sudoku*,int);
void play(int);

#include "printfunctions.h"
#include "helperfunctions.h"
#include "sudoku_algorithms.h"
#include "filedirectory.h"

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
static void menu_event(GtkWidget *widget,gpointer data){
    const char *label = gtk_menu_item_get_label(GTK_MENU_ITEM(widget));
    if(strcmp(label,"Easy")==0 || strcmp(label,"Medium")==0 || strcmp(label,"Hard")==0){
        if(strcmp(label,"Easy")==0) play(EASY);
        if(strcmp(label,"Medium")==0) play(MEDIUM);
        if(strcmp(label,"Hard")==0) play(HARD);
        load_gpuzzle(matrix.puzzle);
        copy_box1_to_box2(matrix.puzzle,current.puzzle);
    }
    else if(strcmp(label,"Rules")==0 || strcmp(label,"About")==0 ){
        if(strcmp(label,"About")==0){
            open_dialog("Project: Sudoku Generator and Solver Using C with Gtk\nName: Zubin Shah\nRoll number: 20CSE1030");
        }
        if(strcmp(label,"Rules")==0){
           const char rules[400] = "Rule 1 - Each row must contain the numbers from 1 to 9, without repetitions\nRule 2 - Each column must contain the numbers from 1 to 9, without repetitions\nRule 3 - The digits can only occur once per block\nEach puzzle has a unique solution\nPress the play button and select the difficulty level to get started";
           open_dialog(rules);
        }
    }
    else if(strcmp(label,"Open")==0){
        GtkWidget *dialog;
        dialog = gtk_file_chooser_dialog_new("Choose a File",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,"_Cancel",GTK_RESPONSE_CANCEL,"_Ok",GTK_RESPONSE_OK,NULL);
        gtk_widget_show_all(dialog);
        gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
        if(resp==GTK_RESPONSE_OK){
            open_progress(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
            load_gpuzzle(current.puzzle);
        }
        gtk_widget_destroy(dialog);
    }
    else if(strcmp(label,"Save")==0){
        load_puzzle(current.puzzle);
        GtkWidget *dialog;
        dialog = gtk_file_chooser_dialog_new("Save",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_SAVE,"_Cancel",GTK_RESPONSE_CANCEL,"_Ok",GTK_RESPONSE_OK,NULL);
        int save_flag = 0;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(strcmp(gtk_entry_get_text(GTK_ENTRY(gmatrix[i][j]))," ")!=0){
                    save_flag = 1;
                    break;
                }
            }
            if(save_flag) break;
        }
        if(save_flag){
            gtk_widget_show_all(dialog);
            gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
            if(resp == GTK_RESPONSE_OK){
                save_progress(&matrix,&current,gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
                gtk_widget_destroy(dialog);
            }
            else{
                gtk_widget_destroy(dialog);
            }
        }
        else open_dialog("Empty file cannot be saved");
    }
}
void reset(GtkWidget *widget,gpointer){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(matrix.puzzle[i][j]!=0){
                char data[2];
                strcpy(data,"0");
                sprintf(data,"%d",matrix.puzzle[i][j]);
                gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]),data);
            }
            else gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j])," ");
        }
    }
}
void solve_gtk_sudoku(GtkWidget *widget,gpointer data){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            char data[2];
            strcpy(data,"0");
            sprintf(data,"%d",matrix.solution[i][j]);
            gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]),data);
        }
    }
}
void hint_gtk_sudoku(GtkWidget *widget,gpointer data){
    load_puzzle(current.puzzle);
    get_a_hint(&current);
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



    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);
    gtk_main();

return 0;
}
