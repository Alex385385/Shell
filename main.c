#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
//#include <gtk/gtk.h>
#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gtk/gtkx.h>
#include <signal.h>
#include <math.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/wait.h>


GtkWidget *window;
GtkWidget *textfield;
GtkTextBuffer *textBuffer;
GtkBuilder *builder;
GtkTextTag *textTag;
GtkTextIter start, end;
GtkTextIter iter;
char *command, cmds[20] = "";
//cd - Change directory
//Use chdir()
void changeDirectory(char* dir) {

    char s[100];
    char *ptr;

    chdir(dir);

    // display new current dir
    ptr = getcwd(s, sizeof(s));

    free(ptr);
}

//pwd - Present Working directory
// Use getcwd()
void printCurrentDirectory() {

    char s[100];
    printf("%s\n", getcwd(s, sizeof(s)));
}

//mkdir - Make a directory (Alerts if already exists)
//Use mkdir()
void makeDirectory(char* name) {
    int value;
    value = mkdir(name, 0777);
    if(value == -1) {
        printf("%s\n", strerror(errno));
    }
}

//rmdir - Remove the directory (Alerts if no such file or directory)
//Use rmdir()
void removeDirectory(char* dirName) {
    int status = rmdir(dirName);
    if(status == -1) {
        printf("%s\n", strerror(errno));
    }
}

//ls - List contents of pwd
//Look at dirent.h library
void lsCommand(char* arg) {
    DIR *directory;
    directory = opendir(arg);
    if(!directory) {
        perror(arg);
        return;
    }
    if(directory == NULL){
        directory = opendir(".");
    }

    struct dirent *dp;


    if(directory) {
        while((dp = readdir(directory)) != NULL) {
            if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
                continue;
            }
           // printf("%s\n", dp->d_name);
        }
    }
    closedir(directory);
}

//cp - Copy contents from one file to another
//Use fgetc() and fputc()
void copyFile(char* parentName, char* childName) {
    FILE *parentFile, *childFile;

    parentFile = fopen(parentName, "rb");
    if (parentFile == NULL) {
        perror("Error ");
        return;
    }

    childFile = fopen(childName, "wb");

    if(childFile == NULL) {
        perror("Error ");
        return;
    }

    fseek(parentFile,0, SEEK_END);
    int fileLength = (int)ftell(parentFile);
    fseek(parentFile, 0, SEEK_SET);

    for(int i = 0; i < fileLength; i++) {
        fputc(fgetc(parentFile), childFile);
    }
}

//exit
void exitCommand() {
    printf("/nEXIT/n");
    exit(0);
}

//
void runExecutable(char* execName) {
    char *args[] = {execName, NULL};

    pid_t pid = fork();

    if(pid == -1) {
        printf("%s\n", strerror(errno));
    } else if(pid == 0) {
        execvp(args[0], args);
    } else {
        wait(NULL);
    }
}

void readCommand(char** cmd) { //char** array of strings
    int numOfCmds = 7;
    int ownCmd = 0;
    char* cmdList[numOfCmds];

    cmdList[0] = "cd";
    cmdList[1] = "pwd";
    cmdList[2] = "mkdir";
    cmdList[3] = "rmdir";
    cmdList[4] = "ls";
    cmdList[5] = "cp";
    cmdList[6] = "exit";


    if (sizeof(cmd) == 0) {
        //call method to restart newline
    }

    for (int i=0; i<numOfCmds; i++){
        if (strcmp(cmd[0], cmdList[i]) == 0){
            ownCmd = i + 1;
            break;
        }
    }
     
    switch (ownCmd) {
    case 1:
        changeDirectory(cmd[1]); //cmd[1] should have the argument
    case 2:
        printCurrentDirectory();
    case 3:
        makeDirectory(cmd[1]);
    case 4:
        removeDirectory(cmd[1]);
    case 5:
        lsCommand(cmd[1]);
    case 6:
        //copyFile(cmd[1]);
    case 7:
        exitCommand();
    default:
        break;
    } 
}


//char *argv[] is an array of char pointers

gboolean keyPressed(GtkWidget *widget, GdkEventKey *event, gpointer data);
void displayAfterEnterKey();
char* concat(const char *s2);

int main(int argc, char *argv[] ) {
    
    char s[100];
    char* dir = getcwd(s, sizeof(s));

    strcat(dir, ":");

    gtk_init(&argc, &argv);

//----------------------------------------------------------------
// establish contact with xml code used to adjust widget settings
//----------------------------------------------------------------

    //any gtk method will return an address of the data structure.
    //Thus, to reference the data structure and not the address
    //of the data structure, pointers are used to point to the
    //actual data structure

    builder = gtk_builder_new_from_file("terminal.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "terminal_window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    textfield = GTK_WIDGET(gtk_builder_get_object(builder, "terminal_textfield"));

    textBuffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textfield));

    gtk_text_buffer_create_tag(textBuffer, "editability", "editable", False, NULL);

    
    gtk_text_buffer_get_iter_at_offset(textBuffer, &iter, 0);
    

    gtk_text_buffer_insert_with_tags_by_name(textBuffer, &iter, dir, -1, "editability", NULL);


    g_signal_connect(textfield, "key-press-event", G_CALLBACK(keyPressed), NULL);

    gtk_widget_show(window);
    gtk_main();

    return 0;
}

gboolean keyPressed(GtkWidget *widget, GdkEventKey *event, gpointer data){
    
    char *temp;
    if (event->keyval == GDK_KEY_Return || event->keyval == GDK_KEY_KP_Enter)
    {
        
        gtk_text_buffer_get_start_iter(textBuffer, &start);
        gtk_text_buffer_get_end_iter(textBuffer, &end);
        gtk_text_buffer_apply_tag_by_name(textBuffer, "editability", &start, &end);





        memset(cmds,0,strlen(cmds));

        printf("%s\n", cmds);

        displayAfterEnterKey(&end);
        
       
        return True;
    }

    temp = gdk_keyval_name(event->keyval);
    strcat(cmds, temp);
    printf("%s\n", cmds);

    return False;
}


void displayAfterEnterKey(GtkTextIter *iter){
    char s[100];
    char* dir = getcwd(s, sizeof(s));
    strcat(dir, ":");
   
    gtk_text_buffer_insert_with_tags_by_name(textBuffer, iter, "\n", -1, "editability", NULL);
    gtk_text_buffer_insert_with_tags_by_name(textBuffer, iter, dir, -1, "editability", NULL);
}


