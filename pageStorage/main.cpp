
/*
���ݽṹ
	ҳ��ṹ	struct Page
	ָ��ṹ
����
	ҳ��С	PAGESIZE
	�������ҳ��		MAX_PAGE
	�������ҳ��		MAX_MEMPAGE
	������ֵ	MAX

	����ҳ��		Page memPageTab[MAX_Page]
	�������ҳ��ѭ������	size_t memPageNum[MAX_PAGE]
	ȱҳ�±�		size_t k
	ָ������	
����
	��ʼ�������ڴ�ҳ
	����ָ���±�ȡָ���ָ��


*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PAGESIZE	4096	//ҳ���С
#define MAX_PAGE	7		//���ҳ��
#define MAX_MEMPAGE	4		//�������ҳ��
#define INF			99		//�����,���������ҳ�ܺ�
#define MAX_INSTCT	12		//���ָ����

struct Page
{
	int		pageId;			//ҳ��
	bool	estFlg;			//�Ƿ�������
	int		mainId;			//ҳ�ܺţ��趨ҳ���������λ��
	bool	chFlg;			//�޸ı�־���趨ҳ�����������Ƿ��޸Ĺ�
	int		dskIndex;		//������λ�ã��趨ҳ���ڸ����е�λ��
};

struct  Instct
{
	char	op;			//����
	int		pageId;		//ҳ��
	int		pageAddr;	//ҳ�ڵ�ַ
};

void init(Page* memPageTab, int* memPageId, Instct* instct);
void inOutMen(int k, Instct* tmpInstct, Page* pageTab, int* memPageId);

int main()
{
	Page	pageTab[MAX_PAGE];		//����ҳ��ҳ��
	Instct	instct[MAX_INSTCT];		//����ָ��

	int		k = 0;					//ѭ������β
	int		memPageId[MAX_MEMPAGE];	//������ҳ��,ѭ������
	Instct*	tmpInstct=NULL;
	int		absAddr = 0;
	//��ʼ��
	init(pageTab, memPageId, instct);
	//��ѭ���ظ�ȡָ��, iΪָ���±�
	for (int i = 0; i < MAX_INSTCT; ++i)
	{
		//ȡָ��� 
		tmpInstct = &instct[i];
		assert(tmpInstct->op);	//ָ�������Ϊ�ռ���
		printf("%d.ִ��[%c]ָ��\t", i,tmpInstct->op);
		//�����Ƿ����������������
		if (pageTab[tmpInstct->pageId].estFlg)
			absAddr = pageTab[tmpInstct->pageId].mainId*PAGESIZE + tmpInstct->pageAddr;
		else //�����ڴ���
		{
			printf("[*] ҳ��Ϊ %d �����ڴ�\n", tmpInstct->pageId);
			printf("\tҳ��Ϊ %d ���ڴ�\t", memPageId[k]);
			//��β�±�k,ָ��tmpInstct,ҳ��pageTab,���ڵ�ҳID memPageId
			inOutMen(k, tmpInstct, pageTab, memPageId);
			absAddr = pageTab[tmpInstct->pageId].mainId*PAGESIZE + tmpInstct->pageAddr;
		}

		if (tmpInstct->op == 'i')//ָ��Ϊ��ʱ���޸�chFlgΪ1
			pageTab[tmpInstct->pageId].chFlg = 1;
		printf("���Ե�ַΪ:%d\n", absAddr);
		if (i == MAX_INSTCT - 1)
			printf("����ָ��ִ�����!\n");
	}
	system("pause");
	return 0;
}

//��ʼ������ҳ���ָ��
void init(Page* memPageTab, int* memPageId, Instct* instct)
{
	//��ʼ������ҳ��
	int		pageId_t[MAX_PAGE] = { 0, 1, 2, 3, 4, 5, 6 };
	bool	estFlg[MAX_PAGE] = { 1, 1, 1, 1, 0, 0, 0 };
	int		mainId[MAX_PAGE] = { 5, 8, 9, 1, INF, INF, INF };//MAX��ʾ�����в�����
	bool	chFlg[MAX_PAGE] = { 0 };
	int		dskIndex[MAX_PAGE] = { 11, 12, 13, 21, 22, 23, 121 };

	for (int i = 0; i < MAX_PAGE; ++i)
	{
		memPageTab[i].chFlg = chFlg[i];
		memPageTab[i].dskIndex = dskIndex[i];
		memPageTab[i].estFlg = estFlg[i];
		memPageTab[i].mainId = mainId[i];
		memPageTab[i].pageId = pageId_t[i];
		if (i < 4)	//ҳ�ܺž��������д��ڵ�ҳID
			memPageId[i] = memPageTab[i].pageId;	//��ʼ�����ڴ��ҳID
	}

	//��ʼ������ָ��iΪ����, oΪ����
	char op[MAX_INSTCT] = { '+', '-', '*', 'i', 'o', '-', 'm', '+', 'i', 'o', '+', 'i' };
	int pageId_i[MAX_INSTCT] = { 0, 1, 2, 3, 0, 6, 4, 5, 1, 2, 4, 6 };
	int	pageAddr[MAX_INSTCT] = { 70, 50, 15, 21, 56, 40, 53, 23, 37, 78, 1, 84 };

	for (int i = 0; i < MAX_INSTCT; ++i)
	{
		instct[i].op = op[i];
		instct[i].pageAddr = pageAddr[i];
		instct[i].pageId = pageId_i[i];
	}
	printf("��ʼ�����!\n");
}

//��β�±�k,��ǰָ��,ҳ��pageTab,���ڵ�ҳID memPageId
void inOutMen(int k, Instct* tmpInstct, Page* pageTab, int* memPageId)
{
	pageTab[memPageId[k]].estFlg = 0;//�����ϵĴ��ڱ���0
	memPageId[k] = tmpInstct->pageId;//������ҳID
	k = (k + 1) % MAX_MEMPAGE;//�ƶ�ѭ������ָ��
	pageTab[tmpInstct->pageId].estFlg = 1;//������Ĵ��ڱ���1
	//�������,�����ҳ�ܺ�Ϊ����λ��
	pageTab[tmpInstct->pageId].mainId = pageTab[tmpInstct->pageId].dskIndex;
	printf("\tҳ��Ϊ %d ���ڴ�\t", tmpInstct->pageId);
}


//����ҳ����ҳ������Ƿ�����ڴ�(����ҳ��,�ڴ�ҳid��)
bool isEstMem(int pageId, int* memId)
{
	bool flg = 0;
	for (int i = 0; i < MAX_MEMPAGE; ++i)
	{
		if (memId[i] == pageId)
		{
			flg = 1;
			break;
		}
	}
	return flg;
}

//��������IDҳ��,����ҳ��, ����ҳ�Ŷ�Ӧҳ��
int findMainId(int pageId, Page* memPageTab)
{
	int mainId = 0;
	int i = 0;
	for (i = 0; i < MAX_PAGE; ++i)
	{	//����ҳ��,��ҳ�����Ӧ��pageIdʱ,��ֵ
		if (memPageTab[i].estFlg && memPageTab[i].pageId == pageId)
		{
			mainId = memPageTab[i].mainId;
			break;
		}
	}
	if (i == MAX_PAGE)	//�ҵ����Ҳû���ҵ�,��������
		printf("findMainId error!\n");
	return mainId;
}

//�����Ƴ�����(�ڴ������ϵ�ҳ��,ȱҳ��ҳ��,����ID����)
//insertMainMem(oldPageId, tmpInstct->pageId, memPageId);
