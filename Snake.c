#include<stdlib.h>
#include<stdio.h>
#include<windows.h> 
#include<unistd.h>
#include<conio.h>
#include <time.h> 

char const CHAR_VAZIO = 0;//219;
char const CHAR_MEIO_VERTICAL        = 186;
char const CHAR_MEIO_HORIZONTAL      = 205;
char const CHAR_CANTO_DIREITA_BAIXO  = 201;
char const CHAR_CANTO_DIREITA_CIMA   = 200;
char const CHAR_CANTO_ESQUERDA_BAIXO = 187;
char const CHAR_CANTO_ESQUERDA_CIMA  = 188;
char const CHAR_CABECA = 206;
char const CHAR_COMIDA = 207;
unsigned char const teclaDireita  = 77;
unsigned char const teclaEsquerda = 75;
unsigned char const teclaCima     = 72;
unsigned char const teclaBaixo    = 80;

int const MAX_HEIGHT = 20;
int const MAX_WIDTH  = 35;

struct CoordenadasComidinha{
	int X;
	int Y;
};

struct Componente{
       struct Componente *anterior;
       int CoordenadasX;
       int CoordenadasY;
       int descritivo;
       char valor;
       struct Componente *proximo;
};

struct CoordenadasComidinha comidinha[700];
struct CoordenadasComidinha PosicoesComidas;

struct Componente *ponta;
struct Componente *cabeca;
struct Componente *meio;
int Tamanho;
int QuantidadeComidas;
int Pontuacao = 0;

void gotoxy (int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void RemoveCoordenadaComida(int X, int Y){
	int I;
	for (I = 0; I<=699; I++){
		if (comidinha[I].X == X && comidinha[I].Y == Y  ){
			int auxX, auxY;
		    auxX = comidinha[I].X;
		    auxY = comidinha[I].Y;
		    
		    comidinha[I].X = comidinha[700 - Tamanho].X;
		    comidinha[I].Y = comidinha[700 - Tamanho].Y;
		    
		    comidinha[700 - Tamanho].X = auxX;
		    comidinha[700 - Tamanho].Y = auxY;
		    break;
		}
	}
}

void Insere(int X, int Y, char Valor){
	struct Componente *Novo;

	Novo = (struct Componente *) malloc(sizeof(struct Componente));
	Novo->valor = Valor;
	Novo->CoordenadasX = X;
	Novo->CoordenadasY = Y;
	Novo->anterior = NULL;	
    Novo->proximo = ponta;

	ponta = Novo;
	Tamanho++;
	RemoveCoordenadaComida(cabeca->CoordenadasX,cabeca->CoordenadasY);
}

void desenha_pointer(){
	struct Componente *atual;
	atual = ponta;
	int i = 1;
    while (i<=Tamanho){
		gotoxy(atual->CoordenadasX,atual->CoordenadasY);
		printf("%c", atual->valor);
    	atual = atual->proximo;
    	i++;
	}
}

void limpa_pointer(){
	struct Componente *atual;
	atual = ponta;
	int i = 1;
    while (i<=Tamanho){
		gotoxy(atual->CoordenadasX,atual->CoordenadasY);
		printf("%c", CHAR_VAZIO);
    	atual = atual->proximo;
    	i++;
	}
}

void limpa(){
	struct Componente *atual;
	atual = ponta;
	int i = 1;
    while (i<=Tamanho){
    	ponta = atual->proximo;
    	free(atual);
        atual = ponta;
    	i++;
	}
}

void redefineCabeca(unsigned char pTecla){
	struct Componente *cabeca_old;
	struct Componente *anterior;
	
	cabeca_old = cabeca->anterior;
	anterior   = cabeca_old->anterior;
	
	if (anterior->CoordenadasX == cabeca->CoordenadasX){
		cabeca_old->valor = CHAR_MEIO_VERTICAL;
	}else if(anterior->CoordenadasY == cabeca->CoordenadasY){
		cabeca_old->valor = CHAR_MEIO_HORIZONTAL;
	}else if(pTecla == teclaEsquerda){
		if (anterior->CoordenadasY<cabeca->CoordenadasY){
			cabeca_old->valor = CHAR_CANTO_ESQUERDA_CIMA;
		}else{
			cabeca_old->valor = CHAR_CANTO_ESQUERDA_BAIXO;
		}
	}else if(pTecla == teclaDireita){
		if (anterior->CoordenadasY<cabeca->CoordenadasY){
			cabeca_old->valor = CHAR_CANTO_DIREITA_CIMA;
		}else{
			cabeca_old->valor = CHAR_CANTO_DIREITA_BAIXO;
		}
	}else if(pTecla == teclaCima){
		if (anterior->CoordenadasX<cabeca->CoordenadasX){
			cabeca_old->valor = CHAR_CANTO_ESQUERDA_CIMA;
		}else{
			cabeca_old->valor = CHAR_CANTO_DIREITA_CIMA;
		}
	}else if(pTecla == teclaBaixo){
		if (anterior->CoordenadasX<cabeca->CoordenadasX){
			cabeca_old->valor = CHAR_CANTO_ESQUERDA_BAIXO;
		}else{
			cabeca_old->valor = CHAR_CANTO_DIREITA_BAIXO;
		}
	}
}

void ZeraVariaveis(){
	int X, Y, I;
	ponta = (struct Componente *) malloc(sizeof(struct Componente));
	ponta->valor = CHAR_MEIO_VERTICAL;
	ponta->CoordenadasX = 5;
	ponta->CoordenadasY = 5;
	ponta->descritivo = 1;	

	meio = (struct Componente *) malloc(sizeof(struct Componente));
	meio->valor = CHAR_MEIO_VERTICAL;
	meio->CoordenadasX = 5;
	meio->CoordenadasY = 4;
	meio->anterior = ponta;
	meio->descritivo = 2;
	ponta->proximo = meio;

	cabeca = (struct Componente *) malloc(sizeof(struct Componente));
	cabeca->valor = CHAR_CABECA;
	cabeca->CoordenadasX = 5;
	cabeca->CoordenadasY = 3;
	cabeca->anterior = meio;
	cabeca->descritivo = 3;
	meio->proximo = cabeca;
	
	QuantidadeComidas = 0;			

	gotoxy(0, MAX_HEIGHT);
	for (X = 0; X<=MAX_WIDTH; X++ ){
		printf("_");
	}
		
	for (X = 0; X<=MAX_HEIGHT; X++){
		gotoxy(MAX_WIDTH,X);
		printf("|");	
	}
		
	for (X = 0; X <= MAX_WIDTH-1; X++){
		for (Y = 0; Y <= MAX_HEIGHT-1; Y++){
			comidinha[I].X = X;
			comidinha[I].Y = Y;
			I++;
		}
	}
}

void PosicionaComida(){
    srand(time(0)); 
    
    int fator =  (rand() %8) + 1;
    fator--;

    if (QuantidadeComidas < 1){
        int max = 700 - Tamanho;
        int lower = fator * (max/8);
	    int upper = lower + (max/8);	    
		if (upper<=700){
		    int num = (rand() % (upper - lower + 1)) + lower;

		    PosicoesComidas.X = comidinha[num -1].X;
		    PosicoesComidas.Y = comidinha[num -1].Y;

		    gotoxy(comidinha[num -1].X, comidinha[num-1].Y);
		    printf("%c", CHAR_COMIDA); 
		    QuantidadeComidas++;
		}
	}
}

int ValidaPosicao(){
	if ((cabeca->CoordenadasX == PosicoesComidas.X) &&
		(cabeca->CoordenadasY == PosicoesComidas.Y ) ){
		return 1;
	}
	

	struct Componente *atual;
	atual = ponta;
	int i = 1;
    while (i<=Tamanho){
    	if  ((cabeca->CoordenadasX == atual->CoordenadasX) &&
		     (cabeca->CoordenadasY == atual->CoordenadasY )&&
			 (cabeca!=atual) ){
			return 2;
		}
    	atual = atual->proximo;
    	i++;
	}
	return 0;
}

void TrocaCoordenadaComida(int pVoltaX, int pVoltaY, int pSaiX, int pSaiY){
	int Volta, Sai;
	int auxX, auxY;
	for (Volta = 700-Tamanho ; Volta<=699; Volta++){
		if (comidinha[Volta].X == pVoltaX && comidinha[Volta].Y == pVoltaY  ){
		    break;
		}
	}
	for (Sai = 0; Sai<=699 - Tamanho; Sai++){
		if (comidinha[Sai].X == pSaiX && comidinha[Sai].Y == pSaiY  ){
		    break;
		}
	}
	
	auxX = comidinha[Volta].X;
	auxY = comidinha[Volta].Y;
	
	comidinha[Volta].X = comidinha[Sai].X;
	comidinha[Volta].Y = comidinha[Sai].Y;
	
	comidinha[Sai].X = auxX;
	comidinha[Sai].Y = auxY;
}

int main(){
	ShowWindow( GetConsoleWindow() , SW_MAXIMIZE);
	
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf; 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE; 
	SetConsoleCursorInfo(hOut, &ConCurInf);

    ZeraVariaveis();
	Tamanho = 1;
	RemoveCoordenadaComida(5,5);

	Tamanho = 2;
	RemoveCoordenadaComida(5,4);

	Tamanho = 3;
	RemoveCoordenadaComida(5,3);

	limpa_pointer();
	desenha_pointer();
	struct Componente *temp;
	struct Componente *temp2;

    int SairDoLoop = 0;
    unsigned char uchTecla;
    
	while(SairDoLoop == 0){
		if(kbhit()){
			uchTecla = getch();
			if (uchTecla == 0x1b){
				SairDoLoop = 1;
			}
	    }
        
        if ((uchTecla == teclaDireita)||
		    (uchTecla == teclaEsquerda)||
			(uchTecla == teclaCima)||
			(uchTecla == teclaBaixo)){
				
		 	limpa_pointer();
		 	int auxX, auxY;
		 	char auxChar;
	        temp =  ponta->proximo;
	        ponta->anterior = cabeca;
	        ponta->proximo = NULL; 

	        auxChar = ponta->valor;	        
	        auxX = ponta->CoordenadasX;
	        auxY = ponta->CoordenadasY;	

	        ponta->valor = CHAR_CABECA;

	        temp2 = ponta;
	        ponta = temp;
	        cabeca->proximo = temp2;
	        temp2->CoordenadasX = cabeca->CoordenadasX;
	        temp2->CoordenadasY = cabeca->CoordenadasY;
	        cabeca = temp2;
	
			if (uchTecla == teclaDireita){
				cabeca->CoordenadasX = cabeca->CoordenadasX + 1;
				
				if (cabeca->CoordenadasX == MAX_WIDTH ){
					cabeca->CoordenadasX = 0;
				}
			}else if (uchTecla == teclaEsquerda){
				cabeca->CoordenadasX = cabeca->CoordenadasX - 1;
				
				if (cabeca->CoordenadasX == -1){
					cabeca->CoordenadasX = MAX_WIDTH - 1 ;
				}
			}else if (uchTecla == teclaCima){
				cabeca->CoordenadasY = cabeca->CoordenadasY - 1;

				if (cabeca->CoordenadasY == -1){
					cabeca->CoordenadasY = MAX_HEIGHT -1;
				}
			}else if (uchTecla == teclaBaixo){
				cabeca->CoordenadasY = cabeca->CoordenadasY + 1;
				if (cabeca->CoordenadasY == MAX_HEIGHT){
					cabeca->CoordenadasY = 0;
				}
			}
			int validacao = ValidaPosicao();
            if (validacao == 1){
            	QuantidadeComidas--;
            	gotoxy(40,1);
				Pontuacao++;
            	printf("PONTUACAO: %d", Pontuacao);
            	Insere(auxX, auxY, auxChar);
			}else if (validacao == 2){
			    SairDoLoop = 1;	
			}else{
				TrocaCoordenadaComida(auxX, auxY, cabeca->CoordenadasX, cabeca->CoordenadasY);
			}
            
			redefineCabeca(uchTecla);
			desenha_pointer();
			PosicionaComida();
            int tempo = 200 - (Pontuacao*3);
            if (tempo > 0){
				Sleep(tempo);
			}else{
				Sleep(0);
			}
		}
	}

    system("cls");
    printf("FIM DE JOGO!\n");
    printf("PONTUACAO %d\n", Pontuacao);
    system("pause");
}
