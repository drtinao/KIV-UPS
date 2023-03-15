#include "game_logic.h"

/* ____________________________________________________________________________
    short check_card_validity(char previous_card_code[2], char new_card_code[2], short is_active)

    Returns 1 if user can place card defined by code "new_card_code"
    on card "previous_card_code" - else returns 0;

    Parameter "is_active" => 0 if the previous card is not active for the actual
    player (like 7 - user will not take 2 cards because previous one already took).
   ____________________________________________________________________________
*/
short check_card_validity(char previous_card_code[2], char new_card_code[2], short is_active){
    if(previous_card_code[0] == KARTA_KOULE_7[0] && previous_card_code[1] == KARTA_KOULE_7[1]){ /* koule 7 */
        if((new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
        || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
        || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1])){ /* 25 */
            return 1;
        }

        if(is_active == 0){
            if((new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
               || (new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
               || (new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
               || (new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
               || (new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
               || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
               || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
               || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
               || (new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
               || (new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1])){ /* 08 */
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_KOULE_8[0] && previous_card_code[1] == KARTA_KOULE_8[1]){ /* koule 8 */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1])){ /* 26 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_KOULE_9[0] && previous_card_code[1] == KARTA_KOULE_9[1]){ /* koule 9 */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1])){ /* 27 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_KOULE_10[0] && previous_card_code[1] == KARTA_KOULE_10[1]){ /* koule 10 */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1])){ /* 28 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_KOULE_SPODEK[0] && previous_card_code[1] == KARTA_KOULE_SPODEK[1]){ /* koule spodek */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1])){ /* 29 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && previous_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]){ /* koule menic -> koule */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1])){ /* 30 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_KOULE_KRAL[0] && previous_card_code[1] == KARTA_KOULE_KRAL[1]){ /* koule kral */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1])){ /* 31 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_KOULE_ESO[0] && previous_card_code[1] == KARTA_KOULE_ESO[1]){ /* koule eso */
        if((new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1]) /* 24 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }

        if(is_active == 0){
            if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
               || (new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
               || (new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
               || (new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
               || (new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
               || (new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
                  || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
                  || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
                  || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
               || (new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1])){ /* 07 */
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_7[0] && previous_card_code[1] == KARTA_CERVENA_7[1]){ /* cervena 7 */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1])){ /* 25 */
            return 1;
        }

        if(is_active == 0){
            if((new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
               || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
               || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
               || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
               || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
               || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
               || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
               || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
               || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
               || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1])){ /* 16 */
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_8[0] && previous_card_code[1] == KARTA_CERVENA_8[1]){ /* cervena 8 */
        if((new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1])){ /* 26 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_9[0] && previous_card_code[1] == KARTA_CERVENA_9[1]){ /* cervena 9 */
        if((new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1])){ /* 27 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_10[0] && previous_card_code[1] == KARTA_CERVENA_10[1]){ /* cervena 10 */
        if((new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1])){ /* 28 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_SPODEK[0] && previous_card_code[1] == KARTA_CERVENA_SPODEK[1]){ /* cervena spodek */
        if((new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1])){ /* 16 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && previous_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]){ /* cervena menic -> cervena */
        if((new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1])){ /* 30 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_KRAL[0] && previous_card_code[1] == KARTA_CERVENA_KRAL[1]){ /* cervena kral */
        if((new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1])){ /* 31 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_ESO[0] && previous_card_code[1] == KARTA_CERVENA_ESO[1]){ /* cervena eso */
        if((new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1])/* 08 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1]) /* 24 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }

        if(is_active == 0){
            if((new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
               || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
               || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
               || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
               || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
               || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
               || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
               || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
               || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
               || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1])){ /* 15 */
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_7[0] && previous_card_code[1] == KARTA_ZELENA_7[1]){ /* zelena 7 */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1])){ /* 25 */
            return 1;
        }

        if(is_active == 0){
            if((new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
               || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
               || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
               || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
               || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
                  || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
                  || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
                  || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
               || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
               || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1])){ /* 24 */
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_8[0] && previous_card_code[1] == KARTA_ZELENA_8[1]){ /* zelena 8 */
        if((new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1]) /* 24 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1])){ /* 26 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_9[0] && previous_card_code[1] == KARTA_ZELENA_9[1]){ /* zelena 9 */
        if((new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1]) /* 24 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1])){ /* 27 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_10[0] && previous_card_code[1] == KARTA_ZELENA_10[1]){ /* zelena 10 */
        if((new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1]) /* 24 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1])){ /* 28 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_SPODEK[0] && previous_card_code[1] == KARTA_ZELENA_SPODEK[1]){ /* zelena spodek */
        if((new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1]) /* 24 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1])){ /* 29 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && previous_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]){ /* zelena menic -> zelena */
        if((new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1]) /* 24 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1])){ /* 30 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_KRAL[0] && previous_card_code[1] == KARTA_ZELENA_KRAL[1]){ /* zelena kral */
        if((new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1]) /* 24 */
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1])){ /* 31 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_ESO[0] && previous_card_code[1] == KARTA_ZELENA_ESO[1]){ /* zelena eso */
        if((new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }

        if(is_active == 0){
            if((new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
               || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
               || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
               || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
               || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
               || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
                  || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
                  || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
                  || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
               || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1])){ /* 23 */
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_7[0] && previous_card_code[1] == KARTA_ZALUDY_7[1]){ /* zaludy 7 */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1])){ /* 17 */
            return 1;
        }

        if(is_active == 0){
            if((new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1]) /* 26 */
               || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1]) /* 27 */
               || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1]) /* 28 */
               || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
               || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]) /* 30 */
                  || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
                  || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
                  || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
               || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1]) /* 31 */
               || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_8[0] && previous_card_code[1] == KARTA_ZALUDY_8[1]){ /* zaludy 8 */
        if((new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1]) /* 25 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1]) /* 27 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1]) /* 28 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]) /* 30 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1]) /* 31 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_9[0] && previous_card_code[1] == KARTA_ZALUDY_9[1]){ /* zaludy 9 */
        if((new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1]) /* 25 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1]) /* 26 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1]) /* 28 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]) /* 30 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1]) /* 31 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_10[0] && previous_card_code[1] == KARTA_ZALUDY_10[1]){ /* zaludy 10 */
        if((new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1]) /* 25 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1]) /* 26 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1]) /* 27 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]) /* 30 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1]) /* 31 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_SPODEK[0] && previous_card_code[1] == KARTA_ZALUDY_SPODEK[1]){ /* zaludy spodek */
        if((new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1]) /* 25 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1]) /* 26 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1]) /* 27 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1]) /* 28 */
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]) /* 30 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1]) /* 31 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && previous_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]){ /* zaludy menic -> zaludy */
        if((new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1]) /* 25 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1]) /* 26 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1]) /* 27 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1]) /* 28 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1]) /* 31 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_KRAL[0] && previous_card_code[1] == KARTA_ZALUDY_KRAL[1]){ /* zaludy kral */
        if((new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1]) /* 25 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1]) /* 26 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1]) /* 27 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1]) /* 28 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]) /* 30 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_ESO[0] && previous_card_code[1] == KARTA_ZALUDY_ESO[1]){ /* zaludy eso */
        if((new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1])){ /* 24 */
            return 1;
        }

        if(is_active == 0){
            if((new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1]) /* 25 */
               || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1]) /* 26 */
               || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1]) /* 27 */
               || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1]) /* 28 */
               || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
               || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]) /* 30 */
                  || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
                  || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
                  || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
               || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1])){  /* 31 */
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && previous_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]){ /* koule menic -> cervena */
        if((new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1])){ /* 30 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && previous_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]){ /* koule menic -> zelena */
        if((new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1]) /* 24 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1])){ /* 30 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && previous_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]){ /* koule menic -> zaludy */
        if((new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1]) /* 25 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1]) /* 26 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1]) /* 27 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1]) /* 28 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]) /* 30 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1]) /* 31 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && previous_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]){ /* cervena menic -> koule */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
              || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
                 || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1])){ /* 30 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && previous_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]){ /* cervena menic -> zelena */
        if((new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1]) /* 24 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1])){ /* 30 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && previous_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]){ /* cervena menic -> zaludy */
        if((new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1]) /* 25 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1]) /* 26 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1]) /* 27 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1]) /* 28 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]) /* 30 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1]) /* 31 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && previous_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]){ /* zelena menic -> koule */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1])){ /* 30 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && previous_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]){ /* zelena menic -> cervena */
        if((new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1])){ /* 30 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && previous_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]){ /* zelena menic -> zaludy */
        if((new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_ZALUDY_7[0] && new_card_code[1] == KARTA_ZALUDY_7[1]) /* 25 */
           || (new_card_code[0] == KARTA_ZALUDY_8[0] && new_card_code[1] == KARTA_ZALUDY_8[1]) /* 26 */
           || (new_card_code[0] == KARTA_ZALUDY_9[0] && new_card_code[1] == KARTA_ZALUDY_9[1]) /* 27 */
           || (new_card_code[0] == KARTA_ZALUDY_10[0] && new_card_code[1] == KARTA_ZALUDY_10[1]) /* 28 */
           || (new_card_code[0] == KARTA_ZALUDY_SPODEK[0] && new_card_code[1] == KARTA_ZALUDY_SPODEK[1]) /* 29 */
           || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZALUDY[1]) /* 30 */
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1])
              || (new_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1])
           || (new_card_code[0] == KARTA_ZALUDY_KRAL[0] && new_card_code[1] == KARTA_ZALUDY_KRAL[1]) /* 31 */
           || (new_card_code[0] == KARTA_ZALUDY_ESO[0] && new_card_code[1] == KARTA_ZALUDY_ESO[1])){ /* 32 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_MENIC_KOULE[0] && previous_card_code[1] == KARTA_ZALUDY_MENIC_KOULE[1]){ /* zaludy menic -> koule */
        if((new_card_code[0] == KARTA_KOULE_7[0] && new_card_code[1] == KARTA_KOULE_7[1]) /* 01 */
           || (new_card_code[0] == KARTA_KOULE_8[0] && new_card_code[1] == KARTA_KOULE_8[1]) /* 02 */
           || (new_card_code[0] == KARTA_KOULE_9[0] && new_card_code[1] == KARTA_KOULE_9[1]) /* 03 */
           || (new_card_code[0] == KARTA_KOULE_10[0] && new_card_code[1] == KARTA_KOULE_10[1]) /* 04 */
           || (new_card_code[0] == KARTA_KOULE_SPODEK[0] && new_card_code[1] == KARTA_KOULE_SPODEK[1]) /* 05 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_KOULE_KRAL[0] && new_card_code[1] == KARTA_KOULE_KRAL[1]) /* 07 */
           || (new_card_code[0] == KARTA_KOULE_ESO[0] && new_card_code[1] == KARTA_KOULE_ESO[1]) /* 08 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1])){ /* 22 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_MENIC_CERVENA[0] && previous_card_code[1] == KARTA_ZALUDY_MENIC_CERVENA[1]){ /* zaludy menic -> cervena */
        if((new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_CERVENA_7[0] && new_card_code[1] == KARTA_CERVENA_7[1]) /* 09 */
           || (new_card_code[0] == KARTA_CERVENA_8[0] && new_card_code[1] == KARTA_CERVENA_8[1]) /* 10 */
           || (new_card_code[0] == KARTA_CERVENA_9[0] && new_card_code[1] == KARTA_CERVENA_9[1]) /* 11 */
           || (new_card_code[0] == KARTA_CERVENA_10[0] && new_card_code[1] == KARTA_CERVENA_10[1]) /* 12 */
           || (new_card_code[0] == KARTA_CERVENA_SPODEK[0] && new_card_code[1] == KARTA_CERVENA_SPODEK[1]) /* 13 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_CERVENA_KRAL[0] && new_card_code[1] == KARTA_CERVENA_KRAL[1]) /* 15 */
           || (new_card_code[0] == KARTA_CERVENA_ESO[0] && new_card_code[1] == KARTA_CERVENA_ESO[1]) /* 16 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1])){ /* 22 */
            return 1;
        }else{
            return 0;
        }
    }else if(previous_card_code[0] == KARTA_ZALUDY_MENIC_ZELENA[0] && previous_card_code[1] == KARTA_ZALUDY_MENIC_ZELENA[1]) { /* zaludy menic -> zelena */
        if((new_card_code[0] == KARTA_KOULE_MENIC_KOULE[0] && new_card_code[1] == KARTA_KOULE_MENIC_KOULE[1]) /* 06 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_CERVENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_CERVENA[1]) /* 33 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZELENA[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZELENA[1]) /* 34 */
           || (new_card_code[0] == KARTA_KOULE_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_KOULE_MENIC_ZALUDY[1]) /* 35 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_CERVENA[1]) /* 14 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_CERVENA_MENIC_KOULE[1]) /* 36 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZELENA[1]) /* 37 */
           || (new_card_code[0] == KARTA_CERVENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_CERVENA_MENIC_ZALUDY[1]) /* 38 */
           || (new_card_code[0] == KARTA_ZELENA_7[0] && new_card_code[1] == KARTA_ZELENA_7[1]) /* 17 */
           || (new_card_code[0] == KARTA_ZELENA_8[0] && new_card_code[1] == KARTA_ZELENA_8[1]) /* 18 */
           || (new_card_code[0] == KARTA_ZELENA_9[0] && new_card_code[1] == KARTA_ZELENA_9[1]) /* 19 */
           || (new_card_code[0] == KARTA_ZELENA_10[0] && new_card_code[1] == KARTA_ZELENA_10[1]) /* 20 */
           || (new_card_code[0] == KARTA_ZELENA_SPODEK[0] && new_card_code[1] == KARTA_ZELENA_SPODEK[1]) /* 21 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_KOULE[0] && new_card_code[1] == KARTA_ZELENA_MENIC_KOULE[1]) /* 39 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_CERVENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_CERVENA[1]) /* 40 */
              || (new_card_code[0] == KARTA_ZELENA_MENIC_ZALUDY[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZALUDY[1]) /* 41 */
           || (new_card_code[0] == KARTA_ZELENA_MENIC_ZELENA[0] && new_card_code[1] == KARTA_ZELENA_MENIC_ZELENA[1]) /* 22 */
           || (new_card_code[0] == KARTA_ZELENA_KRAL[0] && new_card_code[1] == KARTA_ZELENA_KRAL[1]) /* 23 */
           || (new_card_code[0] == KARTA_ZELENA_ESO[0] && new_card_code[1] == KARTA_ZELENA_ESO[1])){ /* 24 */
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}