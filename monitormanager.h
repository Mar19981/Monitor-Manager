#pragma once
#include <vector>
#include <stdexcept>
#include <windows.h>
#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#include <QtWidgets/QMainWindow>
#include "ui_monitormanager.h"

class MonitorManager : public QMainWindow
{
    Q_OBJECT

public:
    MonitorManager(QWidget *parent = nullptr);
    ~MonitorManager();

private:
    HANDLE monitorHandle;
    std::vector<PHYSICAL_MONITOR> physicalMonitors;
    Ui::MonitorManagerClass ui;
};
