#pragma once
// dao/course_schedule/schedule_dao.h
#pragma once
#ifndef SCHEDULE_DAO_H
#define SCHEDULE_DAO_H

#include "../../core/list.h"
#include "../../core/course_schedule.h"

typedef struct {
    /**
     * @brief ���ļ����������ſ�����
     * @return ���������ſε�����ָ��
     */
    LinkedList* (*load_all)();

    /**
     * @brief ���������ſ����ݵ��ļ�
     * @param list �ſ���������
     * @return �������������
     */
    ErrorCode(*save_all)(LinkedList* list);

    /**
     * @brief �ͷ��ſ��ڴ�
     * @param schedule Ҫ�ͷŵ��ſ�ָ��
     */
    void (*free_schedule)(Schedule* schedule);

    /**
     * @brief ����ID�����ſ�
     * @param id �ſ�ID
     * @return �ҵ����ſ�ָ�룬δ�ҵ�����NULL
     */
    Schedule* (*get_by_id)(int id);

    /**
     * @brief ���ʱ���ͻ
     * @param classroom_id ����ID
     * @param week �ܴ�
     * @param day ����
     * @param slot �ڴ�
     * @return ���ڳ�ͻ����1�����򷵻�0
     */
    int (*check_conflict)(int classroom_id, int week, int day, int slot);
} ScheduleDAO;

/**
 * @brief ��ȡ�ſ�DAO����
 * @return ScheduleDAOʵ��ָ��
 */
ScheduleDAO* get_schedule_dao();

#endif // SCHEDULE_DAO_H
