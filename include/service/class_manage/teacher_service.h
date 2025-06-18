#pragma once
// service/course_schedule/teacher_service.h
#pragma once
#ifndef TEACHER_SERVICE_H
#define TEACHER_SERVICE_H

#include "../../core/common.h"
#include "../../core/list.h"
#include "../../core/course_schedule.h"

typedef struct {
    ErrorCode(*add_teacher)(int id, const char* name, const char* title, const char* department);
    ErrorCode(*update_teacher)(int id, const char* name, const char* title, const char* department);
    Teacher* (*get_teacher)(int id);
    ErrorCode(*delete_teacher)(int id);
    LinkedList* (*get_all_teachers)();
    void (*print_all_teachers)();
} TeacherService;

TeacherService* get_teacher_service();

#endif // TEACHER_SERVICE_H
