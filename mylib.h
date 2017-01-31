//Progetto di AZZARELLI MATTEO

	//Definisco i generi dei vari libri
	typedef enum genre{
		thriller,
		novel,
		fantasy
	} eGenre;

	//Definisco la struttura Date
	typedef struct date {
		unsigned short day;
		unsigned short month;
		short year;
	} sDate;
	
	//definisco la struttora Book
	typedef struct book{
		char title[64];
		char writer[32];
		eGenre genre;
		sDate *date;
		unsigned short inLibrary;
		unsigned short outLibrary;
		unsigned short id;
	} sBook;
	
	//Definisco la struttura cell
	typedef struct cell{
		struct cell *pPrev;	//Puntatore all'elemento precedente
		struct cell *pNext;	//Puntatore al'elemento successivo
		sBook *book;	//Variabile di tipo sBook dove vengono allocate le informazioni del Libro
	} sCell;
	
	//definisco la struttura book list
	typedef struct bookList{
		sCell *pFirst;	//Puntatore al primo elemento della lista collegata 
		sCell *pLast;		//Puntatore all'ultimo elemento della lista
	} sBookList;
	
	//Prototipi delle funzioni
	void insHead();		//Prototipo della funzione inserisci in cima alla lista
	void insTail();		//Prototipo della funzione inserisci in fondo alla lista
	void rmvHead();		//Prototipo della funzione elimina il primo elemento della lista
	void rmvTail();		//Prototipo della funzione elimina l'ultimo elemento della lista
	void rmvId(unsigned short searchedId);	//Eliminazione di un elemento dato un preciso id
	int searchId(unsigned short searchedID);	//Ricerca di un elemento all’interno della lista attraverso il campo id
	void copyOut(unsigned short searchedId);	//Prestito di un libro con un dato id
	void copyIn(unsigned short searchedId);	//Rientro di un libro con un dato id
	void printElem(unsigned short searchedId);	//Stampa di (tutti i campi di) un elemento con un dato id
	void printList();	//Stampa di (tutti i campi di) tutta la lista
	
	void printAllByGenre();	//Stampare tutti i libri della lista con un dato genere (e.g., thriller ) passato dall’utente
	void orderListId();	//Ordinamento della lista in base a id crescente
	void orderListTitle();	//Ordinamento della lista in base al titolo in ordine alfabetico
	void rmvTitleChar();	//rimuove tutti i libri che iniziano con un determinato carattere passatogli dall'utente
