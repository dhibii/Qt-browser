#include "downloaditem.h"


downloaditem::downloaditem(QNetworkReply* telechargement,QString dos) : QWidget()

{
    doss=dos+"/hui.txt";
    annuler=new QPushButton("annuler",0);
    retele=new QPushButton("reesayer",0);
    infofichier= new QLabel;
    layoutv1=new QVBoxLayout;
    layoutv1->addSpacing(50);
    layoutv1->addWidget(annuler);
    layoutv1->addWidget(retele);
    layoutv1->addSpacing(50);

    progression=new QProgressBar;
    nomdufichier=new QLabel;
    layoutv2=new QVBoxLayout;
    layoutv2->addSpacing(50);
    layoutv2->addWidget(nomdufichier);
    layoutv2->addWidget(progression);
    layoutv2->addWidget(infofichier);
    layouth=new QHBoxLayout;
    layoutv2->addSpacing(50);

    layouth->addLayout(layoutv2);
    layouth->addLayout(layoutv1);
    layouth->setMargin(0);

    setLayout(layouth);
    setFixedSize(400,80);
    nomdufichier->setText(QFileInfo(telechargement->url().toString()).fileName());
    nomdufichier->setToolTip(telechargement->url().toString());
    progression->setMinimum(0);
    connect(telechargement,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(progress(qint64,qint64)));
    connect(telechargement,SIGNAL(finished()),this,SLOT(telechargementfini()));
}
void downloaditem::progress(qint64 recu, qint64 total)
{
    progression->setMaximum(total);
    progression->setValue(recu);
    infofichier->setText("telechargement: "+QString::number(recu)+" / "+QString::number(total));

}

void downloaditem::telechargementfini()
{
    QNetworkReply *reponse = qobject_cast<QNetworkReply *>(sender());
    if (reponse)
    {
        reponse->deleteLater();

        // Un code basique pour récupérer le vrai nom du fichier
        QFile fichierATelecharger(doss);
        fichierATelecharger.setFileName(QFileInfo(reponse->url().toString()).fileName());
        fichierATelecharger.open(QIODevice::WriteOnly | QIODevice::Truncate);
        fichierATelecharger.write(reponse->readAll());
        fichierATelecharger.close();

    }


}
