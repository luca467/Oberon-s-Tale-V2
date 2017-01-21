#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib.h"

static struct Terra *head = NULL;
static struct Terra *lastland = NULL;

void crea_percorso(){
  int t,x=0;
	
  do{
    printf("Cosa vuoi fare?\n");      
    printf("1)Inserisci Terra\n");
    printf("2)Cancella Terra\n");
    printf("3)Stampa Percorso\n");
    printf("4)Torna indietro\n");

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
	else if((tm==2 && tt!=1)||(tm==2 && tt!=4)){
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
    struct Terra *lastland = head;
    while(lastland->next != NULL){
      lastland = lastland ->next;
    }
    lastland->next = malloc(sizeof(struct Terra));	
    lastland->next->Tipo_terra = tt;
    lastland->next->Tipo_mostro= tm;
    lastland->next->tesoro = ts;
    lastland->next->next = NULL;
  }
}

void canc_terra(){
  
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


void stampa_percorso(){
	
  struct Terra *pp = head;
  
  if(pp == NULL){
    printf("Non c'è nessuna terra in memoria.\n");
  }
  
  else{
    do{
      printf("\n%d, %d, %hd\n\n", pp->Tipo_terra, pp->Tipo_mostro, pp->tesoro);
      pp = pp->next;
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
