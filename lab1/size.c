#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size;
    
    size = sizeof(char);
    printf("char size: %d\n",size);
    
    size = sizeof(short);
    printf("short size: %d\n",size);
    
    size = sizeof(int);
    printf("int size: %d\n",size);
    
    size = sizeof(long);
    printf("long size: %d\n",size);
    
    size = sizeof(long long);
    printf("long long size: %d\n",size);
    
    size = sizeof(float);
    printf("float size: %d\n",size);
    
    size = sizeof(double);
    printf("double size: %d\n",size);
    
    size = sizeof(long double);
    printf("long double size: %d\n",size);
    
    size = sizeof(void*);
    printf("void* size: %d\n",size);
    
    return 0;
}
