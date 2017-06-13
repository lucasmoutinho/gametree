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

t_no* criaTabuleiro(){
	t_no* tab = criaNo();
	for(i=0;i<2;i++){
		for(j=0;j<6;j++){
			tab->tabuleiro[i][j] = 4;
		}
		tab->tabuleiro[i][j] = 0;
	}
	return tab;
}

void mostraTabuleiro(t_no* tab){
	int i = 0;
	for(j=6;j>=0;j--){
		printf("%d ", tab->tabuleiro[i][j]);
	}
	i++;
	printf("\n");
	for(j=0;j<7;j++){
		printf("%d ", tab->tabuleiro[i][j]);
	}
	printf("\n");
}

void jogada(int pos){

}

int main(){


	return 0;
}