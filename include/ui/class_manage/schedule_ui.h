// ui/course_schedule/schedule_ui.h
#pragma once
#ifndef SCHEDULE_UI_H
#define SCHEDULE_UI_H

#include "../core/list.h"
#include "../core/course_schedule.h"

/**
 * @brief 显示所有排课信息
 */
void view_all_schedules();

/**
 * @brief 显示排课管理菜单
 */
void show_schedule_menu();

/**
 * @brief 处理排课管理用户输入
 */
void handle_schedule_input();

/**
 * @brief 添加排课界面
 */
void add_schedule_ui();

/**
 * @brief 修改排课界面
 */
void modify_schedule_ui();

/**
 * @brief 删除排课界面
 */
void delete_schedule_ui();


#endif // SCHEDULE_UI_H