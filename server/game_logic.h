#ifndef UPSSERVER_GAME_LOGIC_H
#define UPSSERVER_GAME_LOGIC_H

/* assign number to each card (czech - no english equivalent) - START */
#define KARTA_KOULE_7 "01"
#define KARTA_KOULE_8 "02"
#define KARTA_KOULE_9 "03"
#define KARTA_KOULE_10 "04"
#define KARTA_KOULE_SPODEK "05"
#define KARTA_KOULE_MENIC_KOULE "06"
#define KARTA_KOULE_KRAL "07"
#define KARTA_KOULE_ESO "08"

#define KARTA_CERVENA_7 "09"
#define KARTA_CERVENA_8 "10"
#define KARTA_CERVENA_9 "11"
#define KARTA_CERVENA_10 "12"
#define KARTA_CERVENA_SPODEK "13"
#define KARTA_CERVENA_MENIC_CERVENA "14"
#define KARTA_CERVENA_KRAL "15"
#define KARTA_CERVENA_ESO "16"

#define KARTA_ZELENA_7 "17"
#define KARTA_ZELENA_8 "18"
#define KARTA_ZELENA_9 "19"
#define KARTA_ZELENA_10 "20"
#define KARTA_ZELENA_SPODEK "21"
#define KARTA_ZELENA_MENIC_ZELENA "22"
#define KARTA_ZELENA_KRAL "23"
#define KARTA_ZELENA_ESO "24"

#define KARTA_ZALUDY_7 "25"
#define KARTA_ZALUDY_8 "26"
#define KARTA_ZALUDY_9 "27"
#define KARTA_ZALUDY_10 "28"
#define KARTA_ZALUDY_SPODEK "29"
#define KARTA_ZALUDY_MENIC_ZALUDY "30"
#define KARTA_ZALUDY_KRAL "31"
#define KARTA_ZALUDY_ESO "32"

#define KARTA_KOULE_MENIC_CERVENA "33"
#define KARTA_KOULE_MENIC_ZELENA "34"
#define KARTA_KOULE_MENIC_ZALUDY "35"

#define KARTA_CERVENA_MENIC_KOULE "36"
#define KARTA_CERVENA_MENIC_ZELENA "37"
#define KARTA_CERVENA_MENIC_ZALUDY "38"

#define KARTA_ZELENA_MENIC_KOULE "39"
#define KARTA_ZELENA_MENIC_CERVENA "40"
#define KARTA_ZELENA_MENIC_ZALUDY "41"

#define KARTA_ZALUDY_MENIC_KOULE "42"
#define KARTA_ZALUDY_MENIC_CERVENA "43"
#define KARTA_ZALUDY_MENIC_ZELENA "44"
/* assign number to each card (czech - no english equivalent) - END */

/* ____________________________________________________________________________

    Function prototypes
   ____________________________________________________________________________
*/
short check_card_validity(char previous_card_code[2], char new_card_code[2], short is_active);

#endif //UPSSERVER_GAME_LOGIC_H
