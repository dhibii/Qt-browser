#ifndef FENPRINCIPALE
#define FENPRINCIPALE
#include "downloaditem.h"
#include<QFileDialog>
#include <QDesktopServices>
#include <QFile>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QTabBar>
#include <QAction>
#include <QLineEdit>
#include <QTabWidget>
#include <QStatusBar>
#include <QProgressBar>
#include <QLabel>
#include <QtWebKit>
#include <QWebView>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QUrl>
#include<QNetworkRequest>
#include <QListWidget>

class fenprincipale : public QMainWindow
{
    friend class downloaditem;
    Q_OBJECT
public:
    fenprincipale();
    void store(QString title,QString urlpage);
    friend void telechargementfini();
public slots:
    void openhist();
    void openbookmark();
    //slots du tab
    void ajoutertab(QString url="");
    void changetab(int tabn);
    void fermertab(int tabnumber);

    //slots de la page web
    void changeurl(QUrl Url );
    void changetitre (QString titre);

    //slots du status bar
    void debutchargement();
    void chargement(int n);
    void finchargement(bool x);

    //slots du toolbar

    void pagesuivante ();
    void pageprecedente ();
    void pageaccueill ();
    void actualiserpage();
    void  arreterchargement();
    void chargerpage();

    //telechargement
    void  telechargementTermine();
    void telechargerFichierAuto(QNetworkReply *reponse);
    void loadhisto();

    void historiquedelapage();

    void ouvrirf();
    void viderhis();
    void viderbookmark();
    void ajouterbookmark();
    void afficherbookmark();
    void supprbookmark();
    void supprhistorique();
    void ouvrirdt();
    void changerdossiertele();
private :


    void userTelecharger(const QNetworkRequest &request);

    //creation de la pageweb
    QWidget* createwebpage(QString urll="");

    // determiner la page actuelle
    QWebView* pageactuelle();

    void createmenu();
    void createactions();
    void createtoolbar();
    void createstatus();



    //les elements menu

    QMenu *apropos;
    QMenu *personnaliser;
    QMenu *fichier;
    QMenu *historique;
    QMenu *telechargement;
    QMenu *bookmark;
    QMenu *tootbookmark;
    QMenu *affichert;
    QMenu *ajoutert;
    //les element du toolbar
    QToolBar *toolbar;
    QAction *precedente;
    QAction *suivante;
    QAction *acceuil;
    QAction *actualiser;
    QAction *stop;
    QAction *aller;
    QAction *nouvelonglet;
    QLineEdit *adresse;
    QAction *ouvrirfichier;
    QAction *quitter;
    QAction *ajouterbook;
    QAction *afficherbook;
    QAction *privee;
    QAction *ouvrirt;
    QAction *changerdossier;
    //les elements du bar des status
    QProgressBar *progress;
    QLabel       *info;
    QWidget      *statuswidget;
    QHBoxLayout  *layouth;
    QWebHistory *history;

    QListWidget *liste;
    //les element du centre de l'application
    QTabWidget  *tabs;
    QTabBar     *tabsbar;
    QPushButton *nouvonglet;
    QListWidget *listwidget=NULL;
    QLabel *site=NULL;
    QVBoxLayout *layouthis=NULL;
    QWebView *pagehis=NULL;
    QFile *data=new QFile("historique.txt");
    QFile *datab= new QFile("bookmark.txt");
    QListWidget *listbook=NULL;
    QVBoxLayout *layoutbook=NULL;
    QLabel *nbrbookm=NULL;
    QLabel *nbrd=NULL;
    QList<downloaditem*> listtelechargement;
    QVBoxLayout *layoutd=NULL;
    QFile *datadossier=new QFile("dossiert.txt");

};
#endif

