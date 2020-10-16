#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

enum commands{cd, pwd, mkdir, rmdir, ls, cp};

//cd - Change directory
//Use chdir()
void changeDirectory() {

}

//pwd - Present Working directory
//Use getcwd()
void printCurrentDirectory(char[] s) {
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
    if (sizeof(cmd) == NULL) {
        //call method to restart newline
    }
     
    switch (cmd) {
    case "cd":
        changeDirectory(args);
    case "pwd":
        printCurrentDirectory();
    case "mkdir":
        makeDirectory(args);
    case "rmdir":
        removeDirectory(args);
    case "ls":
        lsCommand();
    case "cp":
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
