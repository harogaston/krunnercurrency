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

private:
    QRegularExpression re;
};
