#pragma once
// service/course_schedule/classroom_service.h
#pragma once
#ifndef CLASSROOM_SERVICE_H
#define CLASSROOM_SERVICE_H

#include "../../core/list.h"
#include "../../core/course_schedule.h"

typedef struct {
    ErrorCode(*add_classroom)(Classroom* classroom);
    Classroom* (*get_classroom)(int id);
    LinkedList* (*get_all_classrooms)();
    // 其他函数声明...
    // classroom_service.h 补充
    ErrorCode(*update_classroom)(int id, const char* building, const char* number, int capacity, int type);
    ErrorCode(*delete_classroom)(int id);
} ClassroomService;

ClassroomService* get_classroom_service();

#endif // CLASSROOM_SERVICE_H
