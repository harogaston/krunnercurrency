#pragma once

#include <KRunner/AbstractRunner>

class CurrencyRunner : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    CurrencyRunner(QObject *parent, const KPluginMetaData &data, const QVariantList &args);
    ~CurrencyRunner() override;

public:
    void match(Plasma::RunnerContext &context) override;

protected:
    void init() override;

private:
    Plasma::QueryMatch buildMatch(const QString &data);
    QRegularExpression re;
    QMap<QString, QVariant> currencies;
};
