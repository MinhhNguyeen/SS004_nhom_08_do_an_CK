#pragma warning(disable : 4996)
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <string>

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;
char cur[4][4];   // SV4: hình dạng của khối đang rơi (đã tính xoay)
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

// SV4: sinh khối mới, copy hình dạng vào cur
void spawn(int idx) {
    b = idx;
    x = 5; y = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cur[i][j] = blocks[b][i][j];
}

bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ') {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W - 1 || yt >= H - 1) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}

// ================= PHẦN XOAY KHỐI CỦA SV4 =================
// Kích thước vùng xoay: I = 4, O = 0 (không cần xoay), các khối còn lại = 3
int rotateSize() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ') {
                if (cur[i][j] == 'I') return 4;
                if (cur[i][j] == 'O') return 0;
                return 3;
            }
    return 0;
}

// Tạo bản xoay 90 độ theo chiều kim đồng hồ vào out; false nếu khối không xoay
bool makeRotated(char out[4][4]) {
    int n = rotateSize();
    if (n == 0) return false;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            out[i][j] = ' ';
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i][j] = cur[n - 1 - j][i];
    return true;
}

// Bản xoay hợp lệ khi không ra ngoài tường/đáy và không đè lên khối đã cố định.
// Gọi sau boardDelBlock() nên board không còn chứa khối đang rơi.
bool canRotate(char t[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (t[i][j] != ' ') {
                int xt = x + j;
                int yt = y + i;
                if (xt < 1 || xt >= W - 1 || yt < 0 || yt >= H - 1) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}

void rotateBlock() {
    char t[4][4];
    if (!makeRotated(t)) return;   // khối O: không xoay
    if (!canRotate(t)) return;     // vị trí không hợp lệ: giữ nguyên
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cur[i][j] = t[i][j];
}
// ==========================================================

void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ')
                board[y + i][x + j] = cur[i][j];
}

void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ')
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

int main()
{
    setupConsole();
    srand(time(0));

    int baseBlocks[7] = { 0, 2, 11, 12, 13, 14, 15 };
    initBoard();
    spawn(baseBlocks[rand() % 7]);

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
                if (c == 72) rotateBlock();                 // SV4: mũi tên lên = xoay
            }
            else {
                if ((c == 'a' || c == 'A') && canMove(-1, 0)) x--;
                if ((c == 'd' || c == 'D') && canMove(1, 0)) x++;
                if ((c == 'x' || c == 'X' || c == 's' || c == 'S') && canMove(0, 1)) y++;
                if (c == 'w' || c == 'W') rotateBlock();    // SV4: W = xoay
                if (c == 'q' || c == 'Q') return 0;
            }
        }

        if (timer >= speed) {
            if (canMove(0, 1)) y++;
            else {
                block2Board();
                int lines = removeLine();                // SV5
                if (lines > 0 && speed > 150) {          // SV5: chỉ giảm khi có xóa hàng và chưa chạm tốc độ tối đa
                    speed -= 50 * lines;
                    if (speed < 150) speed = 150;        // SV5: giới hạn tốc độ tối đa
                }
                spawn(baseBlocks[rand() % 7]);
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
