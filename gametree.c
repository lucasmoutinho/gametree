#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int tabuleiro[2][7];
	struct no* esq;
	struct no* dir;
} t_no;

t_no* criaNo(){
	t_no* no = (t_no*)malloc(sizeof(t_no));
	no->esq = NULL;
	no->dir = NULL;
	return no;
}

int main(){


	return 0;
}