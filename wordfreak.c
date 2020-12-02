#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include"tree.h"

void inOrder(struct wordTree *, int lent); 
void printstyle(int, char *, int); 
int fdw; 
void init(); 
int length(int, char *);

int main(int argc, char *argv[]){
    
    set_NULL(); 
    int longest_string; 
    init(); 
    char name[20];
    
    for(int i = 1; i < argc; i++){
        strcpy(name, argv[i]); 
        int file_name = open(argv[i], O_RDONLY);
        if(file_name == -1){
            printf("%s No file of such type\n", argv[i]);
        }else{
            printf("%s File found\n", argv[i]); 
            char word[100] = "";
            char text; 
            int bytes; 
            int i = 0; 
            while((bytes = read(file_name, &text, sizeof(text))) > 0 ){
                int number = text; 
                if((number >= 65) && (number <= 90)){
                    number = number + 32;
                    text = tolower(text); 
                }
                if((number < 97) || (number > 122) || (text == ' ')){
                    word[i] = '\0';
                    i = 0; 
                    if(strlen(word) ==0){
                        continue;
                    }else{
                        longest_string = length(longest_string, word); 
                        tree_Maker(createnode(word));
                    } 
                }else{
                    word[i] = text;
                    i++; 
                }
            }
            close(file_name);
        }
    }
    
    for(int i = 0; i<26; i++){
        if(trees[i] == NULL){
            continue;
        }else{
            inOrder(trees[i], longest_string);
        }
    }    
    close(fdw); 
    
    return 0;
}

void inOrder(struct wordTree *w, int longest_string){
    if(w == NULL){
        return; 
    }
    inOrder(w->left, longest_string); 
    printstyle(longest_string, w->word, w->count); 
    inOrder(w->right, longest_string);
}

int length(int longest_string, char *word){
    if(longest_string>strlen(word)){
        return longest_string;
    }else{
        return strlen(word); 
    }
}

void printstyle(int length, char *word, int count){
    char insert[40] = " "; 
    strcpy(insert, word); 
    for(int i = 0; i < length - strlen(word); i++){
        strcat(insert, " "); 
    }
    strcat(insert, ":"); 
    char second[10]; 
    sprintf(second, "%d\n", count); 
    strcat(insert, second); 
    write(fdw, insert, strlen(insert)); 
}

void init(){
    fdw = open("output.txt", O_CREAT | O_WRONLY, 0600); 
}
