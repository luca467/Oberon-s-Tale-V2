//Progetto di AZZARELLI MATTEO

#include <stdio.h>
#include "mylib.h"

enum selection{
	InsHead = 1,
	InsTail,
	RmvHead,
	RmvTail,
	RmvId,
	RmvTitleChar,
	PrintElem,
	PrintList,
	PrintAllByGenre,
	CopyOut,
	CopyIn,
	OrderListId,
	OrderListTitle,
	SearchId,
	Menu = 19,
	Exit = 20
};

//prototipi delle funzioni
void clearScreen();
void enterToContinue();

int main(){
	int status = -1,	//variabile di appoggio per selezionare la funzione
		exit = 0,	//variabile che definisce se terminare il programma o meno
		menu = 1;	//variabile che definisce quale interfaccia utilizzare
	unsigned short id;
	char c;
	while(!exit){	
		if(menu){
			printf(	"\t\t\t\t\t   ---------------------------\n"
					"\t\t\t\t\t   |           MENU          |\n"
					"\t\t\t\t\t   |    GESTIONE LIBRERIA    |\n"
					"\t\t\t\t\t   ---------------------------\n\n"
					"\t\t\t\t\t      INSERISCI UN ELEMENTO\n"
					"\t 1 - Inserisci un elemento nella prima posizione\t"
					" 2 - Inserisci un elemento nell'ultima posizione\n\n"
					"\t\t\t\t\t\tRIMUOVI ELEMENTO\n"
					"\t 3 - Rimuovi l'elemento della prima posizione\t\t"
					" 4 - Rimouvi l'elemento nell'ultima posizione\n"
					"\t 5 - Rimuovi l'elemento di ID specificato\t\t"
					" 6 - Rimuovi tutti gli elementi che iniziano con un carattere\n\n"
					"\t\t\t\t\t\tSTAMPA ELEMENTI\n"
					"\t 7 - Stampa i dati di un elemento tramite l'ID\t\t"
					" 8 - Stampa tutta la lista degli elementi\n"
					"\t 9 - Stampa tutti i libri di un dato genere\n\n"
					"\t\t\t\t\t\tREGISTRA COPIE\n"
					"\t10 - Registra una copia in uscita\t\t\t"
					"11 - Registra una copia in rientro\n\n"
					"\t\t\t\t\t\tORDINA ELEMENTI\n"
					"\t12 - Ordina la lista con ID crescente\t\t\t"
					"13 - Ordina la lista con titolo in ordine alfabetico\n\n"
					"\t\t\t\t\t\t  VERIFICA ID\n"
					"\t14 - Verifica presenza di un ID\n\n\n"
					"\t19 - Menu' compresso\t\t\t\t\t"
					"20 - EXIT\n\n");
			do{
				scanf("%d",&status);
			}while(!((status>=1 && status<=14) || (status>=19 && status<=20)));
		
			switch(status){
				case InsHead:
					insHead();
					enterToContinue();
					break;
				case InsTail:
					insTail();
					enterToContinue();
					break;
				case RmvHead:
					rmvHead();
					enterToContinue();
					break;
				case RmvTail:
					rmvTail();
					enterToContinue();
					break;
				case RmvId:
					printf("Inserisci l'id del libro da rimuovere ");
					scanf("%hu",&id);
					rmvId(id);
					enterToContinue();
					break;
				case RmvTitleChar:
					rmvTitleChar();
					enterToContinue();
					break;
				case PrintElem:
					printf("Inserisci l'id del libro da cercare e stampare i dati: \n ");
					scanf("%hu",&id);
					printElem(id);
					enterToContinue();
					break;
				case PrintList:
					printList();
					enterToContinue();
					break;
				case PrintAllByGenre:
					printAllByGenre();
					enterToContinue();
					break;
				case CopyOut:
					printf("Inserisci l'id del libro da prestare ");
					scanf("%hu",&id);
					copyOut(id);
					enterToContinue();
					break;
				case CopyIn:
					printf("Inserisci l'id del libro da riprendere ");
					scanf("%hu",&id);
					copyIn(id);
					enterToContinue();
					break;
				case OrderListId:
					orderListId();
					enterToContinue();
					break;
				case OrderListTitle:
					orderListTitle();
					enterToContinue();
					break;
				case SearchId:
					printf("Inserisci l'id del libro da cercare ");
					scanf("%hu",&id);
					printf("%s\n",searchId(id)?"Elemento trovato": "Elemento non trovato");
					enterToContinue();
					break;
				case Menu:
					menu = 0;
					clearScreen();
					break;
				case Exit:
					exit = 1;
					break;
			}
		}else{
			printf(	"\t\t\t\t\t---------------------------\n"
					"\t\t\t\t\t|           MENU          |\n"
					"\t\t\t\t\t|    GESTIONE LIBRERIA    |\n"
					"\t\t\t\t\t---------------------------\n\n"
					"\t\t\t\t\t 1 - Inserisci un elemento\n"
					"\t\t\t\t\t 2 - Rimuovi elementi\n"
					"\t\t\t\t\t 3 - Stampa elementi\n"
					"\t\t\t\t\t 4 - Registra copie\n"
					"\t\t\t\t\t 5 - Ordina la lista\n"
					"\t\t\t\t\t 6 - Verifica presenza di un ID\n"
					"\t\t\t\t\t 9 - Menu' esteso\n\n"
					"\t\t\t\t\t10 - EXIT\n"
			  );
			do{
				scanf("%d",&status);
			}while(!((status >= 1 && status <= 6) || (status >= 9 && status <= 10)));
			
			switch(status){
				case 1:
					clearScreen();
					printf(	"\t---------------------------\n"
							"\t|           MENU          |\n"
							"\t|  INSERISCI UN ELEMENTO  |\n"
							"\t---------------------------\n\n"
							" 1 - prima posizione\n"
							" 2 - ultima posizione\n\n"
							"10 - BACK\n"
						  );
					do{
						scanf("%d",&status);
					}while(!((status >= 1 && status <= 2) || status == 10));
					switch(status){
						case InsHead:
							insHead();
							enterToContinue();
							break;
						case InsTail:
							insTail();
							enterToContinue();
							break;
						case 10:
							clearScreen();
							break;
					}
					break;
				case 2:
					clearScreen();
					printf(	"\t---------------------------\n"
							"\t|           MENU          |\n"
							"\t|     RIMUOVI ELEMENTO    |\n"
							"\t---------------------------\n\n"
							" 1 - elemento della prima posizione\n"
							" 2 - elemento nell'ultima posizione\n"
							" 3 - elemento di ID specificato\n"
							" 4 - tutti gli elementi che iniziano con un carattere\n"
							"10 - BACK\n"
						  );
					do{
						scanf("%d",&status);
					}while(!((status >= 1 && status <= 4) || status == 10));
					switch(status){
						case RmvHead-2:
							rmvHead();
							enterToContinue();
							break;
						case RmvTail-2:
							rmvTail();
							enterToContinue();
							break;
						case RmvId-2:
							printf("Inserisci l'id del libro da rimuovere ");
							scanf("%hu",&id);
							rmvId(id);
							enterToContinue();
							break;
						case RmvTitleChar-2:
							rmvTitleChar();
							enterToContinue();
							break;
						case 10:
							clearScreen();
							break;
					}
					break;
				case 3:
					clearScreen();
					printf(	"\t---------------------------\n"
							"\t|           MENU          |\n"
							"\t|     STAMPA ELEMENTI     |\n"
							"\t---------------------------\n\n"
							" 1 - Stampa i dati di un elemento tramite l'ID\n"
							" 2 - Stampa tutta la lista degli elementi\n"
							" 3 - Stampa tutti i libri di un dato genere\n"
							"10 - BACK\n"
						  );
					do{
						scanf("%d",&status);
					}while(!((status >= 1 && status <= 3) || status == 10));
					switch(status){
						case PrintElem-6:
							printf("Inserisci l'id del libro da cercare e stampare i dati: \n ");
							scanf("%hu",&id);
							printElem(id);
							enterToContinue();
							break;
						case PrintList-6:
							printList();
							enterToContinue();
							break;
						case PrintAllByGenre-6:
							printAllByGenre();
							enterToContinue();
							break;
						case 10:
							clearScreen();
							break;
					}
					break;
				case 4:
					clearScreen();
					printf(	"\t---------------------------\n"
							"\t|          MENU           |\n"
							"\t|     REGISTRA COPIE      |\n"
							"\t---------------------------\n\n"
							" 1 - in uscita\n"
							" 2 - in rientro\n\n"
							"10 - BACK\n"
						  );
					do{
						scanf("%d",&status);
					}while(!((status >= 1 && status <= 2) || status == 10));
					switch(status){
						case CopyOut-9:
							printf("Inserisci l'id del libro da prestare ");
							scanf("%hu",&id);
							copyOut(id);
							enterToContinue();
							break;
						case CopyIn-9:
							printf("Inserisci l'id del libro da riprendere ");
							scanf("%hu",&id);
							copyIn(id);
							enterToContinue();
							break;
						case 10:
							clearScreen();
							break;
					}
					break;
				case 5:
					clearScreen();
					printf(	"\t---------------------------\n"
							"\t|           MENU          |\n"
							"\t|     ORDINA ELEMENTI     |\n"
							"\t---------------------------\n\n"
							" 1 - Ordina la lista con ID crescente\n"
							" 2 - Ordina la lista con titolo in ordine alfabetico\n\n"
							"10 - BACK\n"
						  );
					do{
						scanf("%d",&status);
					}while(!((status >= 1 && status <= 2) || status == 10));
					switch(status){
						case OrderListId-11:
							orderListId();
							enterToContinue();
							break;
						case OrderListTitle-11:
							orderListTitle();
							enterToContinue();
							break;
						case 10:
							clearScreen();
							break;
					}
					break;
				case SearchId-8:
					printf("Inserisci l'id del libro da cercare ");
					scanf("%hu",&id);
					printf("%s\n",searchId(id)?"Elemento trovato": "Elemento non trovato");
					enterToContinue();
					break;
				case Menu-10:
					menu = 1;
					clearScreen();
					break;
				case Exit-10:
					exit = 1;
					break;
			}
		}
	}
	return 0;
}

//Funzione di utitlità per simulare una pulizzia del terminale
void clearScreen(){
	int i;
	for(i = 0; i<=80;i++)
		printf("\n");
}

//Funzione che serve per mettere in pausa il programma finche non viene pigiato il tasto enter
void enterToContinue(){
	while ('\n' != getchar ());
	printf ("Pigia enter per continuare...");
	getchar ();
	clearScreen();
}
