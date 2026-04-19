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

int main(int argc, char *argv[]) {
	S_Student_List *p=NULL;
	int i=0;
	
	Read_SSl(&ssl_head);
		
	p = Inquiry_User(&ssl_head);
	if(p==&ssl_head){
		printf("Welcome,%s!\n",p->name);
		show_admin_menu();
		scanf("%d",&i);
		switch(i){
			case 0:
				admin_class_menu();
				break;
			case 1:
				break;
			default:
				break;
		}
	}else{
		printf("Welcome,User:%s",p->name);	
	};
	//接下来写操作，思考用户可以使用的功能。
	Save_SSL(&ssl_head);
	free_malloc_list(&ssl_head);
	return 0;
}