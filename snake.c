#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#pragma warning(disable:4996)
#include"head.h"



#include<Windows.h>
#include<MMSystem.h>
#pragma comment(lib,"winmm.lib")
//#include"resource.h"      //引号 '' 是工程文件   尖括号<>是系统文件

void FirstPage();               //   显示首页        //函数声明
//   播放音乐
void MyPlaySound();   

//   按空格键
void Testspace();      

//   停止播放并清屏
void StopMymusic();       

//   展示背景
void Showbackground();     

//   为蛇产生一个随机位置
void SetSnakeRandPos();      

//画蛇
void DrawSnake();         

//销毁蛇
void Destroysnake();

//动蛇
void SnakeMove();      

//改变蛇的方向
void changeDir();

//蛇的死亡判断
bool IsSnakeDie();

//随机产生一个食物
void Producefood();
//蛇变长
void SnakeGrowthUp();
//计分
void Score();





int main(void)
{
	FirstPage();        //显示首页

	MyPlaySound();      //播放音乐   没有资源

	Testspace();        //按空格键

	StopMymusic();     //停止播放并清屏   

	SetSnakeRandPos(); //为蛇产生一个随机位置

	
	Showbackground();  //展示背景


	

	//游戏界面
	while (1)
	{
		system("cls");

		Producefood();//随机产生一个食物

		SnakeGrowthUp();	//蛇变长

		Showbackground();   //可省略

		if (false == IsSnakeDie())    //蛇的死亡判断
		{
			printf("蛇死亡\n");
			break;
		}

		changeDir();        //  改变方向
		
		SnakeMove();        //蛇动

		Score();           //显示分数
		Sleep(500);

	}

	system("pause");
	return 0;
}

void Score()
{
	COORD rd;
	rd.X = 41;
	rd.Y = 17;

	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf("|分数       |\n");



	rd.X = 41;
	rd.Y = 19;

	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf(":|%d        |",g_nScore);
}

void SnakeGrowthUp()
{
	//蛇头坐标与食物坐标相等
	if (g_nLine_y==g_arrSnake[0][1]&&g_nRow_x*2==g_arrSnake[0][0])
	{
		//长大
		if (to_east == g_arrSnake[g_snakelen][2])
		{
			g_arrSnake[g_snakelen + 1][0] = g_arrSnake[g_snakelen][0]-2;
			g_arrSnake[g_snakelen + 1][1] = g_arrSnake[g_snakelen][1];
			g_arrSnake[g_snakelen + 1][2] = g_arrSnake[g_snakelen][2];
		}
		else if (to_west == g_arrSnake[g_snakelen][2])
		{
			g_arrSnake[g_snakelen + 1][0] = g_arrSnake[g_snakelen][0] + 2;
			g_arrSnake[g_snakelen + 1][1] = g_arrSnake[g_snakelen][1];
			g_arrSnake[g_snakelen + 1][2] = g_arrSnake[g_snakelen][2];
		}
		else if (to_north == g_arrSnake[g_snakelen][2])
		{
			g_arrSnake[g_snakelen + 1][0] = g_arrSnake[g_snakelen][0] + 1;
			g_arrSnake[g_snakelen + 1][1] = g_arrSnake[g_snakelen][1];
			g_arrSnake[g_snakelen + 1][2] = g_arrSnake[g_snakelen][2];
		}
		else if (to_north == g_arrSnake[g_snakelen][2])
		{
			g_arrSnake[g_snakelen + 1][0] = g_arrSnake[g_snakelen][0] - 1;
			g_arrSnake[g_snakelen + 1][1] = g_arrSnake[g_snakelen][1];
			g_arrSnake[g_snakelen + 1][2] = g_arrSnake[g_snakelen][2];
		}
		DrawSnake();

		g_snakelen++;
		g_blsprofood = true;
		g_nScore++;
	}
}
//随机产生一个食物
void Producefood()
{
	int i;
	if (false == g_blsprofood)
	{
		return;
	}
	

	while(1)
	{ 
		
		g_nRow_x = rand() % 18 + 1;
		g_nLine_y = rand() % 18 + 1;
		
		// 防止食物坐标与蛇重合
		for (i = 0; g_arrSnake[i][0] != 0; i++)//      遍历蛇
		{
			if (g_nLine_y == g_arrSnake[i][1] && g_nRow_x == g_arrSnake[i][0])
			{
				g_blsprofood = false;
				break;
			}
			
	     }
		if (true == g_blsprofood)
		{
			break;
		}

	}

	//坐标食物
	strncpy(&g_arrBackground[g_nLine_y][g_nRow_x*2], "★", 2);
	g_blsprofood = false;

}

//  蛇死
bool IsSnakeDie()
{
	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		if (0==strncmp(&g_arrBackground[g_arrSnake[0][1]][g_arrSnake[0][0] + g_arrSnake[0][2]], "■", 2))
		{
			return false;
		}
	}
	else
	{
		if (0==strncmp(&g_arrBackground[g_arrSnake[0][1] + g_arrSnake[0][2]][g_arrSnake[0][0]], "■", 2))
			return false;
	}

	return true;
}

void changeDir()
{
	//_getch();   //同步检测
	if (GetAsyncKeyState('W')) //异步检测
	{
		if (to_south != g_arrSnake[0][2])
		{
			g_nSnakedir = to_north;
		}
		
	}
	else if (GetAsyncKeyState('S'))
	{
		if (to_north != g_arrSnake[0][2])
		{
			g_nSnakedir = to_south;
		}
	}
	else if (GetAsyncKeyState('A'))
	{
		if (to_east != g_arrSnake[0][2])
		{
			g_nSnakedir = to_west;
		}
	}
	else if (GetAsyncKeyState('D'))
	{
		if (to_west != g_arrSnake[0][2])
		{
			g_nSnakedir = to_east;
		}
		
	}

}

void SnakeMove()
{
	int i = DEF_SNAKE_LONG-1;

	// 销毁蛇
	Destroysnake();

	for (; i >= 1; i--)
	{
		//过滤空白蛇身
		if (0 == g_arrSnake[i][0])
		{
			continue;
		}
		//把前一个节点的值，赋给当前的节点
		g_arrSnake[i][0] = g_arrSnake[i - 1][0];
		g_arrSnake[i][1] = g_arrSnake[i - 1][1];
		g_arrSnake[i][2] = g_arrSnake[i - 1][2];
	}

	//处理蛇头
	g_arrSnake[0][2] = g_nSnakedir;
	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		g_arrSnake[0][0] += g_arrSnake[0][2];
	}
	else
	{
		g_arrSnake[0][1] += g_arrSnake[0][2];
	}

	DrawSnake();  //画蛇

}

void SetSnakeRandPos()
{
	int nX = -1, nY = -1;
	//产生随机数
	srand((unsigned int)time(NULL));    //种种子
	nX = rand() % 16 + 1;       
	nY = rand() % 18 + 1;


	//初始化蛇的三个节点
	g_arrSnake[0][0]= nX*2;
	g_arrSnake[0][1] = nY;
	g_arrSnake[0][2]= to_west;

	g_arrSnake[1][0] = nX*2+2;
	g_arrSnake[1][1] = nY;
	g_arrSnake[1][2] = to_west;

	g_arrSnake[2][0] = nX*2+4;
	g_arrSnake[2][1] = nY;
	g_arrSnake[2][2] = to_west;


	DrawSnake();      //   画蛇

}


void Destroysnake()
{
	int i;
	for (i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_arrBackground[g_arrSnake[i][1]][g_arrSnake[i][0]], "  ", 2);
	}
}

//  画蛇
void DrawSnake()
{
	int i;
	for (i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_arrBackground[g_arrSnake[i][1]][g_arrSnake[i][0]],"■",2);
	}
}

void Showbackground()    //游戏界面
{
	int i;
	for (i = 0; i < 20; i++)
	{
		printf(g_arrBackground[i]);
	}
}


void FirstPage()
{
	printf("\n\n\n\n");
	printf("\t\t\t欢迎进入贪吃蛇的世界\n");
	printf("\t\t\t 按空格键开始游戏\n");
	printf("\t\t\tw a s d 控制蛇的方向\n");
}

void MyPlaySound()    //音乐播放
{
	PlaySound(L"1.wav", NULL, SND_FILENAME | SND_ASYNC);    //可以自主修改       加载路径的方式  可以替换内容
															//绝对路径：完整的路径
															//相对路径：
	//PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);   添加因音乐资源

}

void StopMymusic()
{
	PlaySound(NULL, 0, 0);
	system("cls");
}
void Testspace()     //检测空格
{
	char chInput;
	while (1)
	{
		chInput = _getch();
		if (' ' == chInput)
		{
			break;
		}
	}
}



