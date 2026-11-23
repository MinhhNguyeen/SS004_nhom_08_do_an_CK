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

// ======================== PHAN CUA SV4 ========================

// 7 dang block co ban trong mang blocks.
const int baseBlocks[7] = {0, 2, 11, 12, 13, 14, 15};

// Luu hinh dang goc de block moi khong bi giu lai huong xoay cua block truoc.
char originalBlocks[16][4][4];

// Kiem tra block sau khi xoay co nam trong ban choi va khong cham block co dinh.
bool canPlaceBlock(const char shape[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == ' ')
                continue;

            int boardX = x + j;
            int boardY = y + i;

            // Khong cho block cham vien trai, phai, tren hoac day.
            if (boardX <= 0 || boardX >= W - 1 ||
                boardY <= 0 || boardY >= H - 1) {
                return false;
            }

            // O da co block co dinh.
            if (board[boardY][boardX] != ' ')
                return false;
        }
    }
    return true;
}

// Xoay block 90 do theo chieu kim dong ho.
// Chi cap nhat blocks[b] khi toan bo vi tri moi hop le.
bool rotateBlock() {
    char rotated[4][4] = {};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotated[j][3 - i] = blocks[b][i][j];
        }
    }

    if (!canPlaceBlock(rotated))
        return false;

    memcpy(blocks[b], rotated, sizeof(rotated));
    return true;
}

// Kiem tra vi tri xuat hien cua block moi.
bool canSpawnBlock(int blockIndex) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[blockIndex][i][j] == ' ')
                continue;

            int boardX = x + j;
            int boardY = y + i;

            if (boardX <= 0 || boardX >= W - 1 ||
                boardY <= 0 || boardY >= H - 1) {
                return false;
            }

            if (board[boardY][boardX] != ' ')
                return false;
        }
    }
    return true;
}

// Tao block moi. Tra ve false neu khong con vi tri de xuat hien.
bool spawnBlock() {
    x = 5;
    y = 1;
    b = baseBlocks[rand() % 7];

    memcpy(blocks[b], originalBlocks[b], sizeof(blocks[b]));
    return canSpawnBlock(b);
}

// ====================== HET PHAN CUA SV4 ======================

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

    // SV4: luu hinh dang goc cua cac block.
    memcpy(originalBlocks, blocks, sizeof(blocks));

    initBoard();

    // SV4: ket thuc game neu block dau tien khong the xuat hien.
    if (!spawnBlock()) {
        cout << "GAME OVER: Khong the tao block moi.\n";
        return 0;
    }

    while (1) {
        boardDelBlock();

        if (kbhit()) {
            char c = getch();

            if ((c == 'a' || c == 'A') && canMove(-1, 0)) x--;
            if ((c == 'd' || c == 'D') && canMove(1, 0)) x++;
            if ((c == 'x' || c == 'X') && canMove(0, 1)) y++;

            // SV4: phim W xoay block 90 do theo chieu kim dong ho.
            if (c == 'w' || c == 'W') rotateBlock();

            if (c == 'q' || c == 'Q') break;
        }

        if (canMove(0, 1)) {
            y++;
        } else {
            block2Board();
            removeLine();

            // SV4: tao block tiep theo va kiem tra Game Over.
            if (!spawnBlock()) {
                draw();
                cout << "\nGAME OVER: Khong con vi tri xuat hien block.\n";
                break;
            }
        }

        block2Board();
        draw();
        _sleep(500);
    }

    return 0;
}
