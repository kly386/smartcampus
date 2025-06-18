#pragma once
// dao/course_schedule/course_dao.h
#pragma once
#ifndef COURSE_DAO_H
#define COURSE_DAO_H

#include "../../core/list.h"
#include "../../core/course_schedule.h"

typedef struct {
    LinkedList* (*load_all)();
    ErrorCode(*save_all)(LinkedList* list);
    void (*free_course)(Course* course);
} CourseDAO;

CourseDAO* get_course_dao();

#endif // COURSE_DAO_H