#pragma once
#define DEF_SNAKE_LONG 20

typedef int bool;
#define true 1
#define false 0


char g_arrBackground[20][42] = {     { "■■■■■■■■■■■■■■■■■■■■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■                                    ■\n" },
									{ "■■■■■■■■■■■■■■■■■■■■\n" } };


//方向
enum{to_east=2,to_west=-2,to_north=-1,to_south=1};
//  蛇数组
int g_arrSnake[DEF_SNAKE_LONG][3] = { 0 };
// 蛇的方向
int g_nSnakedir = to_west;

bool g_blsprofood = true;

int g_nLine_y, g_nRow_x;//产生食物的坐标
// 蛇长度
int g_snakelen = 2;
// 分数
int g_nScore = 0;

