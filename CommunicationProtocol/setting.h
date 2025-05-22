#ifndef SETTING_H
#define SETTING_H

#include <QSettings>

class Setting : public QSettings
{
public:
    explicit Setting(QObject *parent = nullptr);
    QSettings* GetSettings();//获取设置指针
    void AddSettingsValue(QString key,QString value);//增加设置
    QStringList GetAllKeys();//获取所有键值
    QString GetValue(QString key);//获取key的键值
private:
    QSettings *m_pSettings = nullptr;
};

#endif // SETTING_H
