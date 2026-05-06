#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "show.h"
#include"major_code.h"

/*
本来想采用建立一个数据库，给每个学生的id都填上的，
并且设置初始密码，但是吧，要花很长时间，而且要都是重复的工作，
所以我选择在空链表上慢慢添加每一个注册的学生。
*/
extern Major_Code_List mcl_head;            //全局变量major_code——list
// function of inquiry for new users

//检查完毕 1
S_Student_List *Inquiry_User(S_Student_List *ssl_head)        //问询入口
{	
	S_Student_List *p=NULL;                   // ssl指针
    lli s_id = 0;                                //读入id
    char key[KEY_LINE]={0};                     //密码变量
    char out=0;                            //判断变量
    int i;                             //i是操作数    
    Bool flag = OFF;                      //开关接口
    //check
    do{
    	SAFE_READ(lld,"Student ID:",s_id);
	}while(s_id<STUDENT_ID_LINE);               //读入id
	            
	p = Search_Student_ID(ssl_head,s_id);        //在库中寻找对象   
    
    if(p!=NULL){              //在库中对象的密码判断     
    	i=0;
    	do{	
    		flag=OFF;
    		printf("Pass Word:");
    		while(!safe_fgets(key,KEY_LINE)){
    			printf("fgets error!\n");
    			printf("Pass Word:");
			}
			i++;
			if(!strcmp(key,p->key))flag=ON;
			else{
				printf("Incorrect password!\n");
				if(i>=TIP_TIME){
					printf("Your have %d times to try!\n",THE_TRY_LINE-i);
					SAFE_READ(c,"Do you want to exit?(y/n)",out);
					if(out=='y'||out=='Y')exit(0);
				}
				if(i==THE_TRY_LINE){
					printf("Sorry!You can't try again!\n");
					exit(0);
				}
			}
    	}while(!flag);
						//end    	
	}else{
		printf("I can't find your information.\n");
		SAFE_READ(c,"Do you want to create your account?(y/n)",out);
		if(out=='n'||out=='N'){
			printf("See you.");
			exit(0);
		}
		p = Set_Up_Student_Account(ssl_head,s_id);
	}
	return p;
};

//检查完毕 1
S_Student_List *Search_Student_ID(S_Student_List* ssl_head,lli s_id){
	while(ssl_head!=NULL&&ssl_head->ID!=s_id){
		ssl_head=ssl_head->next;
	}
	return ssl_head;
}

//检查完毕 1
S_Student_List* Set_Up_Student_Account(S_Student_List* ssl_head,lli s_id){
	S_Student_List *p=NULL;
	Major_Code_List *mcl_p=NULL;
	S_Student_List temp_student={0};
	char key1[KEY_LINE]={0};
	char out=0;
	int i=0;
	Bool flag = OFF;
	
	temp_student.ID = s_id;
	_set_up_again_:
	do{	
		printf("Your Password:");
		while(!safe_fgets(temp_student.key,KEY_LINE)){
			printf("fgets_error!\n");
			printf("Your Password:");
		}
		flag = password_security(temp_student.key);
		if(!flag){
			printf("The password security is too low.\n");
			printf("Your password needs to be at least 12 characters long\n");
			printf("and contain uppercase and lowercase letters\n");
			printf("as well as other characters like\"#\"\n");
			buffer_line();
		}
	}while(!flag);
	
	i = 0;
	do{
		if(i>=TIP_TIME){
			SAFE_READ(c,"We can go back to set up password,do we?(Y/N)",out);
			if(out=='y'||out=='Y')goto _set_up_again_;
		}
		printf("Confirm Password:");
		while(!safe_fgets(key1,KEY_LINE)){
			printf("fgets error!\n");
			printf("Confirm Password:");
		}
		if(!strcmp(key1,temp_student.key))flag=ON;
		i++;
	}while(!flag);
	
	printf("Congratulation!\n");
	buffer_line();
	
	Read_major_code_list(&mcl_head);	
	
	do{
		printf("Your major code:");
		while(!safe_fgets(temp_student.major_code,CODE_LINE)){
			printf("fgets error!\n");
			printf("Your major code:");
		}
		mcl_p = Search_mcl_item_code(&mcl_head,temp_student.major_code);
		if(mcl_p==NULL)printf("Could not find your major code.\n");
	}while(mcl_p==NULL);
	
	cpystring(mcl_p->name,temp_student.major_name,COURSE_NAME_LINE);	
	give_elective_credits(mcl_p->Category,&temp_student);
	free_malloc_mcl(&mcl_head);
	
	printf("Your name:");
	while(!safe_fgets(temp_student.name,NAME_LINE)){
		printf("fgets error!\n");
		printf("Your name:");
	}
	
	if((p=(S_Student_List*)malloc(sizeof(S_Student_List)))==NULL){
		printf("malloc error!\n");
		exit(1);
	}
	copy_ssl_without_next(&temp_student,p);            //show.h
	Insert_account(ssl_head,p);
	
	return p;
}

//检查完毕 1
void Insert_account(S_Student_List* ssl_head,S_Student_List *p){
	S_Student_List *r=ssl_head->next;
	S_Student_List *l=ssl_head;
	while(r!=NULL){
		if(p->ID < r->ID)break;
		l = r;
		r = r->next;
	}		
	l->next = p;
	p->next = r;
}

//检查完毕 1   
void free_malloc_ssl_list(S_Student_List* ssl_head){     
	S_Student_List* r=ssl_head->next;
	S_Student_List* temp =NULL;
	while(r){
		temp = r;                  
		r=r->next;
		free(temp);
	}
	ssl_head->next=NULL;
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
			else if(key[i]>='0'&&key[i]<='9');
			else others=ON;
			if(uppercase&&lowercase&&others){
				flag=ON;break;
			}
		}
	}
		
	return flag;
}

//检查完毕 1
void cpystring(char *paste,char *wall,int size){
	int i=0;
	
	for(i=0;i<size;i++){                //我写了对wall的清空，可以用来清空很多东西
		wall[i]=0;
	}
	
	i=0;
	while(*paste){
		wall[i++]=*paste;
		paste++;
	}
}

//检查完毕 1
void give_elective_credits(Bool category,S_Student_List*p){
	
	if(category){
		p->elective_credits[HSS][0]=MAX_SCORE;
		p->elective_credits[SS][0]=MIN_SCORE;
	}else{
		p->elective_credits[HSS][0]=(MIN_SCORE+MAX_SCORE)/2.0;
		p->elective_credits[SS][0]=(MIN_SCORE+MAX_SCORE)/2.0;
	}
}

void clean_the_history(S_Student_List *p){
	int i=0;
	for(i=0;i<10;i++){
		p->elective_record[0][i][0]=0;
		p->elective_record[1][i][0]=0;
		p->elective_record[0][i][1]=0;
		p->elective_record[1][i][1]=0;
	}
}

void show_ssl_item(S_Student_List *p){
	int i = 0;
	
	printf("Student ID:%lld\n",p->ID);
	printf("Name:%s\n",p->name);
	printf("Key:%s\n",p->key);
	printf("Major Code:%s\n",p->major_code);
	printf("Major NAME:%s\n",p->major_name);
	printf("HSS:%3.1lf/%3.1lf\n",p->elective_credits[HSS][1],p->elective_credits[HSS][0]);
	printf("SS:%3.1lf/%3.1lf\n",p->elective_credits[SS][1],p->elective_credits[SS][0]);
	printf("HSS record:\n");
	for(i=0;i<10;i++){
		if(p->elective_record[0][i][0]!=0){
			printf("Course Number:%d\n",(int)(p->elective_record[0][i][0]));
		}else break;
	}
	printf("SS record:\n");
	for(i=0;i<10;i++){
		if(p->elective_record[1][i][0]!=0){
			printf("Course Number:%d\n",(int)(p->elective_record[1][i][0]));
		}else break;
	}
}	

void del_ssl_item(S_Student_List *ssl_head,lli id){
	S_Student_List *r = ssl_head->next;
	S_Student_List *l = ssl_head;
	
	while(r!=NULL){
		if(r->ID==id){
			l->next = r->next;
			free(r);
			break;
		}
		l = r;
		r = r->next;
	}
}

void view_course_grades(S_Student_List *p){
	int i=0;
	
	printf("HSS course record:\n");
	for(i=0;i<10;i++){
		if(p->elective_record[HSS][i][0]!=0){
			printf("course_num:%d",(int)(p->elective_record[HSS][i][0]));
			if(p->elective_record[HSS][i][1]!=0){
				printf("--%.2lf\n",p->elective_record[HSS][i][1]);
			}else{
				printf("--The course has not been completed.\n");
			}
		}else{
			break;
		}
	}
	if(i==0)printf("No course record.\n");
	
	printf("SS course record:\n");
	for(i=0;i<10;i++){
		if(p->elective_record[SS][i][0]!=0){
			printf("course_num:%d",(int)(p->elective_record[SS][i][0]));
			if(p->elective_record[SS][i][1]!=0){
				printf("--%.2lf\n",p->elective_record[SS][i][1]);
			}else{
				printf("--The course has not been completed.\n");
			}
		}else{
			break;
		}
	}
	if(i==0)printf("No course record.\n");
	//可以函数优化的，看情况吧。
	
} 

void change_password(S_Student_List *p){
	char key[KEY_LINE]={0};
	char key2[KEY_LINE]={0};     //需要一个用于验证，不要先保存，那样是错误的。
	Bool flag = OFF;
	char out = 0;
	
	do{
		printf("Please input the original password:");
		while(!safe_fgets(key,KEY_LINE)){
			printf("fgets error!\n");
			printf("Please input the original password:");
		}
		if(!strcmp(key,p->key)){
			flag = ON;
		}else{
			printf("Incorrect password.\n");
		}
	}while(!flag);
	
	_input_new_:
	do{
		printf("Please input your new password:");
		while(!safe_fgets(key,KEY_LINE)){
			printf("fgets error!\n");
			printf("Please input your new password:");
		}
		flag = password_security(key);
		if(!flag){
			printf("The password security is too low!\n");
			printf("Your password needs to be at least 12 characters long\n");
			printf("and contain uppercase and lowercase letters\n");
			printf("as well as other characters like\"#\"\n");
			buffer_line();
		}
	}while(!flag);
	
	do{
		printf("Please confirm new password:");
		while(!safe_fgets(key2,KEY_LINE)){
			printf("fgets error!\n");
			printf("Please confirm new password:");
		}
		flag = !strcmp(key,key2);
		if(!flag){
			printf("Incorrect password.\n");
			SAFE_READ(c,"Do you want to go back?(y/n)",out);
			if(out=='y'||out=='Y'){
				goto _input_new_;
			}
		}
	}while(!flag);
	
	cpystring(key,p->key,KEY_LINE);
	
	printf("finshed!");	
	buffer_line();	
}