
 #pragma warning(disable : 4996)
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

#define H 20
#define W 15

char board[H][W] = {};

int x, y, b;
char cur[4][4]; // SV4: ma trận khối đang rơi, dùng riêng để xoay

char blocks[][4][4] = {
    { { ' ','I',' ',' ' }, { ' ','I',' ',' ' }, { ' ','I',' ',' ' }, { ' ','I',' ',' ' } },
    { { ' ','I',' ',' ' }, { ' ','I',' ',' ' }, { ' ','I',' ',' ' }, { ' ','I',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ','O','O',' ' }, { ' ','O','O',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ','O','O',' ' }, { ' ','O','O',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ','O','O',' ' }, { ' ','O','O',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ','O','O',' ' }, { ' ','O','O',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ','O','O',' ' }, { ' ','O','O',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ','O','O',' ' }, { ' ','O','O',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ','O','O',' ' }, { ' ','O','O',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { 'I','I','I','I' }, { ' ',' ',' ',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ','O','O',' ' }, { ' ','O','O',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ','T',' ',' ' }, { 'T','T','T',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ','S','S',' ' }, { 'S','S',' ',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { 'Z','Z',' ',' ' }, { ' ','Z','Z',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { 'J',' ',' ',' ' }, { 'J','J','J',' ' }, { ' ',' ',' ',' ' } },
    { { ' ',' ',' ',' ' }, { ' ',' ','L',' ' }, { 'L','L','L',' ' }, { ' ',' ',' ',' ' } }
};

// SV4: kiểm tra di chuyển dựa trên ma trận hiện tại cur.
bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ') {
                int xt = x + j + dx;
                int yt = y + i + dy;

                if (xt < 1 || xt >= W - 1 || yt < 0 || yt >= H - 1)
                    return false;

                if (board[yt][xt] != ' ')
                    return false;
            }
    return true;
}

// SV4: ghi hình dạng hiện tại của khối lên board.
void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ')
                board[y + i][x + j] = cur[i][j];
}

// SV4: xóa hình dạng hiện tại của khối khỏi board trước khi xử lý di chuyển/xoay.
void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ')
                board[y + i][x + j] = ' ';
}

// SV4: sinh ngẫu nhiên 1 trong 7 loại khối cơ bản.
// Giữ y = 0 như main hiện tại; các ô có hình của khối nằm từ hàng 1 trở xuống.
bool spawn() {
    const int baseBlocks[7] = { 0, 2, 11, 12, 13, 14, 15 };

    x = 5;
    y = 0;
    b = baseBlocks[rand() % 7];

    memcpy(cur, blocks[b], sizeof(cur));
    return canMove(0, 0);
}

// SV4: xoay khối 90 độ theo chiều kim đồng hồ.
// Chỉ chấp nhận phép xoay nếu tất cả ô có hình vẫn nằm trong vùng chơi
// và không đè lên các khối đã cố định trên board.
void rotateBlock() {
    char rotated[4][4] = {};

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            rotated[j][3 - i] = cur[i][j];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rotated[i][j] == ' ')
                continue;

            int xt = x + j;
            int yt = y + i;

            if (xt < 1 || xt >= W - 1 || yt < 0 || yt >= H - 1)
                return;

            if (board[yt][xt] != ' ')
                return;
        }
    }

    memcpy(cur, rotated, sizeof(cur));
}

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (i == H - 1 || j == 0 || j == W - 1) board[i][j] = '#';
            else board[i][j] = ' ';
}

// ================= PHẦN GIAO DIỆN CỦA SV3: GIỮ NGUYÊN =================
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
            if (i == H - 1 && j == 0)          frame += " \xE2\x96\x9D";
            else if (i == H - 1 && j == W - 1) frame += "\xE2\x96\x98 ";
            else if (i == H - 1)               frame += "\xE2\x96\x80\xE2\x96\x80";
            else if (j == 0)                   frame += " \xE2\x96\x90";
            else if (j == W - 1)               frame += "\xE2\x96\x8C ";
            else if (board[i][j] == ' ')       frame += "  ";
            else                               frame += "[]";
        }
        if (i < H - 1) frame += "\n";
    }
    cout << frame << flush;
}

// ================= PHẦN SV5: GIỮ NGUYÊN =================
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

int main() {
    setupConsole();
    srand(static_cast<unsigned int>(time(0)));
    initBoard();

    int speed = 500; // SV5
    int timer = 0;   // SV5

    // SV4: sinh khối đầu tiên và kiểm tra Game Over.
    if (!spawn()) {
        draw();
        cout << "\nGAME OVER!" << endl;
        return 0;
    }

    while (1) {
        // SV4: xóa khối đang rơi khỏi board trước khi kiểm tra thao tác.
        boardDelBlock();

        while (kbhit()) {
            int c = getch();

            if (c == 0 || c == 224) {
                c = getch();
                if (c == 75 && canMove(-1, 0)) x--;
                if (c == 77 && canMove(1, 0)) x++;
                if (c == 80 && canMove(0, 1)) y++;
            } else {
                if ((c == 'a' || c == 'A') && canMove(-1, 0)) x--;
                if ((c == 'd' || c == 'D') && canMove(1, 0)) x++;
                if ((c == 'x' || c == 'X' || c == 's' || c == 'S') && canMove(0, 1)) y++;
                if (c == 'w' || c == 'W') rotateBlock(); // SV4: W để xoay
                if (c == 'q' || c == 'Q') return 0;
            }
        }

        // SV5: giữ nguyên cơ chế rơi theo timer và speed.
        if (timer >= speed) {
            if (canMove(0, 1)) {
                y++;
            } else {
                // Khối hiện tại đã chạm đáy/khối khác: cố định rồi xóa hàng.
                block2Board();

                int lines = removeLine(); // SV5
                if (lines > 0) {
                    speed -= 50 * lines;
                    if (speed < 100) speed = 100;
                }

                // SV4: sinh khối mới; nếu vị trí xuất hiện bị chiếm thì Game Over.
                if (!spawn()) {
                    draw();
                    cout << "\nGAME OVER! Nhan phim bat ky de thoat." << endl;
                    getch();
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
