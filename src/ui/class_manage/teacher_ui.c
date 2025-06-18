// ui/course_schedule/teacher_ui.c
#include "../include/ui/class_manage/teacher_ui.h"
#include "../include/service/class_manage//teacher_service.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_teacher_menu() {
    printf("\n===== 教师管理 =====\n");
    printf("1. 添加教师\n");
    printf("2. 修改教师信息\n");
    printf("3. 删除教师\n");
    printf("4. 查看所有教师\n");
    printf("0. 返回上级菜单\n");
    printf("=====================\n");
    printf("请选择操作: ");
}

void add_teacher_ui() {
    int id;
    char name[20];
    char title[20];
    char department[30];

    printf("\n------ 添加教师 ------\n");
    printf("教师ID: ");
    scanf_s("%d", &id);
    getchar(); // 清除输入缓冲区

    printf("姓名: ");
    scanf_s("%19s", name, (unsigned)_countof(name));
    getchar();

    printf("职称: ");
    scanf_s("%19s", title, (unsigned)_countof(title));
    getchar();

    printf("所属院系: ");
    scanf_s("%29s", department, (unsigned)_countof(department));
    getchar();

    ErrorCode error = get_teacher_service()->add_teacher(id, name, title, department);
    printf("%s\n", error_message(error));
    system("pause");
}

// ui/course_schedule/teacher_ui.c (新增函数)
void modify_teacher_ui() {
    int id;
    printf("\n------ 修改教师信息 ------\n");
    printf("请输入要修改的教师ID: ");
    scanf_s("%d", &id);
    getchar();

    // 获取现有教师信息
    Teacher* teacher = get_teacher_service()->get_teacher(id);
    if (teacher == NULL) {
        printf("错误: 未找到该教师记录！\n");
        system("pause");
        return;
    }

    // 显示当前信息
    printf("\n当前教师信息:\n");
    printf("1. 姓名: %s\n", teacher->name);
    printf("2. 职称: %s\n", teacher->title);
    printf("3. 所属院系: %s\n", teacher->department);

    // 获取修改信息
    char name[20], title[20], department[30];
    int choice;
    printf("\n请选择要修改的项(1-3, 0保存并退出): ");
    while (1) {
        scanf_s("%d", &choice);
        getchar();

        if (choice == 0) break;

        switch (choice) {
        case 1:
            printf("新的姓名: ");
            scanf_s("%19s", name, (unsigned)_countof(name));
            getchar();
            strncpy_s(teacher->name, sizeof(teacher->name), name, _TRUNCATE);
            break;
        case 2:
            printf("新的职称: ");
            scanf_s("%19s", title, (unsigned)_countof(title));
            getchar();
            strncpy_s(teacher->title, sizeof(teacher->title), title, _TRUNCATE);
            break;
        case 3:
            printf("新的所属院系: ");
            scanf_s("%29s", department, (unsigned)_countof(department));
            getchar();
            strncpy_s(teacher->department, sizeof(teacher->department), department, _TRUNCATE);
            break;
        default:
            printf("无效选择！\n");
        }
        printf("请继续选择要修改的项(1-3, 0保存并退出): ");
    }

    // 调用服务层更新教师
    ErrorCode result = get_teacher_service()->update_teacher(teacher->id,
        teacher->name, teacher->title, teacher->department);

    if (result != SUCCESS) {
        printf("修改教师信息失败: %s\n", error_message(result));
    }
    else {
        printf("教师信息修改成功！\n");
    }
    system("pause");
}


// ui/course_schedule/teacher_ui.c (新增函数)
void delete_teacher_ui() {
    int teacher_id;
    printf("\n------ 删除教师 ------\n");
    printf("请输入要删除的教师ID: ");
    scanf_s("%d", &teacher_id);
    getchar();

    // 先获取教师信息用于确认
    Teacher* teacher = get_teacher_service()->get_teacher(teacher_id);
    if (teacher == NULL) {
        printf("错误: 未找到该教师记录！\n");
        system("pause");
        return;
    }

    // 显示教师详情
    printf("\n即将删除以下教师:\n");
    printf("教师ID: %d\n", teacher->id);
    printf("姓名: %s\n", teacher->name);
    printf("职称: %s\n", teacher->title);
    printf("所属院系: %s\n", teacher->department);

    // 确认删除
    printf("\n确认删除？(Y/N): ");
    char confirm;
    scanf_s("%c", &confirm, 1);
    getchar();

    if (confirm == 'Y' || confirm == 'y') {
        ErrorCode result = get_teacher_service()->delete_teacher(teacher->id);
        if (result != SUCCESS) {
            printf("删除教师失败: %s\n", error_message(result));
        }
        else {
            printf("教师删除成功！\n");
        }
    }
    else {
        printf("已取消删除操作\n");
    }
    system("pause");
}


void list_all_teachers_ui() {
    printf("\n------ 教师列表 ------\n");

    LinkedList* list = get_teacher_service()->get_all_teachers();
    if (list == NULL || list->size == 0) {
        printf("暂无教师数据！\n");
        system("pause");
        return;
    }

    printf("%-6s %-20s %-20s %-30s\n", "ID", "姓名", "职称", "院系");
    printf("------------------------------------------------------------\n");

    ListIterator it = list_begin(list);
    while (it != NULL) {
        Teacher* teacher = (Teacher*)it->data;
        printf("%-6d %-20s %-20s %-30s\n",
            teacher->id, teacher->name, teacher->title, teacher->department);
        it = list_next(it);
    }

    printf("\n共 %zu 名教师\n", list->size);
    system("pause");
}

// ui/course_schedule/teacher_ui.c (更新handle_teacher_input函数)
// 修改 handle_teacher_input 函数中的 case 2,3,4 部分
void handle_teacher_input() {
    int choice;
    while (1) {
        system("cls");
        show_teacher_menu();

        if (scanf_s("%d", &choice) != 1) {
            printf("输入无效，请输入数字！\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            add_teacher_ui();
            break;
        case 2:
            modify_teacher_ui();  // 移除 initialize_teacher_data_if_needed()
            break;
        case 3:
            delete_teacher_ui();  // 移除 initialize_teacher_data_if_needed()
            break;
        case 4:
            list_all_teachers_ui();
            break;
        case 0:
            return;
        default:
            printf("无效选择，请重新输入！\n");
            system("pause");
        }
    }
}