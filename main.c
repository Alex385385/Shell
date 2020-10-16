#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

//cd - Change directory
//Use chdir()
void changeDirectory() {
    fafkldsanfkldsnflklk
}

//pwd - Present Working directory
//Use getcwd()
void printCurrentDirectory(char* s) {
    printf("/n" + getcwd(s,100) + "\n");
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
void copyFile() {

}

//exit
void exitCommand() {
    printf("/nEXIT/n");
    exit(0);
}

void readCommand(int cmd, char* args) {
    if (sizeof(cmd) == NULL) {
        //call method to restart newline
    }
    
    switch (cmd) {
    case 1:
        changeDirectory(args);
    case 2:
        printCurrentDirectory();
    case 3:
        makeDirectory(args);
    case 4:
        removeDirectory(args);
    case 5:
        lsCommand();
    case 6:
        copyFile(args);
    default:
        break;
    } 
}

//
void runExecutable() {

}

int main() {
    printf("Hello, World!\n");
    return 0;
}
