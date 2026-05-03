#include"major_code.h"
#include<stdio.h>
#include<stdlib.h>
#include"show.h"
#include<errno.h>
#include<string.h>
#include"student.h"
//2025年广工，08工学，12管理学，07理学
//05文学，13艺术类，03法学，02经济学
//04教育学

//02，03，04，05，12，13-->HSS
//07，08-->SS

//后面我要加入代号判断的功能。



void admin_major_menu(Major_Code_List* mcl_head){
	int i = 0;
	
	do{
		show_major_code_menu();
		SAFE_READ(d,"Your choose:",i);
		Read_major_code_list(mcl_head);
		switch(i){
			case 0:
				Browse_mcl(mcl_head);
				Save_mcl(mcl_head);
				free_malloc_mcl(mcl_head);
				break;
			case 1:
				Entry_Major_Code(mcl_head);
				Save_mcl(mcl_head);
				free_malloc_mcl(mcl_head);
				break;
			case 2:		
				Delete_mcl_item(mcl_head);
				Save_mcl(mcl_head);
				free_malloc_mcl(mcl_head);
				break;
			case 3:
				free_malloc_mcl(mcl_head);
				fresh_file(MCL_FILE);
				break;
			case 4:
				free_malloc_mcl(mcl_head);
				printf("Go back\n");
				return;
				break;	
			case 5:
				free_malloc_mcl(mcl_head);
				printf("Exit\n");
				exit(0);
				break;
			default:
				printf("Input the illegal number.\n");
				break;
		}
	}while(1);
}

//检查完毕 1
void Read_major_code_list(Major_Code_List * mcl_head){
	FILE *fp=NULL;
	Major_Code_List mcl_temp={0},
		cleaner = {0};
	Major_Code_List *p=NULL,
		*head=mcl_head;

	while((fp=fopen(MCL_FILE,"rb"))==NULL){
		if(errno==ENOENT){
			 Save_mcl(mcl_head);
		}else{
			printf("%s fopen error!\n",MCL_FILE);
			exit(1);
		}
	}
	
	while((fread(&mcl_temp,sizeof(Major_Code_List)-sizeof(mcl_temp.next),1,fp))==1){
		if((p=(Major_Code_List*)malloc(sizeof(Major_Code_List)))==NULL){
			printf("malloc error!");
			exit(1);
		}
		copy_mcl_item_without_next(&mcl_temp,p);
		p->next = NULL;
		head->next = p;
		head = head->next;
		copy_mcl_item_without_next(&cleaner,&mcl_temp);
	}
	
	fclose(fp);
}

//检查完毕 1
void copy_mcl_item_without_next(Major_Code_List* paste,Major_Code_List* wall){
	wall->Category=paste->Category;
	cpystring(paste->code,wall->code,CODE_LINE);
	cpystring(paste->name,wall->name,COURSE_NAME_LINE);	
}


void Browse_mcl(Major_Code_List* mcl_head){
	Major_Code_List *r=mcl_head->next;
	int i=0;
	
	for(i=0;r!=NULL;i++){
		if(i%20==0&&i!=0)	{
			buffer_line();
			printf("| Category | Major Code | Major Name\n");
		}
		if(r->Category){
			printf("|%-10s|","SS");
		}else printf("|%-10s|","HSS");
		printf("%-12s|",r->code);
		printf("%s\n",r->name);
		r = r->next;
	}
}

void free_malloc_mcl(Major_Code_List* mcl_head){
	Major_Code_List *r = mcl_head->next;
	Major_Code_List *l = mcl_head;
	
	while(r!=NULL){
		l = r;
		r = r->next;
		free(l);
	}
	
	mcl_head->next = NULL;
}

void Entry_Major_Code(Major_Code_List* mcl_head){
	char out = 0;
	Major_Code_List* p =NULL;
	Major_Code_List* same=NULL;
	int c= 0;
	
	Bool flag = OFF;
	
	do{
	
		p = (Major_Code_List*)malloc(sizeof(Major_Code_List));
		printf("Input the Major:\n");
		
		do{
			flag = OFF;
			printf("Major Code:");
			while(!safe_fgets(p->code,CODE_LINE)){
				printf("fgets error!\n");
				printf("Major Code:");
			}
			if(strcmp(p->code,"0000000")<0){
				printf("Your input is illegal\n");
				flag = ON;
			}
		}while(flag);
		
		if((same=Search_mcl_item_code(mcl_head,p->code))!=NULL){
			printf("There have a same one.\n");
			show_mcl_item(same);
			SAFE_READ(c,"Do you want to delete?(y/n)",out);
			if(out=='y'||out=='Y'){
				Delete_mcl_item(mcl_head);
				printf("Let's continue.\n");
			}else{
				printf("go back.\n");
				free(p);
			}
		}
		
		printf("Major Name:");
		while(!safe_fgets(p->name,COURSE_NAME_LINE)){
			printf("fgets error!\n");
			printf("Major Name:");
		}
		
		p->Category = code2category(p->code);
		
		Insert(mcl_head,p);
		
		SAFE_READ(c,"continue?(y/n)",out);
		if(out=='n'||out=='N'){
			break;
		}
	}while(1);
}

Bool code2category(char* code){
	int count=0;
	Bool out=OFF;
		
	count = char2number(code,2+1);
	
	if(count==8||count==7){
		out = ON;
	}
	return out;
}

void Insert(Major_Code_List* mcl_head,Major_Code_List *p){
	char out = 0;
	Major_Code_List* r= mcl_head->next;
	Major_Code_List* l= mcl_head;
	Major_Code_List* next =NULL;
	Bool flag = ON;
	
	while(r!=NULL){
		if(strcmp(p->code,r->code)<0){
			flag = OFF;
			l->next = p;
			p->next = r;
			break;
		}else if(strcmp(p->code,r->code)==0){
			printf("There has the same major code:\n");
			show_mcl_item(r);
			SAFE_READ(c,"Do you want to replace this one?(y/n)",out);
			if(out=='y'||out=='Y'){
				next = r->next;
				copy_mcl_item_without_next(p,r);
				r->next = next;
				flag =OFF;
				free(p);
				break;
			}
			printf("Now your input will be cleaned.\n");
			free(p);
			printf("Now we will go back.\n");
			return;
		}
		l = r;
		r = r->next;
	}
	
	if(flag){
		l->next=p;
		p->next=NULL;
	}
}

int char2number(char* code,int n){
	int i=0;
	int count=0;
	
	for(i=0;i<n-1;i++){
		count = code[i]-'0'+count*10;
	}
	
	return count;
}

void show_mcl_item(Major_Code_List* p){
	printf("Category:");
	if(p->Category)printf("SS\n");
	else printf("HSS\n");
	printf("Major Code:%s\n",p->code);
	printf("Major Name:%s\n",p->name);
}

//检查完毕 1
void Save_mcl(Major_Code_List* mcl_head){
	Major_Code_List* r =mcl_head->next;
	FILE *fp =NULL;
	
	if((fp=fopen(MCL_FILE,"wb"))==NULL){
		printf("%s fopen error!\n",MCL_FILE);
		exit(1);
	}
	
	while(r!=NULL){
		if((fwrite(r,sizeof(Major_Code_List)-sizeof(mcl_head->next),1,fp))!=1){
			printf("fwrite error!\n");
			exit(1);
		}
		r = r->next;
	}
	fclose(fp);
}

void Delete_mcl_item(Major_Code_List*mcl_head){
	char code[CODE_LINE]={0};
	char out = 0;
	int c=0;
	Major_Code_List* p = NULL;
	Major_Code_List* l = mcl_head;
	
	printf("Input the Major Code to delete:");
	while(!safe_fgets(code,CODE_LINE)){
		printf("fgets error!\n");
		printf("Input the Major Code to delete:");
	}
	
	if((p=Search_mcl_item_code(mcl_head,code))==NULL){
		printf("Counld not find the %s\n",code);
		printf("go back.\n");
		return;
	}
	printf("We find:\n");
	show_mcl_item(p);
	SAFE_READ(c,"Are you sure?(y/n)",out);
	while(l!=NULL){
		if(l->next==p)break;
		l = l->next;
	}
	if(out=='y'||out=='Y'){
		l->next = p->next;
		free(p);
	}
}

//检查完毕 1
Major_Code_List* Search_mcl_item_code(Major_Code_List*mcl_head,char *code){
	Major_Code_List*p = NULL;
	Major_Code_List *r = mcl_head->next;
	
	while(r!=NULL){
		if(strcmp(code,r->code)==0){
			p = r;
			break;
		}
		r = r->next;
	}
	return p;
}