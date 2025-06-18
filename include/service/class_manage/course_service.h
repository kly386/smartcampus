// include/service/class_manage/course_service.h
#ifndef COURSE_SERVICE_H
#define COURSE_SERVICE_H

#include "../core/common.h"
#include "../core/list.h"
#include"schedule_service.h"
//typedef struct Course {
//    int id;
//    char name[30];
//    int credit;
//    int hours;
//    int teacher_id;
//    int student_count;
//} Course;

typedef struct CourseService {
    ErrorCode(*add_course)(Course* course);
    LinkedList* (*get_all_courses)();
    Course* (*get_course)(int id);
    ErrorCode(*update_course)(int id, Course* course);
    ErrorCode(*delete_course)(int id);
} CourseService;

CourseService* get_course_service();

#endif