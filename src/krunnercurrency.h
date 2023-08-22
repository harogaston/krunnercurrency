#pragma once

#include <KRunner/AbstractRunner>

class CurrencyRunner : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    CurrencyRunner(QObject *parent, const QVariantList &args);
    ~CurrencyRunner() override;

public:
    void match(Plasma::RunnerContext &context) override;
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;
};


