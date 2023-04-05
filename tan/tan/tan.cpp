// tan.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include<stdlib.h>
#include <graphics.h>
#include<windef.h>
#include<conio.h>
enum dir {
    up,
    down,
    left,
    right,


};
struct Snake {
    int size;
    int dir;
    int speed;
    POINT coor[500];

}snake;
struct Food {
    int x;
    int y;
    bool flag;
    DWORD color;
    int r;
}food;


void GameInit() {
    
    
    initgraph(640, 480,SHOWCONSOLE);
    srand(GetTickCount());
    snake.size = 3;
    snake.speed = 10;
    snake.dir= right ;
    snake.coor[0].x = 10;
    snake.coor[0].y = 10;
    for (int i = 0; i < snake.size;i++) {
        snake.coor[i].x = 40-10*i;
        snake.coor[i].y = 10 ;

        printf("?%d %d", snake.coor[i].x, snake.coor[i].y);
    }

    food.x = rand() % 640;
    food.y = rand() % 480;
    food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
    food.r = rand() % 10 + 5;
    food.flag = true;

}
void Gamedraw(){
    BeginBatchDraw();
    setbkcolor(RGB(100, 200, 130));
    cleardevice();
    setfillcolor(BLUE);
    for (int i = 0; i < snake.size; ++i) {
        solidcircle(snake.coor[i].x ,snake.coor[i].y ,5);
    }

    if (food.flag==true) {
        solidcircle(food.x, food.y, food.r);
    }

    EndBatchDraw();
        

}
void move() {

    for (int i = snake.size-1; i >0; i--) {
        snake.coor[i] = snake.coor[i - 1];
    }

    
    switch (snake.dir)
        {
        case up:
            snake.coor[0].y -= snake.speed;
            if (snake.coor[0].y== 0){
                snake.coor[0].y = 480;
            }
            
            break;
        case down:
            snake.coor[0].y+=snake.speed;
            if (snake.coor[0].y == 480) {
                snake.coor[0].y = 0;
            }
            break;
        case left:
            snake.coor[0].x-= snake.speed;
            if (snake.coor[0].x == 0) {
                snake.coor[0].x = 640;
            }
            break;
        case right:
            snake.coor[0].x+= snake.speed;
            if (snake.coor[0].x == 640) {
                snake.coor[0].x = 0;
            }
            break;
    
        }

    
    
}

void keycontrol() {

    if (_kbhit()) {
        switch (_getch()) {
        case 'w':
        case 'W':
        case 72:
            if (snake.dir != down) {
                snake.dir = up;
                
            }
            break;
        case 's':
        case 'S':
        case 80:
            if (snake.dir != up) {
                snake.dir = down;
                
            }
            break;
        case 'A':
        case 'a':
        case 75:
            if (snake.dir != right) {
                snake.dir = left;
                
            }
            break;
        case 'D':
        case 'd':
        case 77:
            if (snake.dir != left) {
                snake.dir = right;

            }

            break;

        }
    }
}

void eatfood(){
    if (food.flag==true&&snake.coor[0].x >= food.x-food.r && snake.coor[0].x <= food.x + food.r 
        && snake.coor[0].y >= food.y-food.r&& snake.coor[0].y <= food.y+food.r) {
        food.flag = false;
        snake.size++;
    }
    if (food.flag == false) {
        food.x = rand() % 640;
        food.y = rand() % 480;
        food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
        food.r = rand() % 10 + 5;
        food.flag = true;
    }
    
}


void stop() {
    if (_kbhit()) {
        if (_getch() == ' ') {
            while(_getch() == ' ');
        }
    }
}


int main()
{
    
    GameInit();

   
    
    
    

    while (true) {

        move();
        Gamedraw();
        keycontrol();
        eatfood();
        Sleep(50);
        stop();
        
    }


    return 0;



}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
