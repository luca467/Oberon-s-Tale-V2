//Progetto di AZZARELLI MATTEO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib.h"

	//Prototipi delle funzioni Static
	static sBookList* getPBookList();
	static void freeSCell(sCell *pCell);
	static eGenre selectGenere();
	static sDate* inizializeDate();
	static sBook* initializeBook();
	static sCell* initializeCell(sCell *pCellPrev, sCell *pCellNext);
	static void printGenre(sCell *pAppoggio);
	static void printDate(sCell *pAppoggio);
	static void rmvElemByAdr(sCell *rmvCell);
	static void printElemByAdr(sCell *pAppoggio);
	static void swapBook(sCell *p1Appoggio, sCell *p2Appoggio);
	void stringToLowerCase(char *s, char *appoggio);

	//-----------------------------
	//|----- STATIC FUNCTION -----|
	//-----------------------------
	static sBookList *bookList = NULL;
	
	/*	Funzione che restituisce l'indirizzo di memoria della struttura bookList
	 *	Utilizzo la tecnica del Singleton per far si che ogni utilizzo della bookList venga richiamata
	 *	tramite questa funzione.
	 *	Quindi se la variabile *booklist è già allocata, la funzione restituisce l'indirizzo di memoria corrispondente
	 *	altrimenti cerca di allocare memoria per la bookList, se non dovesse riuscirci il programma termina
	 */
	static sBookList* getPBookList(){
		if(bookList == NULL){	//controllo se booklist e' inizializzata
			bookList = calloc(1 , sizeof(sBookList));	//alloco memoria per bookList e 
														//tramite calloc inizializza tutti i valori a 0(NULL)
			if(bookList == NULL){	//controllo se booklist e' stata inizializzata correttamente dalla calloc, se ha fallito sttampo a video un errore e termina il programma
				puts("Errore, allocazione di memoria non riuscita\n");
				exit(EXIT_FAILURE);		//Dato che la memoria per la bookList non è stata allocata, cio' provocherebbe un errore irreversibile nell'esecuzione delle funzioni, quindi termino il programma.
			}
		}
		return bookList;	//Ritorna il puntatore alla varialile booklist
	}
	
	//funzione per liberare la memoria di una data cella della lista tramite l'indirizzo di memoria di quest'ultima
	static void freeSCell(sCell *pCell){
		free(pCell->book->date);	//libero la memoria della struttura date
		free(pCell->book);	//libero la memoria della struttura book
		free(pCell);	//libero la memoria della cella
	}
	
	//selezione del genere del libro
	static eGenre selectGenere(){
		int genere;
		do{	
			puts("Scegli il genere del libro\n\t0 - thriller\n\t1 - novel\n\t2 - fantasy");
			scanf("%d", &genere);
		}while(genere <=-1 || genere >= 3 );	//controllo che la selezione dell'utente sia coerente con le possibilità date
		return genere;
	}
	
	//alloco memoria per la struttura date e richiede l'inserimento dei valori
	static sDate* inizializeDate(){
		sDate *pSDate = malloc(sizeof(sDate));	//alloco memoria per la struttura sDate
		if(pSDate != NULL){	//controllo se la struttura dati è stata allocata correttamente
			int bisestile = 0;	//variabile di controllo per l'anno bisestile
			puts("Inserisci la data di pubblicazione del libro");
			puts("Inserisci l'anno");
			scanf("%hd", &(pSDate->year));
			bisestile = pSDate->year%4==0 && (pSDate->year % 400 == 0 || pSDate->year % 100 !=0);	//Verifica anno bisestile(Un anno è bisestile se il suo numero è divisibile per 4, con l'eccezione degli anni secolari (quelli divisibili per 100) che non sono divisibili per 400.)
			do{
				puts("Inserisci il mese");
				scanf("%hu", &(pSDate->month));
			}while(!(pSDate->month >= 1 && pSDate->month <= 12));	//controllo che la selezione del mese sia appropriata
			do{
				puts("Inserisci il giorno");
				scanf("%hu", &(pSDate->day));
			}while(!(pSDate->day >= 1 && ((pSDate->month == 2 && pSDate->day <= (!bisestile ? 28 : 29)) || ((pSDate->month == 4 || pSDate->month == 6 || pSDate->month == 9 || pSDate->month == 11) && pSDate->day <= 30) || ((pSDate->month == 1 || pSDate->month == 3 || pSDate->month == 5 || pSDate->month == 7 || pSDate->month == 8 || pSDate->month == 10 || pSDate->month == 12) && pSDate->day <= 31))));	//controllo sui giorni dei vari mesi
		}else{	//se l'allocazione di memoria fallisce, restituisce un errore e termina il programma
			puts("Errore, allocazione di memoria non riuscita\n");
			exit(EXIT_FAILURE);		//Dato che la memoria per la bookList non è stata allocata, cio' provocherebbe un errore irreversibile nell'esecuzione delle funzioni, quindi termino il programma.
		}
		return pSDate;
	}
	
	//alloco memoria per la struttura sBook e faccio inserire i dati
	static sBook* initializeBook(){
		sBook *pSBook = malloc(sizeof(sBook));	//alloco memoria per la struttura sBook
		if(pSBook != NULL){	//controllo se ha allocato correttamente la memoria
			puts("Inserisci il titolo del libro");
			scanf("\n%63[^\n]%*[^\n]", pSBook->title);
			puts("Inserisci il nome e cognome dell'autore");
			scanf("\n%31[^\n]%*[^\n]", pSBook->writer);
			//controllo che la scelta effettuata dall'utente sia corretta
			int genere = selectGenere();
			switch(genere){
				case thriller:
					pSBook->genre = thriller;
					break;
				case novel:
					pSBook->genre = novel;
					break;
				case fantasy:
					pSBook->genre = fantasy;
					break;
			}
			pSBook->date = inizializeDate();
			puts("Inserisci il numero di copie presenti in biblioteca");
			scanf("%hd", &(pSBook->inLibrary));
			pSBook->outLibrary = 0;
			do{
				puts("Inserisci l'ID del libro");
				scanf("%hu", &(pSBook->id));
			}while(searchId(pSBook->id));
			puts("\n\tINSERIMENTO COMPLETATO\n\n");
			return pSBook;
		}else{
			puts("Errore, allocazione di memoria non riuscita\n");
			exit(EXIT_FAILURE);		//Dato che la memoria per la bookList non è stata allocata, cio' provocherebbe un errore irreversibile nell'esecuzione delle funzioni, quindi termino il programma.
		}
	}

	//passare l'indirizzo di memoria della cella successiva inserire null se è l'ultimo elemento della lista
	static sCell* initializeCell(sCell *pCellPrev, sCell *pCellNext){
		sCell *pSCell = malloc(sizeof(sCell));	//alloco memoria per la sCell
		if(pSCell != NULL){
			pSCell->pPrev = pCellPrev;	//associo il puntatore al precedente
			pSCell->pNext = pCellNext;	//associo il puntatore al successivo
			pSCell->book = initializeBook();	//associo il puntatore alla struttura book che è restituito dalla funzione chiamata
			return pSCell;
		}else{
			puts("Errore, allocazione di memoria non riuscita\n");
			exit(EXIT_FAILURE);		//Dato che la memoria per la bookList non è stata allocata, cio' provocherebbe un errore irreversibile nell'esecuzione delle funzioni, quindi termino il programma.
		}
	}

	//Stampa a video il genere di un libro dato come parametro l'indirizzo di memoria del libro
	static void printGenre(sCell *pAppoggio){
		switch((pAppoggio->book)->genre){
			case thriller:
				puts("Genere: thriller");
				break;
			case novel:
				puts("Genere: novel");
				break;
			case fantasy:
				puts("Genere: fantasy");
				break;
		};
	}
	
	//Stampa a video la data di pubblicazione del libro dato come parametro l'indirizzo di memoria del libro
	static void printDate(sCell *pAppoggio){
		printf("Anno: %u - mese: %hu - giorno: %hu\n", ((pAppoggio->book)->date)->year, ((pAppoggio->book)->date)->month, ((pAppoggio->book)->date)->day);
	}

	//rimuovi un elemento passatogli come parametno l'indirizzo di memoria dell'elemento
	static void rmvElemByAdr(sCell *rmvCell){
		if(getPBookList()->pFirst == rmvCell)
			rmvHead();
		else if(getPBookList()->pLast == rmvCell)
			rmvTail();
		else{
			(rmvCell->pPrev)->pNext = rmvCell->pNext;
			(rmvCell->pNext)->pPrev = rmvCell->pPrev;
			freeSCell(rmvCell);
			puts("--RIMOZIONE AVVENUTA CON SUCCESSO--\n");
		}
	}
	
	/**	Funzione di utilità:
	 *	Stampa tutti i campi di un Elemento tramite l'indirizzo della cella
	**/
	static void printElemByAdr(sCell *pAppoggio){
		if(pAppoggio != NULL){
			//printf("LOCAZIONI MEMORIA:\n\tPrecedente: %p\n\tCorrente: %p\n\tSuccessivo: %p\n", pAppoggio->pPrev, pAppoggio, pAppoggio->pNext);	//utilità per debug
			printf("Id Libro: %hu\n",(pAppoggio->book)->id);
			printf("Titolo: %s\n",(pAppoggio->book)->title);
			printf("Scrittore: %s\n",(pAppoggio->book)->writer);
			printGenre(pAppoggio);
			printDate(pAppoggio);
			printf("Libri in Biblioteca: %hu\n",(pAppoggio->book)->inLibrary);
			printf("Libri prestati Biblioteca: %hu\n\n",(pAppoggio->book)->outLibrary);
			puts("Operazione eseguita con successo\n\n");
		}else
			puts("Non ci sono libri con questo ID\n");
	}
	
	//scambia i puntatori ai rispettivi book delle due celle passate come parametro, funzione di utilità
	static void swapBook(sCell *p1Appoggio, sCell *p2Appoggio){
		sBook *pAppoggio;
		pAppoggio = p1Appoggio->book;
		p1Appoggio->book = p2Appoggio->book;
		p2Appoggio->book = pAppoggio;
	}
	
	//Funzione che serve per trasformare una stringa in miniscolo passatogli come parametri la stringa e l'indirizzo di memoria della stringa di appoggio
	void stringToLowerCase(char *s, char *appoggio){
		int conta;
		for(conta = 0; conta < strlen(s); conta++){	//scorro tutta la stringa s
			appoggio[conta] = tolower(s[conta]);	//converto carattere a carattere in minuscolo
		}
		appoggio[conta] = '\0';	//aggiungo il carattere di terminazione in fondo alla stringa
	}
		
	//--------------------------
	//|--- PROGECT FUNCTION ---|
	//--------------------------

	//Inserimento di un elemento in cima alla lista
	void insHead(){
		//printf("-insHead-\n");
		sCell *pSCell;
		if(getPBookList()->pLast == NULL){	//controllo se la lista è vuota e inserisco il primo libro
			pSCell = initializeCell(NULL, NULL);
			getPBookList()->pLast = pSCell;
		}else{	//altrimenti inserisco in testa
			pSCell = initializeCell(NULL, getPBookList()->pFirst);
			getPBookList()->pFirst->pPrev = pSCell;
		}
		getPBookList()->pFirst = pSCell;
	}

	//Inserimento di un elemento in fondo alla lista
	void insTail(){
		//printf("-insTail-\n");
		if(getPBookList()->pFirst == NULL){	//controllo se la lista è vuota, in tale caso richiamo la funzione insHead che gestisce questo caso
			insHead();
		}else{	//altrimenti inserisco in coda
			(getPBookList()->pLast)->pNext = initializeCell(getPBookList()->pLast, NULL);
			getPBookList()->pLast = (getPBookList()->pLast)->pNext;
		}
	}

	//rimuovi il primo elemento della lista
	void rmvHead(){
		//printf("-RemoveHead-\n");
		if(getPBookList()->pFirst != NULL){	//controllo se la lista è vuota
			if((getPBookList()->pFirst)->pNext == NULL){	//caso in cui è presente un solo elemento
				puts("E' l'unico elemento della lista");
				freeSCell(getPBookList()->pFirst);	//Libero la memoria 
				bookList->pFirst = NULL;	//imposto i puntatori al primo e all'ultimo a NULL
				bookList->pLast = NULL;
				printf("bookList->pFirst: %p - bookList->pLast: %p\n",bookList->pFirst,bookList->pLast);
			}else{
				puts("Non è l'unico elemento della lista, quindi aggiorno i puntatori");
				bookList->pFirst = (getPBookList()->pFirst)->pNext;	//aggiorno il puntatore al primo elemento
				freeSCell(getPBookList()->pFirst->pPrev);	//Libero la memoria
				getPBookList()->pFirst->pPrev = NULL;	//aggiorno il puntatore al precedente del nuovo primo elemento
			}
			puts("--RIMOZIONE AVVENUTA CON SUCCESSO--\n");
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}

	//rimuovi l'ultimo elemento della lista
	void rmvTail(){
		//printf("-RemoveTail-\n");
		if(getPBookList()->pFirst != NULL){	//controllo se la lista è vuota
			if(getPBookList()->pFirst->pNext == NULL)	//se è presente un solo elemento nella lista richiamo la funzione rmvHead che gestisce il caso
				rmvHead();
			else{
				getPBookList()->pLast = getPBookList()->pLast->pPrev;	//aggiorno il valore del pLast
				freeSCell(getPBookList()->pLast->pNext);	//svuoto la memoria
				(getPBookList()->pLast)->pNext = NULL;		//aggiorno il pNext dell'ultimo elemento a NULL
				puts("--RIMOZIONE AVVENUTA CON SUCCESSO--\n");
			}
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}

	/**funzione per cercare un libro tramite l'ID
	 *	Return:
	 *	NULL - elemento non trovato
	 *	indirizzo dell'elemento - elemento trovato
	**/
	sCell* getAdrsFromID(unsigned short searchedId){
		//printf("-getAdrsFromID-\n");
		sCell *appoggio = (getPBookList()->pFirst);	
		//scorro tutta la lista finchè non arrivo all'ultimo elemento o non trovo un ID uguale
		while(appoggio != NULL){
			if(((appoggio->book)->id) == searchedId){
				return appoggio;
			}
			appoggio = appoggio->pNext;		//scorro la lista
		}
		return NULL;
	}

	void rmvId(unsigned short searchedId){
		//printf("-RemoveId-\n");
		if(getPBookList()->pFirst != NULL){
			sCell *pId = getAdrsFromID(searchedId);	//associo l'indirizzo di memoria della cella dell'elemento con id cercato, se non trovato associo NULL
			if(pId == NULL){	//controllo se l'id esiste o meno
				printf("L'Id: %hu non presente\n", searchedId);
			}else{
				rmvElemByAdr(pId);	//rimuovo l'elemento
			}
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}

	//Prestito di un libro con un dato ID
	void copyOut(unsigned short searchedId){
		//printf("-CopyOut-\n");
		if(getPBookList()->pFirst != NULL){	//controllo se la lista è vuota
			sCell *pAppoggio = getAdrsFromID(searchedId);	//associo l'indirizzo della cella dell'elemento di ID cercato
			if(pAppoggio != NULL){	//verifico se l'id è stato trovato
				if((pAppoggio->book)->inLibrary > 0){	//verifico che ci siano ancora copie in libreria
					(pAppoggio->book)->inLibrary--;		//sottraggo un libro dalle copie rimanenti in libreria
					(pAppoggio->book)->outLibrary++;	//aggiungo un libro nelle copie prestate
					puts("Operazione eseguita con successo\n");
				}else
					puts("Non ci sono più copie a disposizione\n");
			}else
				puts("Non ci sono libri con questo ID\n");
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}

	//Rientro di un libro con un dato ID
	void copyIn(unsigned short searchedId){
		//printf("-CopyIn-\n");
		if(getPBookList()->pFirst != NULL){	//controllo se la lista è vuota
			sCell *pAppoggio = getAdrsFromID(searchedId);	//associo l'indirizzo della cella dell'elemento di ID cercato
			if(pAppoggio != NULL){	//verifico se l'id è stato trovato
				if((pAppoggio->book)->inLibrary + 1<=(pAppoggio->book)->inLibrary + (pAppoggio->book)->outLibrary){	//controllo che non si possano ritirare piu' libri di quelli prestati
					(pAppoggio->book)->inLibrary++;	//reinserisco un libro in libreria
					(pAppoggio->book)->outLibrary--;	//sottraggo un libro da quelli prestati
					puts("Operazione eseguita con successo\n");
				}else
					puts("Le copie prestate per questo libro sono già rientrate tutte\n");
			}else
				puts("Non ci sono libri con questo ID\n");
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}

	//Stampa tutti i campi di un dato Libro passatogli l'ID come parametro
	void printElem(unsigned short searchedId){
		//printf("-PrintElem-\n");
		if(getPBookList()->pFirst != NULL){		//controllo se la lista è vuota
			sCell *pAppoggio = getAdrsFromID(searchedId);		//associo l'indirizzo della cella dell'elemento di ID cercato
			printElemByAdr(pAppoggio);	//stampo l'elemento tramite la funzione apposita
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}

	//Stampa di (tutti i campi di) tutta la lista
	void printList(){
		//printf("-PrintList-\n");
		if(getPBookList()->pFirst != NULL){	//controllo se la lista è vuota
			sCell *pAppoggio = getPBookList()->pFirst;
			while(pAppoggio != NULL){
				printElemByAdr(pAppoggio);	//stampo l'elemento corrente tramite l'apposita funzione
				pAppoggio = pAppoggio->pNext;	//scorro la lista
			}
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}


	/**funzione per cercare un libro tramite l'ID
	 *	Return:
	 *	0 - elemento non trovato
	 *	1 - elemento trovato
	**/
	int searchId(unsigned short searchedId){
		//printf("-SearchId-\n");
		if(getPBookList()->pFirst != NULL){	//controllo se esiste almeno un elemento nella lista
			sCell *pAppoggio = (getPBookList()->pFirst);	//Variabile di appoggio, utilizzata per scorrere la lista
			//scorro tutta la lista finchè non arrivo all'ultimo elemento o non trovo un ID uguale
			while(pAppoggio != NULL){
				if(((pAppoggio->book)->id) == searchedId){
					return 1;
				}
				pAppoggio = pAppoggio->pNext;	//scorro la lista
			}
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
		return 0;
	}


	//Stampare tutti i libri della lista con un dato genere (e.g., thriller ) passato dall’utente
	void printAllByGenre(){
		//printf("-PrintAllByGenre-\n");
		if(getPBookList()->pFirst != NULL){	//controllo che la lista non sia vuota
			eGenre genre = selectGenere();	//scelgo il genere
			//scorro tutta la lista e stampo tutti i libri aventi quel dato genere
			sCell *pAppoggio = getPBookList()->pFirst;
			while(pAppoggio != NULL){
				if((pAppoggio->book)->genre == genre){
					printElemByAdr(pAppoggio);
					pAppoggio = pAppoggio->pNext;
				}
			}
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}

	//Ordinamento della lista con ID crescente
	void orderListId(){
		//printf("-orderListId-\n");
		if(getPBookList()->pFirst != NULL){
			if(getPBookList()->pFirst->pNext !=NULL){
				sCell *p1WhileAppoggio = getPBookList()->pFirst,	//Variabile per lo scorrimento della lista
					  *p2WhileAppoggio = getPBookList()->pFirst;	//Variabile per lo scorrimento della lista

				//bubble sort
				while(p1WhileAppoggio != NULL){
					while(p2WhileAppoggio !=NULL){
						if(p1WhileAppoggio->book->id > p2WhileAppoggio->book->id){	//verifico se esistono id maggiori e in caso li scambio di posto per ordinarli
							swapBook(p1WhileAppoggio, p2WhileAppoggio);	//scambio
						}
						p2WhileAppoggio = p2WhileAppoggio->pNext;	//passo all'elemento successivo del ciclo interno
					}
					p2WhileAppoggio = p1WhileAppoggio->pNext;	//passo all'elemento successivo del ciclo esterno
					p1WhileAppoggio = p1WhileAppoggio->pNext;	//passo all'elemento successivo del ciclo esterno
				}
				puts("Lista ordinata con ID Crecente\n");
			}else
				puts("C'e' un solo elemento nella lista, quindi e' ordinata\n");
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}
	
	
	void orderListTitle(){
		//printf("-orderListTitle-\n");
		if(getPBookList()->pFirst != NULL){	//controllo che la lista non sia vuota
			if(getPBookList()->pFirst->pNext !=NULL){	//controllo che l'elemento della lista non sia l'unico
				sCell *p1WhileAppoggio = getPBookList()->pFirst,	//Variabile per lo scorrimento della lista
					  *p2WhileAppoggio = getPBookList()->pFirst;	//Variabile per lo scorrimento della lista
				
				//bobbleSort
				while(p1WhileAppoggio != NULL){	//scorro la lista
					while(p2WhileAppoggio !=NULL){	//scorro la lista
						char titolo1[strlen(p1WhileAppoggio->book->title)], titolo2[strlen(p2WhileAppoggio->book->title)];
						stringToLowerCase(p1WhileAppoggio->book->title, titolo1);	//converto il titolo in minuscolo e lo metto nella variabile titolo1
						stringToLowerCase(p2WhileAppoggio->book->title, titolo2);	//converto il titolo in minuscolo e lo metto nella variabile titolo2
						if(strcmp(titolo1, titolo2)>0){	//comparo i due titoli(tramite strcmp) precedentemente convertiti ambedue in minuscolo
							swapBook(p1WhileAppoggio, p2WhileAppoggio);	//richiamo la funzione swapBook per scambiare di posto ai due libri
						}
						p2WhileAppoggio = p2WhileAppoggio->pNext;	//passo all'elemento successivo del ciclo interno
					}
					p2WhileAppoggio = p1WhileAppoggio->pNext;	//passo all'elemento successivo del ciclo esterno
					p1WhileAppoggio = p1WhileAppoggio->pNext;	//passo all'elemento successivo del ciclo esterno
				}
				puts("Lista ordinata in ordine Alfabetico\n");
			}else
				puts("C'e' un solo elemento nella lista, quindi e' ordinata\n");
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}
	
	//rimuove tutti i libri che iniziano con un determinato carattere passatogli dall'utente
	void rmvTitleChar(){
		//printf("-rmvTitleChar-\n");
		if(getPBookList()->pFirst != NULL){	//verifico che la lista non sia vuota
			char c;	//variabile di appoggio per scegliere il carattere
			puts("Inserisci il carattere iniziale dei libri che vuoi eliminare\n");
			scanf("\n%1[^\n]%*[^\n]",&c);
			//Scorro tutta la lista
			sCell *pAppoggio = getPBookList()->pFirst;
			//scorro tutta la lista
			while(pAppoggio != NULL){
				if(tolower((pAppoggio->book)->title[0]) == tolower(c)){	//comparo la prima lettera del titolo del libro con il carattere inserito, per sicurezza li trasformo ambedue in minuscolo prima di compararli
					rmvElemByAdr(pAppoggio);	//rimuovo l'elemento
				}
				pAppoggio = pAppoggio->pNext;	//scorro la lista
			}
			printf("Elementi che iniziano con %c rimossi con successo\n",c);
		}else
			puts("Errore: Non ci sono elemeti nella lista\n");
	}
