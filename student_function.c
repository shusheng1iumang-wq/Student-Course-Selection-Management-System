#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"


/*
本来想采用建立一个数据库，给每个学生的id都填上的，
并且设置初始密码，但是吧，要花很长时间，而且要都是重复的工作，
所以我选择在空链表上慢慢添加每一个注册的学生。
*/

// function of inquiry for new users
S_Student_List *Inquiry_User(S_Student_List *ssl_head)
{	
	S_Student_List *p=NULL;
    lli s_id = 0;
    char key[KEY_LINE]={0};
    char out=0;
    int i;
    //check
    do{
    printf("Student ID:\n");
    scanf("%lld",&s_id);
    getchar();
	}while(s_id<STUDENT_ID_LINE);
	
	if(s_id==STUDENT_ID_LINE)p=ssl_head;
	else p = Search_Student_ID(ssl_head,s_id);
    
    if(p!=NULL){
    	i=0;
    	do{	
    		flag=OFF;
    		printf("Pass Word:\n");
    		if((fgets(key,KEY_LINE,stdin))!=NULL){
    			fgets_demo(key);
    			flag=key2key(p->key,key);
			}else{
				i++;
				printf("input error!\n");
				if(i>=TIP_TIME){
					printf("Your have %d times to try!\n",THE_TRY_LINE-i);
					printf("Do you want to exit?(y/n)");
					scanf("%c",&out);
					getchar();
					if(out=='y'||out=='Y')exit(0);
				}
				if(i==THE_TRY_LINE){
					printf("Sorry!You can't try again!\n");
					exit(0);
				}
			}
    	}while(!flag);
    	
	}else{
		printf("I can't find your information.\n");
		printf("Do you want to create your account?(y/n)");
		scanf("%c",&out);
		getchar();
		if(out=='n'||out=='N'){
			printf("See you.");
			exit(0);
		}
		p = Set_Up_Student_Account(ssl_head,s_id);
	}
	return p;
};

S_Student_List *Search_Student_ID(S_Student_List* ssl_head,lli s_id){
	S_Student_List *p=NULL;
	S_Student_List *temp=ssl_head;
	while(temp!=NULL&&temp->ID!=s_id){
		temp=temp->next;
	}
	if(temp!=NULL)p=temp;
	return p;
}

S_Student_List* Set_Up_Student_Account(S_Student_List* ssl_head,lli s_id){
	S_Student_List *p=NULL;
	char key1[KEY_LINE]={0};
	char key2[KEY_LINE]={0};
	char out=0;
	int major_code=0,i=0;
	
	if((p = (S_Student_List*)malloc(sizeof(S_Student_List)))==NULL){
		printf("malloc error!\n");
		exit(0);
	};
	p->ID = s_id;
	again:
	flag=OFF;
	do{	
		printf("Your Password:\n");
		printf("Your password needs to be at least 12 characters long\n");
		printf("and contain uppercase and lowercase letters\n");
		printf("as well as other characters like\"#\"\n");
		if((fgets(key1,KEY_LINE,stdin))==NULL){
			printf("fgets error!\n");
			exit(1);
		}
		fgets_demo(key1);
		flag = password_security(key1);
	}while(!flag);
	
	cpystring(key1,p->key,KEY_LINE);
	i = 0;
	flag = OFF;
	do{
		printf("Confirm Password:");
		if(i>=TIP_TIME){
			printf("We can go back to set up password,do we?(Y/N)");
			scanf("%c",&out);
			getchar();
			if(out=='y'||out=='Y')goto again;
		}
		if((fgets(key2,KEY_LINE,stdin))==NULL){
			printf("fgets error!\n");
			exit(1);
		}
		fgets_demo(key2);
		flag = key2key(key2,p->key);
		i++;
	}while(!flag);
	
	printf("Congratulation!\n");
	printf("Your major code:");
	scanf("%d",&major_code);getchar();
	give_elective_credits(p,major_code);
	
	clean_the_history(p);
	
	input_the_name(p);
	
	Insert_account(ssl_head,p);
	

	
	return p;
}

void Insert_account(S_Student_List* ssl_head,S_Student_List *p){
	S_Student_List *r=ssl_head->next;
	S_Student_List *l=ssl_head;
	while(r){
		if(!r){
			break;
		}else if(r->ID > p->ID){
			break;
		}else{
			l = r;
			r = r->next;
		}
	}		
	l->next = p;
	p->next = r;
}

void free_malloc_ssl_list(S_Student_List* ssl_head){
	S_Student_List* r=ssl_head->next;
	
	while(r){
		S_Student_List* temp = r;
		r=r->next;
		free(temp);
	}
	ssl_head->next=NULL;
}

void fgets_demo(char* string){
	int length=strlen(string)-1;
	
	if(string[length]=='\n')string[length]=0;
}

Bool key2key(char *key,char *key_input){
	Bool flag=ON;
	int i;
	
	if(strlen(key)==strlen(key_input)){
		for(i=0;i<strlen(key);i++){
			if(key[i]!=key_input[i]){
				flag=OFF;
				break;
			}
		}
	}else flag=OFF;
	
	return flag;
}

Bool password_security(char* key){
	Bool flag=OFF;
	int i=0;
	Bool uppercase=OFF,
		lowercase=OFF,
		others=OFF;
		
	if(strlen(key)>=KEY_BOTTOM_LINE){
		for(i=0;i<strlen(key);i++){
			if(key[i]>='a'&&key[i]<='z')lowercase=ON;
			else if(key[i]>='A'&&key[i]<='Z')uppercase=ON;
			else others=ON;
			if(uppercase&&lowercase&&others){
				flag=ON;break;
			}
		}
	}
		
	return flag;
}

void cpystring(char *paste,char *wall,int size){
	int i=0;
	
	for(i=0;i<size;i++){
		wall[i]=0;
	}
	
	i=0;
	while(*paste){
		wall[i++]=*paste;
		paste++;
	}
}

void give_elective_credits(S_Student_List* p,int major_code){
	//先简单的写一个逻辑来代替，如果有空查资料我再来做
	if(major_code%2){
		p->elective_credits[HSS]=MAX_SCORE;
		p->elective_credits[SS]=MIN_SCORE;
	}else{
		p->elective_credits[HSS]=MIN_SCORE;
		p->elective_credits[SS]=MAX_SCORE;
	}
}

void clean_the_history(S_Student_List *p){
	int i=0;
	for(i=0;i<10;i++){
		p->elective_record[0][i]=0;
		p->elective_record[1][i]=0;
	}
}

void input_the_name(S_Student_List *p){
	int i=0;
	for(i=0;i<NAME_LINE;i++){
		p->name[i]=0;
	}
	printf("Your name:");
	if((fgets(p->name,NAME_LINE,stdin))==NULL){
		printf("fgets error!");
		exit(1);
	}
}