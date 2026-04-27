#ifndef __MAJOR_CODE_HEAD__
#define __MAJOR_CODE_HEAD__
//专业代号处理的头文件
#include"student.h"
#define MCL_FILE "major_code_list.txt"    //后续优化

typedef struct MAJOR_CODE_LIST{
	Bool Category;        //OFF for HSS ,ON for SS;
	char code[CODE_LINE];   
	char name[COURSE_NAME_LINE];      
	struct MAJOR_CODE_LIST *next;
}Major_Code_List;

Major_Code_List* Search_mcl_item_code(Major_Code_List*mcl_head,char *code);    //查找mcl_item  by code
void Delete_mcl_item(Major_Code_List*mcl_head);                     //删除元素模块
void Save_mcl(Major_Code_List* mcl_head,char* mcl_file);     //保存链表到文件
void show_mcl_item(Major_Code_List* p);                  //show mcl item
int char2number(char* code,int n);                        //char to number
//注意我少了一位计算，因为一般最后一位用来放字符串结束符号。使用的时候注意。
void Insert(Major_Code_List* mcl_head,Major_Code_List *p);    //插入mcl，根据code排序
Bool code2category(char code[CODE_LINE]);               //code -> category
void Entry_Major_Code(Major_Code_List* mcl_head);    //添加mcl_item
void free_malloc_mcl(Major_Code_List* mcl_head);    //free malloc mcl
void Browse_mcl(Major_Code_List* mcl_head);      //浏览mcl
void clean_mcl_item(Major_Code_List* wall);     //清空mcl_item
//慎用我启用的时候把next也清空了，在list中需要注意加回来。
void cpy_mcl_item(Major_Code_List* paste,Major_Code_List* wall);      //复制mcl_item
void Read_major_code_list(Major_Code_List * mcl_head,char * file);   //读取major文件
void admin_major_menu(Major_Code_List* mcl_head);       //major菜单--管理员

#endif