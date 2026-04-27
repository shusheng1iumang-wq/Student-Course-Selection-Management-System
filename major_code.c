#include"major_code.h"
#include<stdio.h>
#include<stdlib.h>
#include"show.h"
#include<errno.h>
#include"student.h"
//2025年广工，08工学，12管理学，07理学
//05文学，13艺术类，03法学，02经济学
//04教育学

//02，03，04，05，12，13-->HSS
//07，08-->SS

//后面我要加入代号判断的功能。


void admin_major_menu(Major_Code_List* mcl_head){
	char* mcl_file="major_code_list.txt";
	int i = 0;
	
	do{
		show_major_code_menu();
		scanf("%d",&i);getchar();
		Read_major_code_list(mcl_head,mcl_file);
		switch(i){
			case 0:
				Browse_mcl(mcl_head);
				Save_mcl(mcl_head,mcl_file);
				free_malloc_mcl(mcl_head);
				break;
			case 1:
				Entry_Major_Code(mcl_head);
				Save_mcl(mcl_head,mcl_file);
				free_malloc_mcl(mcl_head);
				break;
			case 2:		
				Delete_mcl_item(mcl_head);
				Save_mcl(mcl_head,mcl_file);
				free_malloc_mcl(mcl_head);
				break;
			case 3:
				free_malloc_mcl(mcl_head);
				fresh_file(mcl_file);
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
				break;
		}
	}while(1);
}

void Read_major_code_list(Major_Code_List * mcl_head,char * file){
	FILE *fp=NULL;
	Major_Code_List mcl_temp={0};
	Major_Code_List *p=NULL,*head=mcl_head;
	
	flag = ON;
	//我将加入更加安全的文件保护，这是第一次尝试，如果可以，前面的我都会找机会修改。
	//怀疑bug在这里
	again:
	errno = 0;
	if((fp=fopen(file,"rb"))==NULL){
		if(errno==ENOENT){
			printf("%s does not exist\n",file);
			printf("Creating the %s\n",file);
			if((fp=fopen(file,"wb"))==NULL){
				printf("Creating error!");
				exit(1);
			}else printf("Success.\n");
			fclose(fp);
			goto again;
		}else{
			printf("%s fopen error!\n",file);
			exit(1);
		}
	}
	
	flag = ON;
	while((fread(&mcl_temp,sizeof(Major_Code_List)-sizeof(mcl_temp.next),1,fp))==1){
		if((p=(Major_Code_List*)malloc(sizeof(Major_Code_List)))==NULL){
			printf("malloc error!");
			exit(1);
		}
		if(flag){
			cpy_mcl_item(&mcl_temp,head);
			flag = OFF;	
		}else{
			cpy_mcl_item(&mcl_temp,p);
			head->next = p;
			head = p;
		}
	}
	
	fclose(fp);
}

void cpy_mcl_item(Major_Code_List* paste,Major_Code_List* wall){
	clean_mcl_item(wall);
	wall->Category=paste->Category;
	cpystring(paste->code,wall->code,CODE_LINE);
	cpystring(paste->name,wall->name,COURSE_NAME_LINE);
	
}

void clean_mcl_item(Major_Code_List* wall){
	char white_code[CODE_LINE]={0};
	char white_name[COURSE_NAME_LINE]={0};
	
	wall->Category=OFF;
	cpystring(white_code,wall->code,CODE_LINE);
	cpystring(white_name,wall->name,COURSE_NAME_LINE);
	wall->next=NULL;
}

void Browse_mcl(Major_Code_List* mcl_head){
	Major_Code_List *r=mcl_head->next;
	
	printf("| Category | Major Code | Major Name\n");
	while(r!=NULL){
		if(r->Category){
			printf("|%10s|","SS");
		}else printf("|%10s|","HSS");
		printf("%12s|",r->code);
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
	
	do{
	
		p = (Major_Code_List*)malloc(sizeof(Major_Code_List));
		clean_mcl_item(p);
		printf("Input the Major:\n");
		printf("Major Code:");
		fgets(p->code,CODE_LINE,stdin);
		fgets_demo(p->code);
		printf("Major Name:");
		fgets(p->name,COURSE_NAME_LINE,stdin);
		fgets_demo(p->name);
		p->Category = code2category(p->code);
		
		Insert(mcl_head,p);
		
		printf("continue?(y/n)");
		out = getchar();getchar();
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
	int count =  char2number(p->code,CODE_LINE);
	int temp = 0;
	char out = 0;
	Major_Code_List* r= mcl_head->next;
	Major_Code_List* l= mcl_head;
	Major_Code_List* next =NULL;
	flag = ON;
	
	while(r!=NULL){
		temp =char2number(r->code,CODE_LINE);
		if(count<temp){
			flag = OFF;
			l->next = p;
			p->next = r;
			break;
		}
		if(count== temp){
			printf("There has the same major code:\n");
			show_mcl_item(r);
			printf("Do you want to replace this one?(y/n)");
			out = getchar();getchar();
			if(out=='y'||out=='Y'){
				next = r->next;
				cpy_mcl_item(p,r);
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

void Save_mcl(Major_Code_List* mcl_head,char* file){
	Major_Code_List* l =mcl_head;
	FILE *fp =NULL;
	
	if((fp=fopen(file,"wb"))==NULL){
		printf("%s fopen error!\n",file);
		exit(1);
	}
	
	while(l!=NULL){
		if((fwrite(l,sizeof(Major_Code_List)-sizeof(l->next),1,fp))!=1){
			printf("%s fwrite error!\n");
			exit(1);
		}
		l = l->next;
	}
	fclose(fp);
}

void Delete_mcl_item(Major_Code_List*mcl_head){
	char code[CODE_LINE]={0};
	char out = 0;
	Major_Code_List* p = NULL;
	Major_Code_List* l = mcl_head;
	
	printf("Input the Major Code to delete:");
	fgets(code,CODE_LINE,stdin);
	fgets_demo(code);
	
	if((p=Search_mcl_item_code(mcl_head,code))==NULL){
		printf("Counld not find the %s\n",code);
		printf("go back.\n");
		return;
	}
	printf("We find:\n");
	show_mcl_item(p);
	printf("Are you sure?(y/n)");
	out = getchar();getchar();
	while(l!=NULL){
		if(l->next==p)break;
		l = l->next;
	}
	if(out=='y'||out=='Y'){
		l->next = p->next;
		free(p);
	}
}

Major_Code_List* Search_mcl_item_code(Major_Code_List*mcl_head,char *code){
	Major_Code_List*p = NULL;
	Major_Code_List *r = mcl_head;
	int count = char2number(code,CODE_LINE);
	
	while(r!=NULL){
		if(count==char2number(r->code,CODE_LINE)){
			p = r;
			break;
		}
		r = r->next;
	}
	return p;
}