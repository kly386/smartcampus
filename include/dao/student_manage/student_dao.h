#pragma once  
#ifndef STUDENT_DAO_H  
#define STUDENT_DAO_H  

#include"core/list.h"	
//ѧ���ṹ��
typedef struct {
	char id[10];
	char name[20];
	float gpa;
   char major[30];
}Student;


//��DAO���漰���ĺ�����װ��һ������
typedef struct {
	LinkedList* (*load_all)();//���ļ��м�������ѧ����Ϣ��ת��Ϊ����洢
	ErrorCode (*save_all)(LinkedList* list);//�������е�ѧ����Ϣ���浽�ļ���		
	void (*free_student)(Student* student);//�ͷ�ѧ���ṹ����ڴ�
} StudentDAO;


StudentDAO* get_student_dao();//��ȡѧ��DAO��ʵ��
#endif // STUDENT_DAO_H
