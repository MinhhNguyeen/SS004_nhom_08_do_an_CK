#include <iostream>
#include <conio.h>
#include <cstring>   // SV4: memcpy
#include <cstdlib>   // FIX: rand, srand, system
#include <ctime>     // FIX: time

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;
char cur[4][4];      // SV4: bản sao của khối đang rơi, dùng để xoay
int baseBlocks[7] = {0, 2, 11, 12, 13, 14, 15};   // SV4: chọn đủ 7 loại khối I, O, T, S, Z, J, L
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
            if (cur[i][j] != ' ') {                  // SV4: cur thay cho blocks[b]
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W-1 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}
void block2Board(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (cur[i][j] != ' ')                    // SV4
                board[y+i][x+j] = cur[i][j];
}
void boardDelBlock(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (cur[i][j] != ' ')                    // SV4
                board[y+i][x+j] = ' ';
}

// SV4: xoay khối 90 độ theo chiều kim đồng hồ.
// Gọi sau boardDelBlock() nên khối không va chạm với chính nó.
// Vị trí sau khi xoay chạm tường, đáy hoặc khối đã cố định thì giữ nguyên khối.
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

// SV4: khối mới sinh ra có chồng lên khối đã cố định không?
// Bỏ qua hàng 0 vì đó là viền '#', nếu không khối I sẽ bị báo Game Over oan.
bool spawnBlocked(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (cur[i][j] != ' ' && y+i > 0 && board[y+i][x+j] != ' ') return true;
    return false;
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
            for (int jj = 1; jj < W-1; jj++)         // FIX: hàng 1 phải trống, không lấy từ hàng viền 0
                board[1][jj] = ' ';
            i++;
            draw();
            _sleep(200);
        }
    }
}

int main()
{
    srand(time(0));
    x = 5; y = 0; b = baseBlocks[rand()%7];
    memcpy(cur, blocks[b], sizeof(cur));             // SV4
    initBoard();
    while (1){
        boardDelBlock();
        if (kbhit()){
            char c = getch();
            if (c == 'a' && canMove(-1,0)) x--;
            if (c == 'd' && canMove( 1,0)) x++;
            if (c == 'x' && canMove( 0,1)) y++;
            if (c == 'w' || c == 'W') rotateBlock(); // SV4: phím W = xoay
            if (c == 'q') break;
        }
        if (canMove(0,1)) y++;
        else{
            block2Board();
            removeLine();
            x = 5; y = 0; b = baseBlocks[rand()%7];
            memcpy(cur, blocks[b], sizeof(cur));     // SV4
            if (spawnBlocked()) {                    // SV4: không còn chỗ sinh khối -> Game Over
                draw();
                cout << "GAME OVER!" << endl;
                break;
            }
        }
        block2Board();
        draw();
        _sleep(500);
    }
    return 0;
}
