
#include <iostream>
#include <conio.h>
#include <cstring>   // SV4: memcpy

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;
char cur[4][4];      // SV4: khối đang rơi (bản sao có thể xoay)
char blocks[][4][4] ={
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
bool canMove(int dx, int dy){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (cur[i][j] != ' ') {              // SV4: dùng cur
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W-1 || yt < 0 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}
void block2Board(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (cur[i][j] != ' ')                // SV4: dùng cur
                board[y+i][x+j] = cur[i][j];
}
void boardDelBlock(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (cur[i][j] != ' ')                // SV4: dùng cur
                board[y+i][x+j] = ' ';
}

// SV4: sinh khối mới, chép từ blocks[b] sang cur.
// Chọn đủ 7 loại khối (I, O, T, S, Z, J, L).
// y = 1 vì hàng 0 là viền '#'. Trả về false nếu vị trí sinh ra đã bị chiếm (Game Over).
bool spawn(){
    const int baseBlocks[7] = {0, 2, 11, 12, 13, 14, 15};

    x = 5;
    y = 1;
    b = baseBlocks[rand() % 7];

    memcpy(cur, blocks[b], sizeof(cur));
    return canMove(0, 0);
}

// SV4: xoay 90 độ theo chiều kim đồng hồ.
// Gọi sau boardDelBlock() để khối không va chạm với chính nó.
// Nếu vị trí xoay không hợp lệ (xuyên tường, đáy, khối cố định) thì giữ nguyên.
void rotateBlock(){
    char t[4][4];
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            t[j][3-i] = cur[i][j];

    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (t[i][j] != ' ') {
                int xt = x + j;
                int yt = y + i;
                if (xt < 1 || xt >= W-1 || yt < 0 || yt >= H-1) return;
                if (board[yt][xt] != ' ') return;
            }

    memcpy(cur, t, sizeof(cur));
}

void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if (i == 0 || i == H-1 || j ==0 || j == W-1) board[i][j] = '#';
            else board[i][j] = ' ';
}
void draw(){
    system("cls");

    for (int i = 0 ; i < H ; i++, cout<<endl)
        for (int j = 0 ; j < W ; j++) cout<<board[i][j];
}
void removeLine(){
    int i,j;
    for (i = H-2 ; i > 0 ; i-- ){
        for (j = 0 ; j < W ; j++)
            if (board[i][j] == ' ') break;
        if (j == W){
            for (int ii = i ; ii > 0 ; ii--)
                for (int jj = 0; jj < W; jj++)
                    board[ii][jj] = board[ii-1][jj];
            i++;
            draw();
            _sleep(200);
        }
    }
}

int main()
{
    srand(time(0));
    initBoard();
    if (!spawn()) {                              // SV4: kiểm tra cả lần sinh khối đầu tiên
        draw();
        cout << "GAME OVER!" << endl;
        return 0;
    }
    while (1){
        boardDelBlock();
        if (kbhit()){
            char c = getch();
            if ((c == 'a' || c == 'A') && canMove(-1,0)) x--;
            if ((c == 'd' || c == 'D') && canMove( 1,0)) x++;
            if ((c == 'x' || c == 'X') && canMove( 0,1)) y++;
            if (c == 'w' || c == 'W') rotateBlock();   // SV4: phím W = xoay
            if (c == 'q' || c == 'Q') break;
        }
        if (canMove(0,1)) y++;
        else{
            block2Board();
            removeLine();
            if (!spawn()) {                      // SV4: vị trí sinh bị chiếm -> Game Over
                draw();
                cout << "GAME OVER! Nhan phim bat ky de thoat." << endl;
                getch();
                break;
            }
        }
        block2Board();
        draw();
        _sleep(500);
    }
    return 0;
}
