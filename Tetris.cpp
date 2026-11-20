#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cstring>   // SV4: memcpy

using namespace std;

#define H 20
#define W 15

char board[H][W] = {};

int x, y, b;
const int numPieceTypes = 7;

// 7 loai khoi co ban: I (hang 1 de an toan khi spawn o y = 0), O, T, S, Z, J, L
char blocks[numPieceTypes][4][4] = {
    { { ' ',' ',' ',' ' },
      { 'I','I','I','I' },
      { ' ',' ',' ',' ' },
      { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' },
      { ' ','O','O',' ' },
      { ' ','O','O',' ' },
      { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' },
      { ' ','T',' ',' ' },
      { 'T','T','T',' ' },
      { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' },
      { ' ','S','S',' ' },
      { 'S','S',' ',' ' },
      { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' },
      { 'Z','Z',' ',' ' },
      { ' ','Z','Z',' ' },
      { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' },
      { 'J',' ',' ',' ' },
      { 'J','J','J',' ' },
      { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' },
      { ' ',' ','L',' ' },
      { 'L','L','L',' ' },
      { ' ',' ',' ',' ' } }
};

// SV4: Ban sao goc de khoi phuc hinh dang ban dau sau khi khoi ha xuong
char blocksOrig[numPieceTypes][4][4];

bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ') {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W - 1 || yt < 0 || yt >= H - 1) return false;
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

// ================= PHAN XOAY & SINH KHOI CUA SV4 =================
void resetBlock(int id) {
    memcpy(blocks[id], blocksOrig[id], sizeof(blocks[id]));
}

bool canPlaceRotatedBlock(const char r[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (r[i][j] != ' ') {
                int xt = x + j;
                int yt = y + i;
                if (xt < 1 || xt >= W - 1 || yt < 0 || yt >= H - 1) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}

// Xoay 90 do thuan chieu kim dong ho.
// Neu vi tri xoay khong hop le thi giu nguyen khoi va tra ve false.
bool rotateBlock() {
    char rotated[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            rotated[i][j] = blocks[b][3 - j][i];

    if (!canPlaceRotatedBlock(rotated))
        return false;

    memcpy(blocks[b], rotated, sizeof(rotated));
    return true;
}

bool spawnBlock() {
    x = 5;
    y = 0;
    b = rand() % numPieceTypes;
    resetBlock(b);
    return canMove(0, 0);
}
// =================================================================

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (i == 0 || i == H - 1 || j == 0 || j == W - 1) board[i][j] = '#';
            else board[i][j] = ' ';
}

void draw() {
    system("cls");
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)
            cout << board[i][j];
        cout << '\n';
    }
    // SV4: Ghi ro phim xoay W/w trong huong dan
    cout << "\nA: Sang trai | D: Sang phai | X: Roi nhanh";
    cout << "\nW: Xoay theo chieu kim dong ho | Q: Thoat\n";
}

void removeLine() {
    for (int i = H - 2; i > 0; i--) {
        bool full = true;
        for (int j = 1; j < W - 1; j++) {
            if (board[i][j] == ' ') {
                full = false;
                break;
            }
        }
        if (full) {
            for (int ii = i; ii > 0; ii--)
                for (int jj = 1; jj < W - 1; jj++)
                    board[ii][jj] = board[ii - 1][jj];
            for (int jj = 1; jj < W - 1; jj++)
                board[1][jj] = ' ';
            i++;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    memcpy(blocksOrig, blocks, sizeof(blocks));

    initBoard();

    if (!spawnBlock()) {
        draw();
        cout << "\nGame Over!\n";
        return 0;
    }

    bool activeOnBoard = false;

    while (true) {
        if (activeOnBoard) {
            boardDelBlock();
            activeOnBoard = false;
        }

        if (_kbhit()) {
            char c = static_cast<char>(_getch());
            if ((c == 'a' || c == 'A') && canMove(-1, 0)) x--;
            else if ((c == 'd' || c == 'D') && canMove(1, 0)) x++;
            else if ((c == 'x' || c == 'X') && canMove(0, 1)) y++;
            else if (c == 'w' || c == 'W') rotateBlock();
            else if (c == 'q' || c == 'Q') break;
        }

        if (canMove(0, 1)) {
            y++;
        } else {
            block2Board();
            removeLine();

            if (!spawnBlock()) {
                draw();
                cout << "\nGame Over!\n";
                break;
            }
        }

        block2Board();
        activeOnBoard = true;
        draw();
        Sleep(500);
    }

    return 0;
}
