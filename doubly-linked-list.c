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

/* 필요한 헤더파일 추가 if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
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
		printf("[-------------------- [이찬희] [2019068057] --------------------]\n");
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
    
    //헤드노드가 비어있지 않다면 비운다
    if(*h != NULL) {
        freeList(*h);
    }

    *h = (headNode*)malloc(sizeof(headNode));  //헤드노드 메모리 할당
    (*h)->first = NULL;  //헤드노드가 가리키는 첫번째 노드 비우기

	return 1;
}

int freeList(headNode* h){  //모든 노드를 날리는것

    listNode* p = h->first;  //첫번째 노드 p
    listNode* prev = NULL;  //이전 노드
    while(p != NULL) {  //p가 NULL이 아닐때까지 (끝까지)
        prev = p;  //현재 노드 p를 이전 노드로 이동
        p = p->rlink;  //현재 노드 p를 p의 rlink를 타고 다음 노드로 이동
        free(prev);  //현재 노드였던 p에 할당되었던 메모리 반환
    }

    free(h);  //헤드 노드 메모리 반환
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* this = (listNode*)malloc(sizeof(listNode));  //현재 노드 this 선언 및 메모리 할당
	this->key = key;
	this->llink = NULL;
	this->rlink = NULL;

	if(h->first == NULL) {  //노드가 없었다면 첫번째 노드로 설정
		h->first = this;
		return 0;
	}

	listNode* now = h->first;  //now 노드를 처음부터 끝까지 이동
	while(now->rlink != NULL) {
		now = now->rlink;
	}

	now->rlink = this;  //마지막 노드의 rlink를 추가할 노드를 가리키게 설정
	this->llink = now;  //추가할 노드의 llink를 마지막 노드였던 것을 가리키게 설정

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if(h->first == NULL) {  //노드가 없다면 오류 메시지 출력
		printf("nothing to delete");
		return 0;
	}

	listNode* now = h->first;  //리스트의 처음부터 마지막까지 이동할 노드
	listNode* prev;  //그 이전 노드

	while(now->rlink != NULL) {  //마지막 노드에 도달할때까지 prev와 now 노드를 이동
		prev = now;
		now = now->rlink;
	}

	prev->rlink = NULL;  //이전 노드의 rlink를 NULL로 끊어버리고 now 노드 메모리 반환
	free(now);

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* first = (listNode*)malloc(sizeof(listNode));  //첫번째가 될 first 노드 선언 및 메모리 할당
	first->key = key;
	first->llink = NULL;
	first->rlink = NULL;

	if(h->first == NULL) {  //리스트가 비어있었으면 그대로 첫번째 노드로
		h->first = first;
		return 0;
	}

	listNode* second = h->first;  //두번째가 될 첫번째 노드였던것 second
	second->llink = first;  //두번째 노드의 llink를 first로
	first->rlink = second;  //first노드의 rlink를 second로
	h->first = first;  //first 노드를 첫번째 노드로 가리키게 설정

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if(h->first == NULL) {  //리스트가 비어있으면 오류 메시지 출력
		printf("nothing to delete");
		return 0;
	}

	listNode* first = h->first;  //첫번째 노드
	h->first = first->rlink;  //첫번째 노드의 rlink가 가리키는 두번째 노드를 첫번째 노드로 가리키게 설정
	free(first);  //첫번쨰 노드 메모리 반환

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 1;
}