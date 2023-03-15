#ifndef UPSSERVER_PLAYER_PART_H
#define UPSSERVER_PLAYER_PART_H

#include "game_room_part.h"

/* ____________________________________________________________________________

    Function prototypes
   ____________________________________________________________________________
*/
struct player{
    char nickname[15]; /* nickname of player */
    char IP[20]; /* IP address of player */
    int stage; /* in which stage of game player is => -1 = currently disconnected, 1 = connected to server, 2 = lobby, 3 = waiting for other player, 4 = play */
    struct game_room *game_room; /* room in which is user playing */
    int cards_hand[32]; /* array represents which cards user currently holds (1 if respective card is present, else 0) */
    short cards_assigned; /* 1 if cards in actual game have already been assigned, else 0 */
    long int last_ping; /* from Jan. 1, 1970 - ping in sec */
};

int check_player_new(struct player *player_arr, int player_arr_length, int client_socket);
struct player * add_player(struct player *player_arr, int player_arr_length, int client_socket);
struct player * remove_player(struct player *player_arr, int player_arr_length, char IP[20]);
struct player * get_player_by_IP(struct player *player_arr, int player_arr_length, char IP[20]);
#endif //UPSSERVER_PLAYER_PART_H