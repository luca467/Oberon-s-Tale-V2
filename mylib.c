#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib.h"
#include <time.h>

static struct Terra *head = NULL;
static struct Terra *lastland = NULL;
static struct Terra *px = NULL;
static int w=0;
static struct Oberon Oberon = {10, 5, 2, 1};  //Definisci Oberon con il tipo struttura Oberon

void crea_percorso(){
  int t,x=0;
	
  do{
    printf("Cosa vuoi fare?\n");      
    printf("1)Inserisci Terra\n");
    printf("2)Cancella Terra\n");
    printf("3)Stampa Percorso\n");
    printf("4)Chiudi Percorso\n");
    printf("5)Torna indietro\n");

    scanf("%d", &t);

    switch (t){

      case 1:{
	ins_terra();
	break;
      }

      case 2:{
        canc_terra();
        break;
      }

      case 3:{
	stampa_percorso();
	break;
      }

      case 4:{
	w=1;
	printf("Il percorso è stato chiuso. Ora Oberon può giocare.\n");
	break;
      }

      case 5:{
	x++;
	break;
      }

      default:{
        printf("Hai inserito un comando sbagliato .-.\n");
        break;
      }
    };
  }while(x==0);
}

void ins_terra(){
	
  int tt, tm,x=0;
  short int ts;	

	
  if(w==0){
	       		
  do{
    printf("Che Terra vuoi inserire?\n");
    printf("0)Deserto\n");
    printf("1)Foresta\n");
    printf("2)Palude\n");
    printf("3)Villaggio\n");
    printf("4)Pianura\n");
    scanf("%d", &tt);
    
    if(tt>4){
      printf("Hai sbagliato comando\n");
    }
    else{
      x++;
    }
  }while(x==0);
  x=0;
  
  if(head!=NULL){
    if(tt!=3){
      do{
	printf("Che mostro vuoi inserire?\n");
	printf("0)Nessuno\n");
	printf("1)Scheletro\n");
	printf("2)Lupo\n");
	printf("3)Orco\n");
	printf("4)Drago\n");
	
	scanf("%d", &tm);
	if(tm>4){
	  printf("Hai sbagliato comando\n");
	}
	else if(tm==1 && tt==2){
	  printf("Lo scheletro non può stare su una palude\n");
	}
	else if(tm==3 && tt==0){
	  printf("L'orco non può stare su un deserto\n");
	}
	else if((tm==2 && tt!=1)&&(tm==2 && tt!=4)){
	  printf("Il lupo può stare solo sulla foresta o sulla pianura\n");
	}
	else{
	  x++;
	}
      }while(x==0);
    }
    else{
      tm=0;
    }
  }
  else{
    tm=0;
  }
  x=0;
  do{
    printf("Quanto oro vuoi inserire in questa terra? N.B. Il massimo è 200, per i villaggi 10\n");
    scanf("%hd", &ts);
    if(ts>10 && tt==3){
      printf("Il tesoro è troppo grande\n"); 
    }
    else if(ts>200){
      printf("Il tesoro è troppo grande!\n");
    }
    else{
      x++;
    }
  }while(x==0);			
  x=0;
  
  if(head==NULL){
    head =  malloc(sizeof(struct Terra));
    head->Tipo_terra = tt;
    head->Tipo_mostro= tm;
    head->tesoro = ts;
    head->next = NULL;
  }
  else{	
    lastland = head;
    while(lastland->next != NULL){
      lastland = lastland ->next;
    }
    lastland->next = malloc(sizeof(struct Terra));	
    lastland->next->Tipo_terra = tt;
    lastland->next->Tipo_mostro= tm;
    lastland->next->tesoro = ts;
    lastland->next->next = NULL;
  }
	lastland=NULL;
 } 

else{

	printf("Il percorso è stato chiuso, non puoi aggiungere altre terre.\n");
 }
}



void canc_terra(){

	if(w==0){
  
  if(head == NULL){
    printf("Non c'è nessuna terra in memoria.\n");
  }
  
  else if(head->next == NULL){
    free(head);
    head=NULL;
  }

  else{
    struct Terra *current = head;
    while(current->next->next != NULL){ //arriva in fondo alla lista
      current = current->next;
    }

    free(current->next);
    current->next = NULL;
  }
 } 
  else{
		
	printf("Il percorso è stato chiuso, non puoi cancellare terre.\n");
 }
}


void stampa_percorso(){
	
  struct Terra *pp = head;
 
 
  
  if(pp == NULL){
    printf("Non hai creato nessuna Terra\n");
  }
  
  else{
	
	int c=1;

    do{

	printf("La terra n %d è", c);
	
	switch(pp->Tipo_terra){

	case 0:{
		printf(" un deserto");
		break;}

	case 1:{
		printf(" una foresta");
		break;}

	case 2:{
		printf(" una palude");
		break;}

	case 3:{
		printf(" un villaggio");
		break;}

	case 4:{
		printf(" una pianura");
		break;}
	}


	switch(pp->Tipo_mostro){

	case 0:{
		printf(" in cui non è presente nessun mostro.");
		break;}

	case 1:{
		printf(" in cui è presente un ostile scheletro.");
		break;}

	case 2:{
		printf(" dove girovaga un lupo affamato.");
		break;}

	case 3:{
		printf(" dove abita un possente orco.");
		break;}

	case 4:{
		printf(" dove riposa un 'amichevole' drago.");
		break;}
	}

	printf("\n Questa Terra contiene %hd monete d'oro.\n", pp->tesoro); 

      	pp = pp->next;
	c++;

    }while(pp != NULL);
  } 
}


void termina_gioco(){
  while(head!=NULL){
    if(head->next == NULL){
      free(head);
      head=NULL;
    }
    
    else{
      struct Terra *current = head;
      while(current->next->next != NULL){ //arriva in fondo alla lista
	current = current->next;
      }
      
      free(current->next);
      current->next = NULL;
    }
  }
}

void muovi_Oberon(){
	
	static int c=0;
	if(c==0){
		px = head;
		++c;}
	
	//inserire il controllo se il percorso è stato chiuso

	//stampa su schermo il tipo di terra e il mostro che contiene
	printf("Ti trovi");
	
	switch(px->Tipo_terra){

	case 0:{
		printf(" in un deserto");
		break;}

	case 1:{
		printf(" in una foresta");
		break;}

	case 2:{
		printf(" in una palude");
		break;}

	case 3:{
		printf(" in un villaggio");
		break;}

	case 4:{
		printf(" in una pianura");
		break;}
	}


	switch(px->Tipo_mostro){

	case 0:{
		printf(" in cui non è presente nessun mostro.\n");
		break;}

	case 1:{
		printf(" dove uno scheletro ti guarda in modo ostile.\n");
		break;}

	case 2:{
		printf(" dove un famelico lupo sta cacciando.\n");
		break;}

	case 3:{
		printf(" in cui un possente orco è a guardia della sua casa.\n");
		break;}

	case 4:{
		printf(" dove un drago custodisce il suo tesoro.\n");
		break;}
	}

	printf("Che cosa vuoi fare?\n");
	printf("1) Avanza 2) Combatti 3) Usa una pozione 4) Prendi tesoro 5) Distruggi Terra\n");
	int a, g;
	scanf("%d", &a);
	
	do{switch(a){
	
	case 1:{
		avanza();
		break;}

	case 2:{
		combatti();
		break;}

	case 3:{
		usa_pozione();
		break;}

	case 4:{
		prendi_tesoro();
		break;}

	case 5:{
		//distruggi_terra();
		printf("scocciaterra.\n");
		break;}

	default:{ 
		printf("Il comando che hai inserito non può essere accettato.\n");
		g=1;
		break;}
	}
	}while(g==1);
		
}

void avanza(){
	
	if(px->Tipo_mostro==4){
	
	printf("Non puoi sfuggire a un drago!\n");
	
	muovi_Oberon();}
		
	if(px->next==NULL){
	
	printf("Hai vinto! Incredibile, non me lo sarei mai aspettato da te.\n");}

	px = px->next;
	muovi_Oberon();}

void combatti(){
	
	int atk, atkm, pf; //Variabili per attacco di Oberon, attacco del Mostro, punti ferita del mostro

	if(px->Tipo_mostro == 0){
		printf("Non c'è nessun mostro da combattere\n");
		}
	
	else{

	switch(px->Tipo_mostro){               //determina i punti ferita del mostro
	
	case 1:{
		pf=2;
		break;}

	case 2:{
		pf=1;
		break;}

	case 3:{
		pf=3;
		break;}

	case 4:{
		pf=5;
		break;}
	}
	}

	time_t t;
	srand((unsigned)time(&t));
	
	atk = rand()%100;

	if(atk>=60){
		pf-=3;
	          }

	if(pf<=0){
		printf("Hai sconfitto il mostro.\n");
		px->Tipo_mostro = 0;
		muovi_Oberon();
	        }

	atkm = rand()%100;

	if(atkm>=50){
		Oberon.punti_ferita -= pf;
		}
	

	if(Oberon.punti_ferita<=0){                             //controlla che Oberon sia vivo
		
		int f, t;
		printf("Oberon è morto. Hai perso. Cosa ti aspettavi?\n\n");
		printf("Vuoi riprovare?\n");
		printf("1)Si 2)No\n");

		scanf("%d", &f);
		
		do{
		switch(f){
	
		case 1:{
			px = head;
			muovi_Oberon();
			break;}

		case 2:{
			termina_gioco();
			break;}

		default:{
			printf("Hai inserito un comando sbagliato.\n");
			t=0;}
		}		
		}while(t==0);
		}

	muovi_Oberon();
	}
	
void usa_pozione(){
	
	if(Oberon.pozione_guaritrice>0){
		Oberon.pozione_guaritrice -=1;
		Oberon.punti_ferita =5;
		printf("Hai bevuto una pozione e ristabilito i tuoi punti ferita a 5.\n");}
		
	else{
		printf("Non hai più pozioni da usare.\n");}

	muovi_Oberon();
	}

void prendi_tesoro(){

	if(px->tesoro>0){
		Oberon.borsa_oro += px->tesoro;
		if(Oberon.borsa_oro>=500){
			Oberon.borsa_oro=500;}
		printf("Hai raccolto il tesoro. Ora hai %d oro.\n", Oberon.borsa_oro);
		}
	else{
		printf("Hai già raccolto il tesoro presente in questa terra.\n");}

	muovi_Oberon();
	}
		 
