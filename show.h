#ifndef __SHOW_HEAD__
#define __SHOW_HEAD__
#include "student.h"
#include "class.h"
#define BUFFER_LINE 128
//来玩玩宏！我觉得宏好玩！！！
//prompt提示词  
#define SAFE_READ(type,prompt,var)\
	do{\
		flag = OFF; \
		char _buffer[BUFFER_LINE];\
		char _check_point = 0;\
		\
		printf("%s",prompt);\
		while(!safe_fgets(_buffer,BUFFER_LINE)){\
			printf("buffer fgets error!\n");\
			printf("again:");\
		}\
		if((sscanf(_buffer,"%"#type" %c",&(var),&_check_point))!=1){\
			printf("input error!\n");\
			printf("again.\n");\
			flag = ON; \
		}\
	}while(flag);
//宏能优化性能    用到了#运算 
 
//Bool safe_read_int(int*n)                                 //安全输入int
//我真被缓冲区搞崩溃了，逼我开大是吧！！！
Bool safe_fgets(char*string,int size);                 //安全的输入函数
//包括清空 ，检查，清空缓存
void save_Open_Student_Course(void);          //保存 课程开关
void read_Open_Student_Course(void);         //读取 课程开关
void show_major_code_menu(void);                              //专业号菜单--管理员
void fresh_file(char* file);                                  //清空文件
void show_student_menu(void);                                //学生菜单界面
void show_admin_student_menu(void);							//管理员管理学生菜单界面
void show_admin_menu(void);                                 // 管理员菜单分类
void show_admin_class_menu(void);                           // 管理员课程菜单
void Save_SSL(S_Student_List *ssl_head);                    // 保存ssl，通常在show之后
void Read_SSL(S_Student_List *ssl_head);                    // 读取ssl，通常在show之前
void copy_ssl(S_Student_List *paste, S_Student_List *wall); // 复制ssl
void clean_ssl_item(S_Student_List *wall);                  // 清空下，初始化ssl
void show_cl_item(Class_List *p);                          //展示cl元素

#endif