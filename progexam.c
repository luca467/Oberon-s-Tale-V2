#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib.h"

int main(){

  
  
  int a;
  int b=0;
  do{

    printf("     *  *    *   *  /////////////////////////////////////////////////////////////////    *   *   *     * \n");		
    printf("   *     *      *   ///----------------MAGO OBERON CALZINO BUCATO-----------------\\\      *  *     *    \n");
    printf("  *     *     *   * ///In questo gioco si dovrà condurre il Mago Oberon attraverso\\\   *     *     *    \n");
    printf("     *     *     *  ///varie terre, con lo scopo di farlo arrivare sano e salvo a \\\    *      *        \n");
    printf(" *      *     *     ///casa.                                                      \\\      *   *     *   \n");
    printf("    *     *      *  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    *    *   *      \n");
    printf("\n");
    printf(" _________________________________________________\n");
    printf("|                                                 |\n");
    printf("| COSA VUOI FARE?                                 |\n");
    printf("| (Digita 1, 2, o 3 a seconda dell'opzione scelta)|\n");
    printf("|                                                 |\n");
    printf("| 1)Crea Percorso.                                |\n");
    printf("|                                                 |\n");
    printf("| 2)Muovi Oberon.                                 |\n");
    printf("|                                                 |\n");
    printf("| 3)Termina Gioco.                                |\n");
    printf("|_________________________________________________|\n");
    
    scanf("%d", &a);
    switch (a){
      
      case 1:{
        crea_percorso();
        break;
      }
      
      case 2:{
        printf("Appena implementerò la funzione, muoverai Oberon.\n");
        break;
      }
      
      case 3:{
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
