// create_teachers.c （独立工具）
#define _CRT_SECURE_NO_WARNINGS
#include "../core/course_schedule.h"
#include <stdio.h>
#include <string.h>

#define TEACHER_FILE "data/course_schedule/teachers.dat"

void create_initial_teachers() {
    Teacher teachers[5] = { 0 };

    // 初始化教师数据（使用strncpy_s）
    teachers[0] = (Teacher){ 1, "张三", "教授", "计算机科学与技术学院" };
    teachers[1] = (Teacher){ 2, "李四", "副教授", "信息工程学院" };
    teachers[2] = (Teacher){ 3, "王五", "讲师", "数学学院" };
    teachers[3] = (Teacher){ 4, "赵六", "教授", "物理学院" };
    teachers[4] = (Teacher){ 5, "钱七", "副教授", "化学化工学院" };

    FILE* file = fopen(TEACHER_FILE, "wb");
    if (file) {
        fwrite(teachers, sizeof(Teacher), 5, file);
        fclose(file);
        printf("初始教师数据已生成\n");
    }
    else {
        perror("创建文件失败");
    }
}

