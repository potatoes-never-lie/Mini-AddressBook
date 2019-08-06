#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct person{
	char name[20];
	char address[100];
	char phone[20];
	struct person *next;
} Person;

void DataLoad(Person **);
int menu(void);
void allPrint(Person **);
void swap(char *, char *);
void AddMember(Person **);
void SearchMember(Person **);
void ModifyMember(Person **);
void DeleteMember(Person **);
void SaveTxt(Person **);
void ClearBuffer(void);
void justPrint(void);

int main(void){
	int button, end=0;
	Person *head=(Person *)malloc(sizeof(Person));
	head=NULL;
	DataLoad(&head);
	button=menu();
	justPrint();
	while(1){
		switch(button)
		{
			case 1:
				allPrint(&head);
				break;
			case 2:
				AddMember(&head);
				break;
			case 3:
				SearchMember(&head);
				break;
			case 4:
				ModifyMember(&head);
				break;
			case 5:
				DeleteMember(&head);
				break;
			case 6:
				SaveTxt(&head);
				end=1;
				break;
			default:
				break;
		}
		if (end==1)
			break;
		justPrint();
		printf("선택할 기능을 입력하세요 : ");
		scanf("%d",&button);
		ClearBuffer();
		justPrint();
	} 
	return 0;
}

void ClearBuffer(void){
	while ((getchar())!='\n');
}

void DataLoad(Person **head){
	FILE *fp=fopen("스플럭 명단관리.txt", "r");
	if (fp==NULL)
		printf("파일 오픈 실패\n");
	else{
		Person *prev, *p, *next;
		while (feof(fp)==0){
			p=(Person *)malloc(sizeof(Person));
			fscanf(fp,"%[^|]|%[^|]|%[^\n]\n",p->name,p->address,p->phone);
			if ((*head)==NULL)
				(*head)=p;
			else
				prev->next=p;
			p->next=NULL;
			prev=p;
		}
	}
	fclose(fp);
	printf("\n");
}

int menu(void){
	int button;
	printf("                      =메뉴=                      \n");
	printf("1. 모든 주소록 정보 출력\n");
	printf("2. 회원 등록\n");
	printf("3. 회원 정보 검색\n");
	printf("4. 회원 정보 수정\n");
	printf("5. 회원 삭제\n");
	printf("6. 프로그램 종료\n\n");
	justPrint();
	printf("선택할 기능을 입력하세요: ");
	scanf("%d",&button);
	ClearBuffer();
	return button;
}

void allPrint(Person **head){			
	Person *p=(*head);
	Person *copyHead=NULL;
	Person *cprev, *cp, *cnext;
	Person *temp;
	int count=1;
	while (p!=NULL){
		cp=(Person *)malloc(sizeof(Person));
		strcpy(cp->name,p->name); strcpy(cp->address,p->address); strcpy(cp->phone,p->phone); 
		if (copyHead==NULL)
			copyHead=cp;
		else
			cprev->next=cp;
		cp->next=NULL;
		cprev=cp;
		p=p->next;
	}
	for (cp=copyHead;cp->next!=NULL;cp=cp->next){
		for (temp=cp->next;temp!=NULL;temp=temp->next){
			if (strcmp(cp->name,temp->name)>0){
				swap(cp->name,temp->name);
				swap(cp->address,temp->address);
				swap(cp->phone,temp->phone);
			}
		}
	}	
	cp=copyHead;
	while (cp!=NULL){	
		printf("#%d\n",count++);	
		printf("이름: %s\n주소: %s\n전화번호: %s\n",cp->name,cp->address,cp->phone);
		if (cp->next!=NULL)
			justPrint();
		temp=cp;
		cp=cp->next;
		free(temp);
	}
}

void swap(char *p, char *q){
	char temp[100];
	strcpy(temp,p);
	strcpy(p,q);
	strcpy(q,temp);
}

void AddMember(Person **head){
	char buffer[100]={0};
	Person *test;
	Person *p=(*head);
	Person *new=(Person *)malloc(sizeof(Person));
	while ((p->next)!=NULL){
		p=p->next;
	}
	new->next=p->next;
	p->next=new; 
	printf("이름 : "); scanf("%[^\n]",buffer); ClearBuffer(); strcpy(new->name,buffer);
	printf("주소 : "); scanf("%[^\n]",buffer);  ClearBuffer(); strcpy(new->address,buffer);
	printf("전화번호 : "); scanf("%[^\n]",buffer); ClearBuffer(); strcpy(new->phone,buffer);
	printf("\n추가되었습니다.\n");
}

void SearchMember(Person **head){
	char search[100];
	int button,check=0,end=0;
	Person *p=(*head);
	while(1){
		printf("1. 이름으로 검색\n"); printf("2. 주소로 검색\n"); printf("3. 전화번호로 검색\n");
		justPrint();
		printf("선택할 기능을 입력하세요: ");
		scanf("%d",&button); ClearBuffer();
		justPrint();
		switch(button){
			case 1:
				printf("찾으실 회원의 이름을 입력하세요 : ");
				scanf("%[^\n]",search); ClearBuffer();
				while (p!=NULL){
					if (strstr(p->name, search)!=NULL){
						printf("\n이름 : %s\n",p->name); printf("주소 : %s\n",p->address); printf("전화번호 : %s\n",p->phone);
						check=1;
					}
					p=p->next;
				}
				end=1;
				break;
			case 2:
				printf("찾으실 회원의 주소를 입력하세요 : ");
				scanf("%[^\n]",search); ClearBuffer();
				while (p!=NULL){
					if (strstr(p->address, search)!=NULL){
						printf("\n이름 : %s\n",p->name); printf("주소 : %s\n",p->address); printf("전화번호 : %s\n",p->phone);
						check=1;
					}
					p=p->next;
				}
				end=1;
				break;
			case 3:
				printf("찾으실 회원의 전화번호를 입력하세요 : ");
				scanf("%[^\n]",search); ClearBuffer();
				while (p!=NULL){
					if (strstr(p->phone, search)!=NULL){
						printf("\n이름 : %s\n",p->name); printf("주소 : %s\n",p->address); printf("전화번호 : %s\n",p->phone);
						check=1;
					}
					p=p->next;
				}
				end=1;
				break;
			default:
				break;
		}
		if (end==1)
			break;
	}
	if (check==0)
		printf("\n회원이 존재하지 않습니다.\n");
}

void ModifyMember(Person **head){
	char search[100]; char b_name[20]={0}; char b_address[100]={0}; char b_phone[20]={0};
	char check=0;
	Person *p=(*head);	
	printf("수정할 회원의 이름을 입력하세요 : ");
	scanf("%[^\n]",search); ClearBuffer();
	while (p!=NULL){
		if (strstr(p->name,search)!=NULL){
			check=1;
			break;
		}
		p=p->next;
	}
	if (check==1){
		printf("이름 : "); scanf("%[^\n]",b_name); ClearBuffer(); 
		printf("주소 : "); scanf("%[^\n]",b_address);  ClearBuffer(); 
		printf("전화번호 : "); scanf("%[^\n]",b_phone); ClearBuffer(); 
		printf("저장하시겠습니까?(Y/N) ");
		if (getchar()=='Y'|| getchar()=='y'){
			strcpy(p->name,b_name); 
			strcpy(p->address,b_address);
			strcpy(p->phone,b_phone);
			printf("\n정보가 수정되었습니다.\n");
		}
		else
			printf("\n정보 수정이 취소되었습니다.\n");
	}
	else
		printf("\n해당 회원의 정보가 존재하지 않습니다.\n");
}

void DeleteMember(Person **head){
	char search[100];
	int check=0;
	Person *p=(*head);
	Person *prev=NULL;
	Person *remove;
	printf("삭제할 회원의 이름을 입력하세요 : ");
	scanf("%[^\n]",search); ClearBuffer();
	while (p!=NULL){
		if (strstr(p->name,search)!=NULL){
			check=1;
			break;
		}
		prev=p;
		p=p->next;
	}
	if (check==1){
		if (prev!=NULL){
			remove=prev->next;
			prev->next=remove->next;
			free(remove);
		}
		else{
			remove=(*head);
			(*head)=(*head)->next;
			free(remove);
		}
		printf("\n정보가 삭제되었습니다.\n");
	}
	else
		printf("\n해당 회원의 정보가 존재하지 않습니다.\n");
}

void SaveTxt(Person **head){
	Person *p=(*head);
	Person *next;
	FILE *fp=fopen("스플럭 명단관리.txt","w");
	if (fp==NULL)
		printf("파일 오픈 실패");
	else{
		while (p!=NULL){
			fprintf(fp,"%s|%s|%s\n",p->name,p->address,p->phone);
			p=p->next;
		}
	}
	fclose(fp);
	p=(*head);
	while (p!=NULL){
		next=p->next;
		free(p);
		p=next;
	}
	printf("\n프로그램을 종료합니다.\n");
}

void justPrint(void){
	printf("============================\n");	
}
