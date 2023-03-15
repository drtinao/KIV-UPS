#ifndef UPSSERVER_GAME_ROOM_PART_H
#define UPSSERVER_GAME_ROOM_PART_H

/* ____________________________________________________________________________

    Function prototypes
   ____________________________________________________________________________
*/
struct game_room{
    int card_pool[32]; /* array represents which cards are currently available to take from pool (1 if respective card is present, else 0) */
    char name_room[10]; /* name of the game room */
    struct player *players[3]; /* players which are in the room */
    short player_count;
    short actual_player; /* 0, 1, 2 index corresponding to upper array */
    short actual_card; /* 00 - 44 */
    short is_active; /* 1 if last card is active for current player, else 0 */
    short cards_to_take; /* cards number which must be taken (seven card -> 2 cards to take) */
    short game_running; /* 0 game is not running, 1 if game is in progress */
};

int check_room_new(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10]);
struct game_room * add_room(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10]);
struct game_room * remove_room(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10]);
char * get_game_room_list(struct game_room *game_room_arr, int game_room_arr_length);
struct game_room * get_game_room_by_name(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10]);
char * get_player_names_room(struct game_room *game_room);
short check_player_disconnected(struct game_room *game_room_players);

#endif //UPSSERVER_GAME_ROOM_PART_H