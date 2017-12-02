#include<stdio.h>
#include<stdbool.h>
#include<string.h>

/*
1.アルファベット順（a -> z）
2.長さ（apple -> apples）
3.大文字小文字（LINE -> LINe -> LInE -> LIne -> ・・・ -> linE -> line）
*/
int Mystrcmp(char *word, char *str){
	int i,judge;
	bool LFlag_w = false,LFlag_s = false;
	int len = strlen(str) + 1; //どちらかの文字列のNULLまで比較

	for(i=0; i < len; i++){ 
		if(!LFlag_w && !LFlag_s && 'A' <= *word && *word <= 'Z' && 'a' <= *str){ //wordのみ大文字
				judge = strncasecmp(word++,str++,1);
				if(!judge) LFlag_w = true;
   		}
    	else if(!LFlag_w && !LFlag_s && 'A' <= *str && *str <= 'Z' && 'a' <= *word){ //strのみ大文字
				judge = strncasecmp(word++,str++,1);
				if(!judge) LFlag_s = true;
	 	}
		else	judge = strncasecmp(word++,str++,1);
		if(judge != 0) break;
	}
	if      (!judge && LFlag_w == true) return    -1;
	else if(!judge && LFlag_s == true)  return     1;
	else                                return judge;
}

char *GetWord(char *wd){
	int len = 0;
	char c;
	do c = getchar(); while(c == ' ' || c == '\n' || c == '.' || c == '\'' || c == '(' || c == ')');
	while(c != ' ' && c != '\n' && c != '.' && c != ',' && c != '(' && c != ')' && c != '?' && c != '!'){
		if(len > 255)  {
			do c = getchar();
				while(c != ' ' && c != '\n' && c != '.' && c != ',' && c != '(' && c != ')' && c != '?' && c != '!');
			wd[0] = '\n';
			printf("255文字を超えた単語を無効としました。\n");
			return &wd[0];
		}
		wd[len++] = c;
		c = getchar();
	}
	if(wd[len-1] == '\'') wd[len-1] = '\0';
	else wd[len] = '\0';

	return &wd[0];
}