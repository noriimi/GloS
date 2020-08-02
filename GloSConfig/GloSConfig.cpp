#include "GloSConfig.h"
#include "../commons/PortsFinder.hpp"
#include "../commons/RtAudio/RtAudio.h"
GloSConfig::GloSConfig(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}
void GloSConfig::on_b_Port_clicked()
{
    PortsFinder fndr; 
    QStringList qst;
    ui.cB_Ports->clear();   
    fndr.find();
    for (int i = 0; i < fndr.numberOfPorts(); i++)
    {
        qst.append(QString::fromWCharArray(fndr.getFoundPort(i)));
        
    }
    ui.cB_Ports->addItems(qst);
    
}
void GloSConfig::on_cB_Ports_currentIndexChanged(const QString& name)
{
    ui.lE_Port->setText(name);
}
void GloSConfig::on_b_Audio_clicked()
{
    RtAudio snd;
    QStringList qst;
    names.clear();
    ui.cB_Audio->clear();
    for (int i = 0; i < snd.getDeviceCount(); i++)
    {
       qst.append(QString::number(i));
       names.push_back(snd.getDeviceInfo(i).name);
    }
    ui.cB_Audio->addItems(qst);

}
void GloSConfig::on_cB_Audio_currentIndexChanged(const QString& name)
{   
    ui.lE_Audio->setText(QString::fromStdString(names.at(name.toInt())));

}