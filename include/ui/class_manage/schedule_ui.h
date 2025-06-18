// ui/course_schedule/schedule_ui.h
#pragma once
#ifndef SCHEDULE_UI_H
#define SCHEDULE_UI_H

#include "../core/list.h"
#include "../core/course_schedule.h"

/**
 * @brief ��ʾ�����ſ���Ϣ
 */
void view_all_schedules();

/**
 * @brief ��ʾ�ſι���˵�
 */
void show_schedule_menu();

/**
 * @brief �����ſι����û�����
 */
void handle_schedule_input();

/**
 * @brief ����ſν���
 */
void add_schedule_ui();

/**
 * @brief �޸��ſν���
 */
void modify_schedule_ui();

/**
 * @brief ɾ���ſν���
 */
void delete_schedule_ui();


#endif // SCHEDULE_UI_H