#include<stdio.h>
#include<windows.h>
#define M 45
#define N 2*M
//全局变量区
int Map1[M][N] = {0};
int Map2[M][N] = {0};
int thisFlag = 1;

//函数声明区
void CreateMap();//随机创建初始地图
void Print(int thisMap[M][N],int lastMap[M][N]);//打印当前的地图
void InitShowMap(int thisMap[M][N]);//初始化打印地图
void Run();//保持运行的函数
void Calculate(int nowMap[M][N],int lastMap[M][N]);//把RenewMap传过来的地图根据规则计算新的地图
void RenewMap();//根据地图编号，调用计算函数，传入当前的地图，并更新当前的地图编号
void Pos(int x, int y);//设置光标位置，决定要在什么位置输出


int main(void)
{
	system("mode con cols=220 lines=100");
	Run();
	return 0;
}
void RenewMap()
{
	//遍历当前的地图数组,依次计算每个格子的后一个状态，并更新新的地图
	if(1 == thisFlag)
	{
		Calculate(Map1,Map2);
		thisFlag = 2;
	}
	else
	{
		Calculate(Map2,Map1);
		thisFlag = 1;
	}	
}
void Calculate(int nowMap[M][N],int lastMap[M][N])
{
	int i = 0,j = 0,count = 0;
	for(i = 0;i < M;i++)
	{
		for(j = 0;j < N;j++)
		{
			//因为活细胞是1，所以直接将自己周围对应的地图数字相加就是活细胞个数
			count = 0;
			//列举出几种边界情况，特殊计算，否则计算四周
			//第一排   最后一排  左边中间  右边中间  正中间
			if(0 == i)
			{
				//在第一排
				if(0 == j)
				{
					count = nowMap[i][j+1]+nowMap[i+1][j]+nowMap[i+1][j+1];
				}
				else if(j == N-1)
				{
					count = nowMap[i][j-1]+nowMap[i+1][j]+nowMap[i+1][j-1];
				}
				else
				{
					count = nowMap[i][j-1]+nowMap[i+1][j-1]+nowMap[i][j+1]+nowMap[i+1][j]+nowMap[i+1][j+1];
				}
			}
			else if(M-1 == i)
			{
				if(0 == j)
				{
					count = nowMap[i][j+1]+nowMap[i-1][j]+nowMap[i-1][j+1];
				}
				else if(j == N-1)
				{
					count = nowMap[i][j-1]+nowMap[i-1][j]+nowMap[i-1][j-1];
				}
				else
				{
					count = nowMap[i][j-1]+nowMap[i-1][j-1]+nowMap[i][j+1]+nowMap[i-1][j]+nowMap[i-1][j+1];
				}
			}
			else if(0 == j)
				//要注意，前面已经计算过的不用在考虑，所以这个时候，肯定是靠左边中间的
				count = nowMap[i-1][j]+nowMap[i-1][j+1]+nowMap[i][j+1]+nowMap[i+1][j+1]+nowMap[i+1][j];
			else if(N-1 == j)
				count = nowMap[i-1][j]+nowMap[i-1][j-1]+nowMap[i][j-1]+nowMap[i+1][j-1]+nowMap[i+1][j];
			else
				count = nowMap[i-1][j]+nowMap[i-1][j-1]+nowMap[i][j-1]+nowMap[i+1][j-1]+nowMap[i+1][j]+nowMap[i-1][j+1]+nowMap[i][j+1]+nowMap[i+1][j+1];
			//根据count的结果来判断新的地图中细胞的生死
			if(3 == count)
				lastMap[i][j] = 1;
			else if(2 == count)
				lastMap[i][j] = nowMap[i][j];
			else
				lastMap[i][j] = 0;
		}
	}
}
void Run()
{
	int i = 0,j = 0;
	CreateMap();
	InitShowMap(Map1);
	while(1)
	{
		/*
		switch(getch())
		{
			case 'y':RenewMap();break;
			case 27:return ;
		}
		*/
		RenewMap();
		Sleep(200);
		if(1 == thisFlag)
			Print(Map2,Map1);
		else
			Print(Map1,Map2);
	}	
}
void CreateMap()
{
	int i = 0,j = 0;
	char ch = '\0';
	for(i = 0;i < M;i++)
	{
		for(j = 0;j < N;j++)
		{
			if(rand()%10 < 8)
			{
				Map1[i][j] = 0;
				Map2[i][j] = 0;
			}
			else
			{
				Map1[i][j] = 1;
				Map2[i][j] = 1;
			}
		}
	}
}
void Print(int thisMap[M][N],int lastMap[M][N])
{
	int i = 0,j = 0;
	for(i = 0;i < M;i++)
	{
		for(j = 0;j < N;j++)
		{
			//不相等，所以需要改变输出
			if(thisMap[i][j] != lastMap[i][j])
			{//这里的符号需要占两个字符
				Pos(2*j,i);
				if(0 == lastMap[i][j])
					printf("□");
				else
					printf("■");
			}
		}
	}
	//Pos(N,M);
}
void InitShowMap(int thisMap[M][N])
{
	int i = 0,j = 0;
	for(i = 0;i < M;i++)
	{
		for(j = 0;j < N;j++)
		{
			if(0 == thisMap[i][j])
				printf("□");
			else
				printf("■");
		}
		printf("\n");
	}
	//printf("请按Y(y)继续进化：");
}
void Pos(int x, int y)//设置光标位置
{//要注意这里的x和y与我们数组的x和y是反的
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//返回标准的输入、输出或错误的设备的句柄，也就是获得输入、输出/错误的屏幕缓冲区的句柄
	SetConsoleCursorPosition(hOutput, pos);
}
