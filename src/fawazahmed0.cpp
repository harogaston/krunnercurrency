#include "fawazahmed0.h"

#include <QtGlobal>
#include <QJsonArray>
#include <QJsonDocument>
#include <QUrlQuery>

CurrencyAPI::CurrencyAPI(Plasma::AbstractRunner *runner, Plasma::RunnerContext &context, const double amount, const QString &curr_1,
               const QString &curr_1_desc, const QString &curr_2, const QString &curr_2_desc)
        : m_runner(runner), m_context(context), m_amount(amount), m_curr_1(curr_1), m_curr_1_des(curr_1_desc), m_curr_2(curr_2), m_curr_2_desc(curr_2_desc) {
    m_manager = new QNetworkAccessManager(this);

    QUrl url = QUrl(QStringLiteral("https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies/%1/%2.json").arg(curr_1).arg(curr_2));      
    QNetworkRequest request(url);
    m_manager->get(request);
    connect(m_manager, &QNetworkAccessManager::finished, this, &CurrencyAPI::parseResult);
}

void CurrencyAPI::parseResult(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            
            double rate = jsonObj[m_curr_2].toDouble();
                            
            QString data = QStringLiteral("%1 %2").arg(m_amount * rate).arg(m_curr_2_desc);

            Plasma::QueryMatch match(m_runner);
            match.setText(data);
            match.setData(data);
            match.setId(data);
            match.setIconName(QStringLiteral("view-currency-list"));
            match.setRelevance(1.0);
            match.setType(Plasma::QueryMatch::HelperMatch);

            QList<Plasma::QueryMatch> matches;
            matches.append(match);
            m_context.addMatches(matches);
        }
    }

    Q_EMIT finished();
}

#include "moc_fawazahmed0.cpp"