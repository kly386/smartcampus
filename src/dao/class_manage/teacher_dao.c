
#include "../include/dao/class_manage/teacher_dao.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEACHER_FILE "data/course_schedule/teachers.dat"

#define TEACHER_FILE "data/course_schedule/teachers.dat"

// 替换原有的 load_all_teachers 函数实现
LinkedList* load_all_teachers() {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, TEACHER_FILE, "rb");
    if (err != 0 || file == NULL) {
        printf("无法打开教师数据文件！\n");
        return NULL;
    }

    LinkedList* teachers = list_create();
    if (teachers == NULL) {
        fclose(file);
        return NULL;
    }

    Teacher teacher;
    while (fread(&teacher, sizeof(Teacher), 1, file) == 1) {
        Teacher* new_teacher = (Teacher*)safe_malloc(sizeof(Teacher));
        if (new_teacher == NULL) {
            list_destroy(&teachers, (void (*)(void*))get_teacher_dao()->free_teacher);
            fclose(file);
            return NULL;
        }
        *new_teacher = teacher;

        ErrorCode error = list_append(teachers, new_teacher);
        if (error != SUCCESS) {
            safe_free((void**)&new_teacher);
            list_destroy(&teachers, (void (*)(void*))get_teacher_dao()->free_teacher);
            fclose(file);
            return NULL;
        }
    }

    if (ferror(file)) {
        list_destroy(&teachers, (void (*)(void*))get_teacher_dao()->free_teacher);
        teachers = NULL;
    }

    fclose(file);

    if (teachers != NULL) {
        printf("成功加载 %zu 名教师数据\n", teachers->size);
    }
    else {
        printf("加载教师数据失败\n");
    }

    return teachers;
}

       

ErrorCode save_all_teachers(LinkedList* list) {
    if (list == NULL) {
        return ERR_INVALID_INPUT;
    }

    FILE* file = NULL;
    errno_t err = fopen_s(&file, TEACHER_FILE, "wb");
    if (err != 0 || file == NULL) {
        return ERR_FILE_OPEN;
    }

    ErrorCode result = SUCCESS;
    ListIterator it = list_begin(list);
    while (it != NULL) {
        Teacher* teacher = (Teacher*)it->data;
        if (fwrite(teacher, sizeof(Teacher), 1, file) != 1) {
            result = ERR_FILE_WRITE;
            break;
        }
        it = list_next(it);
    }

    if (fflush(file) != 0) {
        result = ERR_FILE_WRITE;
    }

    fclose(file);
    return result;
}

void free_teacher_memory(Teacher* teacher) {
    safe_free((void**)&teacher);
}

// 修改 initialize_teacher_data_if_needed 函数
void initialize_teacher_data_if_needed() {
    // 检查并创建目录
    _mkdir("data");
    _mkdir("data/course_schedule");

    FILE* file = NULL;
    errno_t err = fopen_s(&file, TEACHER_FILE, "rb");
    if (err != 0 || file == NULL) {
        Teacher teachers[5] = {
            {1, "张三", "教授", "计算机科学与技术学院"},
            {2, "李四", "副教授", "信息工程学院"},
            {3, "王五", "讲师", "数学学院"},
            {4, "赵六", "教授", "物理学院"},
            {5, "钱七", "副教授", "化学化工学院"}
        };

        err = fopen_s(&file, TEACHER_FILE, "wb");
        if (err == 0 && file != NULL) {
            size_t written = fwrite(teachers, sizeof(Teacher), 5, file);
            fclose(file);
            if (written != 5) {
                remove(TEACHER_FILE); // 写入失败则删除文件
            }
        }
    }
    else {
        fclose(file);
    }
}

TeacherDAO* get_teacher_dao() {
    static TeacherDAO dao = {
        .load_all = load_all_teachers,
        .save_all = save_all_teachers,
        .free_teacher = free_teacher_memory
    };
    return &dao;
}