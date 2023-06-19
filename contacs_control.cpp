#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

struct contato{
	char nome [51];
	char telefone[18];

};

#define LIMIT 250 //Limite de contatos para salvar
#define FILE_NAME "contatos_agenda.ccp"
struct contato contatos[LIMIT];
int contador=0;
void limpar(void){
	system("cls");
}
void abrir(){
	FILE *file = fopen(FILE_NAME,"r");//r pq não quero escrever no arquivo
	
	if(!file == NULL){
		contador = 0;
		while(!feof(file)){ //comando feof ajuda a saber se esta no final do arquivo
			fgets(contatos[contador].nome, 50, file); //contador de linha
			if(strcmp(contatos[contador].nome, "")> 0){//comparando para saber quando chegar na linha em branco
				fgets(contatos[contador].telefone, 18, file);
				contador++;
			}else{
				//printf("error ao carregar Contatos");
			}
	
		}
	}
	
	fclose(file);
}
void salvarContato(contato ctt, FILE *file){
	fputs(ctt.nome,file);
	fputs(ctt.telefone,file);
}

bool novoFile(int ignore){
	
	bool r = false;
	contato tempo[LIMIT];//tive que criar outro pois nao estava salvado quando excluia 
	int n = 0;
	
	remove(FILE_NAME); //romovo e crio outra pasta para salvar altereção
	FILE *file = fopen(FILE_NAME, "a+");
	
	
	if(!file == NULL){
	
		for (int i=0; i<contador;i++){
			if(i != ignore){
				salvarContato(contatos[i], file);
				tempo[n]= contatos[i];
				n++;
			}
		}
		for(int i=0; i<n; i++){
			contatos[i] = tempo[i];
		}
		contador = n;
		r = true;
    }
    return r;
}

bool inserirContato(contato ctt){
	
	bool r = false;
	FILE *file = fopen(FILE_NAME , "a+"); //a+ serve para que se o arquivo nao existe ele seja criado na hora.
	if(!file == NULL){
		r = true;
		salvarContato(ctt, file);
		contatos[contador] = ctt;
		contador++;
	}
	fclose(file);
	
	return r;
}
void criarCont(){
	printf("\n NOVO CONTATO\n");
	
	contato ctt; //vai ser temporario so vai existe neste escopo 
	if(contador <= LIMIT){
	
		printf("Nome: ");
		fgets(ctt.nome, 50, stdin);
		fflush(stdin);
		printf("Telefone: ");
		fgets(ctt.telefone, 18, stdin);
		if(inserirContato(ctt)){
			printf("\nContato Salvo!\n\n\n");
			system("pause");
			limpar();
		}else{
			printf("Erro!!!\n");
		}
	}else{
		printf("SEM ESPACO NA MEMORIA!!\n\n");
	}
}
void editarCont(int i){//i é o contato selecionado
	 contato ctt;
	
	printf("\nEDITAR CONTATO\n");
	
	printf("%s",contatos[i].nome);
	fgets(ctt.nome, 50, stdin);
	fflush(stdin);
	
	if(strlen(ctt.nome) > 1){
		strcpy(contatos[i].nome, ctt.nome); //strcpy muda caractere do tipo string strcpy(<variavel que quer que seja alteirada, variavel que vai no lugar.)
	}
	printf("%s",contatos[i].telefone);
	fgets(ctt.telefone, 18, stdin);
	fflush(stdin);
	if(strlen(ctt.telefone) > 1){ // maior que 1 pq o enter conta como 1.
		strcpy(contatos[i].telefone, ctt.telefone); //strcpy muda caractere do tipo string strcpy(<variavel que quer que seja alteirada, variavel que vai no lugar.)
	}
	if(novoFile(-1)){
		printf("\n\nCONTATO SALVO!!\n\n");
	}else{
		printf("ERRO AO SALVAR!!\n\n");
	}
}

bool confirmar(char *menssagem){// * na string pq tem que ter referencia se não sempre vai dar erro
	char r;
	
	printf("%s  S para Sim ou N para NAO : ", menssagem );
	scanf("%c", &r);
	
	if(r == 's'|| r == 'S'){
		return true;
		
	}
	else{ //(r == 'n' || r == 'N'){
		return false;
	}//else{
		//printf("opcao invalida!!!");
	//}
	}

void deletCont(int i){
	if(confirmar("\nDeseja Excluir Este Contato\n")){
		novoFile(i);
		printf("\n\nContato Excluido com Sucesso!!\n\n");
	}
	
	
}
void menuSelecionar(){
	int selec =-1;
	int op = 0;
	
	printf("\n\nInsira o Codigo do Contato que deseja Selecionar: | 0 para Voltar ao Menu: ");
	scanf("%i",&selec);
	fflush(stdin);
	limpar();
	if(selec> 0 ){
		if(selec <= LIMIT){
			selec --;
			printf("\nSelecionado : %s\n",contatos[selec].nome);
			printf("1 - Editar\n");
			printf("2 - Excluir\n");
			printf("0 - sair\n");
			scanf("%i",&op);
			fflush(stdin);
			if(op!=0){
			
				switch(op){
					case 1:
						editarCont(selec);
						break;
					case 2:
						deletCont(selec);
						break;
				}
			}
		}
	}
}
void contatosExibir(int i){
	
	printf("[%i] %s", i+1,contatos[i].nome);
	printf("%s", contatos[i].telefone);
}
void listContatos(){
	printf("\nLISTA DE CONTATOS\n");
	
	for(int i=0;i<contador;i++){
		contatosExibir(i);
		printf("------------------------\n");
	}
	if(contador >0){
	
	menuSelecionar();
}
}
bool matchContatos(char *a, char *b, int i , int limit){
	if(a[i] == b[i]){
		i++;
		if(i<limit){
			return matchContatos(a, b, i ,limit);
			
		}else{
			return true;
		}
	}else{
		return false;
	}
	
	
}
void buscarContatos(){
	char nome[51]={""}; //inicializada Vazia
	bool encontrado = false;
	printf("\nBUSCA DE CONTATOS \n\n");
	printf("Digite o Nome para Buscar: ");
	fgets(nome, 50, stdin);
	fflush(stdin);
	
	int limit = strlen(nome); //strlen le e mede o tamanho do string
	limit -=1;// diminuindo 1 por conta da quebra de linha
	printf("Resultado: \n\n");
	for(int i=0; i<contador; i++){ // percorrer o array verificando se é igual.
		if(strlen(contatos[i].nome) >= limit){
			if (matchContatos(nome, contatos[i].nome, 0, limit)){
				contatosExibir(i);
				printf("----------------------\n");
				encontrado=true;
			}
		}
	
	}
	
	if(encontrado){
		
		menuSelecionar();
	}
}

void menu(void){
 int op=0;
 
 do{
 
 printf ("Selecione a Opecao desejada: \n");
 printf("1 - Novo Contato:\n");
 printf("2 - Lista de Contatos:\n");
 printf("3 - Buscar Contato\n");
 printf("4 - Sair\n");	
 
 
 scanf("%i", &op);
 fflush(stdin);
 limpar();
 switch(op){
 	case 1: 
 		criarCont();	
 		break;
 	case 2:
 		listContatos();
 		break;
 	case 3:
 		buscarContatos();
 		break;
 		
 		default: printf("Ate Logo!!!");
 		
 }
 
 }while(op != 4);	
}

int main(){
	abrir();
	menu();
}
