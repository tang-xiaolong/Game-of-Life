/*生命游戏  2018-6-22 01:37:25*/
/*规则：一个细胞周围有3个活细胞，那它下回合一定为活细胞；如果周围只有两个活细胞，那它保持当前的活性不变，死还是死，活还是活。其余情况，下回合为死细胞*/
/*这里设置的是从文件中读取我们的地图，修改里面的*号，*号表示活细胞，其余为死细胞   1234567890只是为了方便自己造地图的时候看着方便，不过要注意宏定义中M N和文件地图大小匹配哟  可以尝试随机生成地图自动进化   这里手动操作方便学习*/
/*使用两个地图，通过编号决定哪个为当前地图，哪个为下一回合的地图*/
#include<stdio.h>
#include<windows.h>
#define M 20
#define N 20
//全局变量区
int Map1[M][N] = {0};
int Map2[M][N] = {0};
int thisFlag = 1;

//函数声明区
void ReadMap();//读取初始地图
void Print(int thisMap[M][N]);//打印当前的地图
void Run();//保持运行的函数
void Calculate(int nowMap[M][N],int lastMap[M][N]);//把RenewMap传过来的地图根据规则计算新的地图
void RenewMap();//根据地图编号，调用计算函数，传入当前的地图，并更新当前的地图编号

int main(void)
{
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
			//if(0 != count)
			//	printf("第%d行 第%d列 %d个\n",i+1,j+1,count);
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
	ReadMap();
	Print(Map1);
	while(1)
	{
		switch(getch())
		{
			case 'y':RenewMap();break;
			case 27:return ;
		}
		system("cls");
		if(1 == thisFlag)
			Print(Map2);
		else
			Print(Map1);
	}
	
}
void ReadMap()
{
	FILE *fp = fopen("LifeGameMap.txt","r");
	int i = 0,j = 0;
	char ch = '\0';
	for(i = 0;i < M;i++)
	{
		for(j = 0;j < N;j++)
		{
			fscanf(fp,"%c",&ch);
			if('*' != ch)
			{
				Map1[i][j] = 0;
				Map2[i][j] = 0;
			}
			else
			{//设置为1，方便后期计算周围活细胞个数（直接累加就行）
				Map1[i][j] = 1;
				Map2[i][j] = 1;
			}
		}
		fscanf(fp,"%c",&ch);
	}
}
void Print(int thisMap[M][N])
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
	printf("请按Y(y)继续进化：");
}