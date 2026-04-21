#ifndef __SHOW_HEAD__  
#define __SHOW_HEAD__
#include"student.h"

void show_admin_menu(void);     //管理员菜单分类
void show_admin_class_menu(void);   //管理员课程菜单
void Save_SSL(S_Student_List *ssl_head);  //保存ssl，通常在show之后
void Read_SSl(S_Student_List *ssl_head);  //读取ssl，通常在show之前
void copy_ssl(S_Student_List *paste,S_Student_List *wall);  //复制ssl 
void clean_ssl(S_Student_List *wall);  //清空下，初始化ssl
void show_cl_item(Class_List *p);
#endif 