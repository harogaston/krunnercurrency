#include "krunnercurrency.h"

#include <KLocalizedString>
#include <QFile>
#include <QJsonDocument>

CurrencyRunner::CurrencyRunner(QObject *parent, const KPluginMetaData &data, const QVariantList &args)
    : Plasma::AbstractRunner(parent, data, args)
{
    re = QRegularExpression(QStringLiteral("(?:exchange )?(\\d+)\\ ?(\\w{3,6})\\ to\\ (\\w{3,6})"));

    // Generate help text
    QStringList syntaxes = {QStringLiteral("exchange <%1> <%2> to <%3>").arg(i18n("amount")).arg(i18n("cur1")).arg(i18n("cur2")),
                            QStringLiteral("<%1> <%2> to <%3>").arg(i18n("amount")).arg(i18n("cur1")).arg(i18n("cur2"))};
    addSyntax(syntaxes, i18n("Input number and 3-letter currency codes"));
}

CurrencyRunner::~CurrencyRunner()
{
}

void CurrencyRunner::init()
{
    QFile currencies_file(QStringLiteral("currencies.json"));
    if (!currencies_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QJsonParseError error;
    QJsonDocument currencies_doc = QJsonDocument::fromJson(currencies_file.readAll(), &error);
    this->currencies = currencies_doc.toVariant().toMap();
}

void CurrencyRunner::match(Plasma::RunnerContext &context)
{
    // Parse query
    QString query = context.query();
    if (query.startsWith(QLatin1Char('?')) || query.length() <= 10) {
        return;
    }

    // Build matches
    QRegularExpressionMatch parsed_query = this->re.match(query);
    if (parsed_query.hasMatch() && parsed_query.lastCapturedIndex() == 3) {
        QString amount = parsed_query.captured(1);
        QString source_currency = parsed_query.captured(2);
        QString destination_currency = parsed_query.captured(3);

        source_currency = this->currencies.value(source_currency, source_currency.toUpper()).toString();
        destination_currency = this->currencies.value(destination_currency, destination_currency.toUpper()).toString();

        QString hint = QStringLiteral("Convert %1 %2 to %3").arg(amount).arg(source_currency).arg(destination_currency);
        Plasma::QueryMatch match = this->buildMatch(hint);

        Plasma::QueryMatch match2 = this->buildMatch(QStringLiteral("%1").arg(this->currencies.size()));

        QList<Plasma::QueryMatch> matches;
        matches.append(match);
        matches.append(match2);
        context.addMatches(matches);
    }
}

Plasma::QueryMatch CurrencyRunner::buildMatch(const QString &data)
{
    Plasma::QueryMatch match(this);
    match.setText(i18n("%1 ", data));
    match.setData(data);
    match.setId(data);
    match.setIconName(QStringLiteral("view-currency-list"));
    match.setRelevance(1.0);
    match.setType(Plasma::QueryMatch::HelperMatch);
    return match;
}

K_PLUGIN_CLASS_WITH_JSON(CurrencyRunner, "plasma-runner-krunner_currency.json")

#include "krunnercurrency.moc"