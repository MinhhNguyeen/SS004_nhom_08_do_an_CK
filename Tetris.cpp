#include <iostream>
#include <conio.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

#define H 20
#define W 15

char board[H][W] = {};

int x, y, b;

char cur[4][4];

int baseBlocks[7] = {0, 2, 11, 12, 13, 14, 15};

char blocks[][4][4] = {
    {{' ','I',' ',' '},
     {' ','I',' ',' '},
     {' ','I',' ',' '},
     {' ','I',' ',' '}},

    {{' ','I',' ',' '},
     {' ','I',' ',' '},
     {' ','I',' ',' '},
     {' ','I',' ',' '}},

    {{' ',' ',' ',' '},
     {' ','O','O',' '},
     {' ','O','O',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {' ','O','O',' '},
     {' ','O','O',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {' ','O','O',' '},
     {' ','O','O',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {' ','O','O',' '},
     {' ','O','O',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {' ','O','O',' '},
     {' ','O','O',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {' ','O','O',' '},
     {' ','O','O',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {' ','O','O',' '},
     {' ','O','O',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {'I','I','I','I'},
     {' ',' ',' ',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {' ','O','O',' '},
     {' ','O','O',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {' ','T',' ',' '},
     {'T','T','T',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {' ','S','S',' '},
     {'S','S',' ',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {'Z','Z',' ',' '},
     {' ','Z','Z',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {'J',' ',' ',' '},
     {'J','J','J',' '},
     {' ',' ',' ',' '}},

    {{' ',' ',' ',' '},
     {' ',' ','L',' '},
     {'L','L','L',' '},
     {' ',' ',' ',' '}}
};

// Kiem tra kha nang di chuyen
bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cur[i][j] != ' ') {
                int xt = x + j + dx;
                int yt = y + i + dy;

                if (xt < 1 || xt >= W - 1 ||
                    yt < 0 || yt >= H - 1) {
                    return false;
                }

                // Hang 0 la vung sinh khoi, khong kiem tra nhu o co dinh
                if (yt > 0 && board[yt][xt] != ' ') {
                    return false;
                }
            }
        }
    }

    return true;
}

// Dua khoi dang roi vao bang
void block2Board() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cur[i][j] != ' ' && y + i > 0) {
                board[y + i][x + j] = cur[i][j];
            }
        }
    }
}

// Xoa khoi dang roi khoi bang
void boardDelBlock() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cur[i][j] != ' ' && y + i > 0) {
                board[y + i][x + j] = ' ';
            }
        }
    }
}

// Xoay khoi 90 do theo chieu kim dong ho
void rotateBlock() {
    char t[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            t[j][3 - i] = cur[i][j];
        }
    }

    // Kiem tra vi tri sau khi xoay
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (t[i][j] != ' ') {
                int xt = x + j;
                int yt = y + i;

                if (xt < 1 || xt >= W - 1 ||
                    yt < 0 || yt >= H - 1) {
                    return;
                }

                if (yt > 0 && board[yt][xt] != ' ') {
                    return;
                }
            }
        }
    }

    // Chi cap nhat khi vi tri xoay hop le
    memcpy(cur, t, sizeof(cur));
}

// Kiem tra khoi moi co bi trung khoi da co hay khong
bool spawnBlocked() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cur[i][j] != ' ' && y + i > 0) {
                if (board[y + i][x + j] != ' ') {
                    return true;
                }
            }
        }
    }

    return false;
}

// Kiem tra khoi co con nam tren vung hien thi khi bi khoa khong
bool pieceAboveTop() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cur[i][j] != ' ' && y + i <= 0) {
                return true;
            }
        }
    }

    return false;
}

// Khoi tao bang
void initBoard() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (i == 0 || i == H - 1 ||
                j == 0 || j == W - 1) {
                board[i][j] = '#';
            }
            else {
                board[i][j] = ' ';
            }
        }
    }
}

// Hien thi bang
void draw() {
    system("cls");

    for (int i = 0; i < H; i++, cout << endl) {
        for (int j = 0; j < W; j++) {
            cout << board[i][j];
        }
    }
}

// Xoa cac hang day
void removeLine() {
    int i, j;

    for (i = H - 2; i > 0; i--) {
        for (j = 1; j < W - 1; j++) {
            if (board[i][j] == ' ') {
                break;
            }
        }

        if (j == W - 1) {
            for (int ii = i; ii > 0; ii--) {
                for (int jj = 0; jj < W; jj++) {
                    board[ii][jj] = board[ii - 1][jj];
                }
            }

            for (int jj = 1; jj < W - 1; jj++) {
                board[1][jj] = ' ';
            }

            i++;
            draw();
            Sleep(200);
        }
    }
}

int main() {
    srand(time(0));

    initBoard();

    // Khoi tao khoi dau tien
    x = 5;
    y = 0;
    b = baseBlocks[rand() % 7];

    memcpy(cur, blocks[b], sizeof(cur));

    while (true) {
        boardDelBlock();

        if (kbhit()) {
            char c = getch();

            if ((c == 'a' || c == 'A') && canMove(-1, 0)) {
                x--;
            }

            else if ((c == 'd' || c == 'D') && canMove(1, 0)) {
                x++;
            }

            else if ((c == 'x' || c == 'X') && canMove(0, 1)) {
                y++;
            }

            else if (c == 'w' || c == 'W') {
                rotateBlock();
            }

            else if (c == 'q' || c == 'Q') {
                break;
            }
        }

        // Khoi tu dong roi xuong
        if (canMove(0, 1)) {
            y++;
        }

        else {
            // Neu khoi van nam ngoai vung hien thi thi Game Over
            if (pieceAboveTop()) {
                block2Board();
                draw();
                cout << "GAME OVER!" << endl;
                break;
            }

            // Co dinh khoi vao bang
            block2Board();

            // Xoa hang day
            removeLine();

            // Sinh khoi moi
            x = 5;
            y = 0;
            b = baseBlocks[rand() % 7];

            memcpy(cur, blocks[b], sizeof(cur));

            // Kiem tra Game Over
            if (spawnBlocked()) {
                draw();
                cout << "GAME OVER!" << endl;
                break;
            }
        }

        block2Board();
        draw();

        Sleep(500);
    }

    return 0;
}
