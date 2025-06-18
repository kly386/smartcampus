#include "service/student_manage/student_service.h"
#include "core/common.h"
#include "core/list.h"
#include "dao/student_manage/student_dao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//����һ��ѧ������ - ȫ�ֱ���
LinkedList* student_list = NULL;

//��ʼ�� -> �õ�һ�����ݼ��صĽ��
void init_student_list() {
	if (student_list == NULL) {
		student_list = get_student_dao()->load_all();
		//if (student_list == NULL) {
		//	student_list = list_create();
		//}
	}
}

//ʵ��get_student
Student* get_student(char* id) {
	init_student_list();
	//���һ����������
	if (id == NULL || student_list == NULL) {
		return NULL;
	}

	//�������ǵ�linklist,�Ƚ�ÿһ���ڵ��id�봫��ڵ�id�Ƿ�һ��
	//1. �õ�ͷ���,�����α�ָ��it
	ListIterator it = list_begin(student_list);
	//2. ѭ����������
	while (it != NULL) {
		Student* stu = (Student*)it->data;
		if (strcmp(stu->id, id) == 0) {
			return stu;
		}
		it = list_next(it);
	}
	return NULL;
}

//get_all_student
LinkedList* get_all_students() {
	init_student_list();
	return student_list;
}

//���ѧ��
ErrorCode add_student(char* id, char* name, float gpa, char* major) {
	// �������Ч�Լ��
	if (NULL == id || name == NULL || major == NULL) {
		return ERR_INVALID_INPUT;
	}
	//���ǰҪ��������
	init_student_list();

	//���ѧ���Ƿ��ظ�
	if (get_student(id) != NULL) {
		return ERR_DUPLICATE;
	}

	//֮��������Ӳ���
	//1. ��id��name��������װ��Student
	Student* new_student = (Student*)safe_malloc(sizeof(Student));
	strncpy_s(new_student->id, sizeof(new_student->id), id, sizeof(new_student->id) - 1);
	strncpy_s(new_student->name, sizeof(new_student->name), name, sizeof(new_student->name) - 1);
	strncpy_s(new_student->major, sizeof(new_student->major), major, sizeof(new_student->major) - 1);
	new_student->gpa = gpa;

	//2. ���ṹ��Student�����뵽student_list��
	ErrorCode error = list_append(student_list, new_student);
	printf("%s\n", error_message(error));

	//2.1 �쳣����list_append�����д����ʱ��
	if (error != SUCCESS) {
		safe_free(&new_student);
		return error;
	}

	//3. ͬ�������ڴ��е�student_list���ļ���
	error = get_student_dao()->save_all(student_list);
	printf("%s\n", error_message(error));
}

StudentService* get_student_service() {  
	StudentService service = {  
		.add_student = add_student,  
		.get_all_students = get_all_students,  
	};  
	return &service;  
}