#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GloSConfig.h"
//#include "../GloSConfig/x64/Debug/uic/ui_GloSConfig.h"
class GloSConfig : public QMainWindow
{
    Q_OBJECT

public:
    GloSConfig(QWidget *parent = Q_NULLPTR);
private slots:
    void on_b_Port_clicked();
    void on_b_Audio_clicked();
    void on_cB_Ports_currentIndexChanged(const QString&);
    void on_cB_Audio_currentIndexChanged(const QString&);
private:
    Ui::GloSConfigClass ui;
    std::vector<std::string> names;


};
