#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define HEIGHT 1080
#define WIDTH 1920

long img[HEIGHT][WIDTH];

void Init();
void Test(void (*function)());
void Func1_basic();     //原始版本 
void Func2();           //行列转换的Cache优化 减少miss 
void Func3();           //循环展开 ,流水线优化 
void Func4();			// 面向CPU指令集并发优化 
void Func5();			//分块cacheline优化 	
int minn(int x, int y);
int main()
{
	
	Test(Func1_basic);
	Test(Func2);
	Test(Func3);
	Test(Func4);
	Test(Func5);

	return 0;
}
void Init()
{
	int i, j;
	int cnt = 0;
	for(i = 0; i < HEIGHT; i ++ )
	{
		for(j = 0; j < WIDTH; j ++ )
		{
			img[i][j] = cnt ++;
		}
	}
	
}
void Test(void (*function)()) 
{
	Init();
	clock_t t1 = clock();
	int t = 100;
	while(t--) 
	{
		function();
	}
	clock_t t2 = clock();
	printf("COST %ldms\n",(t2 - t1) * 1000 / CLOCKS_PER_SEC);
}
void Func1_basic()
{
	int i, j;
	for(j = 1; j < WIDTH - 1; j ++ )
	{
		for(i = 1; i < HEIGHT - 1; i ++ )
		{
			img[i][j] = (img[i - 1][j] + img[i + 1][j] + img[i][j + 1] + img[i][j - 1]) / 4;
		}
	}
}
void Func2()
{
	int i, j;
	for(i = 1; i < HEIGHT - 1; i ++ )
	{
		for(j = 1; j < WIDTH - 1; j ++ )
		{
			img[i][j] = (img[i - 1][j] + img[i + 1][j] + img[i][j + 1] + img[i][j - 1]) / 4;
		}
	}
}
void Func3()
{
	int block = 4;
	int i, j;
	
	for(i = 1; i < HEIGHT - 1; i ++ )
	{
		for(j = 1; j < WIDTH - 4; j += block)
		{
			img[i][j] = (img[i - 1][j] + img[i + 1][j] + img[i][j + 1] + img[i][j - 1]) / 4;
			img[i][j + 1] = (img[i - 1][j + 1] + img[i + 1][j + 1] + img[i][j + 1 + 1] + img[i][j - 1 + 1]) / 4;
			img[i][j + 2] = (img[i - 1][j + 2] + img[i + 1][j + 2] + img[i][j + 1 + 2] + img[i][j - 1 + 2]) / 4;
			img[i][j + 3] = (img[i - 1][j + 3] + img[i + 1][j + 3] + img[i][j + 1 + 3] + img[i][j - 1 + 3]) / 4;
		}
		for(;j < WIDTH - 1; j ++ )
		{
			img[i][j] = (img[i - 1][j] + img[i + 1][j] + img[i][j + 1] + img[i][j - 1]) / 4;
		}
	}
}
void Func4()
{
	int i, j;
	//为什么是14：14|1918 
	for(i = 1; i < HEIGHT - 1; i ++ )
	{
		for(j = 1; j < WIDTH - 1; j += 14)
		{
			img[i][j + 0] = (img[i - 1][j] + img[i + 1][j] + img[i][j + 1] + img[i][j - 1]) / 4;
			img[i][j + 2] = (img[i - 1][j + 2] + img[i + 1][j + 2] + img[i][j + 1 + 2] + img[i][j - 1 + 2]) / 4;
			img[i][j + 4] = (img[i - 1][j + 4] + img[i + 1][j + 4] + img[i][j + 1 + 4] + img[i][j - 1 + 4]) / 4;
			img[i][j + 6] = (img[i - 1][j + 6] + img[i + 1][j + 6] + img[i][j + 1 + 6] + img[i][j - 1 + 6]) / 4;
			img[i][j + 8] = (img[i - 1][j + 8] + img[i + 1][j + 8] + img[i][j + 1 + 8] + img[i][j - 1 + 8]) / 4;
			img[i][j + 10] = (img[i - 1][j + 10] + img[i + 1][j + 10] + img[i][j + 1 + 10] + img[i][j - 1 + 10]) / 4;
			img[i][j + 12] = (img[i - 1][j + 12] + img[i + 1][j + 12] + img[i][j + 1 + 12] + img[i][j - 1 + 12]) / 4;
		}
		for(j = 2; j < WIDTH - 1; j += 14)
		{
			img[i][j + 0] = (img[i - 1][j] + img[i + 1][j] + img[i][j + 1] + img[i][j - 1]) / 4;
			img[i][j + 2] = (img[i - 1][j + 2] + img[i + 1][j + 2] + img[i][j + 1 + 2] + img[i][j - 1 + 2]) / 4;
			img[i][j + 4] = (img[i - 1][j + 4] + img[i + 1][j + 4] + img[i][j + 1 + 4] + img[i][j - 1 + 4]) / 4;
			img[i][j + 6] = (img[i - 1][j + 6] + img[i + 1][j + 6] + img[i][j + 1 + 6] + img[i][j - 1 + 6]) / 4;
			img[i][j + 8] = (img[i - 1][j + 8] + img[i + 1][j + 8] + img[i][j + 1 + 8] + img[i][j - 1 + 8]) / 4;
			img[i][j + 10] = (img[i - 1][j + 10] + img[i + 1][j + 10] + img[i][j + 1 + 10] + img[i][j - 1 + 10]) / 4;
			img[i][j + 12] = (img[i - 1][j + 12] + img[i + 1][j + 12] + img[i][j + 1 + 12] + img[i][j - 1 + 12]) / 4;
		}
	}
} 
void Func5()
{
	register int i, j;
	register int i_, j_;
	register int i__, j__;
	int block = 8;// 8 * 8 = 64 = cache line
	for(i = 1; i < HEIGHT - 1; i += block)
	{
		for(j = 1; j < WIDTH - 1; j += block)
		{
			i__ = minn(HEIGHT - 1, i + block);
			j__ = minn(WIDTH - 1, j + block);
			
			for(i_ = i; i_ < i__; i_ ++)
			{
				for(j_ = j; j_ < j__; j_ ++)
				{
					img[i_][j_] = (img[i_][j_ - 1] + img[i_][j_ + 1] + img[i_ - 1][j_] + img[i_ + 1][j_]) / 4;
				}
			}
		}
	}
} 

int minn(int x, int y)
{
	if(x >= y)
	{
		return y;
	}else
	{
		return x;
	}
}
