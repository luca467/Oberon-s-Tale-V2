//PROGETTO DI CAPOCCIONI LUCA, TOZZI EMANUELE, VERCESI LUCA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib.h"
#include <time.h>

//Definizione di un puntatatore head a struct Terra inizializzato a NULL: questo rappresenta la prima terra della lista che all'avvio del programma è vuota
static struct Terra *head = NULL; 

//Definizione di un puntatore ultima_terra a struct Terra inizializzato a NULL: questo rappresenta l'ultima terra della lista            
static struct Terra *ultima_terra = NULL;  
    
//Questo puntatore è utilizzato nella funzione muovi_Oberon per scorrere le terre lungo la lista
static struct Terra *px = NULL;     
           
//Questa variabile static serve a tenere conto se il percorso è stato chiuso
static int w=0;  
//Questa variabile static serve a tenere conto quante volte si usa distruggi terra
static int dt=1;                             
//Inizializza la sruttuta Oberon con 10 oro, 5 punti ferita, 2 incantesimi e 1 distruggi terra
static struct Oberon Oberon = {10, 5, 2, 1};  

//Questa funziona chiude il percorso impedendo altre modifiche
void chiudi_percorso(){

	//Se non è stata aggiunta nessuna terra non si può chiudere il percorso e ritrona al sottomenù per gestire il percorso
	if(head==NULL){
	  printf("Non puoi chiudere il percorso senza aver aggiunto almeno una Terra!\n\n");
	  crea_percorso();}

	//Se si è aggiunta almeno una terra e il percorso non è già stato chiuso, imposta w a 1 chiudendo il percorso
	if(w!=1){
	  w=1;
	  printf("Il percorso è stato chiuso. Ora Oberon può giocare.\n");}

	//Se il percorso è già stato chiuso, il percorso non può essere richiuso
	else{
	  printf("Hai già chiuso il percorso\n");}
	} 


//Questa funzione apre un sottomenù che richiama attrverso uno switch altre funzioni per la modifica del percorso
void crea_percorso(){  
                 
  //Variabile che gestisce lo switch e il do while
  int t;  

  //Stampa il sottomenù finche non si decide di tornare indietro impostando t=5                            
    do{
    printf("Cosa vuoi fare?\n");               
    printf("1)Inserisci Terra\n");
    printf("2)Cancella Terra\n");
    printf("3)Stampa Percorso\n");
    printf("4)Chiudi Percorso\n");
    printf("5)Torna indietro\n");

    //Permette di scegliere le opzioni 
    scanf("%d", &t);                   
    
    switch (t){
    case 1:{
      //Chiama la funzione per inserire una terra in fondo alla lista
      ins_terra();                     
	break;
    }
    case 2:{
      //Chiama la funzione per cancellare la terra in fondo alla lista (quindi l'ultima aggiunta)
      canc_terra();                    
      break;
    }
    case 3:{
      //Chiama la funziona per stampare su schermo le terre finora inserite
      stampa_percorso();               
      break;
    }
    case 4:{
	//Chiama la funzione per chiudere il percorso
	chiudi_percorso();             
	break;
    }
    case 5:{ 
	//Torna al menù principale (t=5)                         
	break;
    }
    default:{   
      //Controlla che il numero inserito sia valido                       
      printf("Hai inserito un comando sbagliato.\n");
      break;
    }
    }
  }while(t!=5);
}

void ins_terra(){          
   //Queste variabili servono ad impostare il tipo di terra (tt) e il tipo di mostro (tm), x serve a gestire i cicli e vieni impostata a  0 ogniqualvolta si chiama la funziona
  int tt, tm,x=0; 
         
  //Questa variabile imposta il tipo di tesoro (ts), cioè la quantità d'oro presente nella terra
  short int ts;	 
           
  //Controlla che il percorso non sia stat chiuso. Se w fosse diverso da 0 il percorso sarebbe fià stato chiuso e quindi non si può inserire   la terra
  if(w==0){	           
       		
  	do{      
		//Questo do while stampa il sottomenù finche non si inserisce un comando valido            
  		printf("Che Terra vuoi inserire?\n");      
  		printf("0)Deserto\n");
                printf("1)Foresta\n");
                printf("2)Palude\n");
                printf("3)Villaggio\n");
                printf("4)Pianura\n");
			
		//Assegna il numero inserito al tipo di terra
                scanf("%d", &tt);       

    		//Controlla che il numero inserito sia valido, se non lo fosse il do while continuerebbe a stampare il menù
                if(tt>4 || tt<0){   
	           printf("Hai sbagliato comando\n");
                }
		
		//Se il comando è valido incrementa x uscendo dal ciclo
                else{       
	           x++;
                }
       }while(x==0);

    //x viene reimpostata a 0 per poter gestire il ciclo successivo
    x=0;

    //Controlla che la terra inserita non sia la prima della lista: sulla prima terra infatti non possono essere presenti mostri
    if(head!=NULL){
        
      //Controlla che il tipo terra sia diverso da un villaggio: infatti in un vilaggio non possono essere presenti mostri
      if(tt!=3){  
	do{
	  //Stampa il menù per la scelta del mostro fino a che non si inserisce un numero valido
	  printf("Che mostro vuoi inserire?\n");   
	  printf("0)Nessuno\n");
	  printf("1)Scheletro\n");
	  printf("2)Lupo\n");
	  printf("3)Orco\n");
	  printf("4)Drago\n");
	
	  //Assegna il numero inserito al tipo di mostro
	  scanf("%d", &tm);
     
	  //Controlla che il numero inserito sia valido
	  if(tm>4){             
	    printf("Hai sbagliato comando\n");
	  }
	  //Controlla se si è inserito uno scheletro in una palude: ciò non deve accadare e pertanto si deve scegliere un altro mostro
	  else if(tm==1 && tt==2){
	    printf("Lo scheletro non può stare su una palude\n");
	  }
	  //Controlla se si è inserito un orco in un deserto: (vedi sopra)
	  else if(tm==3 && tt==0){  
	    printf("L'orco non può stare su un deserto\n");
	}
	  //Controlla se si è inserito un lupo in una terra che non sia una foresta o una pianura
	  else if((tm==2 && tt!=1)&&(tm==2 && tt!=4)){
	  printf("Il lupo può stare solo sulla foresta o sulla pianura\n");
	  }
	  //Se i comandi sono tutti validi, incrementa la variabile x di uno uscendo dal ciclo
	  else{
	    x++;  
	  }
	}while(x==0);
      }
      //Se la terra è un villaggio, il tipo mostro viene impostato a 0 (cioè nessuno)
      else{
	tm=0; 
      }
    }
    //Se la terra è la prima della lista, il tipo mostro viene impostato a 0 (cioè nessuno)
    else{
      tm=0; 
    }

    //x viene reimpostato a 0 per gestire il prossimo ciclo
    x=0; 

    //Stampa la domanda di quanto oro si vuole inserire finchè non si inserisce una cifra valida
    do{
       printf("Quanto oro vuoi inserire in questa terra? N.B. Il massimo è 200, per i villaggi 10\n");
       //Assegna il numero inserito al tesoro
       scanf("%hd", &ts);
       //Controlla che il tesoro non sia maggiore a 10 se la terra è un villaggio
       if(ts>10 && tt==3){
	 printf("Il tesoro è troppo grande!\n"); 
     } 
       //Controlla che il tesoro non sia minore a 0
       else if(ts<0){
	 printf("Il tesoro non può essere minore a 0!\n");
     }
       //Controlla che il tesoro non sia maggiore a 200
       else if(ts>200){
	 printf("Il tesoro è troppo grande!\n");
     }
       //Se la cifra è valida, incrementa la variabile x di uno uscendo dal ciclo
       else{
	 x++;
     }
    }while(x==0);
			
    //x viene reimpostato a 0 per gestire il prossimo ciclo
    x=0;
    
    //Controlla che la terra inserita sia la prima. In caso affermativo, si alloca memoria nella struttura head e si immpostano i valori di questa secondo i valori precedentemente inseriti
    if(head==NULL){
      head =  malloc(sizeof(struct Terra));
      head->Tipo_terra = tt;
      head->Tipo_mostro= tm;
      head->tesoro = ts;
      head->next = NULL;
    }

    //Se la terra inserita non è la prima, prima scorre tutte le terre inserite fino ad arrivare all'ultima terra per poi allocare memoria dopo questa
    else{
      //si imposta l'ultima terra uguale alla prima: in questo modo si inizia a scorrere la lista dalla prima terra	
      ultima_terra = head;
      //Questo ciclo scorre tutte le terre fino a che non arriva all'ultima inseirita che ha il puntatore next = NULL
      while(ultima_terra->next != NULL){
	ultima_terra = ultima_terra ->next;
      //Viene allocata quindi memoria nell'ultima terra
      }
      ultima_terra->next = malloc(sizeof(struct Terra));	
      ultima_terra->next->Tipo_terra = tt;
      ultima_terra->next->Tipo_mostro= tm;
      ultima_terra->next->tesoro = ts;
      ultima_terra->next->next = NULL;
    }
    //Infine si reimposta l'ultima terra = NULL per poterla riutilizzare per il prossimo ciclo 
    ultima_terra=NULL;
  } 

//Se il percorso è stato chiuso (w è diverso da 0), non si può più aggiungere terre
  else{  
    printf("Il percorso è stato chiuso, non puoi aggiungere altre terre.\n");
  }
}


//Questa funziona cancella dalla memoria l'ultima terra inserita e reimposta a NULL il valore del puntatore next della penultima terra
void canc_terra(){
  //Controlla che il percorso non sia stato chiuso
  if(w==0){
    //Se la prima terra non è stata inserita, il percorso è vuoto: pertanto non si può cancellare nessuna terra
    if(head == NULL){
      printf("Non c'è nessuna terra in memoria.\n");
    }
    //Se la seconda terra non è stata inserita (ed è pertanto presente una sola terra), si libera la memoria di head e la si reimposta a NULL
    else if(head->next == NULL){
      free(head);
      head=NULL;
    }
    
    //Se si è inserita più di una terra, prima si scorre attraverso un ciclo e un puntatore tutte le terre fino ad arrivare all'ultima, dopodichè si libera la memoria da quest'ultima
    else{
      //Il puntatore current, utilizzato per scorrere la lista, inizia dalla prima terra...
      struct Terra *current = head; 
    //...per poi arrivare in fondo alla lista    
    while(current->next->next != NULL){ 
      current = current->next;
    }
    
    free(current->next);
    //Si reimposta il puntatore della penultima terra a NULL
    current->next = NULL;  
    }
  }
 
  //Se il percorso è stato chiuso, non si possono più cancellare terre
  else{
    printf("Il percorso è stato chiuso, non puoi cancellare terre.\n");
  }
}


//Questa funziona stampa su schermo tutte le terre (numerate) con i propri valori finora inserite
void stampa_percorso(){

 //Questo puntatore serve per scorrere la lista di tutte le terre create finora cominciando dalla prima
  struct Terra *pp = head;
  
  //Se non si è inserita nessuna terra, la funziona non stampa nulla
  if(pp == NULL){
    printf("Non hai creato nessuna Terra\n");
  }

  //Se si è inserita almeno una terra, la funziona continua normalmente
  else{
    //c è un contatore: aumenta od ogni ciclo di uno (e quindi conta quante terre si sono inserite) e comincia da 1
    int c=1;
    
    do{    
      printf("La terra n %d è", c);
      
      //Controlla che tipo di terra è
      switch(pp->Tipo_terra){
	
      case 0:{
	printf(" un deserto");
	break;
      }
	
      case 1:{
	printf(" una foresta");
	break;
      }
	
      case 2:{
	printf(" una palude");
	break;
      }

      case 3:{
	printf(" un villaggio");
	break;
      }
	
      case 4:{
	printf(" una pianura");
	break;
      }
      }
      
      //Controlla che mostro è presente nella terra
      switch(pp->Tipo_mostro){
	
      case 0:{
	printf(" in cui non è presente nessun mostro.");
	break;
      }
	
      case 1:{
	printf(" in cui è presente un ostile scheletro.");
	break;
      }
	
      case 2:{
	printf(" dove girovaga un lupo affamato.");
	break;
      }

      case 3:{
	printf(" dove abita un possente orco.");
	break;
      }
	
      case 4:{
	printf(" dove riposa un 'amichevole' drago.");
	break;
      }
      }
      
      //Infine verifica quanto oro è presente nella terra
      printf("\nQuesta Terra contiene %hd monete d'oro.\n\n", pp->tesoro); 
      
      //Passa alla terra successiva e incrementa c di uno
      pp = pp->next; 
      c++;
      
    }while(pp != NULL); //ripete il ciclo finche non arriva in fondo alla lista
  } 
}





//Questa funziona libera dalla memorie tutte le terre inserite ed esce dal programma
void termina_gioco(){

        //Finchè esiste la prima terra, quindi finchè ci sono terre
	while(head!=NULL){

		//Se la seconda terra è NULL ed è pertanto presente solo la prima terra, libera dalla memoria la prima terra
		if(head->next == NULL){
		free(head);
		head=NULL;
		}
  //Se esiste una seconda terra, definisce un puntatore a struct terra = head (per iniziare dalla prima terra) per poi arrivare in fondo alla lista ed eliminare dalla memoria l'ultima terra   		  
    		else{
      			struct Terra *current = head;
      			while(current->next->next != NULL){ 
				current = current->next;
      				}
      
      			free(current->next);
      			current->next = NULL;
      			}
  }
//Infine esce dal programma
exit(EXIT_FAILURE);
}


//Questa funziona serve per far avanzare Oberon lungo le terre e fargli compiere azioni
void muovi_Oberon(){ 
  
  //Verifica che il percorso sia stato chiuso
  if(w==0){
    printf("Non puoi muovere Oberon. Prima il percorso deve essere chiuso.\n");}
 
  //Se è la prima volta che si usa la funziona, px viene posto = head, per iniziare dalla cima della lista (solo la prima volta)
  else{
	static int c=0;
	if(c==0){
	  px = head;
	  ++c;
	}
	
	//stampa su schermo il tipo di terra e il mostro che contiene
	printf("\nTi trovi");
	
	switch(px->Tipo_terra){
	  
	case 0:{
	  printf(" in un deserto");
	  break;
	}
	  
	case 1:{
	  printf(" in una foresta");
	  break;
	}

	case 2:{
	  printf(" in una palude");
	  break;
	}

	case 3:{
	  printf(" in un villaggio");
	  break;
	}

	case 4:{
	  printf(" in una pianura");
	  break;
	}
	}
	
	
	switch(px->Tipo_mostro){
	  
	case 0:{
	  printf(" in cui non è presente nessun mostro.\n");
	  break;
	}

	case 1:{
	  printf(" dove uno scheletro ti guarda in modo ostile.\n");
	  break;
	}

	case 2:{
	  printf(" dove un famelico lupo sta cacciando.\n");
	  break;
	}

	case 3:{
	  printf(" in cui un possente orco è a guardia della sua casa.\n");
	  break;
	}

	case 4:{
	  printf(" dove un drago custodisce il suo tesoro.\n");
	  break;
	}
	}

	int a, g; //Variabili per comodità

	do{
	  //Stampa un sottemenù finchè non si avanza dalla terra: se è un villaggio è aggiunta anche la possibilità di comprare oggetti al negozio
	  printf("Che cosa vuoi fare?\n");
	  if(px->Tipo_terra==3){
	    printf("1) Avanza 2) Negozio 3) Usa una pozione 4) Prendi tesoro 5) Distruggi Terra\n");
	  
	    scanf("%d", &a);
	    
	    switch(a){
	      
	    case 1:{
	      avanza();
	      break;
	    }
	      
	    case 2:{
	      negozio();
	      break;
	    }
	      
	    case 3:{
	      usa_pozione();
	      g=1;
	      break;
	    }
	      
	    case 4:{
	      prendi_tesoro();
	      g=1;
	      break;
	    }
	      
	    case 5:{
	      distruggi_terra();
              g=1;
	      break;
	    }
	      
	    default:{ 
	      printf("Il comando che hai inserito non può essere accettato.\n");
	      g=1;
	      break;
	    }
	    }
	  }
	  
	  else{
	    //Se la terra non è un villaggio, si hanno a disposizione le scelte base
	    printf("1) Avanza 2) Combatti 3) Usa una pozione 4) Prendi tesoro 5) Distruggi Terra\n");
	    
	    scanf("%d", &a);
	    
	    switch(a){
	      
	    case 1:{
	      avanza();
	      break;
	    }
	      
	    case 2:{
	      combatti();
	      break;
	    }
	      
	    case 3:{
	      usa_pozione();
	      g=1;
	      break;
	    }
	      
	    case 4:{
	      prendi_tesoro();
	      g=1;
	      break;
	  }
	      
	    case 5:{
	      distruggi_terra();
	      g=1;
	      break;
	    }
	      
	    default:{ 
	      printf("Il comando che hai inserito non può essere accettato.\n");
	      g=1;
	      break;
	    }
	    }  
	  }
	  
	}while(g==1);
	
  }
}

void negozio(){
  
  int r, jj=0; //variabili che gestiscono lo switch e il do-while
  
  do{	
    
    if(Oberon.borsa_oro==42){
      printf("\nBenvenuto al mercato nero dei goblin del villaggio.\n");
      printf("Cosa vuoi acquistare?\n");
      printf("1) Incantesimo, costa 120  2) Pozione, costa 90. 3) 42, è la risposta a tutto! 4) Esci dal negozio\n");
      
      scanf("%d", &r);
      
      switch(r){
	
      case 1:{
	
	if(80<Oberon.borsa_oro&&Oberon.borsa_oro<120){
	  
	  printf("Hai un bel gruzzolo, ma non basta per questo raro incantesimo.\n");
	}
	
	if(40<Oberon.borsa_oro&&Oberon.borsa_oro<=80){
	  
	  printf("Non siamo in vena di sconti...\n");
	}
	
	if(0<=Oberon.borsa_oro&&Oberon.borsa_oro<=40){
	  
	  printf("Non hai il becco di un quattrino! Pensavi di fregarmi?\n");
	}
	
	if(Oberon.borsa_oro>=120){
	  
	  Oberon.borsa_oro-=120;
	  
	  Oberon.incantesimi++;
	  
	  printf("Un incantesimo? Ottimo acquisto! E' un piacere fare affari con te!\n");
	}
	
	break;
      }
	
      case 2:{
	
	if(60<Oberon.borsa_oro&&Oberon.borsa_oro<90){
	  
	  printf("Questo elisir vale più di quello che hai, amico.\n");
	}
      
	if(30<Oberon.borsa_oro&&Oberon.borsa_oro<=60){
	
	  printf("Non facciamo sconti su articoli del genere...\n");
	}
	
	if(0<=Oberon.borsa_oro&&Oberon.borsa_oro<=30){
	  
	  printf("Vedo che sei al verde... Non che mi aspettassi altro, da un viandante come te.\n");
	}
	
	if(Oberon.borsa_oro>=90){
	  
	  Oberon.borsa_oro-=90;
	  
	  Oberon.pozione_guaritrice++;
	  
	  printf("Ecco a te una pozione guaritrice: usala con saggezza...\n");
	}
	
	break;
      }
	
      case 3:{
	printf("Ti teletrasporti davanti al tuo castello.\nIl tuo maggiordomo Marvin ti accoglie dicendoti che il tuo castello verrà distrutto per fa posto a un'autostrada galattica.\n");
	termina_gioco();
	break;
      }
      case 4:{
	muovi_Oberon();
	break;
      }
      default:{
	
	printf("Comando sbagliato.\n");
	
	break;
      }
	
      }
    }
    else{
      printf("\nBenvenuto al mercato nero dei goblin del villaggio.\n");
      printf("Cosa vuoi acquistare?\n");
      printf("1) Incantesimo, costa 120  2) Pozione, costa 90. 3)Esci dal negozio\n");
      
      scanf("%d", &r);
      
      switch(r){
	
      case 1:{
	
	if(80<Oberon.borsa_oro&&Oberon.borsa_oro<120){
	  
	  printf("Hai un bel gruzzolo, ma non basta per questo raro incantesimo.\n");
	}
	
	if(40<Oberon.borsa_oro&&Oberon.borsa_oro<=80){
	  
	  printf("Non siamo in vena di sconti...\n");
      }
	
	if(0<=Oberon.borsa_oro&&Oberon.borsa_oro<=40){
	  
	  printf("Non hai il becco di un quattrino! Pensavi di fregarmi?\n");
	}
	
	if(Oberon.borsa_oro>=120){
	  
	  Oberon.borsa_oro-=120;
	
	  Oberon.incantesimi++;
	  
	  printf("Un incantesimo? Ottimo acquisto! E' un piacere fare affari con te!\n");
	}
	
	break;}
	
      case 2:{
	
	if(60<Oberon.borsa_oro&&Oberon.borsa_oro<90){
	  
	  printf("Questo elisir vale più di quello che hai, amico.\n");
	}
	
      if(30<Oberon.borsa_oro&&Oberon.borsa_oro<=60){
	
	printf("Non facciamo sconti su articoli del genere...\n");
      }
      
      if(0<=Oberon.borsa_oro&&Oberon.borsa_oro<=30){
	
	printf("Vedo che sei al verde... Non che mi aspettassi altro, da un viandante come te.\n");
      }
      
      if(Oberon.borsa_oro>=90){
	
	Oberon.borsa_oro-=90;
	
	Oberon.pozione_guaritrice++;
	
	printf("Ecco a te una pozione guaritrice: usala con saggezza...\n");
      }
      
      break;}
	
      case 3:{
	
	muovi_Oberon();
	
	break;}
      
      default:{
	
	printf("Comando sbagliato.\n");
	
	break;}
      }
    }
  }while(jj==0);
}


//Questa funzione serve a far avanzare Oberon alla terra successiva
void avanza(){
  
  //Controlla che nella terra non sia presente un drago: se fosse presente non si può avanzare senza sconfiggerlo.
  if(px->Tipo_mostro==4){
    printf("Non puoi sfuggire a un drago!\n");
    muovi_Oberon();
  }
  
  //Se la terra in cui si trova è l'ultima della lista, Oberon ha vinto e si termina l'esecuzione del programma
  else if(px->next==NULL){
    printf("Hai vinto! Incredibile, non me lo sarei mai aspettato da te.\n");
    termina_gioco();
  }
  
  //Se nessuno di quei casi si verifica, si imposta px uguale al suo successivo e si richiama la funzione muovi_Oberon
  else{
    px=px->next;
    muovi_Oberon();
  }
}


//Questa funziona serve per appropiarsi del tesoro presente in una terra
void prendi_tesoro(){
  //Si verifica che non sia presente nessun mostro: non si può prendere il tesoro senza combattere
  if(px->Tipo_mostro != 0){
    printf("Non puoi prendere il tesoro senza aver sconfitto il mostro\n");
  }
  //Se il mostro non c'è
  else{
    //Controlla che il tesoro non sia stato già raccolto o impostato a 0
    if(px->tesoro>0){
      //Si incrementa il valore di Oberon.borsa_oro della quantità di oro presente nella terra per poi reimpostare a 0 il tesoro
      Oberon.borsa_oro += px->tesoro;
      px->tesoro=0;
      
      //Se Oberon raggiugne la quantità di 500 oro, si ricorda all'utente che non si può trasportare più di 500 oro
      if(Oberon.borsa_oro>=500){
	Oberon.borsa_oro=500;
	printf("Ricorda che l'oro che trasporti non può essere maggiore di 500\n");
      }
      //Conferma all'utente che ha raccolto il tesoro e lo informa sulla quantità che attualmente trasporta		
      printf("Hai raccolto il tesoro. Ora hai %d oro.\n", Oberon.borsa_oro);
    }
    //Se il tesoro è già stato raccolto, ovviamente, non si può raccogliere nuovamente
    else{
      printf("Hai già raccolto il tesoro presente in questa terra.\n");
    }   
  }
}


//Questa funzione serve ad usare la pozioen per ristabilre a 5 i punti ferita
void usa_pozione(){
  //Controlla che Oberon.pozione_guaritrice sia almeno 1, dopodichè sottrea 1 a quella quantità e reimposta a 5 Oberon.punti_ferita
  if(Oberon.pozione_guaritrice>0){
    Oberon.pozione_guaritrice -=1;
    Oberon.punti_ferita =5;
    printf("Hai bevuto una pozione e ristabilito i tuoi punti ferita a 5.\n");
  }
   //Se non si hanno pozioni da usare, informa l'utente che non ha pozioni disponibili  
   else{
	  printf("Non hai più pozioni da usare.\n");
   }
}


//Questa pozione serve ad utilizzare un incantesimo che permette di eliminare istantaneamente qualsiasi mostro
void usa_incantesimo(){
  //Controlla che la variabile Oberon.incantesimi non sia uguale a 0 (e quindi che si abbiano incantesimi disponibili)
  if(Oberon.incantesimi==0){
    printf("Non hai più incantesimi disponibili\n");
  }
  //Se si hanno incantesimi disponibili, si sottrea 1 alla valore di Oberon.incantesimi e si setta il Tipo_mostro a 0 (cioè nessuno)
  else{
    Oberon.incantesimi-=1;
    printf("Abracadabra, OcusPocus! Bibidi, Bodibi, Bu! Insomma, il mostro si dissolve in un mucchieto di ceneri\n");
    px->Tipo_mostro=0;
  }
}


//Questa funzione serve per distruggere la terra successiva a quella in cui si trova Oberon
void distruggi_terra(){
  //Controlla se distruggi_terra sia già stata usata
  if(dt==0){
    printf("Non puoi più lanciare il sortilegio, la magia ha sempre un prezzo...\n");
  }
  //Se Oberon si trova sull'ultima Terra, distrugge la sua dimora, perdendo la partita
  else{
    if(px->next==NULL){
      printf("Hai distrutto la tua dimora. Piangi sconsolato mentre guardi la tua riserva di ippograsso scorrere via.\n");
      termina_gioco();
    }
    
    //libera dalla memoria la terra successiva e il puntatore a quella terra viene impostato alla terra successiva ancora
    free(px->next);
    px->next = px->next->next;
    printf("Con il tuo potente sortilegio hai completamente distrutto la terra successiva.\n");
    dt--;
    muovi_Oberon();
  }
}


//Questa funziona gestisce lo scambio di danni tra Oberon e il mostro attraverso la generazione di numeri casuali
int attacca(int pfa, int pf){
  //Variabili per l'attacco di Oberon e l'attacco del mostro
  int atk, atkm;
  time_t t;
  srand((unsigned)time(&t));
  
  //Genera un numero casuale per atk tra 0 e 99
  atk = rand()%100;
  
  //Se il numero generato è maggiore o uguale a 60, l'attacco va a segno e si sottragono quindi 3 punti dai punti ferita attuali del mostro
  if(atk>=60){
    printf(" _____________________________________________________________________________________\n");
    printf("|                                                                                     |\n");
    printf("| Hai messo a segno il tuo attacco!                                                   |\n");
    printf("|                                                                                     |\n");
    pfa-=3;
  }
  //Se non lo è, si informa l'utente che l'attacco non è andato a segno
  else{
    printf(" _____________________________________________________________________________________\n");
    printf("|                                                                                     |\n");
    printf("| Il tuo attacco non è andato a segno.                                                |\n");
    printf("|                                                                                     |\n");
  }
  //Se i punti ferita del mostro sono scesi a 0 o sotto lo 0, il mostro è stato sconfitto e il Tipo_mostro della terra cambia in 0 (nessuno)
  if(pfa<=0){
    printf("| Hai sconfitto il mostro.                                                            |\n");
    printf("|_____________________________________________________________________________________|\n");
    px->Tipo_mostro = 0;
  }

  //Se il mostro sopravvive, si genera un numero casuale tra 0 e 99 per l'attacco del mostro
  else{
    atkm = rand()%100;
    //Se maggiore o uguale a 50, il mostro colpisci e infligge danni pari ai suoi punti farite massimi
    if(atkm>=50){		
      Oberon.punti_ferita -= pf;
      printf("| Il mostro ti ha colpito e ti ha inflitto %d danni. Ora hai %d punti ferita            |\n", pf, Oberon.punti_ferita);
      printf("|_____________________________________________________________________________________|\n");
    }
    //Altrimenti si informa l'utente che il mostro non ha messo a segno il suo attacco
    else{
      printf("| Il mostro ha mancato il suo attacco.                                                |\n");
      printf("|_____________________________________________________________________________________|\n");}
    
    //Se Oberon muore, la partita termina con la sconfitta di Oberon e il proggramma viene arrestato
    if(Oberon.punti_ferita<=0){                            
      printf("|                                                                                     |\n");
      printf("| Oberon è morto. Hai perso. Cosa ti aspettavi?                                       |\n");
      printf("|_____________________________________________________________________________________|\n");
      
      termina_gioco();  
    }
  }
  return pfa;
}		


//Questa funzione serve per combattere contro i mostri
void combatti(){
  //Variabile per i punti ferita del mostro
  int pf; 
  //Controlla che sia presente un mostro
  if(px->Tipo_mostro == 0){
    printf("Non c'è nessun mostro da combattere\n");
    muovi_Oberon();
  }
	
  else{
    //Se è presente un mostro, tramite uno switch vengono determinati i punti ferita del mostro in base al tipo dello stesso
    switch(px->Tipo_mostro){               
      
    case 1:{
      pf=2;
      break;
    }
      
    case 2:{
      pf=1;
      break;
    }

    case 3:{
      pf=3;
      break;
    }

    case 4:{
      pf=5;
      break;
    }
    }
    //Questa variabile indica i punti ferita "attuali" del mostro che inizialmente sono uguali ai punti ferita massimi
    int pfa = pf;
    int ww=0; //Variabile per comodità
    do{
      int gg; //Variabile per comodità
      //Stampa un sottomenù finchè non viene sconfitto il mostro da cui si possono scegliere 3 azioni
      printf("Cosa vuoi fare?\n");
      printf("1) Attacca 2) Usa pozione 3) Usa Incantesimo\n");
      scanf("%d", &gg);
      
      switch(gg){
      case 1:{
	pfa=attacca(pfa,pf);
	if(pfa<=0 || px->Tipo_mostro==0){
	  ww=1;
	}
	break;
      }
	
      case 2:{
	usa_pozione();
	break;
      }

      case 3:{
	usa_incantesimo();
	break;
      }

      default:{
	printf("Comando sbagliato\n");
      }
      }
    }while(ww != 1);
    muovi_Oberon();
  }
}
