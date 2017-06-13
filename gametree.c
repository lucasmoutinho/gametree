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
	int i, j;
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
	int i = 0, j;
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

t_no* jogada(int posicao, int jogador, t_no* tab){
	int pedras, i, j;
	i = jogador-1;
	j = posicao-1;
	pedras = tab->tabuleiro[i][j];
	tab->tabuleiro[i][j] = 0;
	j++;
	while(pedras != 0){
		while(pedras != 0 && i<2){
			while(pedras != 0 && j<7){
				tab->tabuleiro[i][j]+=1;
				pedras--;
				j++;
			}
			j=0;
			i++;
		}
		i=0;
	}


}

int main(){


	return 0;
}