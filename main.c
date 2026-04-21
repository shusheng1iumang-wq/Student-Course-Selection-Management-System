#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "show.h"
#include "class.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//头部空节点，工程优化！
S_Student_List ssl_head={
	STUDENT_ID_LINE,"admin","Your_father",
};

Class_List cl_head={0,};

int main(int argc, char *argv[]) {
	S_Student_List *p=NULL;
	int i=0;
	
	Read_SSl(&ssl_head);  //读取
		
	p = Inquiry_User(&ssl_head);   //询问
	
	//进入
	if(p==&ssl_head){
		//管理员
		printf("Welcome,%s!\n",p->name);
		show_admin_menu();
		scanf("%d",&i);
		switch(i){
			case 0:
				admin_class_menu(&cl_head);
				break;
			case 1:
				break;
			case 2:
				exit(1);
				break;
			default:
				break;
		}
	}else{
		//学生
		printf("Welcome,User:%s",p->name);	
	};

	//保存
	Save_SSL(&ssl_head);
	
	//释放
	free_malloc_ssl_list(&ssl_head);
	
	return 0;
}