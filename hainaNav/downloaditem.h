#ifndef DOWNLOADITEM_H
#define DOWNLOADITEM_H
#include <QFile>
#include <QFileInfo>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>


class downloaditem : public QWidget
{
    Q_OBJECT

public:
    downloaditem(QNetworkReply* telechargement,QString dos);
public slots:
    void progress(qint64 recu ,qint64 total);
    void telechargementfini();

private:
    QLabel *nomdufichier;
    QLabel *infofichier;
    QProgressBar *progression;
    QPushButton *annuler;
    QPushButton *retele;
    QVBoxLayout *layoutv1;
    QVBoxLayout *layoutv2;
    QHBoxLayout *layouth;
    QString doss;

};

#endif
