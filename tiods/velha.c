#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LIN 3
#define COL 3

void jogarPartida(void);
void esvaziarTabuleiro(char[LIN][COL], const char[LIN][COL]);
void mostrarTabuleiro(char[LIN][COL]);
void fazerJogada(int, char[LIN][COL]);
void escolherCoordenadas(int*, int*);
bool jogadoresDesistiram(void);
bool jogoAcabou(char [LIN][COL]);
char lerUmChar(void);
void limparBuffer(void);

/* constantes globais */
const char tabuleiroVazio[LIN][COL] = {{'-', '-', '-'},
									   {'-', '-', '-'},
									   {'-', '-', '-'}};
const char simbolos[2] = {'X', 'O'};


int main(void)
{
	do
	{
		jogarPartida();
	}while(!jogadoresDesistiram());
	
	return EXIT_SUCCESS;
}

void jogarPartida(void)
{
	int jogadorAtual = 0;
	char tabuleiro[LIN][COL];
	
	esvaziarTabuleiro(tabuleiro, tabuleiroVazio);
	
	do
	{
		mostrarTabuleiro(tabuleiro);
		fazerJogada(jogadorAtual, tabuleiro);
		
		/* trocar jogador */
		jogadorAtual = !jogadorAtual; /* se era 0, passa a ser 1 */
	}while(!jogoAcabou(tabuleiro));
}

void esvaziarTabuleiro(char tabuleiro[LIN][COL], const char tabuleiroVazio[LIN][COL])
{
	int lin, col;
	
	/* copia o tabuleiro vazio para o tabuleiro */
	/* que sera usado no jogo */
	for(lin = 0; lin < LIN; lin++)
		for(col = 0; col < COL; col++)
			tabuleiro[lin][col] = tabuleiroVazio[lin][col];
}

void mostrarTabuleiro(char tabuleiro[LIN][COL])
{
	int lin, col;
	
	/* mostra as posicoes dentro de uma caixinha */
	printf("\n\n-------------\n");
	for(lin = 0; lin < LIN; lin++)
	{
		printf("|");
		for(col = 0; col < COL; col++)
			printf(" %c |", tabuleiro[lin][col]);
		printf("\n");
	}
	printf("-------------\n");
}

void fazerJogada(int jogadorAtual, char tabuleiro[LIN][COL])
{
	int linAlterada, colAlterada;
	
	printf("\t>> Jogador %c <<\n", simbolos[jogadorAtual]);

	/* escolhe a linha e a coluna, depois subtsitui */
	/* pelo simbolo do jogador atual */
	escolherCoordenadas(&linAlterada, &colAlterada);	
	tabuleiro[linAlterada][colAlterada] = simbolos[jogadorAtual];
}

void escolherCoordenadas(int *linAlterada, int *colAlterada)
{
	printf("Linha: ");
	while(true)
	{
		*linAlterada = lerUmChar() - '0';
		/* se o valor for aceitavel, sai do laco */
		if(*linAlterada >= 0 && *linAlterada <= 2)
			break;

		/* senão, mostra uma mensagem de erro */
		printf("Linha invalida. Digite novamente: ");
	}
	
	printf("Coluna: ");
	while(true)
	{
		*colAlterada = lerUmChar() - '0';
		if(*colAlterada >= 0 && *colAlterada <= 2)
			break;

		printf("Coluna invalida. Digite novamente: ");
	}
}

bool jogadoresDesistiram(void)
{
	char resposta[3], buffer;
	
	printf("Deseja jogar outra partida [sim/nao]? ");
	fgets(resposta, 3, stdin); /* le-se uma string de tamanho 3 */
	
	/* apaga-se quaisquer caracteres que tenham sobrado no buffer */
	limparBuffer();
	
	/* so eh preciso a primeira letra da palvra */
	return resposta[0] == 'n' ||resposta[0] == 'N';
}

bool jogoAcabou(char tabuleiro[LIN][COL])
{
	int i;
	
	/* verificar linhas */
	for(i = 0; i < LIN; i++)
		if(tabuleiro[i][0] != '-' && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2])
			return true;
			
	/* verificar colunas */
	for(i = 0; i < COL; i++)
		if(tabuleiro[0][i] != '-' && tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i])
			return true;

	/*verificar diagonais */
	if(tabuleiro[0][0] != '-' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2])
		return true;
	if(tabuleiro[0][2] != '-' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0])
		return true;
	
	/* se nenhuma for verdade, entao chega nesta linha */	
	return false;
}

char lerUmChar(void)
{
	char entrada = getchar();
	
	/* limpa caracteres excedentes */
	limparBuffer();
	
	return entrada;
}

void limparBuffer(void)
{
	char buffer;
	
	/* buffer continuara recebendo caracteres ate que */
	/* chege em um \n ou em End Of File (EOF) */
	while((buffer = getchar()) != '\n' && buffer != EOF)
		;
}
