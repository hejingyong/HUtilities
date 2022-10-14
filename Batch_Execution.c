#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    int i = 0;
    char a[100] = {0};
 
    for(i = 0; i < 804; i++)
    {
        sprintf(a, "upx -d %d.exe", i);
        system(a);
    }
 
    return 0;
}