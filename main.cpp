#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "handler.h"

typedef void (*FunctionHandler)(void);

typedef struct _FunctionEntry
{
	char * declaration;
	FunctionHandler handler;
} FunctionEntry;

FunctionEntry * pEntrys = NULL;
const int count = 23;

// �ڴ���亯��
// ��ʵ�Ƕ� calloc �ķ�װ
// ֮����Ҫ�ٷ�װ������ calloc �Ļ����϶������ڴ����ʧ��ʱ�Ĵ������
// ����ڴ治�㣬���̽������򣬲��ټ���ִ��
// ���ǱȽϴֲڵĴ����ַ������ǿ��Ա�֤�����ٷ���������������
// �ڱ���Ŀ�в��漰�û����ݵı��棬��˴ֱ��Ľ�������
// ������������ݶ�ʧ������
void * memoryAllocate(size_t size)
{
	void * p = calloc(1, size);
	if (p == NULL)
	{
		// ����ڴ治�㣬���̽������򣬲��ټ���ִ��
		// �ȽϴֲڵĴ����ַ������ǿ��Ա�֤�����ٷ���������������
		// �ڱ���Ŀ�в��漰�û����ݵı��棬��˴ֱ��Ľ�������
		// ������������ݶ�ʧ������
		puts("allocate memory failed!\n");
		exit(0);
	}
	else
	{
		return p;
	}
}

void setEntry(FunctionEntry * pEntry, char * declaration, FunctionHandler handler)
{
	// �����������������������Ϊ��
	assert(pEntry);
	assert(declaration);
	assert(handler);

	// ��� pEntry �� declaration Ŀǰ�������ݵģ��Ƚ�������ɾ��
	// Ȼ�����滻Ϊ������ ���漰�ڴ���ͷ����ٷ��䣩
	if (pEntry->declaration != NULL)
	{
		free(pEntry->declaration);
		pEntry->declaration = NULL;
	}

	pEntry->declaration = (char *)memoryAllocate(strlen(declaration) + 1);
	strcpy(pEntry->declaration, declaration);

	// ����ָ�������ͷţ����������������ֵ������ֵ
	// ֱ������Ϊ�µ�ֵ����
	pEntry->handler = handler;
}

void createEntry(int index, char * declaration, FunctionHandler handler)
{
	assert(index < count);
	assert(declaration);
	assert(handler);
	setEntry(&pEntrys[index], declaration, handler);
}

void initEntrys()
{
	pEntrys = (FunctionEntry *)memoryAllocate(sizeof(FunctionEntry) * count);
	createEntry(0, "double acos(double x)", acos_handler);

	createEntry(1, "double asinl(double x)", asinl_handler);
	createEntry(2, "double atanl(double x)", atanl_handler);
	createEntry(3, "double cosl(double x)", cosl_handler);
	createEntry(4, "double sinl(double x)", sinl_handler);
	createEntry(5, "double tanl(double x)", tanl_handler);
	createEntry(6, "double coshl(double x)", coshl_handler);
	createEntry(7, "double sinh(double x)", sinhl_handler);
	createEntry(8, "double tanh(double x)", tanhl_handler);
	createEntry(9, "double atan2l(double x, double y)", atan2l_handler);
	createEntry(10, "double fabsl(double x)", fabsl_handler);

	createEntry(12, "double ceill(double x)", ceill_handler);
	createEntry(13, "double floorl(double x)", floorl_handler);
	createEntry(14, "double expl(double x)", expl_handler);
	createEntry(15, "double fmodl(double x, double y)", fmodl_handler);
	//createEntry(16, "double frexpl(double x, int *exp)", frexpl_handler);
	//createEntry(17, "double hpyotl(double x, double y)", hypotl_handler);
	createEntry(18, "double ldexpl(double x, int exp)", ldexpl_handler);
	createEntry(19, "double logl(double x)", logl_handler);
	createEntry(20, "double log10l(double x)", log10l_handler);
	createEntry(22, "double powl(double x, double y)", powl_handler);
	createEntry(11, "double sqrtl(double x)", sqrtl_handler);
}

void showEntrys()
{
	assert(pEntrys);
	for (int i = 0; i < count; i++)
	{
		printf("%d %s\n", i, pEntrys[i].declaration);
	}
}

void begin()
{
	do 
	{
		puts("function list:");
		showEntrys();
		printf("select (-1 for quit): ");
		int i = -1;
		int ret = scanf("%d", &i);
		if (ret != 0)
		{
			if (i == -1)
			{
				break;
			}
			else if (i > -1 && i < count)
			{
				pEntrys[i].handler();
			}
			else
			{
				printf("index out of range [%d, %d]\n", 0, count - 1);
			}
		}
		else
		{
			printf("please input number\n");
		}
	} while (true);
}

int main()
{
	initEntrys();
	begin();
	return 0;
}