#pragma once
#ifndef STUDENT_SERVICE_H
#define STUDENT_SERVICE_H

#include "core/common.h"
#include "core/list.h"
#include "dao/student_manage/student_dao.h"

//ѧ������ӿ�
typedef struct {
	//����ѧ��
	ErrorCode(*add_student)(char* id, char* name, float gpa, char* major);
	//�޸�ѧ��
	ErrorCode(*update_student)(char* id, char* name, float gpa, char* major);
	//��ѯ����ѧ�ţ�
	Student* (*get_student)(char* id);
	//ɾ������ѧ�ţ�
	ErrorCode(*delete_student)(char* id);
	//ͳ�Ʒ���-����רҵͳ�Ʒ���
	void (*caculate_gpa_by_major)();
	//��ȡ����ѧ����Ϣ
	LinkedList* (*get_all_students)();
	//��ӡ����ѧ����Ϣ
	void (*print_all_students)();
}StudentService;

//��ȡѧ������ӿڵ�ʵ��
StudentService* get_student_service();

#endif