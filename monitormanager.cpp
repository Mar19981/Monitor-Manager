#include "monitormanager.h"
#include <iostream>

MonitorManager::MonitorManager(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    HWND handler = GetDesktopWindow();
    HMONITOR monitor = MonitorFromWindow(handler, MONITOR_DEFAULTTOPRIMARY);
    DWORD monitorCount{};

    bool success = GetNumberOfPhysicalMonitorsFromHMONITOR(monitor, &monitorCount);
    if (!success) throw std::runtime_error("Failed to enumerate physical monitors!");

    physicalMonitors.resize(monitorCount);
    if (!monitorCount) throw std::runtime_error("Failed to find any monitor!");

    GetPhysicalMonitorsFromHMONITOR(monitor, monitorCount, physicalMonitors.data());
    for (auto monitor : physicalMonitors) {
        ui.monitorsCombo->addItem(QString::fromWCharArray(monitor.szPhysicalMonitorDescription));
    }
    ui.monitorsCombo->setCurrentIndex(0);
    monitorHandle = physicalMonitors.at(0).hPhysicalMonitor;
    DWORD minimum{}, current{}, maximum{}, monitorCapabilities{}, colorTemperatures{};

    GetMonitorCapabilities(monitorHandle, &monitorCapabilities, &colorTemperatures);

    GetMonitorBrightness(monitorHandle, &minimum, &current, &maximum);


    SetMonitorBrightness(monitorHandle, 50);
    ui.brightnessSpin->setMinimum(minimum);
    ui.brightnessSpin->setValue(current);
    ui.brightnessSpin->setMaximum(maximum);   
    GetMonitorContrast(monitorHandle, &minimum, &current, &maximum);
    ui.contrastSpin->setMinimum(minimum);
    ui.contrastSpin->setValue(current);
    ui.contrastSpin->setMaximum(maximum);

    connect(ui.brightnessSpin, &QSpinBox::valueChanged, this, [=](int value) {SetMonitorBrightness(monitorHandle, value); });
    connect(ui.contrastSpin, &QSpinBox::valueChanged, this, [=](int value) {SetMonitorContrast(monitorHandle, value); });
    connect(ui.monitorsCombo, &QComboBox::currentIndexChanged, this, [=](int index) { monitorHandle = physicalMonitors.at(index).hPhysicalMonitor; });


}

MonitorManager::~MonitorManager()
{}
