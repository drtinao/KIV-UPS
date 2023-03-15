#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "game_room_part.h"
#include "player_part.h"

/* ____________________________________________________________________________
    int check_room_new(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10])

    Function checks if game room with given name is already present.

    Function returns:
    a) 0 - if room is already present
    b) 1 - if room is new
   ____________________________________________________________________________
*/
int check_room_new(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10]){
    /* if array is empty, game room must be new */
    if(game_room_arr_length == 0){
        return 1;
    }

    int i = 0;
    for(; i < game_room_arr_length; i++){
        if(strncmp(game_room_arr[i].name_room, room_name, 10) == 0){
            return 0;
        }
    }

    return 1;
}

/* ____________________________________________________________________________
    struct game_room * get_game_room_by_name(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10])

    Finds game room with wanted name and returns a pointer to structure with game rooms data (or NULL
    if room with given name is not present).
   ____________________________________________________________________________
*/
struct game_room * get_game_room_by_name(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10]){
    int i = 0;

    for(; i < game_room_arr_length; i++){
        if(strncmp(game_room_arr[i].name_room, room_name, 10) == 0){
            return &game_room_arr[i];
        }
    }

    return NULL;
}

/* ____________________________________________________________________________
    struct game_room * add_room(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10])

    Function adds new room to array of rooms.
   ____________________________________________________________________________
*/
struct game_room * add_room(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10]){
    int free_index = game_room_arr_length;

    int i = 0;
    for(; i < game_room_arr_length; i++){
        if(strncmp(game_room_arr[i].name_room, "%%%%%%%%%%", 10) == 0){
            free_index = i;
            break;
        }
    }

    /* init new game_room struct - START */
    strcpy(game_room_arr[free_index].name_room, room_name);
    i = 0;
    for(; i < 32; i++){
        game_room_arr[free_index].card_pool[i] = 1; /* all cards present */
    }

    game_room_arr[free_index].game_running = 0; /* game is not in progress yet */
    game_room_arr[free_index].player_count = 0;
    game_room_arr[free_index].cards_to_take = 0;
    /* init new game_room struct - END */

    return game_room_arr;
}

/* ____________________________________________________________________________
    char * get_game_room_list(struct game_room *game_room_arr, int game_room_arr_length)

    Function returns char of size 50 which contains names of all created rooms.
   ____________________________________________________________________________
*/
char * get_game_room_list(struct game_room *game_room_arr, int game_room_arr_length){
    char *game_room_list = malloc(52 * sizeof(char));

    int counter = 1;
    int i = 0;
    for(; i < 52; i++){
        game_room_list[i] = '%';
    }

    game_room_list[0] = '#';
    game_room_list[51] = '?';

    i = 0;
    for(; i < game_room_arr_length; i++){
        int j = 0;
        for(; j < 10; j++){
            game_room_list[counter] = game_room_arr[i].name_room[j];
            counter += 1;
        }
    }

    return game_room_list;
}

/* ____________________________________________________________________________
    char * get_player_names_room(struct game_room *game_room_arr)

    Function returns char of size 45 which contains names of all players in the room.
   ____________________________________________________________________________
*/
char * get_player_names_room(struct game_room *game_room_player){
    char *player_names = malloc(sizeof(char) * 47); /* 15for name * 3 */

    int i = 0;
    for(; i < 47; i++){
        player_names[i] = '%';
    }

    player_names[0] = '#';
    player_names[46] = '?';

    int counter = 1;
    i = 0;
    for(; i < game_room_player -> player_count; i++){
        int j = 0;
        for(; j < 15; j++){ /* one name */
            player_names[counter] = game_room_player -> players[i] -> nickname[j];
            counter += 1;
        }
    }

    return player_names;
}

/* ____________________________________________________________________________
    struct game_room * remove_room(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10])

    Function removes user from array of players.
   ____________________________________________________________________________
*/
struct game_room * remove_room(struct game_room *game_room_arr, int game_room_arr_length, char room_name[10]){
    /* init new game_room struct - START */

    int i = 0;
    for(; i < game_room_arr_length; i++){
        if(strncmp(room_name, game_room_arr[i].name_room, 10) == 0){
            strcpy(game_room_arr[i].name_room, "%%%%%%%%%%"); /* mark as free */
            break;
        }
    }

    return game_room_arr;
}

/* ____________________________________________________________________________
    short check_player_disconnected(struct game_room *game_room_players)

    Returns number of player which has been disconnected from the server (-1 if no one).
   ____________________________________________________________________________
*/
short check_player_disconnected(struct game_room *game_room_players){
    struct timeval actual_time;
    gettimeofday(&actual_time, NULL);
    long int ms = (actual_time.tv_sec * 1000 + actual_time.tv_usec / 1000);

    int i = 0;
    int num_player = -1;
    for(; i < game_room_players -> player_count; i++){
        if((ms - game_room_players -> players[i] -> last_ping) > 1000 && game_room_players -> players[i] -> last_ping != 0){ /* user has left, 1 sec */
            printf("NO PING from user: %.15s for %ld \n", game_room_players -> players[i] -> nickname, (ms - game_room_players -> players[i] -> last_ping));
            num_player = i;
        }
    }

    return num_player;
}