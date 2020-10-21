#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <gtk-3.0/gtk/gtk.h> 
#include <gtk-3.0/gtk/gtkx.h> 
#include <signal.h>
#include <math.h>
#include <ctype.h>
#include <sys/types.h>

GtkWidget *window;
GtkWidget *textfield;
GtkTextBuffer *textBuffer;
GtkBuilder *builder;

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
void makeDirectory() {

}

//rmdir - Remove the directory (Alerts if no such file or directory)
//Use rmdir()
void removeDirectory() {

}

//ls - List contents of pwd
//Look at dirent.h library
void lsCommand() {

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

void readCommand(char* cmd, char* args) {
//     if (sizeof(cmd) == NULL) {
//         //call method to restart newline
//     }
     
//     switch (cmd) {
//     case "cd":
//         changeDirectory(args);
//     case "pwd":
//         printCurrentDirectory();
//     case "mkdir":
//         makeDirectory(args);
//     case "rmdir":
//         removeDirectory(args);
//     case "ls":
//         lsCommand();
//     case "cp":
//         copyFile(args);
//     default:
//         break;
//     } 
}

//
void runExecutable() {

}

//char *argv[] is an array of char pointers

int main(int argc, char *argv[] ) {

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

    //gtk_text_buffer_insert_with_tags ()

    gtk_widget_show(window);
    gtk_main();
    return 0; 
}
