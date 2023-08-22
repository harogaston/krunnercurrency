#include "krunnercurrency.h"

#include <KLocalizedString>

CurrencyRunner::CurrencyRunner(QObject *parent, const QVariantList &args)
: Plasma::AbstractRunner(parent, args) {}

CurrencyRunner::~CurrencyRunner() {}

void CurrencyRunner::match(Plasma::RunnerContext &context)
{
    QList<Plasma::QueryMatch> matches;
    Plasma::QueryMatch match(this);

    const QString longName = QStringLiteral("Lo has logrado!");

    match.setText(i18n("%1 ", longName));
    match.setData(longName);
    match.setId(longName);
    match.setIconName(QStringLiteral("view-currency-list"));
    match.setRelevance(1.0);
    match.setType(Plasma::QueryMatch::ExactMatch);

    matches.append(match);
    context.addMatches(matches);
}

void CurrencyRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
    Q_UNUSED(match)
}


K_PLUGIN_CLASS_WITH_JSON(CurrencyRunner, "plasma-runner-krunnercurrency.json")

#include "krunnercurrency.moc"