// ui/course_schedule/schedule_ui.c
#include "../include/ui/class_manage/schedule_ui.h"
#include "../include/service/class_manage//schedule_service.h"
#include "../include/service/class_manage/course_service.h"
#include "../include/service/class_manage/classroom_service.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>

void add_schedule_ui() {
    Schedule new_schedule;
    printf("\n------ 添加新排课 ------\n");

    // 获取排课信息
    printf("排课ID: ");
    scanf_s("%d", &new_schedule.id);
    getchar();

    printf("课程ID: ");
    scanf_s("%d", &new_schedule.course_id);
    getchar();

    // 验证课程是否存在
    if (get_course_service()->get_course(new_schedule.course_id) == NULL) {
        printf("错误: 课程不存在！\n");
        system("pause");
        return;
    }

    printf("教室ID: ");
    scanf_s("%d", &new_schedule.classroom_id);
    getchar();

    // 验证教室是否存在
    if (get_classroom_service()->get_classroom(new_schedule.classroom_id) == NULL) {
        printf("错误: 教室不存在！\n");
        system("pause");
        return;
    }

    printf("周次(1-16): ");
    scanf_s("%d", &new_schedule.week);
    getchar();

    printf("星期(1-7): ");
    scanf_s("%d", &new_schedule.day);
    getchar();

    printf("节次(1-12): ");
    scanf_s("%d", &new_schedule.slot);
    getchar();

    // 调用服务层添加排课
    ErrorCode result = get_schedule_service()->add_schedule(&new_schedule);
    if (result != SUCCESS) {
        printf("添加排课失败: %s\n", error_message(result));
    }
    else {
        printf("排课添加成功！\n");
    }
    system("pause");
}

//void delete_schedule_ui() {
//    int schedule_id;
//    printf("\n------ 删除排课 ------\n");
//    printf("请输入要删除的排课ID: ");
//    scanf_s("%d", &schedule_id);
//    getchar();
//
//    // 先获取排课信息用于确认
//    Schedule* schedule = get_schedule_service()->get_schedule(schedule_id);
//    if (schedule == NULL) {
//        printf("错误: 未找到该排课记录！\n");
//        system("pause");
//        return;
//    }
//
//    // 显示排课详情
//    printf("\n即将删除以下排课:\n");
//    printf("排课ID: %d\n", schedule->id);
//    printf("课程ID: %d\n", schedule->course_id);
//    printf("教室ID: %d\n", schedule->classroom_id);
//    printf("时间: 第%d周 星期%d 第%d节\n",
//        schedule->week, schedule->day, schedule->slot);
//
//    // 确认删除
//    printf("\n确认删除？(Y/N): ");
//    char confirm;
//    scanf_s("%c", &confirm, 1);
//    getchar();
//
//    if (confirm == 'Y' || confirm == 'y') {
//        ErrorCode result = get_schedule_service()->delete_schedule(schedule_id);
//        if (result != SUCCESS) {
//            printf("删除排课失败: %s\n", error_message(result));
//        }
//        else {
//            printf("排课删除成功！\n");
//        }
//    }
//    else {
//        printf("已取消删除操作\n");
//    }
//    system("pause");
//}
//
//void modify_schedule_ui() {
//    int schedule_id;
//    printf("\n------ 修改排课信息 ------\n");
//    printf("请输入要修改的排课ID: ");
//    scanf_s("%d", &schedule_id);
//    getchar();
//
//    // 获取现有排课信息
//    Schedule* schedule = get_schedule_service()->get_schedule(schedule_id);
//    if (schedule == NULL) {
//        printf("错误: 未找到该排课记录！\n");
//        system("pause");
//        return;
//    }
//
//    // 显示当前信息
//    printf("\n当前排课信息:\n");
//    printf("1. 课程ID: %d\n", schedule->course_id);
//    printf("2. 教室ID: %d\n", schedule->classroom_id);
//    printf("3. 周次: %d\n", schedule->week);
//    printf("4. 星期: %d\n", schedule->day);
//    printf("5. 节次: %d\n", schedule->slot);
//
//    // 获取修改信息
//    Schedule modified = *schedule;
//    int choice;
//    printf("\n请选择要修改的项(1-5, 0保存并退出): ");
//    while (1) {
//        scanf_s("%d", &choice);
//        getchar();
//
//        if (choice == 0) break;
//
//        switch (choice) {
//        case 1:
//            printf("新的课程ID: ");
//            scanf_s("%d", &modified.course_id);
//            getchar();
//            break;
//        case 2:
//            printf("新的教室ID: ");
//            scanf_s("%d", &modified.classroom_id);
//            getchar();
//            break;
//        case 3:
//            printf("新的周次(1-16): ");
//            scanf_s("%d", &modified.week);
//            getchar();
//            break;
//        case 4:
//            printf("新的星期(1-7): ");
//            scanf_s("%d", &modified.day);
//            getchar();
//            break;
//        case 5:
//            printf("新的节次(1-12): ");
//            scanf_s("%d", &modified.slot);
//            getchar();
//            break;
//        default:
//            printf("无效选择！\n");
//        }
//        printf("请继续选择要修改的项(1-5, 0保存并退出): ");
//    }
//
//    // 调用服务层更新排课
//    ErrorCode result = get_schedule_service()->update_schedule(schedule_id,
//        modified.course_id, modified.classroom_id,
//        modified.week, modified.day, modified.slot);
//
//    if (result != SUCCESS) {
//        printf("修改排课失败: %s\n", error_message(result));
//    }
//    else {
//        printf("排课修改成功！\n");
//    }
//    system("pause");
//}

void view_all_schedules() {
    printf("\n===== 所有排课信息 =====\n");

    // 获取排课服务实例
    ScheduleService* service = get_schedule_service();
    if (service == NULL) {
        printf("排课服务初始化失败！\n");
        system("pause");
        return;
    }

    // 获取所有排课数据
    LinkedList* schedules = service->get_all_schedules();
    if (schedules == NULL || schedules->size == 0) {
        printf("暂无排课数据！\n");
        system("pause");
        return;
    }

    // 打印表头
    printf("%-6s %-10s %-15s %-10s %-10s %-10s %-15s\n",
        "ID", "课程ID", "课程名称", "教室ID", "周次", "星期", "节次");
    printf("------------------------------------------------------------\n");

    // 遍历排课数据
    ListIterator it = list_begin(schedules);
    while (it != NULL) {
        Schedule* schedule = (Schedule*)it->data;

        // 获取课程信息
        Course* course = get_course_service()->get_course(schedule->course_id);
        const char* course_name = course ? course->name : "未知课程";

        printf("%-6d %-10d %-15s %-10d %-10d %-10d %-15d\n",
            schedule->id,
            schedule->course_id,
            course_name,
            schedule->classroom_id,
            schedule->week,
            schedule->day,
            schedule->slot);

        it = list_next(it);
    }

    printf("\n共 %zu 条排课记录\n", schedules->size);
    system("pause");
}

void show_schedule_menu() {
    printf("\n===== 排课管理菜单 =====\n");
    printf("1. 查看所有排课\n");
    printf("2. 添加排课\n");
    printf("3. 修改排课\n");
    printf("4. 删除排课\n");
    printf("0. 返回上级菜单\n");
    printf("========================\n");
    printf("请选择操作: ");
}

void handle_schedule_input() {
    int choice;
    while (1) {
        system("cls");
        show_schedule_menu();

        if (scanf_s("%d", &choice) != 1) {
            printf("输入无效，请输入数字！\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            view_all_schedules();
            break;
        case 2:
            add_schedule_ui();
            break;
        case 3:
            //modify_schedule_ui();
            break;
        case 4:
           // delete_schedule_ui();
            break;
        case 0:
            return;
        default:
            printf("无效选择，请重新输入！\n");
            system("pause");
        }
    }
}