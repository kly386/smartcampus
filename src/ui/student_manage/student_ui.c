#include "ui/student_manage/student_ui.h"
#include <stdio.h>
#include <stdlib.h>
#include "core/common.h"
#include "service/student_manage/student_service.h"


//显示学生管理子系统的主页面
void show_student_menu() {
    printf("\n===== 学生信息管理系统 =====\n");
    printf("1. 添加学生\n");
    printf("2. 删除学生\n");
    printf("3. 修改学生信息\n");
    printf("4. 查询学生\n");
    printf("5. 显示所有学生\n");
    printf("6. 按专业统计GPA\n");
    printf("0. 返回主菜单\n");
    printf("===========================\n");
    printf("请选择操作: ");
}

// 添加学生页面
void add_student_ui() {
    char id[10], name[20], major[30];
    float gpa;

    //打印界面+信息录入
    printf("\n------ 添加学生 ------\n");
    printf("学号："); scanf_s("%9s", id, (unsigned)_countof(id));
    printf("姓名："); scanf_s("%19s", name, (unsigned)_countof(name));
    printf("GPA："); scanf_s("%f", &gpa);
    printf("专业："); scanf_s("%29s", major, (unsigned)_countof(major));


    //将新加入的学生，添加到“学生链表中”，并且获取添加成功与否的信息
    //调用student_service中的add_student来实现该操作
    ErrorCode error = get_student_service()->add_student(id, name, gpa, major);
    printf("%s\n", error_message(error));
}

// 删除学生页面--根据ID
void delete_student_ui() {
    char id[10];
    printf("\n------ 删除学生 ------\n");
    printf("请输入要删除的学生学号：");
    scanf_s("%9s", id, (unsigned)_countof(id));
    while (getchar() != '\n'); // 清除输入缓冲区

    // 先查询确认学生存在
    Student* stu = get_student_service()->get_student(id);
    if (stu == NULL) {
        printf("未找到学号为 %s 的学生！\n", id);
        system("pause");
        return;
    }

    // 显示学生信息供确认
    printf("\n找到以下学生:\n");
    printf("学号：%s\n", stu->id);
    printf("姓名：%s\n", stu->name);
    printf("GPA：%.2f\n", stu->gpa);
    printf("专业：%s\n\n", stu->major);

    // 确认删除
    printf("确认删除该学生？(Y/N): ");
    char confirm;
    scanf_s("%c", &confirm, 1);
    while (getchar() != '\n');

    if (confirm == 'Y' || confirm == 'y') {
        ErrorCode error = get_student_service()->delete_student(id);
        printf("\n%s\n", error_message(error));
    }
    else {
        printf("\n已取消删除操作\n");
    }
    system("pause");
}

// 查询学生页面--根据ID
void query_student_ui() {
    char id[10];
    printf("\n------ 查询学生 ------\n");
    printf("请输入学号：");
    scanf_s("%9s", id, (unsigned)_countof(id));
    while (getchar() != '\n'); // 清除输入缓冲区

    // 调用student_service的get_student实现该操作
    Student* stu = get_student_service()->get_student(id);

    // 打印学生信息
    if (stu == NULL) {
        printf("未找到学号为 %s 的学生！\n", id);
    }
    else {
        printf("\n===== 学生详细信息 =====\n");
        printf("学号：%s\n", stu->id);
        printf("姓名：%s\n", stu->name);
        printf("GPA：%.2f\n", stu->gpa);
        printf("专业：%s\n", stu->major);
        printf("========================\n");
    }
    system("pause"); // 暂停等待用户查看
}

// 修改学生信息
void update_student_ui() {
    char id[10], name[20], major[30];
    float gpa;

    printf("\n------ 修改学生信息 ------\n");
    printf("请输入要修改的学生学号：");
    scanf_s("%9s", id, (unsigned)_countof(id));
    while (getchar() != '\n'); // 清除输入缓冲区

    // 先获取学生信息
    Student* stu = get_student_service()->get_student(id);
    if (stu == NULL) {
        printf("未找到学号为 %s 的学生！\n", id);
        system("pause");
        return;
    }

    // 显示当前信息并获取新信息
    printf("\n当前学生信息:\n");
    printf("学号：%s\n", stu->id);
    printf("姓名：%s\n", stu->name);
    printf("GPA：%.2f\n", stu->gpa);
    printf("专业：%s\n\n", stu->major);

    printf("请输入新姓名（留空保持不变）：");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // 移除换行符
    if (strlen(name) == 0) {
        strcpy(name, stu->name); // 保持原值
    }

    printf("请输入新GPA（输入0保持不变）：");
    char gpa_str[20];
    fgets(gpa_str, sizeof(gpa_str), stdin);
    if (sscanf_s(gpa_str, "%f", &gpa) != 1 || gpa == 0) {
        gpa = stu->gpa; // 保持原值
    }

    printf("请输入新专业（留空保持不变）：");
    fgets(major, sizeof(major), stdin);
    major[strcspn(major, "\n")] = '\0';
    if (strlen(major) == 0) {
        strcpy(major, stu->major); // 保持原值
    }

    // 更新学生信息
    ErrorCode error = get_student_service()->update_student(id, name, gpa, major);
    printf("\n%s\n", error_message(error));
    system("pause");
}


// 列出所有学生信息
void list_all_student_ui() {
    printf("\n------ 学生列表 ------\n");

    // 获取学生链表
    LinkedList* list = get_student_service()->get_all_students();
    if (list == NULL || list->size == 0) {
        printf("暂无学生数据！\n");
        system("pause");
        return;
    }

    // 打印表头
    printf("%-10s %-20s %-8s %-30s\n", "学号", "姓名", "GPA", "专业");
    printf("------------------------------------------------------------\n");

    // 遍历链表打印每个学生信息
    ListIterator it = list_begin(list);
    int count = 0;
    while (it != NULL) {
        Student* stu = (Student*)it->data;
        if (stu != NULL) {
            printf("%-10s %-20s %-8.2f %-30s\n",
                stu->id, stu->name, stu->gpa, stu->major);
            count++;
        }
        it = list_next(it);
    }

    printf("\n共 %d 名学生\n", count);
    system("pause");
}

// 按专业统计信息

// 处理用户输入（1.添加 2.删除...)
// 处理用户输入
void handle_student_input() {
    int choice;
    while (1) {
        system("cls"); // 清屏
        show_student_menu();

        // 接收用户输入
        if (scanf_s("%d", &choice) != 1) {
            printf("输入无效，请输入一个数字.\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n'); // 清除输入缓冲区

        switch (choice) {
        case 1:
            add_student_ui();
            break;
        case 2:
            delete_student_ui();
            break;
        case 3:
            update_student_ui();
            break;
        case 4:
            query_student_ui();
            break;
        case 5:
            list_all_student_ui();
            break;
        case 6:
            printf("按专业统计GPA-待实现\n");
            system("pause");
            break;
        case 0:
            return; // 返回主界面
        default:
            printf("无效输入，请重新选择\n");
            system("pause");
        }
    }
}