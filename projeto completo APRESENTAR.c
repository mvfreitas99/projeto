#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iso646.h>

//definição dos valores máximos de cada componente do circuito
#define ENTRADAS 10
#define SAIDASMAX   10
#define PORTASMAX	10
#define CONECTORMAX 50
#define COMBINACOES 1024

#define AND 	1
#define OR	    2
#define NOT 	3
#define NOR 	4
#define NAND	5
#define XOR	    6
#define XNOR    7
//cria o struct da tabela-verdade
struct tabela{
	int matrizTabela[COMBINACOES][ENTRADAS];
};
//a seguir serão criados os structs das portas logicas, entradas, saidas e conectores, além do
//contador que servirá para verificar quantas vezes um elemento foi resolvido
struct portas{
	int tipo;
	int input[2];
	int output;
	int estado;
};
struct conectores{
	int valor;
	int no;
};
struct input{
	char representacao[5];
	int valor;
	int no;
};
struct output{
	char representacao[5];
	int valor;
	int no;
};
struct contador{
	int conectores;
    int in;
    int out;
    int Porta;
    int Vez;
    int Linha;
};

//criação do array de structs
struct portas porta[PORTASMAX];
struct conectores conect[CONECTORMAX];
struct input in[ENTRADAS];
struct output out[SAIDASMAX];
struct tabela table;
struct contador n;

//A função resolverPorta serve para resolver o circuito lógico fornecido pelo usuário, este circuito será 
//resolvido a partir do switch-case, que recebe como atributos o tipo da porta e suas entradas, podendo assim
//ser resolvido e o resultado, armazenado na saída da porta
int resolverPorta(int tipo, int a, int b){
    switch(tipo){
    	case NOT:
        return !a;
        break;
        
        case AND:
        return a&b;
        break;

        case OR:
        return a|b;
        break;

        case NAND:
        return !(a&b);
        break;
        
        case NOR:
        return !(a|b);
        break;
        
        case XOR:
        return a^b;
        break;
        
        case XNOR:
        return !(a^b);
        break;
    }
}//a função tabela_Verdade serve para atribuir os valores das entradas do circuito
int tabela_Verdade(int nInput){
	char vet[10];
	int in, j, l=0;
    for(in = 0; in < (pow(2, nInput)); in++){
        vet[0] = (in & 1  )?1:0;      
        vet[1] = (in & 2  )?1:0;      
        vet[2] = (in & 4  )?1:0;
        vet[3] = (in & 8  )?1:0;
        vet[4] = (in & 16 )?1:0;
        vet[5] = (in & 32 )?1:0;
        vet[6] = (in & 64 )?1:0;
        vet[7] = (in & 128)?1:0;
        vet[8] = (in & 256)?1:0;
        vet[9] = (in & 512)?1:0;
      
        for(j = 0; j < nInput; j++){
            table.matrizTabela[in][l] = vet[j];
            l++;
        }l=0;
    }
}
int iniciarDados(int qtdEntradas, int qtdConector, int qtdportas, int qtdlinhas){
	int k, l, m, n, o, coluna=0;

	for(k = 0; k < qtdConector; k++){
		conect[k].valor = 5;
	}

	for(l = 0; l < qtdportas; l++){
		porta[l].estado = 0;
	}
	
	for(m = 0; m < qtdEntradas; m++){
		in[m].valor = table.matrizTabela[qtdlinhas][coluna];
		coluna++;
	}

	for(n = 0; n < qtdEntradas; n++){
		for(o = 0; o < qtdConector; o++){
			if(in[n].no == conect[o].no){
				conect[o].valor = in[n].valor;
			}	
		}
	}	return 0;
}
//esta funçao imprimir() serve para desenhar a tabela verdade e seus espaçamentos
int Imprimir(int qtdEntradas, int qtdSaidas){
    int p, q, r, s, t, u, z;
      
    if(n.Vez == 0){

        for(p = qtdEntradas*4+qtdSaidas*4+3;p > 0;p--){
			printf("-");
		}
		printf("\n");
        for(q = 0; q < qtdEntradas; q++){
			printf("| %s ", in[q].representacao);
		}
		printf("|-");

        for(r = 0; r < qtdSaidas; r++){
			printf("| %s ", out[r].representacao);
		}
		printf("|\n");

        for(s = qtdEntradas*4 + qtdSaidas*4 + 3; s > 0; s--){
			printf("-");
		}
			printf("\n");
    }

    for(t = 0; t < qtdEntradas; t++){
        printf("| %d ", in[t].valor);
    }
        printf("|-");
    for(u = 0; u < qtdSaidas; u++){
        printf("| %d ", out[u].valor);
    }
        printf("|\n"); n.Vez++;
}
int salvarConector(int inputNo, int qtdConector){
	int t;
	for(t= 0; t < qtdConector; t++){
		if(inputNo == conect[t].no){
			return 1;
		}
	}	
	conect[qtdConector].no = inputNo;
	n.conectores++;
	return 0;
}
int lerCircuito(){
	//declaração de variáveis, "n" representa o struct
	n.conectores = 0; 
	n.in = 0;
    n.Porta = 0;
    n.out = 0;
    n.Linha = 0;
    n.Vez = 0;
    int resultado = 0;
    int a, b, c, d, e, f, g, h, i, j; 
	char nomeCircuito[50]; 
	char localArquivo[100]; 
	char tipo[10]; 

	/*O programa pede ao usuário que informe onde está localizado o arquivo-circuito
	e o armazena em uma string
	*/
	printf("Digite o diretorio onde o arquivo esta localizado: ");
	fgets(localArquivo, 100, stdin);
	for(a = 0; a < 99; a++){
		if(localArquivo[a] == 10){
			localArquivo[a] = 0;
			break;
		}
	}
	//após gravar o diretório do arquivo, o programa tenta abri-lo como um arquivo de texto
	FILE *arquivo = fopen(localArquivo, "r");
    
    //caso o arquivo especificado pelo usuário não exista, o programa retornará uma mensagem e será preciso rever
	if(arquivo == NULL){ 
		printf("Arquivo nao encontrado\n");
     	return 0;
	}
	/*caso o arquivo exista, serão feitas leituras dentro dele a fim de encontrar as portas logicas, se caso não
	houver nenhum erro, será armazenado dentro dos arrays, caso tenha uma palavra errada ou fora de ordem, será 
	mostrado uma mensagem informando que houve erro ao ler o arquivo, o while rodará até que a ultima linha do
	arquivo de texto for lida
	*/
	while(fscanf(arquivo, "%s", tipo) != EOF){
		
		if(!strcmp(tipo, "CIRCUIT")){
			fgets(nomeCircuito, 50, arquivo);
		}
		else if(!strcmp(tipo, "NOT")){
			fscanf(arquivo, "%d %d", &porta[n.Porta].input[0], &porta[n.Porta].output);
            salvarConector(porta[n.Porta].input[0], n.conectores);
            salvarConector(porta[n.Porta].output, n.conectores);
			porta[n.Porta].tipo = NOT; n.Porta++;
		}
		else if(!strcmp(tipo, "AND")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
            salvarConector(porta[n.Porta].input[0], n.conectores);
            salvarConector(porta[n.Porta].input[1], n.conectores);
			salvarConector(porta[n.Porta].output, n.conectores);
			porta[n.Porta].tipo = AND; n.Porta++;
		}
		else if(!strcmp(tipo, "OR")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
            salvarConector(porta[n.Porta].input[0], n.conectores);
            salvarConector(porta[n.Porta].input[1], n.conectores);
            salvarConector(porta[n.Porta].output, n.conectores);
			porta[n.Porta].tipo = OR; n.Porta++;
		}
		else if(!strcmp(tipo, "NAND")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
			salvarConector(porta[n.Porta].input[0], n.conectores);
            salvarConector(porta[n.Porta].input[1], n.conectores);
            salvarConector(porta[n.Porta].output, n.conectores);
			porta[n.Porta].tipo = NAND; n.Porta++;
		}
		else if(!strcmp(tipo, "NOR")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
			salvarConector(porta[n.Porta].input[0], n.conectores);
            salvarConector(porta[n.Porta].input[1], n.conectores);
            salvarConector(porta[n.Porta].output, n.conectores);
			porta[n.Porta].tipo = NOR; n.Porta++;
		}
		else if(!strcmp(tipo, "XOR")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
			salvarConector(porta[n.Porta].input[0], n.conectores);
            salvarConector(porta[n.Porta].input[1], n.conectores);
            salvarConector(porta[n.Porta].output, n.conectores);
            porta[n.Porta].tipo = XOR; n.Porta++;
		}	
		else if(!strcmp(tipo, "XNOR")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
			salvarConector(porta[n.Porta].input[0], n.conectores);
            salvarConector(porta[n.Porta].input[1], n.conectores);
            salvarConector(porta[n.Porta].output, n.conectores);
            porta[n.Porta].tipo = XNOR; n.Porta++;
		}
		else if(!strcmp(tipo, "INPUT")){
			fscanf(arquivo, "%d %s", &in[n.in].no, in[n.in].representacao);
            salvarConector(in[n.in].no, n.conectores);
			n.in++;
		}
		else if(!strcmp(tipo, "OUTPUT")){
			fscanf(arquivo, "%d %s", &out[n.out].no, out[n.out].representacao);
            salvarConector(out[n.out].no, n.conectores);
            n.out++;
		}
		//caso exista algo errado no arquivo, o programa mostrará uma mensagem de erro.
		else{
			printf("O arquivo aberto contem erro de escrita, por favor, verificar e corrigir.\n");
            exit(0);
		}
	}
	fclose(arquivo); //fecha o arquivo
    tabela_Verdade(n.in); 
    iniciarDados(n.in, n.conectores, n.Porta, n.Linha);
    //a primeira linha do arquivo deverá ter o nome do circuito que será lido pelo programa
	printf("\nTitulo: %s", nomeCircuito);
	
	//a seguir, o programa lerá as portas do arquivo e atribuirá suas saídas e entradas e resolverá
	//as portas. com isso, tudo será armazenado nos arrays de structs para depois ser imprimidas
    do{
        for(b = 0; b < n.Porta; b++){
            if(porta[b].estado == 0){
            if(porta[b].tipo == NOT){
            for(c = 0; c < n.conectores; c++){
            if(porta[b].input[0] == conect[c].no && conect[c].valor != 5){
            for(d = 0; d < n.conectores; d++){       
            if(porta[b].output == conect[d].no){
                conect[d].valor = resolverPorta(porta[b].tipo, conect[c].valor, 0);
                porta[b].estado = 1;
                break;
            }
        }
    }
}
            }else{
                for(e = 0; e < n.conectores; e++){
                    for(f = 0; f < n.conectores; f++){
                    if(porta[b].input[0] == conect[e].no && porta[b].input[1] == conect[f].no && conect[e].valor != 5 && conect[f].valor != 5){
                    for(g = 0; g < n.conectores; g++){
                    if(porta[b].output == conect[g].no){
                        conect[g].valor = resolverPorta(porta[b].tipo, conect[e].valor, conect[f].valor);
                        porta[b].estado = 1;
                        break;
                            }
                        }
                    }
                }
            }
        }
    }
}
		/*A seguir o programa verificará se todas as portas foram resolvidas, caso não fossem resolvidas, o estado 
		da porta será 0, então um flag chamado "resultado" será incrementado para informar que ainda tem porta sem
		ser resolvida*/
        for(h = 0; h < n.Porta; h++){ 
            if(porta[h].estado == 0){
                resultado++; break;
            }
        }
        /*Caso todas as portas sejam resolvidas, elas serão armazenadas em um array de saída chamado output, para 
		posteriormente ser impresso*/
        if(resultado == 0){ 
            for(i = 0; i < n.out; i++){
                for(j = 0; j < n.conectores; j++){
                    if(out[i].no == conect[j].no){
                        out[i].valor = conect[j].valor;
                    }
                }
            }
            Imprimir(n.in, n.out);
            n.Linha++; resultado = 0;
            iniciarDados(n.in, n.conectores, n.Porta, n.Linha);                                      
        }else{
            resultado = 0;
        }
	}while(n.Linha < pow(2, n.in));//o programa executará todas as possibilidades que possam ser calculadas
}
	
int main(){
	printf("-------------Projeto de Programacao-------------\n");
	//chama a função lerCircuito() para exibir a tabela-verdade
	lerCircuito();
		
	return 0;
}
