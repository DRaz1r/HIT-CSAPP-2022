#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define HEIGHT 1080
#define WIDTH 1920

long img[HEIGHT][WIDTH];

void Init();
void Test(void (*function)());

void Func5();			//cacheline分块优化 	
void Func6(); 			//cacheline + 多进程优化 
int minn(int x, int y);
int main()
{
	Init();
	

	Test(Func5);
	Test(Func6);
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
	clock_t t1 = clock();
	int t = 100;
	while(t--) 
	{
		function();
	}
	clock_t t2 = clock();
	printf("COST %ldms\n",(t2 - t1) * 1000 / CLOCKS_PER_SEC);
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

void Func6()
{
	register int i, j;
	register int i_, j_;
	register int i__, j__;
	int block = 8;
 	int id = fork();
 	 
	if(id == 0) 
	{
		for(i = 1; i < HEIGHT / 2; i += block) 
		{
			for(j = 1; j < WIDTH - 1; j += block) 
			{
			
				i__ = minn(HEIGHT / 2, i + block);
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
		exit(0);
	}
	else 
	{
		for(i = HEIGHT / 2; i < HEIGHT - 1; i += block) 
		{
			for(j = 1; j < WIDTH - 1; j += block) 
			{
				i__ = minn(HEIGHT - 1, i + block);
				j__	= minn(WIDTH - 1, j + block);
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


}
