#pragma once
#ifndef STUDENT_SERVICE_H
#define STUDENT_SERVICE_H

#include "core/common.h"
#include "core/list.h"
#include "dao/student_manage/student_dao.h"

//学生服务接口
typedef struct {
	//增加学生
	ErrorCode(*add_student)(char* id, char* name, float gpa, char* major);
	//修改学生
	ErrorCode(*update_student)(char* id, char* name, float gpa, char* major);
	//查询（按学号）
	Student* (*get_student)(char* id);
	//删除（按学号）
	ErrorCode(*delete_student)(char* id);
	//统计分数-按照专业统计分数
	void (*caculate_gpa_by_major)();
	//获取所有学生信息
	LinkedList* (*get_all_students)();
	//打印所有学生信息
	void (*print_all_students)();
}StudentService;

//获取学生服务接口的实例
StudentService* get_student_service();

#endif