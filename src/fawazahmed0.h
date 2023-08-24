#pragma once

#include <KRunner/AbstractRunner>
#include <QtNetwork/QNetworkReply>

class CurrencyAPI : public QObject
{
    Q_OBJECT

public:
    CurrencyAPI(Plasma::AbstractRunner*, Plasma::RunnerContext&, const double, const QString &, const QString &, const QString &, const QString &);

private Q_SLOTS:
   void parseResult(QNetworkReply*);

Q_SIGNALS:
	void finished();
   
private:
   Plasma::AbstractRunner * m_runner;
   QNetworkAccessManager * m_manager;
   Plasma::RunnerContext m_context;
   const double m_amount;
   const QString & m_curr_1;
   const QString & m_curr_1_des;
   const QString & m_curr_2;
   const QString & m_curr_2_desc;
};