/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ���� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
        - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("[-------------------- [������] [2019068057] --------------------]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
    
    //����尡 ������� �ʴٸ� ����
    if(*h != NULL) {
        freeList(*h);
    }

    *h = (headNode*)malloc(sizeof(headNode));  //����� �޸� �Ҵ�
    (*h)->first = NULL;  //����尡 ����Ű�� ù��° ��� ����

	return 1;
}

int freeList(headNode* h){  //��� ��带 �����°�

    listNode* p = h->first;  //ù��° ��� p
    listNode* prev = NULL;  //���� ���
    while(p != NULL) {  //p�� NULL�� �ƴҶ����� (������)
        prev = p;  //���� ��� p�� ���� ���� �̵�
        p = p->rlink;  //���� ��� p�� p�� rlink�� Ÿ�� ���� ���� �̵�
        free(prev);  //���� ��忴�� p�� �Ҵ�Ǿ��� �޸� ��ȯ
    }

    free(h);  //��� ��� �޸� ��ȯ
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* this = (listNode*)malloc(sizeof(listNode));  //���� ��� this ���� �� �޸� �Ҵ�
	this->key = key;
	this->llink = NULL;
	this->rlink = NULL;

	if(h->first == NULL) {  //��尡 �����ٸ� ù��° ���� ����
		h->first = this;
		return 0;
	}

	listNode* now = h->first;  //now ��带 ó������ ������ �̵�
	while(now->rlink != NULL) {
		now = now->rlink;
	}

	now->rlink = this;  //������ ����� rlink�� �߰��� ��带 ����Ű�� ����
	this->llink = now;  //�߰��� ����� llink�� ������ ��忴�� ���� ����Ű�� ����

	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if(h->first == NULL) {  //��尡 ���ٸ� ���� �޽��� ���
		printf("nothing to delete");
		return 0;
	}

	listNode* now = h->first;  //����Ʈ�� ó������ ���������� �̵��� ���
	listNode* prev;  //�� ���� ���

	while(now->rlink != NULL) {  //������ ��忡 �����Ҷ����� prev�� now ��带 �̵�
		prev = now;
		now = now->rlink;
	}

	prev->rlink = NULL;  //���� ����� rlink�� NULL�� ��������� now ��� �޸� ��ȯ
	free(now);

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* first = (listNode*)malloc(sizeof(listNode));  //ù��°�� �� first ��� ���� �� �޸� �Ҵ�
	first->key = key;
	first->llink = NULL;
	first->rlink = NULL;

	if(h->first == NULL) {  //����Ʈ�� ����־����� �״�� ù��° ����
		h->first = first;
		return 0;
	}

	listNode* second = h->first;  //�ι�°�� �� ù��° ��忴���� second
	second->llink = first;  //�ι�° ����� llink�� first��
	first->rlink = second;  //first����� rlink�� second��
	h->first = first;  //first ��带 ù��° ���� ����Ű�� ����

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if(h->first == NULL) {  //����Ʈ�� ��������� ���� �޽��� ���
		printf("nothing to delete");
		return 0;
	}

	listNode* first = h->first;  //ù��° ���
	h->first = first->rlink;  //ù��° ����� rlink�� ����Ű�� �ι�° ��带 ù��° ���� ����Ű�� ����
	free(first);  //ù���� ��� �޸� ��ȯ

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	if(h->first == NULL) {  //����Ʈ�� ��������� ���� �޽��� ���
	printf("nothing to invert");
	return 0;
	}

	listNode* now = h->first;  //���� ���
	listNode* prev = NULL;  //���� ���
	listNode* mid = NULL;  //�߰� ���

	while(now != NULL) {
		prev = mid;  //���� ��带 �ӽ� ����
		mid = now;  //�ӽ� ��带 ���� ����
		now = now->rlink;  //���� ���� �̵�
		mid->rlink = prev;  //�ӽ� ���(���� ��忴�� ��)�� rlink�� ���� ����
		mid->llink = now;  //�ӽ� ����� llink�� ���� ����
	}

	h->first = mid;  //����尡 ����Ű�� ù��° ��带 mid ���� ����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* add = (listNode*)malloc(sizeof(listNode));  //�߰��� ��� add ���� �� �޸� �Ҵ�
	add->key = key;
	add->llink = NULL;
	add->rlink = NULL;

	if(h->first == NULL) {  //����Ʈ�� ��������� ù��° ���� ����
		h->first = add;
		return 0;
	}

	listNode* now = h->first;  //ó������ ���������� Ÿ�� ������ ��� now
	listNode* next = h->first;  //now ����� ���� ��尡 �� ��� next

	while(now != NULL) {  //now�� ������ ��尡 �ɶ�����
		if(add->key >= now->key) {  //���� add�� key�� ũ�ų� ���ٸ� (now�� ���� ��尡 �Ǿ��Ѵٸ�)
			next = now->rlink;  //���� ����� rlink�� ���� ��带 ����Ű�� ����
			now->rlink = add;  //���� ����� rlink�� �߰��� ���� ����
			add->llink = now;  //�߰��� ����� llink�� ���� ���� ����
			add->rlink = next;  //�߰��� ����� rlink�� ���� ���� ����

			return 0;
		}

		now = now->rlink;  //add�� key�� ������ ���� ���� �̵�
	}

	add->llink = now;  //now�� ������ ������ ������ add�� now �ڿ� �߰�
	now->rlink = add;

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if(h->first == NULL) {  //����Ʈ�� ��������� ���� �޽��� ���
	printf("nothing to delete");
	return 1;
	}

	listNode* now = h->first;  //����Ʈ�� ó������ ������ �� now ���
	while(now != NULL) {  //now�� ������ ��尡 �ɶ�����
		if(now->key == key) {  //������� key�� ������
			if(now->llink == NULL) {  //���� ��尡 ù��° �����
				deleteFirst(h);
			}
			else if(now->rlink == NULL) {  //���� ��尡 ������ �����
				deleteLast(h);
			}
			else{
				now->llink->rlink = now->rlink;  //���� ����� ���� ����� rlink�� ���� ����� ���� ����
				now->rlink->llink = now->llink;  //���� ����� ���� ����� llink�� ���� ����� ���� ����
				free(now);
				}  //���� ��� �޸� ��ȯ
			return 1;
		}

		now = now->rlink;
	}

	printf("no node that have typed key");  //key ���� ���� ��尡 ������ ���� �޽���
	return 1;
}