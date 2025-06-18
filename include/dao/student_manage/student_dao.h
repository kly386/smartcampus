#pragma once  
#ifndef STUDENT_DAO_H  
#define STUDENT_DAO_H  

#include"core/list.h"	
//学生结构体
typedef struct {
	char id[10];
	char name[20];
	float gpa;
   char major[30];
}Student;


//将DAO所涉及到的函数封装成一个整体
typedef struct {
	LinkedList* (*load_all)();//从文件中加载所有学生信息，转换为链表存储
	ErrorCode (*save_all)(LinkedList* list);//将链表中的学生信息保存到文件中		
	void (*free_student)(Student* student);//释放学生结构体的内存
} StudentDAO;


StudentDAO* get_student_dao();//获取学生DAO的实例
#endif // STUDENT_DAO_H
