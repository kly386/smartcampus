#pragma once
// dao/course_schedule/teacher_dao.h
#pragma once
#ifndef TEACHER_DAO_H
#define TEACHER_DAO_H

#include "../../core/list.h"
#include "../../core/course_schedule.h"

typedef struct {
    LinkedList* (*load_all)();
    ErrorCode(*save_all)(LinkedList* list);
    void (*free_teacher)(Teacher* teacher);
} TeacherDAO;

TeacherDAO* get_teacher_dao();

#endif // TEACHER_DAO_H
