/*#include "TaskManager.hpp"*/
/*#include "Arduino.h"*/
/**/
/*void TaskManager::addTask(ITaskible &task, const char *const pcName,*/
/*                          const uint32_t usStackDepth, UBaseType_t uxPriority) {*/
/*  xTaskHandle handle;*/
/*  xTaskCreate(taskRunner, pcName, usStackDepth, &task, uxPriority, &handle);*/
/*  tasks.push_back({task, handle});*/
/*}*/
/**/
/*void TaskManager::taskRunner(void *task) {*/
/*  while (true) {*/
/*    ITaskible *taskible = static_cast<ITaskible *>(task);*/
/*    taskible->update();*/
/*    vTaskDelay(10);*/
/*  }*/
/*}*/
