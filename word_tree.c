#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"word.h"

struct node {
	int kaisu;
	char *word;
	struct node *left;
	struct node *right;
};

struct node *insert(struct node *x, char* str){
	int judge;
	if(x == NULL){
		x = (struct node *)malloc(sizeof(struct node));
		x->word = (char *)malloc(sizeof(char )*(strlen(str)+1));
		strcpy(x->word,str);
		x->left = NULL;
		x->right = NULL;
		x->kaisu = 1;
	}
	else{
        judge = Mystrcmp(x->word, str);
             if(judge > 0)   x->left  = insert(x->left,str);
        else if(judge < 0)   x->right = insert(x->right,str);
        else if(judge == 0)  x->kaisu++;
	}
	return x;
}

void treeprint(struct node *x, int long_len, int num_all){
	int i;
	if (x != NULL){
		treeprint(x->left, long_len, num_all);
		printf("%s ",x->word);
		for(i = 0; i < long_len - strlen(x->word); i++) printf(" "); //最低限の空白
		printf("%4d回/%4d",x->kaisu,num_all); //出現回数表示
    	printf("%7.2f%%\n",(float)(x->kaisu)/num_all*100); //出現確立表示
		treeprint(x->right, long_len, num_all);
	}
}

int main(int argc, char *argv[]){
	struct node *root;
	char str[256];
	int long_len = 0;
	int num_all = 0;
	root = NULL;
	
	while(1){
		strcpy(str,GetWord(str));
		if(str[0] == '\n') continue;
    	if(strcmp(str,"***END***") == 0) break;
		root = insert(root,str);
		if(long_len < strlen(str)) long_len = strlen(str); //最高文字数の更新
		num_all++; //確率用個数記憶
	}

	treeprint(root, long_len, num_all);
	free(root);
	return 0;
}