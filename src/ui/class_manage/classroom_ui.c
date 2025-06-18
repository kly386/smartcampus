// ui/course_schedule/classroom_ui.c
#include "../include/ui/class_manage/classroom_ui.h"
#include "../include/service/class_manage/classroom_service.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_classroom_menu() {
    printf("\n===== 教室管理 =====\n");
    printf("1. 添加教室\n");
    printf("2. 修改教室信息\n");
    printf("3. 删除教室\n");
    printf("4. 查看所有教室\n");
    printf("0. 返回上级菜单\n");
    printf("====================\n");
    printf("请选择操作: ");
}

void add_classroom_ui() {
    int id, capacity, type;
    char building[10], number[10];

    printf("\n------ 添加教室 ------\n");
    printf("教室ID: ");
    scanf_s("%d", &id);
    getchar();

    printf("教学楼(如:A): ");
    scanf_s("%9s", building, (unsigned)_countof(building));
    getchar();

    printf("教室号(如:101): ");
    scanf_s("%9s", number, (unsigned)_countof(number));
    getchar();

    printf("容量: ");
    scanf_s("%d", &capacity);
    getchar();

    printf("类型(0:普通教室, 1:实验室): ");
    scanf_s("%d", &type);
    getchar();

    // 创建教室对象
    Classroom* new_classroom = (Classroom*)safe_malloc(sizeof(Classroom));
    new_classroom->id = id;
    strncpy_s(new_classroom->building, sizeof(new_classroom->building), building, _TRUNCATE);
    strncpy_s(new_classroom->number, sizeof(new_classroom->number), number, _TRUNCATE);
    new_classroom->capacity = capacity;
    new_classroom->type = type;

    // 调用服务层添加教室
    ErrorCode error = get_classroom_service()->add_classroom(new_classroom);
    printf("%s\n", error_message(error));
    system("pause");
}

void list_all_classrooms_ui() {
    printf("\n------ 教室列表 ------\n");

    LinkedList* list = get_classroom_service()->get_all_classrooms();
    if (list == NULL || list->size == 0) {
        printf("暂无教室数据！\n");
        system("pause");
        return;
    }

    printf("%-6s %-10s %-10s %-8s %-10s\n",
        "ID", "教学楼", "教室号", "容量", "类型");
    printf("----------------------------------------\n");

    ListIterator it = list_begin(list);
    while (it != NULL) {
        Classroom* room = (Classroom*)it->data;
        printf("%-6d %-10s %-10s %-8d %-10s\n",
            room->id, room->building, room->number,
            room->capacity, room->type == 0 ? "普通教室" : "实验室");
        it = list_next(it);
    }

    printf("\n共 %zu 间教室\n", list->size);
    system("pause");
}

void handle_classroom_input() {
    int choice;
    while (1) {
        system("cls");
        show_classroom_menu();

        if (scanf_s("%d", &choice) != 1) {
            printf("输入无效，请输入一个数字.\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            add_classroom_ui();
            break;
        case 2:
            printf("修改教室信息 - 待实现\n");
            system("pause");
            break;
        case 3:
            printf("删除教室 - 待实现\n");
            system("pause");
            break;
        case 4:
            list_all_classrooms_ui();
            break;
        case 0:
            return;
        default:
            printf("无效输入，请重新选择\n");
            system("pause");
        }
    }
}