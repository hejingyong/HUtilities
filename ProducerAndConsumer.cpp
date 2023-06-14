/****    Synchronous同步机构   ****/
/* 用PV操作解决生产者----消费者问题模拟程序 */
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int pc, in, out, s1, s2, r, ps, vs;
int pv[2] = { 0,5 };  /* pv[0]:生产者进程指针 pv[1]:消费者进程指针 */
char x[6], c[6], b[6] = { "     " };
struct ppcb   /* process control block */
{
	char name[10];
	char status[8];
	char cause[4];
	int trap;
}pcb[2] = { {"producer","Ready","s1",0},{"Consumer","Ready","s2",5} };

int p(int s)   /*P primity s:semaphore  */
{
	s = s - 1;
	ps = s;
	if (s < 0) strcpy(pcb[r].status, "Wait");
	return(ps);
}

int v(int s)   /*V primity s:semaphore  */
{
	s = s + 1;
	vs = s;
	if (s <= 0) { strcpy(pcb[(1 + r) % 2].status, "Ready"); pv[(1 + r) % 2]++; }
	return(vs);
}

void EXECUTE()   /* 处理机执行指令子程序 */
{
	if (r == 0) pc = pv[0]; else pc = pv[1]; /* 随机选择一条指令 */
	strcpy(pcb[r].status, "Ready");   /* 置现行进程为就绪 */
	switch (pc) {
		/***  process producer ***/
	case 0: b[in] = c[in]; pv[0]++; break;    /* 生产者生产一件产品 */
	case 1: p(s1); s1 = ps; if (s1 >= 0)pv[0]++; break;  /* 生产者执行P操作 */
	case 2: printf("product'%c'==>Buffer", b[in]); /* 一件产品送缓冲区 */
		printf("\t    --- wait ---\n\n"); pv[0]++; break;
	case 3: v(s2); s2 = vs; pv[0]++; break; /* 生产者执行V操作 */
	case 4: in = (in + 1) % 6; pv[0] = 0; break; /* 调整缓冲区，GOTO返回 */
	 /***  process consumer ***/
	case 5: p(s2); s2 = ps; if (s2 >= 0) pv[1]++; break;/* 消费者执行P操作 */
	case 6: x[out] = b[out];  /* 从缓冲区取一件产品 */
		printf("  --- wait ---\t\t");
		printf("consume product '%c'\n\n", x[out]);
		pv[1]++; break;
	case 7: v(s1); s1 = vs; pv[1]++; break;  /* 消费者执行V操作 */
	case 8: pv[1]++; break;   /* 消费者消费产品 */
	case 9: b[out] = ' '; out = (out + 1) % 6; pv[1] = 5; break;/* 调整缓冲区，GOTO返回 */
	default: printf("ERROR!");
	}
}

int main()  /*主程序*/
{ /* 初始化子程序 */
	s1 = 5; s2 = 1;    /* 信号量初值*/
	in = 0; out = 0;
	printf("Input products:"); scanf("%s", c); /* 输入产品 */
	srand((int)time(0));

	/* 处理机调度子程序 */
	printf("\n\n  ***Producer***\t  ***Consumer***\n\n");
	while (1)
	{
		pv[0] = pcb[0].trap; pv[1] = pcb[1].trap;  /* 恢复现场 */
		if (strcmp(pcb[0].status, "Ready") == 0)  /* 随机选择就绪进程 */
			if (strcmp(pcb[1].status, "Ready") != 0) r = 0;
			else r = rand() % 2;
		else if (strcmp(pcb[1].status, "Ready") == 0) r = 1;
		else break;
		strcpy(pcb[r].status, "Run");/* 置现行进程为执行 */
		EXECUTE();                 /* 调用执行指令子程序 */
		pcb[0].trap = pv[0]; pcb[1].trap = pv[1]; /* 保护现场 */
		if (b[in] == '\0') strcpy(pcb[0].status, "Finish"); /* 置生产者进程为完成 */
		if (strlen(x) == strlen(b)) strcpy(pcb[1].status, "Finish");  /* 置消费者进程为完成 */
	}
	system("Pause");
}
