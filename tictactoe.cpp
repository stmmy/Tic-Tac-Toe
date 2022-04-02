#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class tictactoe {
    private:
        vector<vector<char>> gm = {{'.','.','.'},{'.','.','.'},{'.','.','.'}};
        vector<int> not_chosen;
        bool gameover = false;
    public:
        void game(string move) {
            if (gameover == true) {
                return;
            }
            find_not_chosen();
            
            //tests if input is valid
            if (test_if_valid_input(move) == false) {
                while(test_if_valid_input(move) != false) {
                    cout << "Invalid - choose again:  ";
                    cin >> move;
                }
            }

            //update player move
            if (move == "tl") {gm[0][0] = 'X';}
            else if (move == "tm") {gm[0][1] = 'X';}
            else if (move == "tr") {gm[0][2] = 'X';}
            else if (move == "ml") {gm[1][0] = 'X';}
            else if (move == "mm") {gm[1][1] = 'X';}
            else if (move == "mr") {gm[1][2] = 'X';}
            else if (move == "bl") {gm[2][0] = 'X';}
            else if (move == "bm") {gm[2][1] = 'X';}
            else if (move == "br") {gm[2][2] = 'X';}
        
            //find tiles not chosen again
            find_not_chosen();

            //test to see if player won
            int tmp = test_game_over();
            if (tmp == 1) {
                print();
                cout << "Crosses has won the game!" << endl;
                gameover = true;
                return;
            }
            else if (tmp == 0 && not_chosen.size() == 0) {
                cout << "Draw!" << endl;
                gameover = true;
                return;
            }
            
            //make choice for O's based on what tiles are available
            int num;
            srand(time(NULL));
            num = rand()%not_chosen.size();
            if (not_chosen[num] < 3) {gm[0][not_chosen[num]] = 'O';}
            else if (not_chosen[num] >= 3 && not_chosen[num] < 6) {gm[1][not_chosen[num]-3] = 'O';}
            else if (not_chosen[num] >= 6) {gm[2][not_chosen[num]-6] = 'O';}
            not_chosen.erase(not_chosen.begin()+num);

            //test to see if AI won the game
            int tmp2 = test_game_over();
            if (tmp2 == 2) {
                print();
                cout << "Circles has won the game!" << endl;
                
                gameover = true;
                return;
            }
            else if (tmp2 == 0 && not_chosen.size() == 0) {
                print();
                cout << "Draw!" << endl;
                gameover = true;
                return;
            }

            //print, get next move, then recursive call
            print();
            printf("Enter move:  ");
            cin >> move;
            game(move);
        }

        bool test_if_valid_input(string move) {
            int test_tile;
            int count;
            if (move == "tl") {test_tile = 0;}
            else if (move == "tm") {test_tile = 1;}
            else if (move == "tr") {test_tile = 2;}
            else if (move == "ml") {test_tile = 3;}
            else if (move == "mm") {test_tile = 4;}
            else if (move == "mr") {test_tile = 5;}
            else if (move == "bl") {test_tile = 6;}
            else if (move == "bm") {test_tile = 7;}
            else if (move == "br") {test_tile = 8;}
            for (int i=0; i != not_chosen.size(); i++) {
                if (not_chosen[i] == test_tile) {
                    return true;
                }
            }
            return false;
        }

        void find_not_chosen() {
            not_chosen = {};
            for (int i=0; i != 3; i++) {
                for (int j=0; j != 3; j++) {
                    if (gm[i][j] == '.') {
                        if (i==0) {not_chosen.push_back(j);}
                        else if (i==1) {not_chosen.push_back(j+3);}
                        else if (i==2) {not_chosen.push_back(j+6);}
                    }
                }
            }
        }

        int test_game_over() {
            int win_num =0;
            
            //check column win;
            for (int i=0; i != 3; i++) {
                if (gm[0][i] != '.') {
                    win_num = 0;
                    for (int j=0; j != 3; j++) {
                        if (gm[j][i] == gm[0][i]) {
                            win_num++;
                        }
                    }
                    if (win_num == 3) {
                        if (gm[0][i] == 'X') {return 1;}
                        else {return 2;}
                    }
                }
            }
            
            //check column win
            for (int i=0; i != 3; i++) {
                if (gm[i][0] != '.') {
                    win_num = 0;
                    for (int j=0; j != 3; j++) {
                        if (gm[i][j] == gm[i][0]) {
                            win_num++;
                        }
                    }
                    if(win_num == 3) {
                        if (gm[i][0] == 'X') {return 1;}
                        else {return 2;}
                    }
                }
            }

            //check diag & reverse diag win
            if (gm[0][0] == 'X' || gm[0][0] == 'O'){
                if (gm[0][0] == gm[1][1] && gm[0][0] == gm[2][2]) {
                    if (gm[0][0] == 'X') {return 1;}
                    else {return 1;}
                }
            }
            if (gm[0][2] == 'X' || gm[0][2] == 'O'){
                if (gm[0][2] == gm[1][1] && gm[0][2] == gm[2][0]) {
                    if (gm[0][2] == 'X') {return 1;}
                    else {return 2;}
                }
            }
            
            return 0;
        }
        
        void print() {
            printf(" %c | %c | %c \n --+---+--- \n %c | %c | %c \n --+---+--- \n %c | %c | %c \n",
            gm[0][0],gm[0][1],gm[0][2], gm[1][0],gm[1][1],gm[1][2], gm[2][0],gm[2][1],gm[2][2]);
        }
};


int main() {
    int num_players;
    string input;
    
    printf("Controls: \n\n");
    printf("tr - top left, tm - top middle, tr - top right \n");
    printf("ml - middle left, mm - middle middle, mr - middle right \n");
    printf("bl - bottom left, bm - bottom middle, br - bottom right \n\n");

    printf("Enter first move:  ");
    cin >> input;
    tictactoe main_game;
    main_game.game(input);
}
