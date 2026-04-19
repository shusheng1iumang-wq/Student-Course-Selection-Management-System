#include"class.h"
#include<stdio.h>
#include<stdlib.h>
#include"show.h"

void admin_class_menu(void){
	int i=0;
	
	show_admin_class_menu();
	scanf("%d",&i);
	
	switch(i){
		case 0:
			Course_Entry();
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			break;
	}
}

void Course_Entry(void){
	
}