#pragma warning(disable : 4996)
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <cstring>

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;
char blocks[][4][4] = {
        { { ' ','I',' ',' ' },
         { ' ','I',' ',' ' },
         { ' ','I',' ',' ' },
         { ' ','I',' ',' ' } },
        { { ' ','I',' ',' ' },
         { ' ','I',' ',' ' },
         { ' ','I',' ',' ' },
         { ' ','I',' ',' ' } },
        { { ' ',' ',' ',' ' },
         { ' ','O','O',' ' },
         { ' ','O','O',' ' },
         { ' ',' ',' ',' ' } },
        { { ' ',' ',' ',' ' },
         { ' ','O','O',' ' },
         { ' ','O','O',' ' },
         { ' ',' ',' ',' ' } },
        { { ' ',' ',' ',' ' },
         { ' ','O','O',' ' },
         { ' ','O','O',' ' },
         { ' ',' ',' ',' ' } },
        { { ' ',' ',' ',' ' },
         { ' ','O','O',' ' },
         { ' ','O','O',' ' },
         { ' ',' ',' ',' ' } },
        { { ' ',' ',' ',' ' },
         { ' ','O','O',' ' },
         { ' ','O','O',' ' },
         { ' ',' ',' ',' ' } },
        { { ' ',' ',' ',' ' },
         { ' ','O','O',' ' },
         { ' ','O','O',' ' },
         { ' ',' ',' ',' ' } },
        { { ' ',' ',' ',' ' },
         { ' ','O','O',' ' },
         { ' ','O','O',' ' },
         { ' ',' ',' ',' ' } },
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
            if (i == H - 1 || j == 0 || j == W - 1) board[i][j] = '#';
            else board[i][j] = ' ';
}

// ================= PHẦN GIAO DIỆN CỦA SV3 =================
void setupConsole() {
    SetConsoleOutputCP(65001);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | 0x0004);

    // Ẩn con trỏ nhấp nháy để không bị vệt giật
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
    cout << "\033[?25l";

    system("cls");
}

void resetCursor() {
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw() {
    resetCursor();
    string frame = "";
    frame.reserve(1000);

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (i == H - 1 && j == 0)          frame += " \xE2\x96\x9D";             //  ▝ (góc dưới trái khít viền)
            else if (i == H - 1 && j == W - 1) frame += "\xE2\x96\x98 ";             // ▘  (góc dưới phải khít viền)
            else if (i == H - 1)               frame += "\xE2\x96\x80\xE2\x96\x80"; // ▀▀ (viền đáy nằm sát mép trên)
            else if (j == 0)                   frame += " \xE2\x96\x90";             //  ▐ (viền trái sát mép trong)
            else if (j == W - 1)               frame += "\xE2\x96\x8C ";             // ▌  (viền phải sát mép trong)
            else if (board[i][j] == ' ')       frame += "  ";
            else                               frame += "[]";
        }
        if (i < H - 1) frame += "\n";
    }
    cout << frame << flush;
}

int removeLine() {
    int cleared = 0;
    for (int i = H - 2; i > 0; i--) {
        bool full = true;
        for (int j = 1; j < W - 1; j++)
            if (board[i][j] == ' ') {
                full = false;
                break;
            }
        if (full) {
            for (int ii = i; ii > 0; ii--)
                for (int jj = 1; jj < W - 1; jj++)
                    board[ii][jj] = board[ii - 1][jj];
            for (int jj = 1; jj < W - 1; jj++)
                board[1][jj] = ' ';
            i++;
            cleared++;
        }
    }
    return cleared;
}


// ================= PHẦN CHỨC NĂNG CỦA SV4 =================

const int baseBlocks[7] = { 0, 2, 11, 12, 13, 14, 15 };
char originalBlocks[16][4][4];

static_assert(sizeof(blocks) / sizeof(blocks[0]) == 16,
              "blocks phai co dung 16 phan tu");

// Kiểm tra vị trí của hình dạng khối, dùng khi xoay khối.
bool canPlaceBlock(const char shape[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (shape[i][j] != ' ') {
                int boardX = x + j;
                int boardY = y + i;

                if (boardX < 1 || boardX >= W - 1 ||
                    boardY < 0 || boardY >= H - 1)
                    return false;

                if (board[boardY][boardX] != ' ')
                    return false;
            }
    return true;
}

// Xoay khối 90 độ theo chiều kim đồng hồ.
// Chỉ thay đổi khối hiện tại nếu vị trí sau khi xoay hợp lệ.
bool rotateBlock() {
    char rotated[4][4] = {};

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            rotated[j][3 - i] = blocks[b][i][j];

    if (!canPlaceBlock(rotated))
        return false;

    memcpy(blocks[b], rotated, sizeof(rotated));
    return true;
}

// Kiểm tra khối mới có thể xuất hiện tại vị trí bắt đầu hay không.
bool canSpawnBlock(int blockIndex) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[blockIndex][i][j] != ' ') {
                int boardX = x + j;
                int boardY = y + i;

                if (boardX < 1 || boardX >= W - 1 ||
                    boardY < 0 || boardY >= H - 1)
                    return false;

                if (board[boardY][boardX] != ' ')
                    return false;
            }
    return true;
}

// Tạo khối mới và khôi phục hình dạng gốc trước khi kiểm tra.
bool spawnBlock() {
    x = 5;
    y = 0;
    b = baseBlocks[rand() % 7];

    memcpy(blocks[b], originalBlocks[b], sizeof(blocks[b]));
    return canSpawnBlock(b);
}

// ====================== HẾT PHẦN SV4 ======================

int main()
{
    setupConsole();
    srand(time(0));

    initBoard();
    memcpy(originalBlocks, blocks, sizeof(blocks));
    if (!spawnBlock()) {
        draw();
        cout << "\nGAME OVER: Khong the tao block dau tien.\n";
        return 0;
    }

    int speed = 500;
    int timer = 0;

    while (1) {
        boardDelBlock();

        while (kbhit()) {
            int c = getch();
            if (c == 0 || c == 224) {
                c = getch();
                if (c == 75 && canMove(-1, 0)) x--;
                if (c == 77 && canMove(1, 0)) x++;
                if (c == 80 && canMove(0, 1)) y++;
            }
            else {
                if ((c == 'a' || c == 'A') && canMove(-1, 0)) x--;
                if ((c == 'd' || c == 'D') && canMove(1, 0)) x++;
                if ((c == 'x' || c == 'X' || c == 's' || c == 'S') && canMove(0, 1)) y++;
                if (c == 'w' || c == 'W') rotateBlock();
                if (c == 'q' || c == 'Q') return 0;
            }
        }

        if (timer >= speed) {
            if (canMove(0, 1)) y++;
            else {
                block2Board();
                int lines = removeLine();                // SV5
                if (lines > 0) {                         // SV5: xóa càng nhiều hàng càng nhanh
                    speed -= 50 * lines;
                    if (speed < 100) speed = 100;        // SV5: giới hạn tốc độ tối đa
                }
                if (!spawnBlock()) {
                    draw();
                    cout << "\nGAME OVER: Khong con vi tri xuat hien block.\n";
                    return 0;
                }
            }
            timer = 0;
        }

        block2Board();
        draw();
        Sleep(50);
        timer += 50;
    }
    return 0;
} 
