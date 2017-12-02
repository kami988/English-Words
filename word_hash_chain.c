#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"word.h"

#define bucket_size 1009

typedef struct _bucket{
    char *data;
    int kaisu;
    struct _bucket *next;
} bucket;

int get_hashval(char *key) {
    int hashval = 0;

    while(*key){
        hashval = (hashval * 137 + *key++) % bucket_size;
    }
    return hashval;
}

void hash_init(bucket **table) { // ハッシュテーブルをNULLで初期化
    int i;
    for(i = 0; i < bucket_size; i++){
        table[i] = NULL;
    }
}


bucket *insert_cycle(bucket *table, char *data){
    if(table == NULL){//登録
        table = (bucket *)malloc(sizeof(bucket));
        table->data = (char *)malloc(sizeof(char)*(strlen(data)+1));
        strcpy(table->data, data);
        table->kaisu = 1;
        table->next = NULL;
    }
    else if(strcmp(table->data,data) == 0){//同じ単語
        table->kaisu++;
    }
    else {
        table->next = insert_cycle(table->next,data);
    }
    return table;
}

void insert(bucket **table, char *data) {//dataをキーと扱う
    int hashval = get_hashval(data);
    table[hashval] = insert_cycle(table[hashval],data);
}

void spaceprint1(int i){
    if(i < 10)       printf("   ");
    else if(i < 100) printf("  ");
    else if(i < 1000)printf(" ");
}

void num_space_print(int i, int j){
    if(j == 0){
        printf("table[%d]:", i);
        if(i < 10)       printf("   ");
        else if(i < 100) printf("  ");
        else if(i < 1000)printf(" ");
    }
    else
        printf("            ");
}

void hash_print_table(bucket **table, int num_all, int long_len) {
    int i,j,k;
    bucket *chain;

    for(i = 0; i < bucket_size; i++){
        if(table[i] != NULL){
            chain = table[i];
            /* リスト内部を走査して出力する */
            for(j=0; chain != NULL; chain = chain->next,j++){
                num_space_print(i,j);
                printf("%s ", (chain->data));
                for(k = 0; k < long_len - strlen(chain->data); k++) printf(" "); //最低限の空白
		        printf("%4d回/%4d",chain->kaisu,num_all); //出現回数表示
    	        printf("%7.2f%%\n",(float)(chain->kaisu)/num_all*100); //出現確立表示
            }
        }
    }
}

int main(int argc, char *argv[]) {
    bucket *table[bucket_size];
    char str[256];
	int i, long_len = 0, num_all = 0;
	
    // ハッシュの初期化
    hash_init(table);

	while(1){
        strcpy(str,GetWord(str));
		if(str[0] == '\n') continue;
    	if(strcmp(str,"***END***") == 0) break;
		insert(table,str);
		if(long_len < strlen(str)) long_len = strlen(str); //最高文字数の更新
		num_all++; //確率用個数記憶
	}

    hash_print_table(table, num_all, long_len);

    for(i=0;i<bucket_size;i++) free(table[i]);
    return(0);
}