#ifndef UPSSERVER_SERVER_H
#define UPSSERVER_SERVER_H
#include "player_part.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define SERVER_PORT_NUM_BASE 10
#define SERVER_MAX_CLIENT_NUM 5
#define SERVER_SOCKET_CREATE_ERROR "Error while creating server socket, exiting!\n"
#define SERVER_SOCKET_CREATE_OK "Socket created OK!\n"
#define SERVER_BINDING_ERROR "Error while binding socket!\n"
#define SERVER_BINDING_OK "Binding OK!\n"
#define SERVER_LISTEN_ERROR "Error while trying to listen!\n"
#define SERVER_LISTEN_OK "Listening OK!\n"
#define SERVER_LISTEN_PORT "Listening on port no.: %d\n"
#define SERVER_SELECT_ERROR "Error while performing select command!\n"
#define SERVER_NEW_CONNECTION "IP: %s, stage %d => new connection, new user\n"
#define SERVER_EXISTING_CONNECTION "IP: %s, stage %d => new connection, existing user\n"
#define SERVER_DATA_SIZE "IP: %s, stage %d => got data of size %dB\n"

#define SERVER_WRITE_RECEIVED_OK "#99?" /* received ok */
#define SERVER_WRITE_RECEIVED_FAIL "#98?" /* message from client is incomplete */

#define SERVER_PING_CHAR '0' /* pinging character */

#define SERVER_STAGE1_RECEIVED_NICKNAME "IP: %s, stage %d => valid, got nickname %.15s\n"
#define SERVER_RECEIVED_FAIL "IP: %s, stage %d => valid, but incomplete message - FAIL!\n"

/* STAGE 2 */
/* server request stage2 - START */
#define SERVER_STAGE2_GET_GAME_ROOM_LIST '1' /* get game room list request */
/* server request stage2 - START */

/* server response stage2 - START */
#define SERVER_STAGE2_WRITE_ROOM_EXISTS "#97?" /* server response to room creation req -> room already exists, err */
#define SERVER_STAGE2_WRITE_ROOM_DOES_NOT_EXIST "#96?" /* server response to room creation req -> room does not exist anymore, err */
#define SERVER_STAGE2_WRITE_ROOM_RUNNING "#95?" /* server response to room joining req -> game is running in wanted room or room is full, err */
/* server response stage2 - END */

/* server debug printf stage2 - START */
#define SERVER_STAGE2_RECEIVED_GET_GAME_ROOM_LIST "IP: %s, stage %d => valid, got \"1\" (code for GET_GAME_ROOM_LIST)\n"
#define SERVER_STAGE2_RECEIVED_JOIN "IP: %s, stage %d => valid, joined room with players: "
#define SERVER_STAGE2_RECEIVED_CREATE "IP: %s, stage %d => valid, created new room name %.10s\n"
/* server debug printf stage2 - END */

/* STAGE 3 */
/* server request stage3 - START */
#define SERVER_STAGE3_START_GAME '5' /* game start - request code */
#define SERVER_STAGE3_BACK_LOBBY '6' /* back to lobby (stage2) - request code */
#define SERVER_STAGE3_GAME_STATE '7' /* check game state (started or not) - request code */
/* server request stage3 - END */

/* server response stage3 - START */
#define SERVER_STAGE3_WRITE_GAME_STARTED "#10?" /* server code for game started by some user */
#define SERVER_STAGE3_WRITE_GAME_CANNOT_START "#11?" /* server code for - in game is only one player, cannot start, err */
/* server response stage3 - END */

/* server debug printf stage3 - START */
#define SERVER_STAGE3_RECEIVED_START "IP: %s, stage %d => valid, request for game start %.10s\n"
#define SERVER_STAGE3_RECEIVED_STAGE2_MOVE "IP: %s, stage %d => valid, request for going back to lobby\n"
#define SERVER_STAGE3_RECEIVED_ASK_STATE "IP: %s, stage %d => valid, asks if game has been started\n"
#define SERVER_STAGE3_STARTED "Game with name %.10s successfully started\n"
#define SERVER_STAGE3_CANNOT_START "Game with name %.10s is empty and cannot be started\n"
#define SERVER_STAGE3_GAME_NOT_RUNNING "Game with name %.10s has not started yet\n"
#define SERVER_STAGE3_GAME_RUNNING "Game with name %.10s has been already started started\n"
/* server debug printf stage3 - END */

/* STAGE 4 */
/* server request stage4 - START */
#define SERVER_STAGE4_TAKE_STAND "45" /* send one card (take) - request code */
#define SERVER_STAGE4_DISCONNECTED "46" /* player disconnected */
#define SERVER_STAGE4_GET_PLAYER_NAMES "50" /* get player names - request code */
#define SERVER_STAGE4_GET_CARDS "51" /* send game cards (user on hand - 32length - zero if not present, 1 if present) - request code */
#define SERVER_STAGE4_BACK_LOBBY "52" /* user wants to go back to lobby - request code */
/* server request stage4 - END */

/* server response stage4 - START */
#define SERVER_STAGE4_WRITE_CANNOT_PLACE "#69?" /* card cannot be placed */
#define SERVER_STAGE4_WRITE_NOT_TURN_PLACE "#68?" /* it is not users turn to play */
#define SERVER_STAGE4_WRITE_NOT_TURN_TAKE "#79?" /* cannot take card / stand - not users turn */
#define SERVER_STAGE4_WRITE_NO_FREE_CARDS "#78?" /* there are no more free cards in pool */

#define SERVER_STAGE4_MUST_TAKE_1_CARDS "#67?" /* user must take 1 card (7 placed) */
#define SERVER_STAGE4_MUST_TAKE_2_CARDS "#66?" /* user must take 2 cards (7 placed) */
#define SERVER_STAGE4_MUST_TAKE_3_CARDS "#65?" /* user must take 3 cards (7 placed) */
#define SERVER_STAGE4_MUST_TAKE_4_CARDS "#64?" /* user must take 4 cards (7 placed) */
#define SERVER_STAGE4_MUST_TAKE_5_CARDS "#63?" /* user must take 5 cards (7 placed) */
#define SERVER_STAGE4_MUST_TAKE_6_CARDS "#62?" /* user must take 6 cards (7 placed) */
#define SERVER_STAGE4_MUST_TAKE_7_CARDS "#61?" /* user must take 7 cards (7 placed) */
#define SERVER_STAGE4_MUST_TAKE_8_CARDS "#60?" /* user must take 8 cards (7 placed) */
/* server response stage4 - END */

/* server debug printf stage4 - START */
#define SERVER_STAGE4_RECEIVED_GET_CARDS "IP: %s, stage %d => valid, cards in hand request\n"
#define SERVER_STAGE4_GET_STATE "IP: %s, stage %d => valid, ping / get game state\n"
#define SERVER_STAGE4_CARDS_NEW "Sending NEW cards: %.32s\n"
#define SERVER_STAGE4_CARDS_OLD "Sending OLD cards: %.32s\n"
#define SERVER_STAGE4_RECEIVED_GET_PLAYER_NAMES "IP: %s, stage %d => valid, nicknames in room request\n"
#define SERVER_STAGE4_RECEIVED_TAKE_STAND "IP: %s, stage %d => valid, take / stand request\n"
#define SERVER_STAGE4_RECEIVED_PLACE "IP: %s, stage %d => valid, place card request\n"
#define SERVER_STAGE4_CHEATER "IP: %s, stage %d => invalid, place card request for invalid card!\n"
/* server debug printf stage4 - END */


/* printf dropped data with invalid size in some stage - START */
#define SERVER_INVALID_DATA_STAGE1 "From IP %s, DROPPED DATA - in stage1 invalid data with size %d\n"
#define SERVER_INVALID_DATA_STAGE2 "From IP %s, DROPPED DATA - in stage2 invalid data with size %d\n"
#define SERVER_INVALID_DATA_STAGE3 "From IP %s, DROPPED DATA - in stage3 invalid data with size %d\n"
#define SERVER_INVALID_DATA_STAGE4 "From IP %s, DROPPED DATA - in stage4 invalid data with size %d\n"
/* printf dropped data with invalid size in some stage - END */

/* ____________________________________________________________________________

    Function prototypes
   ____________________________________________________________________________
*/
int start_server();
int try_port_assign(char *second_param);
int check_data_validity_stage1(int socket, char *IP, struct player *player_send, int size_to_read);
int check_data_validity_stage2(int socket, char *IP, struct player *player_send, int size_to_read);
int check_data_validity_stage3(int socket, char *IP, struct player *player_send, int size_to_read);
int check_data_validity_stage4(int socket, char *IP, struct player *player_send, int size_to_read);

#endif //UPSSERVER_SERVER_H