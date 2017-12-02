#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"word.h"

typedef struct {
	int   kaisu;
	char *word;
} cell;

cell *add_new(cell *data, char *str,int num, int *num_data){
	int i,j;
	data[num].word = (char*)malloc(sizeof(char)*(strlen(str)+1)); //文字数分配列用意
	strcpy(data[num].word,str); //単語登録
	data[num].kaisu = 1; //回数初期化
	(*num_data)++;
	return data;
}

cell *insert(cell *data, char *str, int *num_data){
	int i,j,cmp;
	for(i = 0; i < *num_data; i++){//同じ単語
		cmp = Mystrcmp(data[i].word, str);
		if(cmp == 0) {
			data[i].kaisu++;
			return data;
		}
		else if(cmp > 0){//降順
			data = (cell *)realloc(data,sizeof(cell)*(*num_data+1)); //配列追加
			for(j = *num_data; j > i; j--){
				if(j == *num_data) data[j].word = (char*)malloc(sizeof(char)*(strlen(data[j-1].word)+1));
				else              data[j].word = (char*)realloc(data[j].word, sizeof(char)*(strlen(data[j-1].word)+1)); //文字数分配列用意
				strcpy(data[j].word,data[j-1].word); //単語登録
				data[j].kaisu = data[j-1].kaisu; //回数初期化
			}
			data = add_new(data, str, j, num_data);
			return data;
		}
	}
	if(!(*num_data)) data = (cell *)malloc(sizeof(cell)); //配列用意
	else          data = (cell *)realloc(data,sizeof(cell)*(*num_data+1)); //配列追加
	data = add_new(data, str, *num_data, num_data);
	
	return data; //配列数更新
}

void dataprint(cell *data, int *num_data, int num_all, int long_len){
	int i,j;
	for(i = 0; i < *num_data; i++) {
        printf("%s ", data[i].word);
		for(j = 0; j < long_len - strlen(data[i].word); j++) printf(" "); //最低限の空白
		printf("%4d回/%4d",data[i].kaisu,num_all); //出現回数表示
    	printf("%7.2f%%\n",(float)(data[i].kaisu)/num_all*100); //出現確立表示
    }
}

int main(int argc, char *argv[]){
	int long_len = 0;
	int num_all = 0;
	int num_data = 0;
	int i;
	char str[256];
	cell *data;
	
	while(1){
		strcpy(str,GetWord(str));
		if(str[0] == '\n') continue;
   	 	if(strcmp(str,"***END***") == 0) break;
		if(long_len < strlen(str)) long_len = strlen(str); //最高文字数の更新
		data = insert(data, str, &num_data);
		num_all++; //確率用個数記憶
	}

	dataprint(data, &num_data, num_all, long_len);

	free(data);//メモリの解放
	return 0;
}
