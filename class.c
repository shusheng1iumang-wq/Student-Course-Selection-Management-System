#include"class.h"
#include<stdio.h>
#include<stdlib.h>
#include"show.h"

void admin_class_menu(Class_List *cl_head){
	int i=0;
	
	show_admin_class_menu();
	scanf("%d",&i);
	
	switch(i){
		case 0:
			Course_Entry(cl_head);
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			return;
			break;
		case 4:
			exit(1);
			break;
		default:
			break;
	}
}

void Course_Entry(Class_List* cl_head){
	Class_List *p=NULL;
	Class_List *head = cl_head;
	Class_List *temp=NULL;
	int i;
	char out=0;
	FILE *fp=NULL;
	char *cl_file = "class_list.txt";
	
	flag = ON;
	
	do{
		if((p=(Class_List*)malloc(sizeof(Class_List)))==NULL){
			printf("malloc error!");
			exit(1);
		}
		
		re_entry:
		printf("Course Number:");
		scanf("%d",&p->Course_Number);getchar();
		temp = check_course_number(cl_head,p->Course_Number);
		if(temp!=NULL){
			printf("There have the same Course Number.\n");
			show_cl_item(temp);
			do{
				printf("What do you want?\n");
				printf("0->delete\n");
				printf("1->re-entry\n");
				printf("Your choose:");
				scanf("%d",&i);getchar();
			}while(i!=0&&i!=1);
			if(i==0){
				delete_cl_item(cl_head,p->Course_Number);
			}else if(i==1){
				goto re_entry;
			}	
		}
		
		printf("Course Name:");
		cpystring("",p->Course_Name,COURSE_NAME_LINE); //清理空间
		fgets(p->Course_Name,COURSE_NAME_LINE,stdin);
		fgets_demo(p->Course_Name);
		
		printf("Credits:");
		scanf("%lf",&p->Credits);
		getchar();
		
		printf("Lecturer:");
		cpystring("",p->Lecturer,NAME_LINE);
		fgets(p->Lecturer,NAME_LINE,stdin);
		fgets_demo(p->Lecturer);
		
		printf("Max Seats:");
		scanf("%d",&p->Max_Enrollment);
		
		p->Current_Students=0;
		
		printf("Category:\n");
		printf("0->HSS,1->SS\n");
		do{
			scanf("%d",&i);
		}while(i!=0&&i!=1);
		p->Category = i;
		p->next=NULL;
		
		Insert_class(p,head);
		
		getchar();
		printf("continue?(y/n)");
		scanf("%c",&out);
		if(out=='n'||out=='N')flag=OFF;
		
	}while(flag);
	
	printf("------Saving Now------\n");
	if((fp=fopen(cl_file,"wb"))==NULL){
		printf("fopen error!\n");
		exit(1);
	}
	while(head!=NULL){
		p = head ;
		head = head->next;
		if((fwrite(p,sizeof(Class_List)-sizeof(p->next),1,fp))!=1){
			printf("fwrite error!\n");
			exit(1);
		}
	}
	
	printf("------Finshed------\n");
	
	free_malloc_cl_list(cl_head);
//接下来写read函数，然后还是要在插入功能上查一下是否课程号重复，不然容易重复保存。
	
	fclose(fp);
	
}

void Insert_class(Class_List* p,Class_List *head){
	Class_List *l=head;
	Class_List *r=head->next;
	while(r&&r->Course_Number<p->Course_Number){
		l = r;
		r = r->next;
	}
	l->next = p;
	p->next = r;	
}

void free_malloc_cl_list(Class_List* cl_head){
	Class_List* l = cl_head;
	Class_List* r = cl_head->next;
	while(r!=NULL){
		l = r;
		r = r->next;
		free(l);
	}
	cl_head->next=NULL;
}

Class_List * check_course_number(Class_List* cl_head,int number){
	Class_List *p=NULL;
	while(cl_head!=NULL){
		if(cl_head->Course_Number==number){
			p = cl_head;
			break;
		}
		cl_head = cl_head->next;
	}
	return p;
}

void delete_cl_item(Class_List* cl_head,int number){
	Class_List *l = cl_head;
	Class_List *r = cl_head->next;
	flag = OFF;
	while(r!=NULL){
		if(r->Course_Number==number){
			l->next = r->next;
			free(r);
			flag = ON;
			break;
		}
		l = r;
		r = r->next;
	}
	if(flag){
		printf("delete success!\n");
	}else{
		printf("cannot find\n");
	}
}