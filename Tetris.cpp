#include <iostream>
#include <conio.h>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#define H 20
#define W 15

char board[H][W] = {};

int x, y, b;

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

// ======================= PHAN BO SUNG CUA SV4 =======================

// Cac vi tri dai dien cho 7 dang block khac nhau trong mang blocks.
const int baseBlocks[7] = {0, 2, 11, 12, 13, 14, 15};

// Luu hinh dang goc de moi block moi khong bi giu lai huong xoay truoc do.
char blocksOrig[16][4][4];

bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ') {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W - 1 || yt >= H - 1) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}

void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
                board[y + i][x + j] = blocks[b][i][j];
}

void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
                board[y + i][x + j] = ' ';
}

// Khoi phuc hinh dang ban dau cua block duoc chon.
void resetBlock(int id) {
    memcpy(blocks[id], blocksOrig[id], sizeof(blocks[id]));
}

// Kiem tra block sau khi xoay co nam trong bien va khong cham block co dinh.
bool canPlaceRotatedBlock(const char rotated[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rotated[i][j] == ' ')
                continue;

            int xt = x + j;
            int yt = y + i;

            if (xt < 1 || xt >= W - 1 || yt < 0 || yt >= H - 1)
                return false;

            if (board[yt][xt] != ' ')
                return false;
        }
    }
    return true;
}

// Xoay block 90 do theo chieu kim dong ho.
// Neu vi tri sau xoay khong hop le, giu nguyen block hien tai.
bool rotateBlock() {
    char rotated[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotated[j][3 - i] = blocks[b][i][j];
        }
    }

    if (!canPlaceRotatedBlock(rotated))
        return false;

    memcpy(blocks[b], rotated, sizeof(rotated));
    return true;
}

// Sinh ngau nhien mot trong 7 dang block co ban.
void spawnBlock() {
    x = 5;
    y = 0;
    b = baseBlocks[rand() % 7];
    resetBlock(b);
}

// ===================== KET THUC PHAN SV4 ============================

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (i == 0 || i == H - 1 || j == 0 || j == W - 1) board[i][j] = '#';
            else board[i][j] = ' ';
}

void draw() {
    system("cls");

    for (int i = 0; i < H; i++, cout << endl)
        for (int j = 0; j < W; j++) cout << board[i][j];

}

void removeLine() {
    int i, j;
    for (i = H - 2; i > 0; i--) {
        for (j = 0; j < W; j++)
            if (board[i][j] == ' ') break;
        if (j == W) {
            for (int ii = i; ii > 0; ii--)
                for (int jj = 0; jj < W; jj++)
                    board[ii][jj] = board[ii - 1][jj];
            i++;
            draw();
            _sleep(200);
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // SV4: Luu lai hinh dang goc truoc khi bat dau game.
    memcpy(blocksOrig, blocks, sizeof(blocks));

    initBoard();
    spawnBlock();

    while (1) {
        boardDelBlock();

        if (kbhit()) {
            char c = getch();

            if ((c == 'a' || c == 'A') && canMove(-1, 0)) x--;
            if ((c == 'd' || c == 'D') && canMove(1, 0)) x++;
            if ((c == 'x' || c == 'X') && canMove(0, 1)) y++;

            // SV4: W/w xoay block 90 do theo chieu kim dong ho.
            if (c == 'w' || c == 'W') rotateBlock();

            if (c == 'q' || c == 'Q') break;
        }

        if (canMove(0, 1)) y++;
        else {
            block2Board();
            removeLine();
            spawnBlock();
        }

        block2Board();
        draw();
        _sleep(500);
    }

    return 0;
}
