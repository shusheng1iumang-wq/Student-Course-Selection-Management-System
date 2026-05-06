#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "show.h"
#include "admin_student.h"
#include "major_code.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include<windows.h>

// 头部空节点，工程优化！
S_Student_List ssl_head = {
    STUDENT_ID_LINE,
    "admin",
    "Your_father",
};

Class_List cl_head = {
    0,
};

Major_Code_List mcl_head={
	0                                     //这几个头节点没啥要注释的吧
};

Bool Open_Student_Course = OFF;             //选课开关变量

Bool extern_flag;

int main(int argc, char *argv[])
{
	//SetConsoleOutputCP(65001);   //编码统一，之前调试一直有bug
    S_Student_List *p = NULL;         //用于验证的指针
    int i = 0;                        //i用于case
    S_Student_List student_temp ={0};      //临时学生元素，节省内存开销
	read_Open_Student_Course();            //读取选课开关情况   //show.h
    Read_SSL(&ssl_head); // 读取             //show.h

    p = Inquiry_User(&ssl_head); // 询问       //student.h

    // 进入
    if (p == &ssl_head)
    {
        // 管理员
        printf("Welcome,%s!\n", p->name);
        free_malloc_ssl_list(p);                     //student.h
        buffer_line();
        do
        {
            show_admin_menu();
            SAFE_READ(d,"Your choose:",i);
            switch (i)
            {
            case 0:
                admin_class_menu(&cl_head);
                break;
            case 1:
                admin_student_menu(p);
                break;
            case 2:
            	admin_major_menu(&mcl_head);
            	break;
            case 3:
                exit(1);
                break;
            default:
            	printf("Input the illegal number.\n");
                break;
            }
        } while (1);
    }
    else
    {
        // 学生
        copy_ssl_without_next(p,&student_temp);
        Save_SSL(&ssl_head);
        free_malloc_ssl_list(&ssl_head);
        printf("Welcome,User:%s\n", student_temp.name);
        printf("The course selection channel is");
        if(Open_Student_Course)printf(" Opened.\n");
        else printf(" Closed.\n");
        do{
        	show_student_menu();
        	SAFE_READ(d,"Your choose:",i);
        	switch(i){
        		case 0:
        			read_cl_list(&cl_head);
        			Browse_Courses(&cl_head);
        			free_malloc_cl_list(&cl_head);
        			break;
        		case 1:
        			show_ssl_item(&student_temp);
        			break;
        		case 2:
        			view_course_grades(&student_temp);
        			break;
        		case 3:
        			read_cl_list(&cl_head);
        			Course_registration(&student_temp,&cl_head);
        			save_cl_list(&cl_head);
        			free_malloc_cl_list(&cl_head);
        			
        			Read_SSL(&ssl_head);
        			p = Search_Student_ID(&ssl_head,student_temp.ID);
        			copy_ssl_without_next(&student_temp, p);
        			Save_SSL(&ssl_head);
        			free_malloc_ssl_list(&ssl_head);
        			break;
        		case 4:
        			read_cl_list(&cl_head);
        			Cancel_the_course(&student_temp,&cl_head);
        			save_cl_list(&cl_head);
        			free_malloc_cl_list(&cl_head);
        			
        			Read_SSL(&ssl_head);
        			p = Search_Student_ID(&ssl_head,student_temp.ID);
        			copy_ssl_without_next(&student_temp, p);
        			Save_SSL(&ssl_head);
        			free_malloc_ssl_list(&ssl_head);
        			break;
        		case 5:
     				change_password(&student_temp);
     				Read_SSL(&ssl_head);
        			p = Search_Student_ID(&ssl_head,student_temp.ID);
        			copy_ssl_without_next(&student_temp, p);
        			Save_SSL(&ssl_head);
        			free_malloc_ssl_list(&ssl_head);
        			break;
        		case 6:
        			printf("See you!\n");
        			exit(0);
        			break;
        		default:
        			printf("Input the illegal number.\n");
        			break;
			}
			buffer_line();
    	}while(1);
    };

    return 0;
}