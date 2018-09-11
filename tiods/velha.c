#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define LIN 3
#define COL 3

bool jogadoresDesistiram(void);

const char tabuleiroVazio[LIN][COL] = {{'-', '-', '-'},
										{'-', '-', '-'},
										{'-', '-', '-'}};
const char simbolos[2] = {'X', 'O'};


int main(void)
{
	do
	{
		printf("jogo\n");
		//jogarPartida();
	}while(!jogadoresDesistiram());
	
	return 0;
}

bool jogadoresDesistiram(void)
{
	char resposta[3], buffer;
	
	printf("Deseja jogar outra partida? [sim/nao]\n");
	
	fgets(resposta, 3, stdin);
	
	while((buffer = getchar()) != '\n' && buffer != EOF)
		;
	
	return resposta[0] == 'n';
}

void jogarPartida(void)
{
	int jogadorAtual = 0;
	char tabuleiro[LIN][COL];
	
	esvaziarTabuleiro(tabuleiro, tabuleiroVazio);
	
	do
	{
		fazerJogada(jogadorAtual, tabuleiro);
		
		jogadorAtual = !jogadorAtual; /* trocar jogador */
	}while(!jogoAcabou(tabuleiro));
}

void esvaziarTabuleiro(char tabuleiro[LIN][COL], const char tabuleiroVazio[LIN][COL])
{
	int lin, col;
	
	for(lin = 0; lin < LIN; lin++)
		for(col = 0; col < COL; col++)
			tabuleiro[lin][col] = tabuleiroVazio[lin][col];
}

void fazerJogada(int jogadorAtual, char tabuleiro[LIN][COL])
{
	int i;
	int linAlterada, colAlterada;
	
	mostrarTabuleiro(tabuleiro);
	
	printf("\t>> Jogador %c <<\n", simbolos[jogadorAtual]);
	printf("Qual linha queres alterar? ");
	
	do
	{
		linAlterada = atoi(getchar());
	}while(linAlterada < 0 || linAlterada > 2);
}
