#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	/*Jogador 1 == Computador && Jogador 2 == Usuário*/
	int tabuleiro[2][7];
	int jogador;
	struct no* first;
	struct no* second;
	struct no* third;
	struct no* fourth;
	struct no* fifth;
	struct no* sixth;
} t_no;

void limpaTela(){
	#ifdef _WIN32
    	system("cls");
	#else
	    system("clear");
	#endif
}

t_no* criaNo(){
	t_no* no = (t_no*)malloc(sizeof(t_no));
	no->jogador = 0;
	no->first = NULL;
	no->second = NULL;
	no->third = NULL;
	no->fourth = NULL;
	no->fifth = NULL;
	no->sixth = NULL;
	return no;
}

t_no* criaTabuleiro(int comeca){
	int i, j;
	t_no* tab = criaNo();
	tab->jogador = comeca;
	for(i=0;i<2;i++){
		for(j=0;j<6;j++){
			tab->tabuleiro[i][j] = 4;
		}
		tab->tabuleiro[i][j] = 0;
	}
	return tab;
}

t_no* copiaTabuleiro(t_no* tab){
	t_no* tab2 = criaNo();
	int i, j;
	tab2->jogador = tab->jogador;
	for(i=0;i<2;i++){
		for(j=0;j<7;j++){
			tab2->tabuleiro[i][j] = tab->tabuleiro[i][j];
		}
	}
	return tab2;
}

int removeArvore(t_no* r){
	if(r == NULL){
		return 0;
	}
	removeArvore(r->first);
	removeArvore(r->second);
	removeArvore(r->third);
	removeArvore(r->fourth);
	removeArvore(r->fifth);
	removeArvore(r->sixth);
	free(r);
	return 0;
}

void mostraTabuleiro(t_no* tab){
	int i = 0, j;
	printf("  ----------TABULEIRO----------\n\n\n");
	printf("    ");
	for(j=5;j>=0;j--){
		printf(" %2d ", tab->tabuleiro[i][j]);
	}
	printf("\n  %2d                        %2d\n", tab->tabuleiro[0][6], tab->tabuleiro[1][6]);
	i++;
	printf("    ");
	for(j=0;j<6;j++){
		printf(" %2d ", tab->tabuleiro[i][j]);
	}
	printf("\n");
}

int testeAcabou(t_no* tab){
	int acabou = 1, j = 0;
	while(acabou && j<6){
		if(tab->tabuleiro[0][j] != 0){
			acabou = 0;
		}
		j++;
	}
	j=0;
	if(!acabou){
		acabou = 1;
		while(acabou && j<6){
			if(tab->tabuleiro[1][j] != 0){
				acabou = 0;
			}
			j++;
		}	
	}
	return acabou;
}

t_no* montaJogada(int posicao, t_no* tab){
	t_no* tab2 = NULL;
	int pedras, i, j, k;
	i = (tab->jogador)-1;
	j = posicao-1;
	pedras = tab->tabuleiro[i][j];
	if(pedras!=0){
		tab2 = copiaTabuleiro(tab);
		tab2->tabuleiro[i][j] = 0;
		j++;
		while(pedras != 0){
			while(pedras != 0 && i<2){
				while(pedras != 0 && j<7){
					if( j == 6 && ((tab->jogador == 1 && i==1) || (tab->jogador == 2 && i==0))){
						j++;
					}
					else{
						tab2->tabuleiro[i][j]+=1;
						pedras--;
						if(pedras == 0 && j != 6){
							if(tab->jogador == 1){
								tab2->jogador = 2;
							}
							else{
								tab2->jogador = 1;
							}
							if(tab->jogador == 1 && i == 0 && tab2->tabuleiro[0][j] == 1 && tab2->tabuleiro[1][5-j] != 0){
								tab2->tabuleiro[0][6] += (1 + tab2->tabuleiro[1][5-j]);
								tab2->tabuleiro[1][5-j] = 0;
								tab2->tabuleiro[0][j] = 0;
							}
							else if(tab->jogador == 2 && i == 1 && tab2->tabuleiro[1][j] == 1 && tab2->tabuleiro[0][5-j] != 0){
								tab2->tabuleiro[1][6] += (1 + tab2->tabuleiro[0][5-j]);
								tab2->tabuleiro[0][5-j] = 0;
								tab2->tabuleiro[1][j] = 0;
							}
						}
						if(pedras == 0 && testeAcabou(tab2)){
							for(k=0;k<6;k++){
								tab2->tabuleiro[1][6]+=tab2->tabuleiro[1][k];
								tab2->tabuleiro[1][k]=0;
								tab2->tabuleiro[0][6]+=tab2->tabuleiro[0][k];
								tab2->tabuleiro[0][k]=0;
							}

						}
						j++;
					}
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
	if(altura!=0 && tab!=NULL){
		tab->first = montaJogada(1,tab);
		criaArvore(tab->first, altura-1);
		tab->second = montaJogada(2,tab);
		criaArvore(tab->second, altura-1);
		tab->third = montaJogada(3,tab);
		criaArvore(tab->third, altura-1);
		tab->fourth = montaJogada(4,tab);
		criaArvore(tab->fourth, altura-1);
		tab->fifth = montaJogada(5,tab);
		criaArvore(tab->fifth, altura-1);
		tab->sixth = montaJogada(6,tab);
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

void pressioneEnter(){
	printf("Pressione Enter para continuar\n");
	getchar();
	limpaTela();
}

t_no* organizaRodada(t_no* tab){
	t_no* tab2;
	int posicao, naovalido = 1;
	mostraTabuleiro(tab);
	printf("\n\n");
	if(tab->jogador == 1){
		printf("Vez do Computador!\n\n");
		printf("Que peca mover?\n");
		scanf("%d", &posicao);
		getchar();
		while(naovalido){
			naovalido = 0;	
			while(posicao < 1 || posicao > 6){
				printf("Esta posicao nao existe no tabuleiro, escolha outra\n");
				scanf("%d", &posicao);
				getchar();
				naovalido = 1;
			}
			while(tab->tabuleiro[0][posicao-1] == 0){
				printf("Posicao invalida, nao existem pedras nesta, escolha outra\n");
				scanf("%d", &posicao);
				getchar();
				naovalido = 1;
			}
		}
		printf("Computador selecionou a posicao %d\n\n", posicao);

	}
	else{
		printf("Sua vez!\n\n");
		printf("Informe a posicao que voce deseja mover: ");
		scanf("%d", &posicao);
		getchar();
		while(naovalido){
			naovalido = 0;	
			while(posicao < 1 || posicao > 6){
				printf("Esta posicao nao existe no tabuleiro, escolha outra: ");
				scanf("%d", &posicao);
				getchar();
				naovalido = 1;
			}
			while(tab->tabuleiro[1][posicao-1] == 0){
		;		printf("Nao existem pedras nesta posicao, escolha outra: ");
				scanf("%d", &posicao);
				getchar();
				naovalido = 1;
			}
		}
		printf("Voce selecionou a posicao %d\n\n", posicao); 
	}
	pressioneEnter();
	tab2 = montaJogada(posicao, tab);
	free(tab);
	return tab2;
}

int organizaPartida(){
	char comeca;
	t_no* tab;
	limpaTela();
	printf("***** BEM VINDO AO JOGO MANCALA *****\n\n\n");
	pressioneEnter();
	printf("Deseja comecar jogando? (S/N)\n\n");
	scanf("%c", &comeca);
	getchar();
	while(comeca != 'S' && comeca != 's' && comeca != 'N' && comeca != 'n'){
		printf("\nResposta invalida\n\n");
		printf("Deseja comecar jogando? (S/N)\n\n");
		scanf(" %c", &comeca);
		getchar();
	}
	if(comeca == 'S' || comeca == 's'){
		tab = criaTabuleiro(2);
	}
	else{
		tab = criaTabuleiro(1);
	}
	printf("\n");
	limpaTela();
	while(!testeAcabou(tab)){
		tab = organizaRodada(tab);
	}
	mostraTabuleiro(tab);
	printf("\n\nO jogo acabou!\n\n");
	if(tab->tabuleiro[1][6] > tab->tabuleiro[0][6]){
		printf("Voce ganhou! \n\n");
	}
	else if(tab->tabuleiro[1][6] < tab->tabuleiro[0][6]){
		printf("O computador ganhou...");
		printf("\n\n¯\\_(ツ)_/¯\n\n");
	
	}
	else{
		printf("O jogo empatou!\n\n");
	}
	pressioneEnter();
	return 0;
}

int main(){
	organizaPartida();
	return 0;
}