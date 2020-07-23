#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>


struct tree{
    struct tree *left;
    struct tree *right;
    char val;
};

struct node{
    struct node *next;
    int count;
    struct tree *n;
}; 

struct dict{
    struct dict *item;
    char key;
    char value[100];
};

struct node *start = NULL;
struct dict *dict_start = NULL;
struct dict *dict_tail = NULL;
char encrypt[1000] = {'\0'};
char decrypt[1000] = {'\0'};
char en[1000];

void display_ll(){
    struct node *temp = start;
    while(temp!=NULL){
        printf("%d %d\n", temp->n->val, temp->count);
        temp = temp->next;
    }
}

void push(char data){
    if(start==NULL){
        struct tree* newtree = (struct tree*)malloc(sizeof(struct tree));
        newtree->val = data;
        newtree->left = NULL;
        newtree->right = NULL;
        struct node* newnode = (struct node*)malloc(sizeof(struct node));        
        newnode->n = newtree;
        newnode->next = NULL;
        newnode->count = 1;
        start = newnode;
    } 
    else{
        struct node *prev = NULL;
        struct node *temp = start;
        while(temp->next!=NULL && temp->n->val!=data){           
            prev = temp;
            temp = temp->next;
        }
        if(temp->n->val==data){
            temp->count += 1;
            if(temp->next!=NULL){
                if(prev==NULL){
                    start = temp->next;
                }
                else{
                    prev->next = temp->next;
                }
                struct node *t = temp->next;
                while(t->next!=NULL && t->next->count<temp->count){
                    t = t->next;
                }
                temp->next = t->next;
                t->next = temp;
            }
        }
        else{ 
            struct tree* newtree = (struct tree*)malloc(sizeof(struct tree));
            newtree->val = data;
            newtree->left = NULL;
            newtree->right = NULL;           
            struct node* newnode = (struct node*)malloc(sizeof(struct node));        
            newnode->n = newtree;
            newnode->next = start;
            newnode->count = 1;
            start = newnode;
        }
    }
}

void display_tree(struct tree *node){
    if(node==NULL){
        return;
    }
    printf("%c\n", node->val);
    display_tree(node->left);
    display_tree(node->right);
}

void form_tree(){
    struct node *n1 = start;
    struct node *n2 = start->next;
    struct tree* newtree = (struct tree*)malloc(sizeof(struct tree));
    newtree->val = 'r';
    newtree->left = n1->n;
    newtree->right = n2->n;
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->count = n1->count + n2->count;
    newnode->n = newtree;
    if(n2->next==NULL){
        start = newnode;
        newnode->next = NULL;
    }
    else{
        start = n2->next;
        struct node *prev = NULL;
        struct node *temp = start;
        while(temp->next!=NULL && temp->count<newnode->count){
            prev = temp;
            temp = temp->next;
        }
        if(temp->next==NULL && temp->count<newnode->count){
            temp->next = newnode;
            newnode->next = NULL;
        }
        else{
            newnode->next = temp;
            if(prev==NULL){
                start = newnode;
            }
            else{
                prev->next = newnode;
            }
        }
    }
}

void display(){
    struct dict *temp = dict_start;
    while(temp!=NULL){
        // printf("******\n");
        // tree_traversal(temp->n);
        printf("%c %s\n", temp->key, temp->value);
        temp = temp->item;
    }
}

void add_item(struct tree* node, char *v){
    // display();
    if(node==NULL){
        return;
    }
    else{
        if(node->left==NULL && node->right==NULL){    
            struct dict *newitem = (struct dict*)malloc(sizeof(struct dict));
            newitem->key = node->val;
            strcpy(newitem->value, v);
            // printf("%s", newitem->key);
            newitem->item = NULL;
            if(dict_start == NULL){
                dict_start = newitem;
                dict_tail = newitem;
            }
            else if(dict_start==dict_tail){
                dict_tail = newitem;
                dict_start->item = dict_tail;
            }
            else{
                dict_tail->item = newitem;
                dict_tail = newitem;
                // struct dict *temp = dict_start;
                // while(temp->item!=NULL){
                //     temp = temp->item;
                // }
                // temp->item = newitem;
            }
        }
        char l[100];
        char r[100];
        strcpy(l, v);
        strcpy(r, v);
        // printf("%s", r);
        // printf("s");
        // strcat(r, v);     
        strcat(l, "0");    
        strcat(r, "1"); 
        // printf("%s\n", v);
        // printf("%c\n", node->val);
        add_item(node->left, l);
        add_item(node->right, r);
    }
}

char *retrieve_item(char c){
    struct dict *temp = dict_start;
    while(temp->key!=c){
        temp = temp->item;
    }
    return(temp->value);
}

void tree_traversal(struct tree* node, int i, int ascii, int count){
    int f=0;
    char c;
    if(en[i+1]=='\0'){
        if(ascii==0){
            f = 1;
        }
    }
    if(node->left==NULL && node->right==NULL){
        c = node->val;
        strcat(decrypt, &c);
        // printf("%s\n", decrypt);
        if(f){
            return;
        }
        tree_traversal(start->n, i, ascii, count);
    } 
    else if(ascii==0){
        if(count==7){
            tree_traversal(node, i+1, en[i+1], 0);
        }
        else{
            tree_traversal(node->left, i, 0, count+1);
        }
    }
    else{
        if(ascii%2==0){
            tree_traversal(node->left, i, ascii/2, count+1);
        }
        else{
            tree_traversal(node->right, i, ascii/2, count+1);
        }
    }
}

void main(){
    FILE *file;
    int len=0, i=0, ascii, q, r;
    char empty[] = {'\0'}, buff[1000], string[1000]={'\0'};
    file = fopen("text.txt", "r");
    while(fgets(buff, sizeof(buff), file)){
        strcat(string, buff);
    }
    fclose(file);
    printf("\n");
    while(string[len]!='\0'){
        push(string[len]);
        len++;
    }
    // display_ll();
    while(start->next!=NULL){
        form_tree();
    }
    // tree_traversal(start->n);
    add_item(start->n, empty);
    len = 0;
    while(string[len]!='\0'){
        strcat(encrypt, retrieve_item(string[len]));
        len++;
    }
    // printf("%s\n", encrypt);
    int j=0, bin, f=0;
    while(true){
        bin = 0;
        for(i=0; i<7; i++){
            if(encrypt[j*7+i]=='\0'){
                f = 1;
                break;
            }
            if(encrypt[j*7+i]=='1'){
                bin += pow(2,i);
            }
        }
        // printf("%d %c\n", bin, bin);
        en[j] = bin;
        j = j+1;
        if(f){
            break;
        }
    }
    file = fopen("short.txt", "w");
    fputs(en, file);
    fclose(file);
    // for(i=0; en[i]!='\0'; i++){
    //     printf("%d\n", en[i]);
    // }
    // display();
    tree_traversal(start->n, 0, en[0], 0);
    file = fopen("long.txt", "w");
    fputs(decrypt, file);
    fclose(file);
    // printf("%s\n", encrypt);
    // printf("%s\n", decrypt);
}