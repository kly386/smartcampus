#pragma once
// service/course_schedule/schedule_service.h
#pragma once
#ifndef SCHEDULE_SERVICE_H
#define SCHEDULE_SERVICE_H

#include "../../core/list.h"
#include "../../core/course_schedule.h"

typedef struct {
    /**
     * @brief ��ȡ�����ſ���Ϣ
     * @return �ſ�����ָ��
     */
    LinkedList* (*get_all_schedules)();

    // �������񷽷�����...
    // ...ԭ������
    
    /**
     * @brief ����ſ�
     * @param schedule �ſ���Ϣ
     * @return ������
     */
    ErrorCode (*add_schedule)(Schedule* schedule);
    
    /**
     * @brief �����ſ�
     * @param id �ſ�ID
     * @param ��������...
     * @return ������
     */
    ErrorCode (*update_schedule)(int id, int course_id, int classroom_id,
                               int week, int day, int slot);
    
    /**
     * @brief ɾ���ſ�
     * @param id �ſ�ID
     * @return ������
     */
    ErrorCode (*delete_schedule)(int id);
    
    // ...��������
} ScheduleService;

/**
 * @brief ��ȡ�ſη���ʵ��
 */
ScheduleService* get_schedule_service();

#endif // SCHEDULE_SERVICE_H