#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>

#include "server.h"
#include "player_part.h"
#include "game_room_part.h"
#include "game_logic.h"

int port_number = -1;

struct player *player_arr; /* array with structures representing individual players */
int player_arr_length = 0;

struct game_room *game_room_arr; /* array with structures representing individual game rooms */
int game_room_arr_length = 0;

char room_buffer[13]; /* used in validity check - stage 2 - buffer for selected room name */
char room_buffer_only[10]; /* used in validity check - stage 2 - buffer for selected room name (without last character */
char buffer[4]; /* used in various stages for checking validity */

short send_win = 0; /* when 2, info about winner will be send */
short stage_set = 0; /* when user disconnects, stage is set to 1 */

/* ____________________________________________________________________________
    int start_server()

    Function starts the main part of the server (listens for new connections etc.)

    Function returns:
    a) 0 - if everything went ok
    b) 1 - if something bad happened (cannot open socket, etc.)
   ____________________________________________________________________________
*/
int start_server(){
    player_arr = malloc(sizeof(struct player) * 15); /* support up to 15 players */
    game_room_arr = malloc(sizeof(struct game_room) * 5); /* support up to 5 game rooms */

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    int server_socket = 0;
    int client_socket = 0;
    int ret_value = 0;
    int len_addr = 0;

    fd_set client_sockets, sock_des;
    int size_to_read;

    /* create server socket - START */
    server_socket = socket(AF_INET, SOCK_STREAM, 0); /* TCP protocol used */
    if(server_socket < 0){
        printf(SERVER_SOCKET_CREATE_ERROR);
        return EXIT_FAILURE;
    }else{
        printf(SERVER_SOCKET_CREATE_OK);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    /* create server socket - END */

    /* bind server socket - START */
    if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        printf(SERVER_BINDING_ERROR);
        return EXIT_FAILURE;
    }else{
        printf(SERVER_BINDING_OK);
    }
    /* bind server socket - END */

    /* listen - START */
    ret_value = listen(server_socket, SERVER_MAX_CLIENT_NUM);
    if(ret_value < 0){
        printf(SERVER_LISTEN_ERROR);
        return EXIT_FAILURE;
    }else{
        printf(SERVER_LISTEN_OK);
    }
    /* listen - END */

    /* empty socket set and add server_socket */
    FD_ZERO(&client_sockets);
    FD_SET(server_socket, &client_sockets);

    /* will be used when getting IP address of change */
    struct sockaddr_in addr;
    socklen_t length = sizeof(struct sockaddr_in);

    struct timespec start_time, stop_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    while(1){
        sock_des = client_sockets;

        ret_value = select(FD_SETSIZE, &sock_des, (fd_set *)0, (fd_set *)0, (struct timeval*) 0);

        if(ret_value < 0){
            printf(SERVER_SELECT_ERROR);
            return EXIT_FAILURE;
        }

        int i = 0;
        for(; i < FD_SETSIZE; i++){ /* go through sockets */
            if(FD_ISSET(i, &sock_des)){
                if(i == server_socket){ /* if change occured on server socket, then add new socket to the list */
                    client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &len_addr);
                    FD_SET(client_socket, &client_sockets);

                    getpeername(client_socket, (struct sockaddr *)&addr, &length);
                    if(check_player_new(player_arr, player_arr_length, client_socket) != EXIT_SUCCESS){ /* player with given IP not present */
                        add_player(player_arr, player_arr_length, client_socket); /* add new player */
                        player_arr_length += 1;
                        printf(SERVER_NEW_CONNECTION, inet_ntoa(addr.sin_addr), 0);
                    }else{
                        /* get stage of existing user */
                        struct player *player = get_player_by_IP(player_arr, player_arr_length, inet_ntoa(addr.sin_addr));
                        player -> stage = 1;
                        printf(SERVER_EXISTING_CONNECTION, inet_ntoa(addr.sin_addr), player -> stage);
                    }

                }else{ /* change occured on socket different from server socket */
                    /* get IP of client where change occured */
                    getpeername(i, (struct sockaddr *)&addr, &length);

                    ioctl(i, FIONREAD, &size_to_read);
                    if(size_to_read > 0){
                        /* get stage of sender, so we can know what kind of data is expected */
                        struct player *player_send = get_player_by_IP(player_arr, player_arr_length, inet_ntoa(addr.sin_addr));
                        printf(SERVER_DATA_SIZE, inet_ntoa(addr.sin_addr), player_send -> stage, size_to_read);

                        if(player_send -> stage == 1){ /* expecting nickname (15 char) */
                            if(check_data_validity_stage1(i, inet_ntoa(addr.sin_addr), player_send, size_to_read) == EXIT_FAILURE){
                                printf(SERVER_INVALID_DATA_STAGE1, inet_ntoa(addr.sin_addr), size_to_read);
                                close(i);
                                FD_CLR(i, &client_sockets);
                            }
                        }else if(player_send -> stage == 2){ /* expecting name of game room (11 char) || request code for getting game room list ('1') */
                            if(check_data_validity_stage2(i, inet_ntoa(addr.sin_addr), player_send, size_to_read) == EXIT_FAILURE){ /* received invalid data in stage2 */
                                printf(SERVER_INVALID_DATA_STAGE2, inet_ntoa(addr.sin_addr), size_to_read);
                                close(i);
                                FD_CLR(i, &client_sockets);
                            }
                        }else if(player_send -> stage == 3){ /* waiting for game start - ('5') */
                            if(check_data_validity_stage3(i, inet_ntoa(addr.sin_addr), player_send, size_to_read) == EXIT_FAILURE){
                                printf(SERVER_INVALID_DATA_STAGE3, inet_ntoa(addr.sin_addr), size_to_read);
                                close(i);
                                FD_CLR(i, &client_sockets);
                            }
                        }else if(player_send -> stage == 4){
                            if(check_data_validity_stage4(i, inet_ntoa(addr.sin_addr), player_send, size_to_read) == EXIT_FAILURE){
                                printf(SERVER_INVALID_DATA_STAGE4, inet_ntoa(addr.sin_addr), size_to_read);
                                close(i);
                                FD_CLR(i, &client_sockets);
                                break;
                            }
                        }else{/* drop data */
                            close(i);
                            FD_CLR(i, &client_sockets);
                        }
                    }else{ /* legal end - remove player from list */
                        printf("Player IP %s has left (EXPECTED).\n", inet_ntoa(addr.sin_addr));
                        close(i);
                        FD_CLR(i, &client_sockets);
                    }
                    printf("\n");
                }
            }
        }
    }
}

/* ____________________________________________________________________________
    int try_port_assign(char *second_param)

    Function tries to convert char sequence entered by user as second parameter
    to int representing port number.

    Function returns:
    a) 0 - if user entered number as a port == 2
    b) 1 - if user entered invalid input != 2
   ____________________________________________________________________________
*/
int try_port_assign(char *second_param){
    int number_entered; /* will contain the numeric part of string which user entered */
    char* not_number_part; /* will contain the non-numeric part of string that user entered */
    number_entered = (int)strtol(second_param, &not_number_part, SERVER_PORT_NUM_BASE);
    if(*not_number_part) {
        return EXIT_FAILURE;
    }else{
        port_number = number_entered;
        printf(SERVER_LISTEN_PORT, port_number);
        return EXIT_SUCCESS;
    }
}

/* ____________________________________________________________________________
    int check_data_validity_stage1(int socket, struct player *player_send, int size_to_read)

    Function checks if data send by user are valid in stage1 or not.
    In stage1 nickname is expected (15char), everything else is invalid.

    Codes send back to user in this stage - START
    SERVER_WRITE_RECEIVED - "99" -> nickname was successfully received
    Codes send back to user in this stage - END

    Function returns:
    a) 0 - if data in stage1 are valid
    b) 1 - if data in stage1 are invalid
   ____________________________________________________________________________
*/
int check_data_validity_stage1(int socket, char *IP, struct player *player_send, int size_to_read){
    char *message_buffer = malloc(sizeof(char) * 17);
    int i = 1;

    if(size_to_read == 17){ /* first is #, last is ? */
        read(socket, message_buffer, size_to_read);
        if(message_buffer[0] == '#' && message_buffer[16] == '?'){ /* message received ok */
            for(; i < 16; i++){ /* copy nick to structure */
                player_send -> nickname[i - 1] = message_buffer[i];
            }

            printf(SERVER_STAGE1_RECEIVED_NICKNAME, IP, 1, player_send -> nickname);
            player_send -> stage = 2; /* move to another stage - pick game room */
            write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4);
        }else{ /* message in wrong format */
            printf(SERVER_RECEIVED_FAIL, IP, 1);
            write(socket, SERVER_WRITE_RECEIVED_FAIL, sizeof(char) * 4);
        }

        free(message_buffer);
        return EXIT_SUCCESS;
    }else{
        free(message_buffer);
        return EXIT_FAILURE;
    }
}

/* ____________________________________________________________________________
    int check_data_validity_stage2(int socket, char *IP, struct player *player_send, int size_to_read)

    Function checks if data send by user are valid in stage2 or not.
    In stage2 code request for game list is expected (1char "1")
    or name of the chosen game (11char) - 10char game name + 1char for game status
    ("0" already created, "1" user wants to create new)
    , everything else is invalid.

    Codes send back to user in this stage - START
    SERVER_WRITE_RECEIVED_OK - "99" -> data successfully received
    SERVER_WRITE_RECEIVED_FAIL - "98" -> data receive failed
    SERVER_STAGE2_WRITE_ROOM_EXISTS - "97" -> user wanted to create a new room => room with this name alrready exists, error
    SERVER_STAGE2_WRITE_ROOM_DOES_NOT_EXIST - "96" -> user wanted to join non-existing room, error
    SERVER_STAGE2_WRITE_ROOM_RUNNING - "95" -> user wanted to join room in which game is already running or the room is full
    Codes send back to user in this stage - END

    Function returns:
    a) 0 - if data in stage2 are valid
    b) 1 - if data in stage2 are invalid
   ____________________________________________________________________________
*/
int check_data_validity_stage2(int socket, char *IP, struct player *player_send, int size_to_read){
    if(size_to_read == 13){ /* 10 for name of room, 11 = 0 if room is already created, 1 if user wants to create new && first is #, last is ? */
        read(socket, &room_buffer, size_to_read);

        if(room_buffer[0] != '#' || room_buffer[12] != '?'){ /* message received fail */
            printf(SERVER_RECEIVED_FAIL, IP, 2, player_send -> nickname);
            write(socket, SERVER_WRITE_RECEIVED_FAIL, sizeof(char) * 4);
            return EXIT_SUCCESS;
        }
        /* message looks ok, go on */

        int i = 0;
        for(; i < 10; i++){
            room_buffer_only[i] = room_buffer[i + 1];
        }

        if(room_buffer[11] == '1'){ /* user attempts to create a new room */
            /* check1 - is there any existing room with this name? */
            if(check_room_new(game_room_arr, game_room_arr_length, room_buffer_only) == EXIT_SUCCESS){ /* room is already present */
                write(socket, SERVER_STAGE2_WRITE_ROOM_EXISTS, sizeof(char) * 4);
                return EXIT_SUCCESS;
            }else{ /* ok, create new room */
                int free_index = game_room_arr_length;
                int i = 0;
                for(; i < game_room_arr_length; i++){
                    if(strncmp(game_room_arr[i].name_room, "%%%%%%%%%%", 10) == 0){
                        free_index = i;
                        break;
                    }
                }

                game_room_arr = add_room(game_room_arr, game_room_arr_length, room_buffer_only);

                if(free_index == game_room_arr_length)
                game_room_arr_length += 1;

                struct game_room *game_room = get_game_room_by_name(game_room_arr, game_room_arr_length, room_buffer_only);
                /* add player to room */
                game_room -> players[0] = player_send;
                game_room -> player_count += 1;

                /* assign room to player */
                player_send -> game_room = game_room;

                printf("Add player %.15s to room created %.10s \n", player_send -> nickname, player_send -> game_room -> name_room);
                /* players turn */
                game_room -> actual_player = 0;
                /* actual card, pick random */

                /* set random card to begin */
                srand(time(NULL));
                int random = rand() % 43; /* 0 - 43 generate -> cards */

                int card_num_no_change = random;
                if(card_num_no_change > 31 && card_num_no_change < 35){
                    card_num_no_change = 5; /* koule menic */
                }else if(card_num_no_change > 34 && card_num_no_change < 38){
                    card_num_no_change = 13; /* cervena menic */
                }else if(card_num_no_change > 37 && card_num_no_change < 41){
                    card_num_no_change = 21; /* zelena menic */
                }else if(card_num_no_change > 40 && card_num_no_change < 44){
                    card_num_no_change = 29; /* zaludy menic */
                }

                if(player_send -> game_room -> card_pool[card_num_no_change] == 1){ /* card is present in pool */
                    player_send -> game_room -> card_pool[card_num_no_change] = 0; /* take card from pool */
                    player_send -> game_room -> actual_card = random;
                    printf("Assigned card %d to pool \n", random);
                }
                player_send -> game_room -> is_active = 1; /* set card as active */
                if(random == 0 || random == 8 || random == 16 || random == 24){ /* 7, cards to take +2 */
                    player_send -> game_room -> cards_to_take += 2;
                }

                printf(SERVER_STAGE2_RECEIVED_CREATE, IP, 2, room_buffer_only);
                player_send -> stage = 3; /* move to another stage - wait for game to start */
                write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4);
                return EXIT_SUCCESS;
            }
        }else if(room_buffer[11] == '0'){ /* user wants to connect to existing game */
            /* check1 - does the room still exist? */
            if(check_room_new(game_room_arr, game_room_arr_length, room_buffer_only) == EXIT_FAILURE){ /* room is not available anymore */
                write(socket, SERVER_STAGE2_WRITE_ROOM_DOES_NOT_EXIST, sizeof(char) * 4);
                return EXIT_SUCCESS;
            /* check2 - has the game been started? */
            }else if((get_game_room_by_name(game_room_arr, game_room_arr_length, room_buffer_only) -> game_running == 1 || get_game_room_by_name(game_room_arr, game_room_arr_length, room_buffer_only) -> player_count == 3) && (player_send -> game_room == NULL || strncmp(room_buffer_only, player_send -> game_room -> name_room, 10) != 0)){ /* game in this room is already running or room is full, allow reconnect */
                write(socket, SERVER_STAGE2_WRITE_ROOM_RUNNING, sizeof(char) * 4);
                return EXIT_SUCCESS;
            }else{ /* ok, join existing room */
                printf(SERVER_STAGE2_RECEIVED_JOIN, IP, 2);

                if(player_send -> game_room != NULL && player_send -> game_room -> game_running == 1 && strncmp(room_buffer_only, player_send -> game_room -> name_room, 10) == 0){ /* player is reconnecting */
                    player_send -> stage = 3; /* move to another stage - wait for game to start */
                    write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4);
                    return EXIT_SUCCESS;
                }

                struct game_room *game_room = get_game_room_by_name(game_room_arr, game_room_arr_length, room_buffer_only);

                /* add new player to free position */
                if(game_room -> player_count == 0){
                    game_room -> players[0] = player_send;
                }else if(game_room -> player_count == 1){
                    game_room -> players[1] = player_send;
                }else{
                    game_room -> players[2] = player_send;
                }

                game_room -> player_count += 1;

                /* assign room to player */
                player_send -> game_room = game_room;

                player_send -> stage = 3; /* move to another stage - wait for game to start */
                write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4);
                return EXIT_SUCCESS;
            }
        }else{ /* received invalid data in stage2 */
            return EXIT_FAILURE;
        }
    }else if(size_to_read == 3){ /* user probably wants to get name of the rooms ("1") */
        read(socket, &buffer, size_to_read);

        if(buffer[1] == SERVER_STAGE2_GET_GAME_ROOM_LIST){
            printf(SERVER_STAGE2_RECEIVED_GET_GAME_ROOM_LIST, IP, 2);
            char *created_rooms = get_game_room_list(game_room_arr, game_room_arr_length);
            write(socket, created_rooms, sizeof(char) * 52);

            free(created_rooms);
            return EXIT_SUCCESS;
        }else{
            return EXIT_FAILURE;
        }
    }else{ /* received invalid data in stage2 */
        return EXIT_FAILURE;
    }
}

/* ____________________________________________________________________________
    int check_data_validity_stage3(int socket, char *IP, struct player *player_send, int size_to_read)

    Function check if data send by user are valid in stage3 or not.
    In stage3 code request for game start is expected (1char "5"),
    code for going back to lobby ("6") or code for checking if the game
    has already been started ("7"), everything else is invalid.

    Codes send back to user in this stage - START
    SERVER_STAGE3_WRITE_GAME_STARTED - "10" -> game was started
    SERVER_STAGE3_WRITE_GAME_CANNOT_START - "11" -> game cannot be started (only one user)
    SERVER_WRITE_RECEIVED "99" -> received request. but the game has not been started yet
    Codes send back to user in this stage - END

    Function returns:
    a) 0 - if data in stage3 are valid
    b) 1 - if data in stage3 are invalid
   ____________________________________________________________________________
*/
int check_data_validity_stage3(int socket, char *IP, struct player *player_send, int size_to_read){
   if(size_to_read == 3){ /* size ok */
        read(socket, &buffer, size_to_read);

       if(buffer[0] != '#' || buffer[2] != '?'){ /* message received fail */
           printf(SERVER_RECEIVED_FAIL, IP, 3, player_send -> nickname);
           write(socket, SERVER_WRITE_RECEIVED_FAIL, sizeof(char) * 4);
           return EXIT_SUCCESS;
       }

        if(buffer[1] == SERVER_STAGE3_START_GAME){ /* user wants to start game */
            printf(SERVER_STAGE3_RECEIVED_START, IP, 3, player_send -> game_room -> name_room);

            /* check 1 - user count >= 2 */
            if(player_send -> game_room -> player_count >= 2){ /* ok, start */
                printf(SERVER_STAGE3_STARTED, player_send -> game_room -> name_room);
                player_send -> game_room -> game_running = 1; /* set game as running */
                write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4);
                return EXIT_SUCCESS;
            }else{
                printf(SERVER_STAGE3_CANNOT_START, player_send -> game_room -> name_room);
                write(socket, SERVER_STAGE3_WRITE_GAME_CANNOT_START, sizeof(char) * 4);
              /*  printf(SERVER_STAGE3_STARTED, player_send -> game_room -> name_room);
                player_send -> game_room -> game_running = 1;
                write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4); here*/
                return EXIT_SUCCESS;
            }
        }else if(buffer[1] == SERVER_STAGE3_BACK_LOBBY){ /* user wants move to lobby */
            printf(SERVER_STAGE3_RECEIVED_STAGE2_MOVE, IP, 3);
            player_send -> stage = 2; /* lobby */
            /* check if there are any user in left room - if not, delete */

            struct game_room *left_room = player_send -> game_room;
            printf("Left room with name %.10s\n", left_room ->name_room);

            int i = 0;
            for(; i < left_room -> player_count; i++){
                if(strcmp(IP, left_room -> players[i] -> IP) == 0){
                   // printf("comparing IP %s with %s - same", IP, left_room -> players[i] -> IP);
                    left_room -> player_count -= 1;
                }else{
                    //printf("comparing IP %s with %s - notsame", IP, left_room -> players[i] -> IP);
                }
            }

            if(left_room -> game_running == 1){/* here */
                game_room_arr = remove_room(game_room_arr, game_room_arr_length, left_room -> name_room);
            }
            player_send -> game_room = NULL; /* left room */

            write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4);
            return EXIT_SUCCESS;
        }else if(buffer[1] == SERVER_STAGE3_GAME_STATE){
            printf(SERVER_STAGE3_RECEIVED_ASK_STATE, IP, 3);

            if(player_send -> game_room -> game_running == 1){ /* game has been started */
                printf(SERVER_STAGE3_GAME_RUNNING, player_send -> game_room -> name_room);
                player_send -> stage = 4; /* game stage */
                write(socket, SERVER_STAGE3_WRITE_GAME_STARTED, sizeof(char) * 4);
            }else{ /* game has not been started yet */
                printf(SERVER_STAGE3_GAME_NOT_RUNNING, player_send -> game_room -> name_room);
                char *player_room = get_player_names_room(player_send -> game_room);
                free(player_room);
                write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4);
            }

            return EXIT_SUCCESS;
        }else{
            return EXIT_FAILURE;
        }
    }else{
        return EXIT_FAILURE;
    }
}

/* ____________________________________________________________________________
    int check_data_validity_stage4(int socket, char *IP, struct player *player_send, int size_to_read)

    Function check if data send by user are valid in stage4 or not.
    In stage4 code request for placing cards is expected ("01"-"44"),
    code request for getting player names (2char "50"),
    code request for getting cards on hand is expected (2char "51"),
    code request for getting one card (2char "52"),
    code request for getting actual player (2char "53") - ping..
    , everything else is invalid.

    Codes send back to user in this stage - START
    SERVER_STAGE4_WRITE_INVALID_CARD - "60" -> invalid card placed
    SERVER_STAGE4_WRITE_PLAYER1_PLAY - "61" -> player1 should play now
    SERVER_STAGE4_WRITE_PLAYER2_PLAY - "62" -> player2 should play now
    SERVER_STAGE4_WRITE_PLAYER2_PLAY - "63" -> player3 should play now
    SERVER_STAGE4_WRITE_PLAYER1_DISCONNECTED - "64" -> player1 was disconnected
    SERVER_STAGE4_WRITE_PLAYER2_DISCONNECTED - "65" -> player2 was disconnected
    SERVER_STAGE4_WRITE_PLAYER2_DISCONNECTED - "66" -> player3 was disconnected

    SERVER_WRITE_RECEIVED "99" -> received request, nothing in game changed
    Codes send back to user in this stage - END

    Function returns:
    a) 0 - if data in stage4 are valid
    b) 1 - if data in stage4 are invalid
   ____________________________________________________________________________
*/
int check_data_validity_stage4(int socket, char *IP, struct player *player_send, int size_to_read){
    if(size_to_read == 4){ /* ok size */
        read(socket, &buffer, size_to_read);

        if(buffer[0] != '#' || buffer[3] != '?'){ /* message received fail */
            printf(SERVER_RECEIVED_FAIL, IP, 4, player_send -> nickname);
            write(socket, SERVER_WRITE_RECEIVED_FAIL, sizeof(char) * 4);
            return EXIT_SUCCESS;
        }

        if(buffer[1] == SERVER_STAGE4_GET_CARDS[0] && buffer[2] == SERVER_STAGE4_GET_CARDS[1]){ /* user wants to know which cards are in his hand */
            printf(SERVER_STAGE4_RECEIVED_GET_CARDS, IP, 4);
            if(player_send -> cards_assigned == 0){ /* cards in actual game have not been assigned */
                /* assign cards from pool */
                srand(time(NULL));
                int total_cards = 0;
                int card_number[4];

                int random;
                while(total_cards != 4){/* get 4 cards */
                    random = rand() % 32; /* 0 - 31 generate -> cards */
                    if(player_send -> game_room -> card_pool[random] == 1){ /* card is present in pool */
                        player_send -> game_room -> card_pool[random] = 0; /* take card from pool */
                        card_number[total_cards] = random; /* get card number */
                        total_cards += 1;
                    }
                }

                player_send -> cards_assigned = 1;

                char *cards_list = malloc(34 * sizeof(char));

                int i = 0;
                for(; i < 34; i++){
                    cards_list[i] = '0'; /* init, not present */
                }
                cards_list[0] = '#';
                cards_list[33] = '?';

                i = 0;
                for(; i < 4; i++){
                    cards_list[card_number[i] + 1] = '1'; /* card is present */
                    player_send -> cards_hand[card_number[i]] = 1; /* card is present in user hand */
                }

                printf(SERVER_STAGE4_CARDS_NEW, cards_list);
                write(socket, cards_list, sizeof(char) * 34);
                free(cards_list);
                return EXIT_SUCCESS;
            }else{ /* return already assigned cards (user may have left the game */
                char *cards_list = malloc(34 * sizeof(char));
                int i = 0;
                for(; i < 32; i++){
                    if(player_send -> cards_hand[i] == 0){
                        cards_list[i + 1] = '0'; /* not present */
                    }else{
                        cards_list[i + 1] = '1'; /* card is present */
                    }
                }
                cards_list[0] = '#';
                cards_list[33] = '?';

                printf(SERVER_STAGE4_CARDS_OLD, cards_list);
                write(socket, cards_list, sizeof(char) * 34);
                free(cards_list);
                return EXIT_SUCCESS;
            }
        }else if(buffer[1] == SERVER_STAGE4_GET_PLAYER_NAMES[0] && buffer[2] == SERVER_STAGE4_GET_PLAYER_NAMES[1]){ /* user wants to know names of players in room */
            printf(SERVER_STAGE4_RECEIVED_GET_PLAYER_NAMES, IP, 4);

            char *player_in_room = get_player_names_room(player_send -> game_room);
            write(socket, player_in_room, sizeof(char) * 47);
            free(player_in_room);
        }else if(buffer[1] == SERVER_STAGE4_TAKE_STAND[0] && buffer[2] == SERVER_STAGE4_TAKE_STAND[1]){ /* user wants to take card / stand */
            printf(SERVER_STAGE4_RECEIVED_TAKE_STAND, IP, 4);

            /* check user turn.. */
            int i = 0;
            for(; i < player_send -> game_room -> player_count; i++){
                if(strcmp(IP, player_send -> game_room -> players[i] -> IP) == 0){
                    break;
                }
            }

            if(player_send -> game_room -> actual_player == i){
                if(player_send -> game_room -> is_active && (player_send -> game_room -> actual_card == 7 || player_send -> game_room -> actual_card == 15 || player_send -> game_room -> actual_card == 23 || player_send -> game_room -> actual_card == 31)){ /* user can just stand, ace is in pool */
                    write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4); /* ok,stand */
                    /* move to next player */
                    player_send -> game_room -> actual_player += 1;
                    if(player_send -> game_room -> actual_player == player_send -> game_room -> player_count){
                        player_send -> game_room -> actual_player = 0;
                    }
                    player_send -> game_room -> is_active = 0; /* set ace as inactive */
                    return EXIT_SUCCESS;
                }

                /* user wants to take another card */
                int random; /* 0 - 31 generate -> cards */
                int assigned = -1;

                int i = 0;
                for(; i < 10; i++){ /* try random card pick */
                    random = rand() % 32;
                    if(player_send -> game_room -> card_pool[random] == 1){ /* card is present in pool */
                        player_send -> game_room -> card_pool[random] = 0; /* take card from pool */
                        player_send -> cards_hand[random] = 1; /* assign card to player */
                        assigned = random;
                        break;
                    }
                }

                i = 0;
                if(assigned == -1){ /* random failed and cannot wait forever, go through free cards and assign first free */
                    for(; i < 32; i++){ /* go through free cards */
                        if(player_send -> game_room -> card_pool[i] == 1){ /* card is present in pool */
                            player_send -> game_room -> card_pool[i] = 0; /* take card from pool */
                            player_send -> cards_hand[i] = 1; /* assign card to player */
                            assigned = i;
                            break;
                        }
                    }
                }

                if(assigned == -1){ /* no free cards in pool, err */
                    write(socket, SERVER_STAGE4_WRITE_NO_FREE_CARDS, sizeof(char) * 4); /* no free cards, err*/
                }else{ /* send desired card */
                    int length_card_code = snprintf( NULL, 0, "%d", assigned);
                    char* card_code = malloc(length_card_code + 1);
                    snprintf(card_code, length_card_code + 1, "%d", assigned);

                    char *card_code_edit = malloc(sizeof(char) * 4);
                    card_code_edit[0] = '#';
                    card_code_edit[3] = '?';

                    if(strlen(card_code) == 1){
                        card_code_edit[1] = '0';
                        card_code_edit[2] = card_code[0];
                    }else{
                        card_code_edit[1] = card_code[0];
                        card_code_edit[2] = card_code[1];
                    }

                    if(player_send -> game_room -> cards_to_take > 0){
                        player_send -> game_room -> cards_to_take -= 1;
                    }

                    if(player_send -> game_room -> cards_to_take == 0){ /* move to next player */
                        player_send -> game_room -> actual_player += 1;
                        if(player_send -> game_room -> actual_player == player_send -> game_room -> player_count){
                            player_send -> game_room -> actual_player = 0;
                        }
                        player_send -> game_room -> is_active = 0; /* make inactive */
                    }
                    write(socket, card_code_edit, sizeof(char) * 4);
                    free(card_code);
                    free(card_code_edit);
                }
                return EXIT_SUCCESS;
            }else{
                write(socket, SERVER_STAGE4_WRITE_NOT_TURN_TAKE, sizeof(char) * 4); /* cannot place */
                return EXIT_SUCCESS;
            }
        }else if(buffer[1] == SERVER_STAGE4_BACK_LOBBY[0] && buffer[2] == SERVER_STAGE4_BACK_LOBBY[1]){ /* user wants to go back to lobby */
            player_send -> stage = 2; /* lobby */
            player_send -> last_ping = 0;
            player_send -> cards_assigned = 0;

            int i = 0;
            for(; i < 32; i++){
                player_send -> cards_hand[i] = 0;
            }

            struct game_room *left_room = player_send -> game_room;
            if(left_room -> game_running == 1){ /* game was running */
                game_room_arr = remove_room(game_room_arr, game_room_arr_length, left_room -> name_room);
            }

            player_send -> game_room = NULL; /* left room */
            write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4); /* ok, go to lobby */
            return EXIT_SUCCESS;
        }else{ /* user wants to place card */
            printf(SERVER_STAGE4_RECEIVED_PLACE, IP, 4);

            /* get actual card code */
            short actual_card_code = player_send -> game_room -> actual_card;
            actual_card_code += 1; /* to match index */

            int length_actual_card_code = snprintf( NULL, 0, "%d", actual_card_code);
            char* actual_card = malloc(length_actual_card_code + 1);
            snprintf(actual_card, length_actual_card_code + 1, "%d", actual_card_code);

            char old_card[2];
            if(strlen(actual_card) == 1){
                old_card[0] = '0';
                old_card[1] = actual_card[0];
            }else{
                old_card[0] = actual_card[0];
                old_card[1] = actual_card[1];
            }
            free(actual_card);

            char new_card_char[3];
            new_card_char[0] = buffer[1];
            new_card_char[1] = buffer[2];
            new_card_char[2] = '\0';

            int valid = check_card_validity(old_card, new_card_char, player_send -> game_room -> is_active);
            printf("Trying place card %.2s over %.2s \n", new_card_char, old_card);

            int placed_card = atoi(new_card_char);
            placed_card -= 1; /* to match index */

            if(player_send -> game_room -> cards_to_take > 0 && placed_card != 0 && placed_card != 8 && placed_card != 16 && placed_card != 24){ /* there are some cards to take and user doesnt want to place 7 */
                if(player_send -> game_room -> cards_to_take == 1){ /* send response - take some card, user! */
                    write(socket, SERVER_STAGE4_MUST_TAKE_1_CARDS, sizeof(char) * 4);
                }else if(player_send -> game_room -> cards_to_take == 2){
                    write(socket, SERVER_STAGE4_MUST_TAKE_2_CARDS, sizeof(char) * 4);
                }else if(player_send -> game_room -> cards_to_take == 3){
                    write(socket, SERVER_STAGE4_MUST_TAKE_3_CARDS, sizeof(char) * 4);
                }else if(player_send -> game_room -> cards_to_take == 4){
                    write(socket, SERVER_STAGE4_MUST_TAKE_4_CARDS, sizeof(char) * 4);
                }else if(player_send -> game_room -> cards_to_take == 5){
                    write(socket, SERVER_STAGE4_MUST_TAKE_5_CARDS, sizeof(char) * 4);
                }else if(player_send -> game_room -> cards_to_take == 6){
                    write(socket, SERVER_STAGE4_MUST_TAKE_6_CARDS, sizeof(char) * 4);
                }else if(player_send -> game_room -> cards_to_take == 7){
                    write(socket, SERVER_STAGE4_MUST_TAKE_7_CARDS, sizeof(char) * 4);
                }else if(player_send -> game_room -> cards_to_take == 8){
                    write(socket, SERVER_STAGE4_MUST_TAKE_8_CARDS, sizeof(char) * 4);
                }
                return EXIT_SUCCESS;
            }

            if(valid == 1){ /* true, set new actual card */
                /* check user turn.. */
                int i = 0;
                for(; i < player_send -> game_room -> player_count; i++){
                    if(strcmp(IP, player_send -> game_room -> players[i] -> IP) == 0){
                       break;
                    }
                }

                if(player_send -> game_room -> actual_player == i){ /* it is users turn */
                    int new_card = atoi(new_card_char);
                    new_card -= 1; /* to match index */

                    int card_num_no_change = new_card;
                    if(card_num_no_change > 31 && card_num_no_change < 35){
                        card_num_no_change = 5; /* koule menic */
                    }else if(card_num_no_change > 34 && card_num_no_change < 38){
                        card_num_no_change = 13; /* cervena menic */
                    }else if(card_num_no_change > 37 && card_num_no_change < 41){
                        card_num_no_change = 21; /* zelena menic */
                    }else if(card_num_no_change > 40 && card_num_no_change < 44){
                        card_num_no_change = 29; /* zaludy menic */
                    }

                    if(player_send -> cards_hand[card_num_no_change] == 0){
                        printf(SERVER_STAGE4_CHEATER, IP, 4);
                        write(socket, SERVER_STAGE4_WRITE_CANNOT_PLACE, sizeof(char) * 4); /* user does not have this card assigned, cheater! */
                        return EXIT_FAILURE;
                    }

                    /* put card back to pool */
                    player_send -> game_room -> card_pool[card_num_no_change] = 1;

                    /* remove card from player */
                    player_send -> cards_hand[card_num_no_change] = 0;

                    /* set as actual card */
                    player_send -> game_room -> actual_card = new_card;

                    player_send -> game_room -> is_active = 1; /* set placed card as active */
                    if(new_card == 0 || new_card == 8 || new_card == 16 || new_card == 24){ /* 7, cards to take +2 */
                        player_send -> game_room -> cards_to_take += 2;
                    }

                    /* check if user has any cards remaining */
                    i = 0;
                    int cards_user_count = 0;
                    for(; i < 32; i++){
                        if(player_send -> cards_hand[i] == 1){
                            cards_user_count += 1;
                        }
                    }

                    printf("User has got %d cards!", cards_user_count);
                    if(cards_user_count == 0){ /* user win, end game */
                        send_win = 1;
                    }else{
                        /* move to next player */
                        player_send -> game_room -> actual_player += 1;
                        if(player_send -> game_room -> actual_player == player_send -> game_room -> player_count){
                            player_send -> game_room -> actual_player = 0;
                        }
                    }
                    write(socket, SERVER_WRITE_RECEIVED_OK, sizeof(char) * 4); /* ok,placed */
                    return EXIT_SUCCESS;
                }else{
                    write(socket, SERVER_STAGE4_WRITE_NOT_TURN_PLACE, sizeof(char) * 4); /* cannot place */
                    return EXIT_SUCCESS;
                }
            }else{
                write(socket, SERVER_STAGE4_WRITE_CANNOT_PLACE, sizeof(char) * 4); /* cannot place */
                return EXIT_SUCCESS;
            }
        }
    }else if(size_to_read == 3){
        read(socket, &buffer, size_to_read);

        if(buffer[1] == SERVER_PING_CHAR){ /* server ping, dont want player kick - in stage 4 send info about actual card and game state */
            printf(SERVER_STAGE4_GET_STATE, IP, 4);
            /* send message in form "xyyz", where x = players num, yy = number of card placed (0-44) OR 00 if waiting for player OR 45 if player takes card OR 46 if he has no cards
             * OR 47 if player disconnected OR 48 if player reconnected */
            struct player *player_ping = get_player_by_IP(player_arr, player_arr_length, IP);
            struct timeval actual_time;
            gettimeofday(&actual_time, NULL);
            long int ms = (actual_time.tv_sec * 1000 + actual_time.tv_usec / 1000);

            int player_disconnected_num = check_player_disconnected(player_send -> game_room);
            player_ping -> last_ping = ms;
            if(player_disconnected_num != -1 && strcmp(player_ping -> IP, player_ping -> game_room -> players[player_disconnected_num] -> IP) != 0) { /* player disconnected, send message to other */
                char created_message[6];
                created_message[0] = '#';
                created_message[5] = '?';

                if(player_disconnected_num == 0){
                    created_message[1] = '0';
                }else if(player_disconnected_num == 1){
                    created_message[1] = '1';
                }else{
                    created_message[1] = '2';
                }

                created_message[2] = SERVER_STAGE4_DISCONNECTED[0];
                created_message[3] = SERVER_STAGE4_DISCONNECTED[1];
                if(player_send -> game_room -> is_active == 0){
                    created_message[4] = '0';
                }else{
                    created_message[4] = '1';
                }

                if(stage_set == 0){ /* stage not set yet */
                    player_send -> game_room -> players[player_disconnected_num] -> stage = 1; /* user is able to reconnect */
                    stage_set = 1;
                }
                write(socket, created_message, sizeof(char) * 6);
                return EXIT_SUCCESS;
            }else{
                stage_set = 0; /* reconnected */
            }

            if(send_win == 1){
                send_win = 0;
                player_send -> game_room -> is_active = 2;
            }

            struct game_room *game_room = get_game_room_by_name(game_room_arr, game_room_arr_length, player_send -> game_room -> name_room);
            /* get actual player num */
            short actual_player_num = game_room -> actual_player;
            int length_player_num = snprintf( NULL, 0, "%d", actual_player_num);
            char* player_num = malloc(length_player_num + 1);
            snprintf(player_num, length_player_num + 1, "%d", actual_player_num);

            /* get actual card code */
            short actual_card_code = game_room -> actual_card;
            int length_card_code = snprintf( NULL, 0, "%d", actual_card_code);
            char* card_num = malloc(length_card_code + 1);
            snprintf(card_num, length_card_code + 1, "%d", actual_card_code);

            /* check if card is activated for current user */
            short activated = player_send -> game_room -> is_active;
            int length_activated = snprintf( NULL, 0, "%d", activated);
            char* activated_num = malloc(length_activated + 1);
            snprintf(activated_num, length_activated + 1, "%d", activated);

            /* build code message to send */
            char created_message[6];
            created_message[0] = '#';
            created_message[5] = '?';

            created_message[1] = player_num[0]; /* assign player to message */
            /* assign card to message - START */
            if(strlen(card_num) == 1){
                created_message[2] = '0';
                created_message[3] = card_num[0];
            }else{
                created_message[2] = card_num[0];
                created_message[3] = card_num[1];
            }
            /* assign card to message - END */

            /* assign activity to card */
            created_message[4] = activated_num[0];
            write(socket, created_message, sizeof(char) * 6);
            printf("Game state is: %.6s\n", created_message);

            free(player_num);
            free(card_num);
            free(activated_num);
            return EXIT_SUCCESS;
        }else{
            return EXIT_FAILURE;
        }
    }else{
        return EXIT_FAILURE;
    }
}