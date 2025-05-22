#include "setting.h"

Setting::Setting(QObject *parent)
    : QSettings{parent}
{
    m_pSettings = new QSettings("ONE","TWO");
}

QSettings* Setting::GetSettings()
{
    return m_pSettings;
}

void Setting::AddSettingsValue(QString key, QString value)
{
    m_pSettings->setValue(key,value);
}

QStringList Setting::GetAllKeys()
{
    return m_pSettings->allKeys();
}

QString Setting::GetValue(QString key)
{
    return m_pSettings->value(key).toString();
}
