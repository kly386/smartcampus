#pragma once
// core/course_schedule.h
#pragma once
#ifndef COURSE_SCHEDULE_H
#define COURSE_SCHEDULE_H

#include "../../include/core/common.h"

// 教师结构体
typedef struct {
    int id;
    char name[20];
    char title[20];
    char department[30];
} Teacher;

// 课程结构体
typedef struct {
    int id;
    char name[30];
    int credit;
    int hours;
    int teacher_id;
    int student_count;
} Course;

// 教室结构体
typedef struct {
    int id;
    char building[10];
    char number[10];
    int capacity;
    int type; // 0:普通, 1:实验室
} Classroom;

// 课表结构体
typedef struct {
    int id;
    int course_id;
    int classroom_id;
    int week;   // 1-16
    int day;    // 1-7
    int slot;   // 1-12
} Schedule;

#endif // COURSE_SCHEDULE_H