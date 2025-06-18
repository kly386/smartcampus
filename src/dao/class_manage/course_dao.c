// src/dao/class_manage/course_dao.c
#include "../../include/dao/class_manage/course_dao.h"
#include"../../include/core/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COURSE_FILE "data/course_schedule/courses.dat"

LinkedList* load_all_courses() {
    FILE* file;
    errno_t err = fopen_s(&file, COURSE_FILE, "rb");
    if (err != 0 || file == NULL) {
        return NULL;
    }

    LinkedList* courses = list_create();
    Course course;

    while (fread(&course, sizeof(Course), 1, file) == 1) {
        Course* new_course = (Course*)malloc(sizeof(Course));
        memcpy(new_course, &course, sizeof(Course));
        list_append(courses, new_course);
    }

    fclose(file);
    return courses;
}

ErrorCode save_all_courses(LinkedList* list) {
    FILE* file;
    errno_t err = fopen_s(&file, COURSE_FILE, "wb");
    if (err != 0 || file == NULL) {
        return ERR_FILE_OPEN;
    }

    ListIterator it = list_begin(list);
    while (it != NULL) {
        Course* course = (Course*)it->data;
        if (fwrite(course, sizeof(Course), 1, file) != 1) {
            fclose(file);
            return ERR_FILE_WRITE;
        }
        it = list_next(it);
    }

    fclose(file);
    return SUCCESS;
}

void free_course_memory(Course* course) {
    if (course != NULL) {
        free(course);
    }
}

// 初始化课程数据文件
void initialize_course_data() {
    // 创建数据目录
    mkdir("data");
    mkdir("data/course_schedule");

    FILE* file;
    errno_t err = fopen_s(&file, COURSE_FILE, "rb");
    if (err != 0 || file == NULL) {
        err = fopen_s(&file, COURSE_FILE, "wb");
        if (err == 0 && file != NULL) {
            // 初始化一些课程数据
            Course courses[] = {
                {1, "C语言编程", 3, 48, 1, 50},
                {2, "数据结构", 4, 64, 2, 45}
            };

            for (int i = 0; i < sizeof(courses) / sizeof(courses[0]); i++) {
                fwrite(&courses[i], sizeof(Course), 1, file);
            }

            fclose(file);
        }
    }
    else {
        fclose(file);
    }
}

CourseDAO* get_course_dao() {
    static CourseDAO dao = {
        .load_all = load_all_courses,
        .save_all = save_all_courses,
        .free_course = free_course_memory
    };
    return &dao;
}