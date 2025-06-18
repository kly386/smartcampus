
#include "../include/dao/class_manage/schedule_dao.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCHEDULE_FILE "data/course_schedule/schedules.dat"

static LinkedList* schedule_list = NULL;

LinkedList* load_all_schedules() {
    FILE* file = fopen(SCHEDULE_FILE, "rb");
    if (file == NULL) {
        schedule_list = list_create();
        return schedule_list;
    }

    schedule_list = list_create();
    Schedule schedule;

    while (fread(&schedule, sizeof(Schedule), 1, file) == 1) {
        Schedule* new_schedule = (Schedule*)safe_malloc(sizeof(Schedule));
        *new_schedule = schedule;
        list_append(schedule_list, new_schedule);
    }

    fclose(file);
    return schedule_list;
}

ErrorCode save_all_schedules(LinkedList* list) {
    if (list == NULL) return ERR_INVALID_INPUT;

    FILE* file = fopen(SCHEDULE_FILE, "wb");
    if (file == NULL) return ERR_FILE_OPEN;

    ListIterator it = list_begin(list);
    while (it != NULL) {
        Schedule* schedule = (Schedule*)it->data;
        if (fwrite(schedule, sizeof(Schedule), 1, file) != 1) {
            fclose(file);
            return ERR_FILE_WRITE;
        }
        it = list_next(it);
    }

    fclose(file);
    return SUCCESS;
}

Schedule* get_schedule_by_id(int id) {
    if (schedule_list == NULL) load_all_schedules();

    ListIterator it = list_begin(schedule_list);
    while (it != NULL) {
        Schedule* schedule = (Schedule*)it->data;
        if (schedule->id == id) {
            return schedule;
        }
        it = list_next(it);
    }
    return NULL;
}

int check_time_conflict(int classroom_id, int week, int day, int slot) {
    if (schedule_list == NULL) load_all_schedules();

    ListIterator it = list_begin(schedule_list);
    while (it != NULL) {
        Schedule* schedule = (Schedule*)it->data;
        if (schedule->classroom_id == classroom_id &&
            schedule->week == week &&
            schedule->day == day &&
            schedule->slot == slot) {
            return 1; // ´æÔÚ³åÍ»
        }
        it = list_next(it);
    }
    return 0; // ÎÞ³åÍ»
}

void free_schedule_memory(Schedule* schedule) {
    if (schedule != NULL) {
        safe_free((void**)&schedule);
    }
}

ScheduleDAO* get_schedule_dao() {
    static ScheduleDAO dao = {
        .load_all = load_all_schedules,
        .save_all = save_all_schedules,
        .free_schedule = free_schedule_memory,
        .get_by_id = get_schedule_by_id,
        .check_conflict = check_time_conflict
    };
    return &dao;
}