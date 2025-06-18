#include "service/student_manage/student_service.h"
#include "core/common.h"
#include "core/list.h"
#include "dao/student_manage/student_dao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义一个学生链表 - 全局变量
LinkedList* student_list = NULL;

//初始化 -> 得到一个数据加载的结果
void init_student_list() {
	if (student_list == NULL) {
		student_list = get_student_dao()->load_all();
		//if (student_list == NULL) {
		//	student_list = list_create();
		//}
	}
}

//实现get_student
Student* get_student(char* id) {
	init_student_list();
	//添加一个保护函数
	if (id == NULL || student_list == NULL) {
		return NULL;
	}

	//遍历我们的linklist,比较每一个节点的id与传入节点id是否一致
	//1. 拿到头结点,创立游标指针it
	ListIterator it = list_begin(student_list);
	//2. 循环整个链表
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

//添加学生
ErrorCode add_student(char* id, char* name, float gpa, char* major) {
	// 输入的有效性检查
	if (NULL == id || name == NULL || major == NULL) {
		return ERR_INVALID_INPUT;
	}
	//添加前要创建链表
	init_student_list();

	//检查学号是否重复
	if (get_student(id) != NULL) {
		return ERR_DUPLICATE;
	}

	//之后再做添加操作
	//1. 将id、name。。。封装成Student
	Student* new_student = (Student*)safe_malloc(sizeof(Student));
	strncpy_s(new_student->id, sizeof(new_student->id), id, sizeof(new_student->id) - 1);
	strncpy_s(new_student->name, sizeof(new_student->name), name, sizeof(new_student->name) - 1);
	strncpy_s(new_student->major, sizeof(new_student->major), major, sizeof(new_student->major) - 1);
	new_student->gpa = gpa;

	//2. 将结构体Student，加入到student_list中
	ErrorCode error = list_append(student_list, new_student);
	printf("%s\n", error_message(error));

	//2.1 异常处理，list_append返回有错误的时候
	if (error != SUCCESS) {
		safe_free(&new_student);
		return error;
	}

	//3. 同步保存内存中的student_list到文件中
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