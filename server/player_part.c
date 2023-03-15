#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#include "player_part.h"

/* ____________________________________________________________________________
    int check_player_new(struct player *player_arr, int player_arr_length, int client_socket)

    Function checks if user is already present in player array (by IP address).

    Function returns:
    a) 0 - if user is already present
    b) 1 - if user is new
   ____________________________________________________________________________
*/
int check_player_new(struct player *player_arr, int player_arr_length, int client_socket){
    /* if array is empty, user must be new */
    if(player_arr_length == 0){
        return 1;
    }

    /* get IP of client */
    struct sockaddr_in address;
    socklen_t address_size = sizeof(struct sockaddr_in);
    getpeername(client_socket, (struct sockaddr *)&address, &address_size);

    int i = 0;
    for(; i < player_arr_length; i++){
        if(strcmp(player_arr[i].IP, inet_ntoa(address.sin_addr)) == 0){
            return 0;
        }
    }

    return 1;
}

/* ____________________________________________________________________________
    struct player * add_player(struct player *player_arr, int player_arr_length, int client_socket)

    Function adds new user to array of players.
   ____________________________________________________________________________
*/
struct player * add_player(struct player *player_arr, int player_arr_length, int client_socket){
    /* get IP of client */
    struct sockaddr_in address;
    socklen_t address_size = sizeof(struct sockaddr_in);
    getpeername(client_socket, (struct sockaddr *)&address, &address_size);

    /* init struct of new player - START */
    strcpy(player_arr[player_arr_length].IP, inet_ntoa(address.sin_addr));
    player_arr[player_arr_length].stage = 1; /* waiting for nick send... */

    player_arr[player_arr_length].last_ping = 0;
    player_arr[player_arr_length].cards_assigned = 0;
    player_arr[player_arr_length].game_room = NULL;


    int i = 0;
    for(; i < 32; i++){
        player_arr[player_arr_length].cards_hand[i] = 0;
    }

    /* init struct of new player - END */
    return player_arr;
}

/* ____________________________________________________________________________
    struct player * remove_player(struct player *player_arr, int player_arr_length, char IP[20])

    Function removes user from array of players.
   ____________________________________________________________________________
*/
struct player * remove_player(struct player *player_arr, int player_arr_length, char IP[20]){
    struct player *player_arr_new = NULL; /* new array, without unwanted client */

    int new_arr_counter = 0;
    int i = 0;
    for(; i < player_arr_length; i++){
        if(strcmp(IP, player_arr[i].IP) == 0){
            player_arr_new = realloc(player_arr_new, (new_arr_counter + 1) * sizeof(struct player));
            player_arr_new[new_arr_counter] = player_arr[i];
            new_arr_counter += 1;
            printf("freed user with IP %s", player_arr[i].IP);
        }
    }

    /* free original array */
    free(player_arr);
    return player_arr_new;
}

/* ____________________________________________________________________________
    struct player * get_player_by_IP(struct player *player_arr, int player_arr_length, char IP[20])

    Finds player with wanted IP and returns a pointer to structure with player´s data (or NULL
    if player with given address is not present).
   ____________________________________________________________________________
*/
struct player * get_player_by_IP(struct player *player_arr, int player_arr_length, char IP[20]){
    int i = 0;
    for(; i < player_arr_length; i++){
        if(strcmp(player_arr[i].IP, IP) == 0){
            return &player_arr[i];
        }
    }

    return NULL;
}