#include<stdio.h>  
#include<stdlib.h>  
#include"dao/student_manage/student_dao.h"  
#include"core/list.h"									  

#define DATA_FILE "data/student_manage/students.dat"  

LinkedList* load_all_student() {  
	FILE* file = fopen(DATA_FILE, "rb");  
	if (file == NULL) {  
		printf("无法读取文件！\n");  
		return NULL;  
	}  

	LinkedList* students = list_create();  

	Student student;  
	while (fread(&student, sizeof(Student), 1, file) == 1) {  
		Student* new_student = (Student*)malloc(sizeof(Student));  
		memcpy(new_student, &student, sizeof(Student));  
		list_append(students, new_student);  
	}  
	fclose(file);  
	return students;  
}  

ErrorCode save_all_student(LinkedList* list) {  
	FILE* file = fopen(DATA_FILE, "wb");  
	if (file == NULL) {  
		printf("无法打开文件进行写入！\n");  
		return ERR_FILE_OPEN;  
	}  

	ListIterator it = list_begin(list);  
	while (it != NULL) {  
		Student* stu = (Student*)it->data;  
		if (fwrite(stu, sizeof(Student), 1, file) != 1) {  
			fclose(file);  
			return ERR_FILE_WRITE;  
		}  
		it = list_next(it);  
	}  
	fclose(file);  
	return SUCCESS;  
}  

void free_student_memory(Student* student) {  
	if (student != NULL) {  
		free(student);  
	}  
}  

StudentDAO* get_student_dao() {  
	static StudentDAO dao = {  
		.load_all = load_all_student,  
		.save_all = save_all_student,  
		.free_student = free_student_memory  
	};  
	return &dao;  
}