//
//  main.cpp
//  Checkers2
//
//  Created by Darlene Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "coordinate.h"
#include "player.h"
#include "piece.h"
#include "checker.h"
#include "square.h"
#include <time.h>
#include "computer_player.h"

using namespace std;

void make_coordinates();
void make_board();
void place_player1_checkers(Player *);
void place_player2_checkers(Player *);
void display_start_menu();
int get_start_menu_selection();
int is_there_a_winner();
string get_board_string();
int get_player_moves(Player *player_ptr);
void display_moves(int);
int get_player_jumps(Player *player_ptr);
void display_jumps(int n, int start = 0);
bool load_game(string file_name);
bool save_game(string file_name, int game_mode, bool jumped);
int play_game(Player *player1_ptr, Player *player2_ptr, bool j);
void update_moves_and_jumps(Player *player1_ptr, Player *player2_ptr);
int get_jumps(Square *square_ptr, Player * player_ptr);
void display_plays();
void clear_board();

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;
const int NUM_CHECKERS = 12; // The number of checker each player starts with
Player PLAYER1(1);
Player PLAYER2(2);
Computer_player COMPUTER_PLAYER(2);
int TURN = 1;

//const int NUM_SQUARES = BOARD_WIDTH * BOARD_HEIGHT;
Coordinate COORDINATES[BOARD_WIDTH][BOARD_HEIGHT];
Square BOARD[BOARD_WIDTH][BOARD_HEIGHT];
Checker PLAYER1_CHECKERS[NUM_CHECKERS];
Checker PLAYER2_CHECKERS[NUM_CHECKERS];
Coordinate START_MOVES[NUM_CHECKERS * 8];
Coordinate END_MOVES[NUM_CHECKERS * 8];
Coordinate START_JUMPS[NUM_CHECKERS * 8];
Coordinate END_JUMPS[NUM_CHECKERS * 8];
int NUMBER_OF_MOVES;
int NUMBER_OF_JUMPS;
int GAME_MODE;
bool JUMPED = false;

int main(int argc, const char * argv[]) {

    make_coordinates();
    make_board();
    int selection = 0;
    int winner = 0;
    while (winner != -1) {
        TURN = 1;
        clear_board();
        display_start_menu();
        selection = get_start_menu_selection();
        if (selection == 1) {
            GAME_MODE = 1;
            place_player1_checkers(&PLAYER1);
            place_player2_checkers(&PLAYER2);
            winner = play_game(&PLAYER1, &PLAYER2, JUMPED);
        } else if (selection == 2) {
            GAME_MODE = 2;
            place_player1_checkers(&PLAYER1);
            place_player2_checkers(&COMPUTER_PLAYER);
            winner = play_game(&PLAYER1, &COMPUTER_PLAYER, JUMPED);
        } else if (selection == 3) {
            string file_name;
            cout << "Enter the file to load: ";
            cin >> file_name;
            bool did_load = false;
            did_load = load_game(file_name);
            if (did_load == false) {
                cout << "Couldn't load " << file_name << endl;
                winner = -3;
            } else {
                winner = play_game(PLAYER1_CHECKERS[0].get_player_ptr(), PLAYER2_CHECKERS[0].get_player_ptr(), JUMPED);
            }

        } else if (selection == 4) {
            return 0;
        }

        if (winner == -1) {
            return 0;
        } else if (winner == -3) {

        } else {
            cout << "Player " << winner << " Won!\n";
        }
    }
}

void make_coordinates() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            COORDINATES[x][y].set_x(x);
            COORDINATES[x][y].set_y(y);
        }
    }
}

void make_board() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            BOARD[x][y].set_coordinate_ptr(&COORDINATES[x][y]);
            if (y > 0 && y < BOARD_HEIGHT - 1 && x > 0 && x < BOARD_WIDTH - 1) {
                BOARD[x][y].set_up_ptr(&BOARD[x][y + 1]);
                BOARD[x][y].set_down_ptr(&BOARD[x][y - 1]);
                BOARD[x][y].set_right_ptr(&BOARD[x + 1][y]);
                BOARD[x][y].set_left_ptr(&BOARD[x - 1][y]);
                BOARD[x][y].set_up_right_ptr(&BOARD[x + 1][y + 1]);
                BOARD[x][y].set_up_left_ptr(&BOARD[x - 1][y + 1]);
                BOARD[x][y].set_down_left_ptr(&BOARD[x - 1][y - 1]);
                BOARD[x][y].set_down_right_ptr(&BOARD[x + 1][y - 1]);
            } else if (y < BOARD_HEIGHT - 1 && x > 0 && x < BOARD_WIDTH - 1) {
                BOARD[x][y].set_up_ptr(&BOARD[x][y + 1]);
                BOARD[x][y].set_right_ptr(&BOARD[x + 1][y]);
                BOARD[x][y].set_left_ptr(&BOARD[x - 1][y]);
                BOARD[x][y].set_up_right_ptr(&BOARD[x + 1][y + 1]);
                BOARD[x][y].set_up_left_ptr(&BOARD[x - 1][y + 1]);
            } else if (y > 0 && x > 0 && x < BOARD_WIDTH - 1) {
                BOARD[x][y].set_down_ptr(&BOARD[x][y - 1]);
                BOARD[x][y].set_right_ptr(&BOARD[x + 1][y]);
                BOARD[x][y].set_left_ptr(&BOARD[x - 1][y]);
                BOARD[x][y].set_down_left_ptr(&BOARD[x - 1][y - 1]);
                BOARD[x][y].set_down_right_ptr(&BOARD[x + 1][y - 1]);
            } else if (y > 0 && y < BOARD_HEIGHT - 1 && x < BOARD_WIDTH - 1) {
                BOARD[x][y].set_up_ptr(&BOARD[x][y + 1]);
                BOARD[x][y].set_down_ptr(&BOARD[x][y - 1]);
                BOARD[x][y].set_right_ptr(&BOARD[x + 1][y]);
                BOARD[x][y].set_up_right_ptr(&BOARD[x + 1][y + 1]);
                BOARD[x][y].set_down_right_ptr(&BOARD[x + 1][y - 1]);
            } else if (y > 0 && y < BOARD_HEIGHT - 1 && x > 0) {
                BOARD[x][y].set_up_ptr(&BOARD[x][y + 1]);
                BOARD[x][y].set_down_ptr(&BOARD[x][y - 1]);
                BOARD[x][y].set_left_ptr(&BOARD[x - 1][y]);
                BOARD[x][y].set_up_left_ptr(&BOARD[x - 1][y + 1]);
                BOARD[x][y].set_down_left_ptr(&BOARD[x - 1][y - 1]);
            } else if (y < BOARD_HEIGHT - 1 && x < BOARD_WIDTH - 1) {
                BOARD[x][y].set_up_ptr(&BOARD[x][y + 1]);
                BOARD[x][y].set_right_ptr(&BOARD[x + 1][y]);
                BOARD[x][y].set_up_right_ptr(&BOARD[x + 1][y + 1]);
            } else if (y < BOARD_HEIGHT - 1 && x > 0) {
                BOARD[x][y].set_up_ptr(&BOARD[x][y + 1]);
                BOARD[x][y].set_left_ptr(&BOARD[x - 1][y]);
                BOARD[x][y].set_up_left_ptr(&BOARD[x - 1][y + 1]);
            } else if (y > 0 && x < BOARD_WIDTH - 1) {
                BOARD[x][y].set_down_ptr(&BOARD[x][y - 1]);
                BOARD[x][y].set_right_ptr(&BOARD[x + 1][y]);
                BOARD[x][y].set_down_right_ptr(&BOARD[x + 1][y - 1]);
            } else if (y > 0 && x > 0) {
                BOARD[x][y].set_down_ptr(&BOARD[x][y - 1]);
                BOARD[x][y].set_left_ptr(&BOARD[x - 1][y]);
                BOARD[x][y].set_down_left_ptr(&BOARD[x - 1][y - 1]);
            }
        }
    }
}

void place_player1_checkers(Player *player_ptr) {
    int i = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if ((x + y) % 2 == 0) {
                PLAYER1_CHECKERS[i].set_player_ptr(player_ptr);
                BOARD[x][y].set_piece_ptr(&PLAYER1_CHECKERS[i++]);
            }
        }
    }
}

void place_player2_checkers(Player *player_ptr) {
    int i = 0;
    for (int y = 5; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if ((x + y) % 2 == 0) {
                PLAYER2_CHECKERS[i].set_player_ptr(player_ptr);
                BOARD[x][y].set_piece_ptr(&PLAYER2_CHECKERS[i++]);
            }
        }
    }
}

void display_start_menu() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
            << "Welcome to the game of Checkers\n"
            << "1. Play Opponent\n"
            << "2. Play Computer\n"
            << "3. Load Game\n"
            << "4. Exit\n";
}

int get_start_menu_selection() {
    char tmp;
    int n = 0;
    cout << "Enter a number (i.e. 1, 2, 3 or 4): ";
    cin >> tmp;
    if (isdigit(tmp)) {
        n = tmp - 48;
    }
    while (n < 1 || n > 4) {
        cout << "Invalid number!\n";
        cout << "Enter a number (i.e. 1, 2, 3 or 4): ";
        cin >> tmp;
        if (isdigit(tmp)) {
            n = tmp - 48;
        }
    }
    return n;
}

int play_game(Player * player1_ptr, Player * player2_ptr, bool j) {
    int winner = is_there_a_winner();
    int selection = -1;
    bool jumped = j;
    Square *square_ptr = Square::get_null_square_ptr();
    Coordinate start;
    Coordinate end;
    Player * player_ptr;
    while (winner == 0) {
        if (TURN == 1) {
            player_ptr = player1_ptr;
        } else {
            player_ptr = player2_ptr;
        }

        if (jumped) {
            get_jumps(square_ptr, player_ptr);
            NUMBER_OF_MOVES = 0;
            if (NUMBER_OF_JUMPS == 0) {
                if (TURN == 1) {
                    TURN = 2;
                } else {
                    TURN = 1;
                }
                jumped = false;
                continue;
            }
        } else {
            update_moves_and_jumps(player1_ptr, player2_ptr);
        }
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        display_plays();
        if (NUMBER_OF_MOVES == 0 && NUMBER_OF_JUMPS == 0) {
            if (TURN == 1) {
                return 2;
            } else {
                return 1;
            }
        }
        selection = player_ptr->get_move(BOARD, START_MOVES, START_JUMPS, NUMBER_OF_MOVES, NUMBER_OF_JUMPS);
        while (jumped == true && selection == -2) {
            cout << "Unable to save while in-between jumps!\n";
            selection = player_ptr->get_move(BOARD, START_MOVES, START_JUMPS, NUMBER_OF_MOVES, NUMBER_OF_JUMPS);
        }
        if (selection == -1) {
            return -1; // quit game
        } else if (selection == -2) {

            string file_name;
            cout << "Enter file name of game: ";
            cin >> file_name;
            string tmp_name = "tmp.checker";
            save_game(tmp_name, GAME_MODE, jumped);
            bool did_save = false;
            did_save = save_game(file_name, GAME_MODE, jumped);
            if (did_save == true) {
                if (GAME_MODE == 1) {
                    load_game(file_name);
                } else {
                    load_game(file_name);
                }
            } else {
                if (GAME_MODE == 1) {
                    load_game(tmp_name);
                } else {
                    load_game(tmp_name);
                }

            }
        } else if (selection == -3) {
            return -3; // main menu
        } else {
            if (NUMBER_OF_JUMPS > 0) {
                start = START_JUMPS[selection];
                end = END_JUMPS[selection];
            } else {
                start = START_MOVES[selection];
                end = END_MOVES[selection];
            }
            int x = start.get_x();
            int y = start.get_y();
            if (NUMBER_OF_JUMPS > 0) {
                square_ptr = BOARD[x][y].jump_piece(&end, player_ptr);
                jumped = true;
            } else {
                BOARD[x][y].move_piece(&end, player_ptr);
                jumped = false;
                if (TURN == 1) {
                    TURN = 2;
                } else {
                    TURN = 1;
                }
            }
            winner = is_there_a_winner();
        }
    }
    winner = is_there_a_winner();
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    display_plays();
    return winner;
}

int is_there_a_winner() {
    bool is_player1_alive = false;
    bool is_player2_alive = false;
    int player_number = 0;
    Piece* p = Piece::get_null_piece_ptr();
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            p = BOARD[x][y].get_piece_ptr();
            if (p == Piece::get_null_piece_ptr()) {
                continue;
            } else {
                player_number = p->get_player_ptr()->get_number();
                if (player_number == 1) {
                    is_player1_alive = true;
                } else {
                    is_player2_alive = true;
                }
            }
        }
    }
    if (is_player1_alive == false & is_player2_alive == false) {
        return -1; // Error
    } else if (is_player1_alive == true & is_player2_alive == false) {
        return 1; // Player 1 won
    } else if (is_player1_alive == false & is_player2_alive == true) {
        return 2; // Player 2 won
    } else {
        return 0; // Game is not over
    }
}

string get_board_string() {
    string board_string = "";
    string tmp = "";
    Piece *p = Piece::get_null_piece_ptr();
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
        tmp = std::to_string(y);
        board_string.append(tmp);
        for (int x = 0; x < BOARD_WIDTH; x++) {
            tmp = "|";
            board_string.append(tmp);
            p = BOARD[x][y].get_piece_ptr();
            tmp = p->get_symbol(&COORDINATES[x][y]);
            board_string.append(tmp);
        }
        tmp = "|\n";
        board_string.append(tmp);
    }
    tmp = " |0|1|2|3|4|5|6|7|\n";
    board_string.append(tmp);
    return board_string;
}

int get_player_moves(Player *player_ptr) {
    int stored_moves_index = 0;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (BOARD[x][y].has_piece(&COORDINATES[x][y], player_ptr) == false) {
                continue;
            }
            Piece *piece_ptr = BOARD[x][y].get_piece_ptr();
            Coordinate *moves_ptr = piece_ptr->get_moves();
            int number_of_moves = piece_ptr->get_number_of_moves();
            for (int i = 0; i < number_of_moves; i++) {
                Coordinate coordinate = COORDINATES[x][y].add(moves_ptr + i);
                if (BOARD[x][y].get_square(&coordinate) == Square::get_null_square_ptr()) {
                    continue;
                } else if (BOARD[x][y].piece_inbetween(&coordinate)) {
                    continue;
                } else {
                    START_MOVES[stored_moves_index] = COORDINATES[x][y];
                    END_MOVES[stored_moves_index++] = coordinate;
                }
            }
        }
    }
    NUMBER_OF_MOVES = stored_moves_index;
    return stored_moves_index;
}

void display_moves(int n) {
    for (int i = 0; i < n; i++) {
        cout << i << ". start (" << START_MOVES[i].get_x() << "," << START_MOVES[i].get_y() << ")";
        cout << " end (" << END_MOVES[i].get_x() << "," << END_MOVES[i].get_y() << ")\n";
    }
}

int get_player_jumps(Player *player_ptr) {
    int stored_jumps_index = 0;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (BOARD[x][y].has_piece(&COORDINATES[x][y], player_ptr) == false) {
                continue;
            }
            Piece *piece_ptr = BOARD[x][y].get_piece_ptr();
            Coordinate *jumps_ptr = piece_ptr->get_attacks();
            int number_of_jumps = piece_ptr->get_number_of_attacks();
            for (int i = 0; i < number_of_jumps; i++) {
                Coordinate coordinate = COORDINATES[x][y].add(jumps_ptr + i);
                int jx = coordinate.get_x();
                int jy = coordinate.get_y();
                if (BOARD[x][y].get_square(&coordinate) == Square::get_null_square_ptr()) {
                    continue;
                } else if (BOARD[x][y].opponent_piece_inbetween(&coordinate, player_ptr) == false) {
                    continue;
                } else if (BOARD[x][y].my_piece_inbetween(&coordinate, player_ptr) == true) {
                    continue;
                } else if (BOARD[jx][jy].get_piece_ptr() != Piece::get_null_piece_ptr()) {
                    continue;
                } else {
                    START_JUMPS[stored_jumps_index] = COORDINATES[x][y];
                    END_JUMPS[stored_jumps_index++] = coordinate;
                }
            }
        }
    }
    NUMBER_OF_JUMPS = stored_jumps_index;
    return stored_jumps_index;
}

void display_jumps(int n, int start) {
    for (int i = 0; i < n; i++) {
        cout << i + start << ". start (" << START_JUMPS[i].get_x() << "," << START_JUMPS[i].get_y() << ")";
        cout << " end (" << END_JUMPS[i].get_x() << "," << END_JUMPS[i].get_y() << ")\n";
    }
}

bool load_game(string file_name) {
    Player *player1_ptr = &PLAYER1;
    Player *player2_ptr = &PLAYER2;
    fstream f;
    f.open(file_name, ios_base::in);
    bool did_open = false;
    did_open = f.is_open();
    if (did_open == false)
        return did_open;
    else {
        char c;
        int x = 0;
        int y = 7;
        int player_one_index = 0;
        int player_two_index = 0;
        while (f.get(c)) {
            if (c == '|') {
                continue;
            } else if (isdigit(c)) {
                continue;
            } else if (c == 'x') {
                PLAYER1_CHECKERS[player_one_index].set_is_king(false);
                PLAYER1_CHECKERS[player_one_index].set_player_ptr(player1_ptr);
                BOARD[x][y].set_piece_ptr(&PLAYER1_CHECKERS[player_one_index++]);
                x++;
            } else if (c == 'X') {
                PLAYER1_CHECKERS[player_one_index].set_player_ptr(player1_ptr);
                PLAYER1_CHECKERS[player_one_index].set_is_king(true);
                BOARD[x][y].set_piece_ptr(&PLAYER1_CHECKERS[player_one_index++]);
                x++;
            } else if (c == 'o') {
                PLAYER2_CHECKERS[player_two_index].set_is_king(false);
                PLAYER2_CHECKERS[player_two_index].set_player_ptr(player2_ptr);
                BOARD[x][y].set_piece_ptr(&PLAYER2_CHECKERS[player_two_index++]);
                x++;
            } else if (c == 'O') {
                PLAYER2_CHECKERS[player_two_index].set_player_ptr(player2_ptr);
                PLAYER2_CHECKERS[player_two_index].set_is_king(true);
                BOARD[x][y].set_piece_ptr(&PLAYER2_CHECKERS[player_two_index++]);
                x++;
            } else if (c == ' ') {
                if (y > 0 && x > 0) {
                    BOARD[x][y].set_piece_ptr(Piece::get_null_piece_ptr());
                }
                x++;
            } else if (c == '\n') {
                y--;
                x = 0;
            } else if (c == 'A') {
                TURN = 1;
            } else if (c == 'B') {
                TURN = 2;
            } else if (c == 'P') {
                player2_ptr = &PLAYER2;
            } else if (c == 'C') {
                player2_ptr = &COMPUTER_PLAYER;
            } else if (c == 'N') {
                JUMPED = false;
            } else if (c == 'J') {
                JUMPED = true;
            } else {
                cout << c;
                return false;
            }
        }
    }
    f.close();
    return did_open;
}

bool save_game(string file_name, int game_mode, bool jumped) {
    fstream f;
    f.open(file_name, ios_base::out);
    bool did_open = f.is_open();
    if (did_open == false) {
        return false;
    } else {
        string s = get_board_string();
        if (TURN == 1) {
            s[s.length() - 1] = 'A';
        } else {
            s[s.length() - 1] = 'B';
        }
        string tmp;
        if (game_mode == 1) {
            tmp = 'P';
            tmp += s;
        } else {
            tmp = 'C';
            tmp += s;
        }
        s = tmp;
        if (jumped == true) {
            tmp = 'J';
            tmp += s;
        } else {
            tmp = 'N';
            tmp += s;
        }
        s = tmp;
        int board_length = static_cast<int> (s.length());
        char char_board[board_length + 1];
        char * cs = char_board;
        for (int i = 0; i < board_length; i++) {
            char_board[i] = s[i];
        }
        f.write(cs, s.length());
    }
    f.close();
    return did_open;
}

void update_moves_and_jumps(Player * player1_ptr, Player * player2_ptr) {
    Player *p = nullptr;
    if (TURN == 1) {
        p = player1_ptr;
    } else {
        p = player2_ptr;
    }
    get_player_jumps(p);
    get_player_moves(p);
}

void display_plays() {
    cout << "Player " << TURN << " Turn\n";
    cout << get_board_string();
    if (NUMBER_OF_JUMPS > 0) {
        cout << "Jumps\n";
        display_jumps(NUMBER_OF_JUMPS);

    } else {
        cout << "Moves\n";
        display_moves(NUMBER_OF_MOVES);
    }
}

int get_jumps(Square *square_ptr, Player * player_ptr) {
    int stored_jumps_index = 0;
    Coordinate* coordinate_ptr = square_ptr->get_coordinate_ptr();

    if (square_ptr->has_piece(coordinate_ptr, player_ptr) == false) {
        return 0;
    }
    Piece *piece_ptr = square_ptr->get_piece_ptr();
    Coordinate *jumps_ptr = piece_ptr->get_attacks();
    int number_of_jumps = piece_ptr->get_number_of_attacks();
    for (int i = 0; i < number_of_jumps; i++) {
        Coordinate coordinate = coordinate_ptr->add(jumps_ptr + i);
        int x = coordinate.get_x();
        int y = coordinate.get_y();
        if (square_ptr->get_square(&coordinate) == Square::get_null_square_ptr()) {
            continue;
        } else if (square_ptr->opponent_piece_inbetween(&coordinate, player_ptr) == false) {
            continue;
        } else if (square_ptr->my_piece_inbetween(&coordinate, player_ptr) == true) {
            continue;
        } else if ((BOARD[x][y].get_piece_ptr() == Piece::get_null_piece_ptr()) == false) {
            continue;
        } else {
            START_JUMPS[stored_jumps_index] = *coordinate_ptr;
            END_JUMPS[stored_jumps_index++] = COORDINATES[x][y];
        }
    }
    NUMBER_OF_JUMPS = stored_jumps_index;
    return stored_jumps_index;
}

void clear_board() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            BOARD[x][y].set_piece_ptr(Piece::get_null_piece_ptr());
        }
    }
    for (int i = 0; i < NUM_CHECKERS; i++) {
        PLAYER1_CHECKERS[i].set_is_king(false);
        PLAYER2_CHECKERS[i].set_is_king(false);
    }
}
