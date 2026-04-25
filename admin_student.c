#include <stdio.h>
#include <stdlib.h>
#include "admin_student.h"
#include "show.h"
#include "student.h"

void admin_student_menu(S_Student_List *ssl_head)
{
    int i = 0;

    do
    {
        show_admin_student_menu();
        scanf("%d", &i);
        Read_SSL(ssl_head);
        switch (i)
        {
        	case 0:
        		Student_Entry(ssl_head);
        		Save_SSL(ssl_head);
           		break;
	        case 1:
	        	Browse_Student(ssl_head);
	            break;
	        case 2:
	        	Delete_Student_item(ssl_head);
	        	Save_SSL(ssl_head);
	            break;
	        case 3:
	        	free_malloc_ssl_list(ssl_head);
	        	return;
	            break;
	        case 4:
	        	free_malloc_ssl_list(ssl_head);
	        	exit(0);
	            break;
        }
        free_malloc_ssl_list(ssl_head);
    } while (1);
}

void Student_Entry(S_Student_List* ssl_head){
	lli id=0;
	char out=0;
	S_Student_List *p=NULL;
	
	do{
		flag =OFF;
		again:
		printf("The Student ID:");
		scanf("%lld",&id);
		
		p = Search_Student_ID(ssl_head,id);
		if(p!=NULL){
			printf("There had a same one:\n");
			show_ssl_item(p);
			getchar();
			printf("Do you want to delete this?(y/n)");
			scanf("%c",&out);
			
			if(out=='y'||out=='Y'){
				del_ssl_item(ssl_head,id);
				printf("finshed!let's continue.\n");
			}else{
				printf("continue?(y/n)");
				getchar();
				scanf("%c",&out);
				if(out=='y'||out=='Y'){
					goto again;
				}else{
					return;
				}
			}		
		}
		p = (S_Student_List*)malloc(sizeof(S_Student_List));
		clean_ssl_item(p);
		p->ID = id;
		cpystring("123456789&&Gdut",p->key,15);
		printf("Major Code:");
		scanf("%d",&p->major_code);
		getchar();
		clean_the_history(p);
		give_elective_credits(p,p->major_code);
		printf("Name:");
		fgets(p->name,NAME_LINE,stdin);
		fgets_demo(p->name);
		
		Insert_account(ssl_head,p);
		
		
		printf("continue?(y/n)");
		out = getchar();
		if(out=='Y'||out=='y')flag=ON;
		
	}while(flag);
}

void Browse_Student(S_Student_List* ssl_head){
	S_Student_List* p=ssl_head->next;
	int i;
	
	printf("| Student ID | Student NAME | m_code |  HSS  |  SS   |\n");
	
	while(p!=NULL){
		printf("|%12lld|",p->ID);
		printf("%14s|",p->name);
		printf("%8d|",p->major_code);
		printf("%3.1lf/%3.1lf|",p->elective_credits[HSS][1],p->elective_credits[0]);
		printf("%3.1lf/%3.1lf|\n",p->elective_credits[SS][1],p->elective_credits[SS][0]);
		printf("HSS record:");
		for(i=0;i<10;i++){
			if(p->elective_record[HSS][i][0]!=0){
				printf("(%d):%d",i,p->elective_record);
				printf(" ");
			}else printf("\n");break;
		}
		printf("SS record:");
		for(i=0;i<10;i++){
			if(p->elective_record[SS][i][0]!=0){
				printf("(%d):%d",i,p->elective_record);
				printf(" ");
			}else printf("\n");break;
		}
		p = p->next;
	}
}

void Delete_Student_item(S_Student_List* ssl_head){
	lli id = 0;
	char out = 0;
	S_Student_List *p = NULL;
	
	do{
		flag =OFF;
		printf("Input student id to delete:");
		scanf("%lld",&id);getchar();
		p = Search_Student_ID(ssl_head,id);
		
		if(p==NULL){
			printf("Cannot find the ID:%lld\n",id);
		}else{
			printf("We find:\n");
			show_ssl_item(p);
			printf("Do you want to delete?(y/n)");
			out = getchar();
			if(out=='y'||out=='Y'){
				del_ssl_item(ssl_head,id);
				printf("finshed.\n"); 
			}
		}
		
		printf("continue?(y/n)");
		getchar();
		out=getchar();
		if(out=='Y'||out=='y')flag=ON;	
		
	}while(flag);
}