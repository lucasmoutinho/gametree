#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int tabuleiro[2][7];
	struct no* first;
	struct no* second;
	struct no* third;
	struct no* fourth;
	struct no* fifth;
	struct no* sixth;
} t_no;

t_no* criaNo(){
	t_no* no = (t_no*)malloc(sizeof(t_no));
	no->first = NULL;
	no->second = NULL;
	no->third = NULL;
	no->fourth = NULL;
	no->fifth = NULL;
	no->sixth = NULL;
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
	printf("  ");
	for(j=5;j>=0;j--){
		printf("%d ", tab->tabuleiro[i][j]);
	}
	printf("\n%d             %d\n", tab->tabuleiro[0][6], tab->tabuleiro[1][6]);
	i++;
	printf("  ");
	for(j=0;j<6;j++){
		printf("%d ", tab->tabuleiro[i][j]);
	}
	printf("\n");
}

t_no* montaJogada(int posicao, int jogador, t_no* tab){
	int pedras, i, j;
	t_no* tab2 = criaNo();
	for(i=0;i<2;i++){
		for(j=0;j<7;j++){
			tab2->tabuleiro[i][j] = tab->tabuleiro[i][j];
		}
	}
	i = jogador-1;
	j = posicao-1;
	pedras = tab2->tabuleiro[i][j];
	if(pedras!=0){
		tab2->tabuleiro[i][j] = 0;
		j++;
		while(pedras != 0){
			while(pedras != 0 && i<2){
				while(pedras != 0 && j<7){
					tab2->tabuleiro[i][j]+=1;
					pedras--;
					j++;
				}
				j=0;
				i++;
			}
			i=0;
		}
	}
	return tab2;
}

int criaArvore(t_no* tab, int altura){
	int jogador;
	if(altura!=0){
		if(altura%2 == 0){
			jogador = 1;
		}
		else{
			jogador = 2;
		}
		tab->first = montaJogada(1,jogador,tab);
		criaArvore(tab->first, altura-1);
		tab->second = montaJogada(2,jogador,tab);
		criaArvore(tab->second, altura-1);
		tab->third = montaJogada(3,jogador,tab);
		criaArvore(tab->third, altura-1);
		tab->fourth = montaJogada(4,jogador,tab);
		criaArvore(tab->fourth, altura-1);
		tab->fifth = montaJogada(5,jogador,tab);
		criaArvore(tab->fifth, altura-1);
		tab->sixth = montaJogada(6,jogador,tab);
		criaArvore(tab->sixth, altura-1);
	}
	return 0;
}

int percursoPos(t_no* r){
	if(r == NULL){
		return 0;;
	}
	percursoPos(r->first);
	percursoPos(r->second);
	percursoPos(r->third);
	percursoPos(r->fourth);
	percursoPos(r->fifth);
	percursoPos(r->sixth);
	mostraTabuleiro(r);
	printf("\n");
	return 0;
}

int main(){
	t_no* tab = criaTabuleiro();
	criaArvore(tab, 4);
	printf("\n");
	percursoPos(tab);
	return 0;
}