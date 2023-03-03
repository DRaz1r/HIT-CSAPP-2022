#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define PTHREAD_NUM 6//线程总数
#define RECNUM 100 
 
typedef struct 
{
    int l;
    int r;
}PTH_ARGV;//线程参数结构体


typedef struct 
{
    int a;
}PTH_RETURN;//线程返回值结构体


#define HEIGHT 1080
#define WIDTH 1920

long img[HEIGHT][WIDTH];
int maxn(int x, int y)
{
	if(x >= y)
	{
		return x;
	}else
	{
		return y;
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
 
void *func(void *argv)//线程函数体
{
    PTH_ARGV *pth_argv;
    PTH_RETURN *pth_return = malloc(sizeof(PTH_RETURN));//为返回值申请空间
    pth_argv = (PTH_ARGV*)argv;//将参数强转为参数结构体
 
    {//线程要做的事情
        register int i, j;
		register int i_, j_;
		register int i__, j__;
		int block = 8;// 8 * 8 = 64 = cache line
		for(i = pth_argv->l; i < pth_argv->r; i += block)
		{
			for(j = 1; j < WIDTH - 1; j += block)
			{
				i__ = minn(pth_argv->r, i + block);
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
 
    free(argv);//释放线程参数空间
    /*
    void pthread_exit(void *retval);
    描述：线程终止；类似于exit，exit是进程终止，两者差距在于结束的对象不同。
    参数：
    retval -- 要带回的值,可以为NULL，如果为NULL，则不需要线程返回值结构体，母线程也不会收到子线程的返回值
    */
    pthread_exit(pth_return);//线程结束，返回母线程需要的返回值，
}

int main()
{
    pthread_t pd[PTHREAD_NUM];//pid
    PTH_ARGV *pth_argv;//线程参数
    //PTH_RETURN *pth_return;//线程返回值
    
    int cnt = RECNUM;
    clock_t t1, t2;
	t1 = clock(); 
    while(cnt --)
    {
    	int i;
    	
    	for(i = 0;i < PTHREAD_NUM;i ++)
    	{
     	   //为线程参数申请空间（注：为什么要申请空间？因为不申请空间，所有线程公用同意参数空间，很可能发生线程间的抢占效果），此函数需要由子线程释放掉
       
	   
	   
	   	
	   		pth_argv = malloc(sizeof(PTH_ARGV));
      	  	{//对线程参数结构体进行初始化
            	pth_argv->l = maxn(1, i * HEIGHT / PTHREAD_NUM);
            	pth_argv->r = minn(HEIGHT - 1, (i + 1) * HEIGHT / PTHREAD_NUM);
        	}
        	/*
        int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
        
        描述：创建一个线程。
        返回值：成功返回0，失败返回一个错误编号。
        参数：
        thread -- 回填创建的线程的PID。
        attr -- 特殊要求。默认为NULL.
        start_routine --  被创建的线程所执行的函数。
                void *(*start_routine) (void *)
        arg -- start_routine函数的传参。
        */
        	pthread_create(pd + i,NULL,func,pth_argv);//创建线程
    	}
 
    	for(i = 0;i<PTHREAD_NUM;i++)
    	{
 
			/*
			int pthread_join(pthread_t thread, void **retval);
			描述：给线程号为thread的线程收尸(线程结束后会变成僵尸线程（不占用空间，但占用线程号），父线程需要等待子线程结束，然后释放掉线程的线程号），
			一般是谁创建谁收尸（不是铁律，线程之间平等），可以起到阻塞非盲等的状态。
			返回值：成功时返回 0；出错时，它返回一个错误编号。
			参数：
			thread -- 线程ID
			retval -- 回填PID为thread的线程的的返回值，可以为NULL，为NULL时，父线程将不在接收到子线程回传的返回值。
			*/
			//pthread_join(pd[i],(void **)&pth_return);//等待线程结束
			pthread_join(pd[i],NULL);//等待线程结束
			//free(pth_return);//释放掉线程返回值结构体
    	}
	}
    
    t2 = clock();

    
    printf("COST %ldms\n",(t2 - t1) * 1000 / CLOCKS_PER_SEC);
    return 0;
}
