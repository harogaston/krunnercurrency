#include "krunnercurrency.h"
#include "currencyrepository.h"
#include "fawazahmed0.h"

#include <KLocalizedString>
#include <QFile>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>

CurrencyRunner::CurrencyRunner(QObject *parent, const KPluginMetaData &data, const QVariantList &args)
    : Plasma::AbstractRunner(parent, data, args)
{
    re = QRegularExpression(QStringLiteral("(?:exchange )?(\\d+)\\ ?(\\w{3,6})\\ to\\ (\\w{3,6})"));

    // Generate help text
    QStringList syntaxes = {QStringLiteral("exchange <%1> <%2> to <%3>").arg(i18n("amount")).arg(i18n("cur1")).arg(i18n("cur2")),
                            QStringLiteral("<%1> <%2> to <%3>").arg(i18n("amount")).arg(i18n("cur1")).arg(i18n("cur2"))};
    addSyntax(syntaxes, i18n("Input number and 3-letter currency codes"));

    setPriority(LowPriority);
}

CurrencyRunner::~CurrencyRunner()
{
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
        double amount = parsed_query.captured(1).toDouble();
        QString curr_1 = parsed_query.captured(2).toLower();
        QString curr_2 = parsed_query.captured(3).toLower();

        if (
            CurrencyRepository::currencies.contains(curr_1) &&
            CurrencyRepository::currencies.contains(curr_2)
        ) {
            QString curr_1_desc = CurrencyRepository::currencies.value(curr_1);
            QString curr_2_desc = CurrencyRepository::currencies.value(curr_2);

            if (!context.isValid()) {
                return;
            }

            QEventLoop loop;
            CurrencyAPI api(this, context, amount, curr_1, curr_1_desc, curr_2, curr_2_desc);
            connect(&api, &CurrencyAPI::finished, &loop, &QEventLoop::quit);
            loop.exec();
        }
    }
}

K_PLUGIN_CLASS_WITH_JSON(CurrencyRunner, "plasma-runner-krunner_currency.json")

#include "krunnercurrency.moc"