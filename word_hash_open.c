#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"word.h"

// ハッシュテーブルの要素数
#define bucket_size 1009

typedef enum {
    EMPTY,  // 空状態
    USE,    // 使用中
    DELETE  // 削除済み
} bucket_state;

typedef struct {
    char *data;
	int kaisu;
    bucket_state state;
} bucket;


void hash_init(bucket *table) {
    int i;

    // バケットを空状態に設定する
    for(i = 0; i < bucket_size; i++){
        table[i].state = EMPTY;
        table[i].data = NULL;
		table[i].kaisu = 0;
    }
}

int get_hashval(char *key) {
    int hashval = 0;

    while(*key){
        hashval = (hashval * 137 + *key++) % bucket_size;
    }
    return hashval;
}

int rehash(int hashval) {
    return (hashval + 1) % bucket_size;
}

void insert(bucket *table, char *data) {
    int hashval = 0;
    int i = 0;

    // 空バケットが見つかるまで再ハッシュする
    hashval = get_hashval(data);
    while(table[hashval].state == USE){
        if(++i > bucket_size){ //全ての配列にデータがある
            printf("これ以上データを格納できません.\n");
            return;
        }
		else if (strcmp(table[hashval].data,data) == 0){//同じ単語
			table[hashval].kaisu++;
			return;
		}
        hashval = rehash(hashval);
    }

    // キーとデータをバケットに保存する
	table[hashval].state = USE;
	table[hashval].kaisu = 1;
    if(table[hashval].data != NULL)
		table[hashval].data = (char *)malloc(sizeof(char)*(strlen(data)+1));
	else//DELET状態だった場合の再登録
		table[hashval].data = (char *)realloc(table[hashval].data,sizeof(char)*(strlen(data)+1));
    strcpy(table[hashval].data, data);

}

void num_val_print(bucket *table, int i){
    printf("table[%d]", i);
	if(i < 10)       printf("   ");
    else if(i < 100) printf("  ");
    else if(i < 1000)printf(" ");
    int val = get_hashval(table[i].data);
    if(i != val ) printf("(hashval = %4d): ",val);
    else          printf("                : ");
}

void hash_print_table(bucket *table, int num_all, int long_len) {
    int i,j;

    for(i = 0; i < bucket_size; i++){
        if(table[i].state == USE){
            num_val_print(table, i);
            printf("%s", table[i].data);
            for(j = 0; j < long_len - strlen(table[i].data); j++) printf(" "); //最低限の空白
		    printf("%4d回/%4d",table[i].kaisu,num_all); //出現回数表示
    	    printf("%7.2f%%\n",(float)(table[i].kaisu)/num_all*100); //出現確立表示
        }
    }
}

int main(int argc, char *argv[]) {
    bucket table[bucket_size];
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

    return(0);
}