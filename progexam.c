#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib.h"

int main(){
  int a;
  int b=0;
  do{ 
    static int c=0;
    
    if(c==0){
      printf("\n");
      printf("     *  *    *   *  |///////////////////////////////////////////////////////////////|    *   *   *     *  \n");		
      printf("   *     *      *   |//----------------MAGO OBERON CALZINO BUCATO-----------------\\\\|      *  *     *     \n");
      printf("  *     *     *   * |//In questo gioco si dovrà condurre il Mago Oberon attraverso\\\\|   *     *     *     \n");
      printf("     *     *     *  |//varie terre, con lo scopo di farlo arrivare sano e salvo a \\\\|    *      *         \n");
      printf(" *      *     *     |//casa.                                                      \\\\|      *   *     *    \n");
      printf("    *     *      *  |///////////////////////////////////////////////////////////////|    *    *   *       \n");
      ++c;
    }
    printf("\n");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    printf("| COSA VUOI FARE?                                  |\n");
    printf("| (Digita 1, 2, 3, 4 a seconda dell'opzione scelta)|\n");
    printf("|                                                  |\n");
    printf("| 1)Tutorial.                                      |\n");
    printf("|                                                  |\n");
    printf("| 2)Crea Percorso.                                 |\n");
    printf("|                                                  |\n");
    printf("| 3)Muovi Oberon.                                  |\n");
    printf("|                                                  |\n");
    printf("| 4)Termina Gioco.                                 |\n");
    printf("|__________________________________________________|\n");
    
    scanf("%d", &a);
    switch (a){
	
    case 1:{
      printf(" _____________________________________________________________________________________________________\n");
      printf("|TUTORIAL                                                                                             |\n");
      printf("|Oberon's Tale è un gioco pensato per due giocatori.                                                  |\n");
      printf("|Uno di voi interpreterà il Master, la 'mente malvagia' che dovrà creare un percorso                  |\n");
      printf("|decidendo il tipo di terre da attraversare, i mostri da dover affrontare (inclusi                    |\n");
      printf("|orrendi orchi, famelici lupi e un classico drago sputafuoco), e la ricompensa per                    |\n");
      printf("|averli sopraffatti. Il Master deve tenere in considerazione che la prima terra non                   |\n");
      printf("|può contenere alcun mostro e che i villaggi non possono nascondere un tesoro più                     |\n");
      printf("|grande di dieci monete d'oro, ma in compenso in essi non si può annidare nessun mostro.              |\n");
      printf("|                                                                                                     |\n");
      printf("|                                                                                                     |\n");
      printf("|L'altro giocatore sarà invece Oberon, che a percorso completato potrà iniziare la sua avventura.     |\n");
      printf("|Avrà a sua disposizione due incantesimi che permettono di liberarsi immediatamente del mostro,       |\n");
      printf("|una pozione che gli permette di riportare al massimo i suoi punti vita (che partono da 5), e un      |\n");
      printf("|potente sortilegio, utilizzabile una sola volta, che gli permette di distruggere la terra successiva |\n");
      printf("|a quella in cui si trova. Per combattere dovrà invece affidarsi alla sua vecchia spada.              |\n");
      printf("|Combattere non è obbligatorio, a meno che non si tratti di un drago, ma in ogni caso se non       |\n");
      printf("|si sconfigge il mostro non si potrà accedere al tesoro che protegge.                                 |\n");
      printf("|                                                                                                     |\n");
      printf("|Buon Viaggio, Oberon! Non ti fermerà nessuno, se non la cara vecchia morte!                          |\n");
      printf("|_____________________________________________________________________________________________________|\n");
      printf("\n");
      
      continue;
    }
      
    case 2:{
      crea_percorso();
      break;
    }
      
    case 3:{
      muovi_Oberon();
      break;
    }
      
    case 4:{
      printf("Cattivone! Te ne vai di già... :(\n");
      termina_gioco();
      b++;
      break;
    }
      
    default:{
      printf("ERROR: Scelta non vailda.\n");
    }
    }
  }while(b==0);
  
  return 0;
}
