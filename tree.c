#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"tree.h"
struct wordTree *createnode(char word[]){
    struct wordTree *node; 
    node = (struct wordTree *)malloc(sizeof(struct wordTree));
    node->root = NULL; 
    strcpy(node->word, word);
    node->count = 1; // the occurance of the word will always be one when it is generated. 
    node->left = NULL; 
    node->right = NULL;
    return node;
}
int hash(char word[]){ //hash function is used to set in which of the trees[] pointer array will the word go to. 
    int loc = word[0]; //ASCII value of the first character is used.  
    return loc % 97; // the ASCII values are between 97-122, so this will return the number from 0 - 25, hence allowing us to designate where the word will go in the tree. 
}
void set_NULL(){
    for(int i = 0; i<26; i++){
        trees[i] = NULL;//Sets all the pointers to null in the beginning in the trees[]; 
    }
}
void placer(struct wordTree *, struct wordTree *);
void tree_Maker(struct wordTree *node){
    int adder = hash(node->word); //used to find which is the first letter. 
    if(trees[adder] == NULL){
        trees[adder] = node; // if null node, then the word is made the root 
    }else{
        struct wordTree *refer = trees[adder];
        placer(node, refer);// placer is used to place where the node will be placed. 
    }
}
void placer(struct wordTree *coming_node, struct wordTree *refer){ // this is the part where the strings are compared and are placed when the condition is satisfied. 
    bool flag = false; 
    while(coming_node->root == NULL){//coming node is the node which is not placed, while reference nodes are already in the tree. 
        if(strcmp(coming_node->word, refer->word) > 0 && (refer->right) == NULL){
            coming_node->root = refer;
            refer->right = coming_node;
        }else if(strcmp(coming_node->word, refer->word) > 0 && (refer->right != NULL)){
            refer = refer->right;
        }
        if(strcmp(coming_node->word, refer->word) < 0 && (refer->left) == NULL){
            coming_node->root = refer; 
            refer->left = coming_node;
        }else if(strcmp(coming_node->word, refer->word) < 0 && (refer->left) != NULL){
            refer = refer->left;
        }
        if(strcmp(coming_node->word, refer->word) == 0){
            refer->count++; 
            flag = true; // if the word already exists then the count of the reference node is incremented by one. 
            break;
        }
    }
    if(flag == true){
        free(coming_node); // node is freed of the memory
    } 
}
