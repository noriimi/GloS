#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GloSConfig.h"
#include"ConfigSaver.hpp"
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
    void on_b_Save_clicked();
private:
    Ui::GloSConfigClass ui;
    std::vector<std::string> names;
    ConfigSaver cfgSaver{ "cfg.txt" };
};
