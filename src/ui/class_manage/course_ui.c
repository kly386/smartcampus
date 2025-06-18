// ui/class_manage/course_ui.c
#include "../../include/ui/class_manage/course_ui.h"
#include "../../include/service/class_manage/course_service.h"
#include "../core/common.h"
#include "../core/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_course_menu() {
    printf("\n===== 课程管理 =====\n");
    printf("1. 添加课程\n");
    printf("2. 修改课程信息\n");
    printf("3. 删除课程\n");
    printf("4. 查看所有课程\n");
    printf("0. 返回主菜单\n");
    printf("=====================\n");
    printf("请选择操作: ");
}

void add_course_ui() {
    int id, credit, hours, teacher_id, student_count;
    char name[30];

    printf("\n------ 添加课程 ------\n");
    printf("课程ID: ");
    scanf_s("%d", &id);
    getchar();

    printf("课程名称: ");
    scanf_s("%29s", name, (unsigned)_countof(name));
    getchar();

    printf("学分: ");
    scanf_s("%d", &credit);
    getchar();

    printf("课时: ");
    scanf_s("%d", &hours);
    getchar();

    printf("任课教师ID: ");
    scanf_s("%d", &teacher_id);
    getchar();

    printf("学生数量: ");
    scanf_s("%d", &student_count);
    getchar();

    // 创建新课程对象并添加到列表
    Course* new_course = (Course*)safe_malloc(sizeof(Course));
    new_course->id = id;
    strncpy_s(new_course->name, sizeof(new_course->name), name, _TRUNCATE);
    new_course->credit = credit;
    new_course->hours = hours;
    new_course->teacher_id = teacher_id;
    new_course->student_count = student_count;

    // 调用服务层添加课程
    ErrorCode error = get_course_service()->add_course(new_course);
    printf("%s\n", error_message(error));
    system("pause");
}

void modify_course_ui() {
    int id;
    printf("\n------ 修改课程信息 ------\n");
    printf("请输入要修改的课程ID: ");
    scanf_s("%d", &id);
    getchar();

    // 获取要修改的课程信息
    Course* course = get_course_service()->get_course(id);
    if (course == NULL) {
        printf("错误: 未找到该课程记录。\n");
        system("pause");
        return;
    }

    // 显示当前信息
    printf("\n当前课程信息:\n");
    printf("1. 课程名称: %s\n", course->name);
    printf("2. 学分: %d\n", course->credit);
    printf("3. 课时: %d\n", course->hours);
    printf("4. 任课教师ID: %d\n", course->teacher_id);
    printf("5. 学生数量: %d\n", course->student_count);

    // 获取修改信息
    Course modified = *course;
    int choice;
    printf("\n请选择要修改的项(1-5, 0表示退出): ");
    while (1) {
        scanf_s("%d", &choice);
        getchar();

        if (choice == 0) break;

        switch (choice) {
        case 1:
            printf("新的课程名称: ");
            scanf_s("%29s", modified.name, (unsigned)_countof(modified.name));
            getchar();
            break;
        case 2:
            printf("新的学分: ");
            scanf_s("%d", &modified.credit);
            getchar();
            break;
        case 3:
            printf("新的课时: ");
            scanf_s("%d", &modified.hours);
            getchar();
            break;
        case 4:
            printf("新的任课教师ID: ");
            scanf_s("%d", &modified.teacher_id);
            getchar();
            break;
        case 5:
            printf("新的学生数量: ");
            scanf_s("%d", &modified.student_count);
            getchar();
            break;
        default:
            printf("无效选择，请重新输入。\n");
        }
        printf("请选择要修改的项(1-5, 0表示退出): ");
    }

    // 调用服务层更新课程信息
    ErrorCode result = get_course_service()->update_course(id, &modified);

    if (result != SUCCESS) {
        printf("修改课程信息失败: %s\n", error_message(result));
    }
    else {
        printf("课程信息修改成功。\n");
    }
    system("pause");
}

void delete_course_ui() {
    int course_id;
    printf("\n------ 删除课程 ------\n");
    printf("请输入要删除的课程ID: ");
    scanf_s("%d", &course_id);
    getchar();

    // 先获取课程信息进行确认
    Course* course = get_course_service()->get_course(course_id);
    if (course == NULL) {
        printf("错误: 未找到该课程记录。\n");
        system("pause");
        return;
    }

    // 显示课程信息
    printf("\n即将删除的课程信息:\n");
    printf("课程ID: %d\n", course->id);
    printf("课程名称: %s\n", course->name);
    printf("学分: %d\n", course->credit);
    printf("课时: %d\n", course->hours);
    printf("任课教师ID: %d\n", course->teacher_id);
    printf("学生数量: %d\n", course->student_count);

    // 确认删除
    printf("\n确认删除吗?(Y/N): ");
    char confirm;
    scanf_s("%c", &confirm, 1);
    getchar();

    if (confirm == 'Y' || confirm == 'y') {
        ErrorCode result = get_course_service()->delete_course(course_id);
        if (result != SUCCESS) {
            printf("删除课程失败: %s\n", error_message(result));
        }
        else {
            printf("课程删除成功。\n");
        }
    }
    else {
        printf("取消删除操作。\n");
    }
    system("pause");
}

void list_all_courses_ui() {
    printf("\n------ 课程列表 ------\n");

    LinkedList* list = get_course_service()->get_all_courses();
    if (list == NULL || list->size == 0) {
        printf("暂无课程数据。\n");
        system("pause");
        return;
    }

    printf("%-6s %-30s %-6s %-6s %-10s %-6s\n",
        "ID", "课程名称", "学分", "课时", "教师ID", "学生数");
    printf("------------------------------------------------------------\n");

    ListIterator it = list_begin(list);
    while (it != NULL) {
        Course* course = (Course*)it->data;
        printf("%-6d %-30s %-6d %-6d %-10d %-6d\n",
            course->id, course->name, course->credit,
            course->hours, course->teacher_id, course->student_count);
        it = list_next(it);
    }

    printf("\n共 %zu 门课程\n", list->size);
    system("pause");
}

void handle_course_input() {
    int choice;
    while (1) {
        system("cls");
        show_course_menu();

        if (scanf_s("%d", &choice) != 1) {
            printf("输入无效，请重新输入一个整数。\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            add_course_ui();
            break;
        case 2:
            modify_course_ui();
            break;
        case 3:
            delete_course_ui();
            break;
        case 4:
            list_all_courses_ui();
            break;
        case 0:
            return;
        default:
            printf("无效选择，请重新输入。\n");
            system("pause");
        }
    }
}