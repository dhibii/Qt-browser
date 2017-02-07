#include "mainwindow.h"


fenprincipale::fenprincipale():QMainWindow()
{

    createactions();
    createmenu() ;
    createtoolbar();
    createstatus();


    //creation des tabs
    nouvonglet= new QPushButton(QIcon("plus.png"),"");
    connect (nouvonglet,SIGNAL(clicked()),this,SLOT(ajoutertab()));
    tabs=new QTabWidget();


    tabs->addTab(createwebpage(),"nouvel onglet");
    tabs->setTabsClosable(1);
    tabs->setUsesScrollButtons(true);
    tabs->setMovable(1);
    tabs->setCornerWidget(nouvonglet);

    connect(tabs,SIGNAL(tabCloseRequested(int)),this,SLOT(fermertab(int)));
    connect(tabs,SIGNAL(currentChanged(int)),this,SLOT(changetab(int)) );
    setCentralWidget(tabs);
    //options
    setMinimumSize(600,350);
    setWindowIcon(QIcon("hainavigo.png"));

    QNetworkProxyFactory::setUseSystemConfiguration(true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);

}


//ajouter ,trouver,permuter et fermer des tabs

QWebView* fenprincipale::pageactuelle()
{
    return tabs->currentWidget()->findChild<QWebView *>();
}

void fenprincipale::fermertab(int tabnumber)
{
    if (tabs->count()==1)
    {

        QMessageBox::information(this,"info","il faut au moin un onglet <br/>dans votre navigateur!<br/><img src='smile.png'></img>");
    }
    if(tabs->count()>1) tabs->removeTab(tabnumber);

}

void fenprincipale::ajoutertab(QString url)
{
    tabs->addTab(createwebpage(url),"nouvel onglet");
    tabs->setCurrentIndex(tabs->count()-1);

    adresse->setText("http://");
    adresse->setFocus();

}

void fenprincipale::changetab(int tabn)
{
    tabs->setTabText(tabn, pageactuelle()->title());
    QString adr = (pageactuelle()->url()).toString();
    if (adr=="qrc:/html/html/accueil.html")
    {
        adresse->setText("http://");
        adresse->setFocus();
    }
    else
    {
        adresse->setText(adr);
    }
}

//creation d'une page web
QWidget* fenprincipale::createwebpage(QString urll)
{

    QWidget *pageonglet = new QWidget;

    QWebView *pageweb = new QWebView;
    QVBoxLayout *layoutv=new QVBoxLayout;

    layoutv->addWidget(pageweb);
    layoutv->setContentsMargins(0,0,0,0);
    pageonglet->setLayout(layoutv);
   
    pageweb->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    pageweb->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    pageweb->settings()->setAttribute(QWebSettings::JavaEnabled,true);
    pageweb->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows,true);

    pageweb->settings()->setAttribute(QWebSettings::AutoLoadImages, true);
      
    pageweb->page()->setForwardUnsupportedContent(true);
    connect(pageweb->page(), SIGNAL(unsupportedContent(QNetworkReply *)), this, SLOT(telechargerFichierAuto(QNetworkReply *)));
    if (urll=="")
    {
        pageweb->load(QUrl("qrc:/html/html/accueil.html"));
    }
    else
    {
        pageweb->load(QUrl(urll));
    }
    /*pageweb->setZoomFactor(5); zoooooooooooooooooom option
    pageweb->setTextSizeMultiplier(1.2);


    */
    
    connect(pageweb,SIGNAL(loadStarted()),this,SLOT(debutchargement()));
    connect(pageweb,SIGNAL(loadProgress(int)),this,SLOT(chargement(int)));
    connect(pageweb,SIGNAL(loadFinished(bool)),this,SLOT(finchargement(bool)));
    connect(pageweb,SIGNAL(urlChanged(QUrl)),this,SLOT(changeurl(QUrl)));
    connect(pageweb,SIGNAL(titleChanged(QString)),this,SLOT(changetitre(QString)));
    //connect(pageweb,SIGNAL(linkClicked(QUrl)),this,SLOT(pageaccueill()));

    return pageonglet;


}

//changer url et titre

void fenprincipale::changeurl(QUrl Url)
{
    QString adr=Url.toString();
    if(adr=="qrc:/html/html/accueil.html")
    {
        adresse->setText("http://");
        adresse->setFocus();
    }
    else
    {
        adresse->setText(adr);
    }
}
void fenprincipale::changetitre(QString titre)
{
    QString titrecourt=titre;
    if (titre.length()>30) titrecourt=titre.left(27)+"...";
    setWindowTitle(titre);
    tabs->setTabText(tabs->currentIndex(), titrecourt);
}


//creation des actions

void fenprincipale::createactions()
{

    acceuil=new QAction (QIcon(":/icons/acceuil.png"),"page d'acceuil",0);
    connect(acceuil,SIGNAL(triggered()),this,SLOT(pageaccueill()));



    precedente=new QAction (QIcon(":/icons/precedente.png"),"page precedente",0);
    connect(precedente,SIGNAL(triggered()),this,SLOT(pageprecedente()));

    suivante =new QAction (QIcon(":/icons/suivante.png"),"page suivante",0);
    connect(suivante,SIGNAL(triggered()),this,SLOT(pagesuivante()));

    stop=new QAction (QIcon(":/icons/stop.png"),"stop",0);
    connect(stop,SIGNAL(triggered()),this,SLOT(arreterchargement()));

    aller=new QAction (QIcon(":/icons/go.png"),"aller a",0);
    connect(aller,SIGNAL(triggered()),this,SLOT(chargerpage()));

    actualiser=new QAction(QIcon(":/icons/actualiser.png"),"actualiser",0);
    connect(actualiser,SIGNAL(triggered()),this,SLOT(actualiserpage()));

    ouvrirfichier =new QAction("Ouvrir fichier",0);
    connect(ouvrirfichier,SIGNAL(triggered()),this,SLOT(ouvrirf()));

    nouvelonglet=new QAction(QIcon("plus.png"),"nouvel onglet",0);
    connect (nouvelonglet,SIGNAL(triggered()),this,SLOT(ajoutertab()));

    ajouterbook=new QAction(QIcon("star.png"),"Ajouter Bookmark",0);
    connect(ajouterbook,SIGNAL(triggered()),this,SLOT(ajouterbookmark()));

    afficherbook=new QAction("tout les bookmarks",0);
    connect(afficherbook,SIGNAL(triggered()),this,SLOT(afficherbookmark()));

    quitter=new QAction("Quitter",0);
    connect(quitter,SIGNAL(triggered()),qApp,SLOT(quit()));

    privee =new QAction(QIcon("private.png"),"Activer le mode privé",0);
    privee->setCheckable(true);

    ouvrirt=new QAction("ouvrir dossier",0);
    connect(ouvrirt,SIGNAL(triggered()),this,SLOT(ouvrirdt()));
    changerdossier=new QAction("changer dossier",0);
    changerdossier->setToolTip("changer le dossier de telechargement");
    connect(changerdossier,SIGNAL(triggered()),this,SLOT(changerdossiertele()));

    adresse=new QLineEdit("");
    connect(adresse,SIGNAL(returnPressed()),this,SLOT(chargerpage()));

}

void fenprincipale::pageaccueill()
{
    pageactuelle()->load(QUrl("qrc:/html/html/accueil.html"));
    // adresse->setText("http://");
    adresse->setFocus();
}

void fenprincipale::pageprecedente()
{
    pageactuelle()->back();
}

void fenprincipale::pagesuivante()
{
    pageactuelle()->forward();
}

void fenprincipale::arreterchargement()
{
    pageactuelle()->stop();
}

void fenprincipale::chargerpage()
{
    QUrl Url( adresse->text());
    pageactuelle()->load(Url);
}


void fenprincipale::actualiserpage()
{
    pageactuelle()->reload();
}


//creation du menu
void fenprincipale::createmenu()
{

    // telechargement=menuBar()->addMenu("telechargement");
    //historique=menuBar()->addMenu("historique");
    fichier=menuBar()->addMenu("fichier");
    fichier->addAction(acceuil);
    fichier->addAction(privee);
    fichier->addAction(precedente);
    fichier->addAction(suivante);
    fichier->addAction(actualiser);
    fichier->addAction(nouvelonglet);
    fichier->addAction(ouvrirfichier);
    fichier->addAction(quitter);

    historique =menuBar()->addMenu("historique");
    bookmark=menuBar()->addMenu("bookmark");
    bookmark->addAction(ajouterbook);
    telechargement=menuBar()->addMenu("telechargement");
     affichert=telechargement->addMenu("afficher");
    // ajoutert=telechargement->addMenu("ajouter");
     telechargement->addAction(ouvrirt);
     telechargement->addAction(changerdossier);
    // bookmark->addAction(afficherbook);
    tootbookmark=  bookmark->addMenu("tout les bookmark");
    connect(tootbookmark,SIGNAL(aboutToShow()),this,SLOT(afficherbookmark()));
    connect(historique,SIGNAL(aboutToShow()),this,SLOT(historiquedelapage()));
    apropos = menuBar()->addMenu("apropos");

}

//creation du toolbar

void fenprincipale::createtoolbar()
{
    toolbar = addToolBar("outils");
    toolbar->addAction(acceuil);
    toolbar->addAction(precedente);
    toolbar->addAction(suivante);
    toolbar->addAction(stop);
    toolbar->addAction(actualiser);
    toolbar->addWidget(adresse);
    toolbar->addAction(ajouterbook);
    toolbar->addAction(aller);



}


//gestion du status bar

void fenprincipale::createstatus()
{
    progress = new QProgressBar;
    info =new QLabel("");

    statuswidget=new QWidget;
    layouth= new QHBoxLayout;
    layouth->addWidget(progress);
    layouth->addWidget(info);
    statuswidget->setLayout(layouth);
    statuswidget->setMaximumHeight(30);
    statusBar()->addWidget(statuswidget,1);


}


void fenprincipale::debutchargement()
{
    info->setVisible(1);
    progress->setVisible(1);
    info->setText("debut...");
}
void fenprincipale::chargement(int n)
{
    info->setVisible(1);
    progress->setVisible(1);
    info->setText("en cours...");
    progress->setValue(n);
};
void fenprincipale::finchargement(bool x)
{
    if(x)
    {
        QWebView *pagecharge = qobject_cast<QWebView*>(sender());
        if (!(privee->isChecked()))
        {
            store(pagecharge->title(),(pagecharge->url()).toString());
        }
        else
        {
            pagecharge->history()->clear();
        };
        statusBar()->showMessage("pret !",2000);

        progress->setValue(0);
        info->setVisible(0);
        progress->setVisible(0);
    }
    else
    {
        info->setText("echec ");
        progress->setValue(0);
    }
}







//telechargement
void fenprincipale::telechargerFichierAuto(QNetworkReply *reponse)
{
    QString dossier;

    datadossier->open(QFile::ReadOnly);
    QTextStream in(datadossier);
    in.readLineInto(&dossier,300);
    if(dossier.length()==0)
    {
        dossier="/home/dh/téléchargements";
    };

    datadossier->close();
    downloaditem *itemd =  new downloaditem(reponse,dossier);
    if(nbrd)delete(nbrd);
    nbrd=new QLabel;
    listtelechargement.append(itemd);
    if(layoutd)delete(layoutd);

    layoutd=new QVBoxLayout;
    int i;
    for(i=0; i<listtelechargement.length(); i++)
    {
        layoutd->addWidget(listtelechargement[i]);

    }
    nbrd->setText("pour cette cession vous avez "+QString::number(i+1)+" telechargements");

    affichert->setLayout(layoutd);




    statusBar()->showMessage(" un telechargement a commencé",850);

    // Au cas où le téléchargement se termine avant que l'utilisateur voit
    // la 1ere boite.
    //  connect(reponse, SIGNAL(finished()), messageBox, SLOT(close()));
}
void fenprincipale::telechargementTermine()
{
    QNetworkReply *reponse = qobject_cast<QNetworkReply *>(sender());
    if (reponse)
    {
        reponse->deleteLater();

        // Un code basique pour récupérer le vrai nom du fichier
        QFile fichierATelecharger("dh");
        fichierATelecharger.setFileName(QFileInfo(reponse->url().toString()).fileName());
        fichierATelecharger.open(QIODevice::WriteOnly |
                                 QIODevice::Truncate);
        fichierATelecharger.write(reponse->readAll());
        fichierATelecharger.close();
        QMessageBox *messageBox = new QMessageBox(
            QMessageBox::Information, "Téléchargement",
            "Téléchargement terminé", QMessageBox::Ok, this);
        messageBox->setModal(true);
        messageBox->setAttribute(Qt::WA_DeleteOnClose);
        messageBox->show();
    }
}


void fenprincipale:: historiquedelapage()
{
    // if(pagehis) delete(pagehis);

    pagehis=(pageactuelle());
    int nbrSite = pagehis->history()->count();
    if (site) delete(site);
    site = new QLabel("", this);
    site->setText("Il y a "+ QString::number(nbrSite)  +"sites dans l'historique de cette onglet");

    // Bouton vider l'historique
    QPushButton *touthistorique=new QPushButton("tout");
    touthistorique->setToolTip("afficher tout l'historique");
    connect(touthistorique,SIGNAL(clicked()),this,SLOT(loadhisto()));

    QPushButton *allera = new QPushButton("aller", this);
    connect(allera,SIGNAL(clicked()),this,SLOT(openhist()));
    if (listwidget)delete(listwidget);
    listwidget =new QListWidget;
    // Affichage de la liste de l'historique

    QList<QWebHistoryItem> listhis=(pagehis->history()->items());


    for(int i =nbrSite-1 ; i>=0 ; i--)
    {
        // Pour chaque page de l'historique, on récupère son url converti en QString et on l'ajoute à la liste
        listwidget->addItem(listhis[i].title());
        // listwidget->item(i)->setIcon(liste[i].icon());
        listwidget->item(nbrSite-1-i)->setToolTip(listhis[i].url().toString());
        listwidget->item(nbrSite-1-i)->setTextColor(QColor(0,0,200));
        listwidget->item(nbrSite-1-i)->setBackgroundColor(QColor(0,200,0,50));

    }

    // "listeHistorique" contient maintenant tous les url de l'historique, on peut l'utiliser pour le modèle

    listwidget->setMinimumHeight(140);
    // Layout
    if (layouthis)delete(layouthis);

    layouthis = new QVBoxLayout;
    layouthis->addWidget(site);
    layouthis->addWidget(touthistorique);
    layouthis->addWidget(listwidget);
    layouthis->addWidget(allera);


    historique->setLayout(layouthis);

}
void fenprincipale::openhist()
{
    if(listwidget->currentItem()) ajoutertab(listwidget->currentItem()->toolTip());
    else
    {
        QMessageBox::information(0,"information !!","selectionner un historique !");
    }
//listwidget->deleteLater();
}


void fenprincipale::ouvrirf()
{
    QString fchier="file://"+QFileDialog::getOpenFileName(this, "Ouvrir un fichier","/home/dh","*(*.*)");

    if (fchier.length()==7)
    {
        QMessageBox::information(this, "Fichier", "pas de fichier selectionnée");
    }
    else
    {
        ajoutertab(fchier);
    };
}


void fenprincipale::store(QString title,QString urlpage)
{

    if (data->open(QFile::Append))
    {
        data->seek(0);
        QTextStream out(data);
        out << title<<"\n"<<urlpage<<"\n";
        data->close();
    }

}


void fenprincipale::loadhisto()
{
    data->open(QFile::ReadOnly);
    QTextStream stream(data);
    QString line;

    if (listwidget)delete(listwidget);
    listwidget =new QListWidget;

    // Affichage de la liste de l'historique
    //QList<QString> listhis ;

    int j=0;
    while( stream.readLineInto(&line,500))
    {

        listwidget->addItem(line);
        listwidget->item(0)->setToolTip("line");
        listwidget->item(j)->setToolTip(stream.readLine(200));
        listwidget->item(j)->setTextColor(QColor(0,0,150));
        listwidget->item(j)->setBackgroundColor(QColor(0,200,0,50));


        j++;
    }
    if(!j)
    {
        listwidget->addItem("..PAS D'HISTORIQUE.. ");
        listwidget->item(0)->setBackgroundColor(QColor(200,0,0,60));
        listwidget->item(0)->setTextColor(QColor(0,0,0));
    };
    if(j)
    {
        listwidget->setMinimumHeight(200);
    }
    QPushButton *allera = new QPushButton("aller", this);
    connect(allera,SIGNAL(clicked()),this,SLOT(openhist()));

    QPushButton *pagehistorique=new QPushButton("page his");
    pagehistorique->setToolTip("afficher l'historique de cette page");
    connect(pagehistorique,SIGNAL(clicked()),this,SLOT( historiquedelapage()));
    pagehistorique->setToolTip("afficher tout l'historique");

    QPushButton *supprhisto=new  QPushButton("supprimer ce lien");
    connect(supprhisto,SIGNAL(clicked()),this,SLOT(supprhistorique()));

    QPushButton *vider=new QPushButton("vider historique");
    vider->setToolTip("tout les anciens historiques seront perdu!");
    connect(vider,SIGNAL(clicked()),this,SLOT(viderhis()));
    if (site) delete(site);
    site = new QLabel("", this);
    site->setText("Il y a "+ QString::number(j)  +" sites dans l'historique");
    if (layouthis)delete(layouthis);

    layouthis = new QVBoxLayout;
    layouthis->addWidget(site);
    layouthis->addWidget(pagehistorique);

    layouthis->addWidget(listwidget);
    layouthis->addWidget(vider);
    layouthis->addWidget(supprhisto);
    layouthis->addWidget(allera);
    historique->setLayout(layouthis);
    data->close();
}
void fenprincipale::supprhistorique()
{
    if(listwidget->currentItem())
    {
        delete listwidget->currentItem();

        data->open(QFile::WriteOnly);
        QTextStream out(data);
        for(int m=0; m<(listwidget->count()); m++)
        {
            out<<listwidget->item(m)->text()<<"\n"<<listwidget->item(m)->toolTip()<<"\n";
        }
        data->close();
        loadhisto();
    }
    else
    {
        QMessageBox::information(historique,"information !!","selectionner un lien !");
    }

}

void fenprincipale:: viderhis()
{
    data->open(QFile::WriteOnly);
    data->close();
    historiquedelapage();

}

void fenprincipale::ajouterbookmark()
{
    QWebView *page=pageactuelle();
    QString title=page->title();
    bool nouveau=true;
    QTextStream out(datab);
    datab->open(QFile::ReadOnly);
    QString ligne;
    int p=0;
    while(out.readLineInto(&ligne,150)&&nouveau)
    {
        if ((p%2)==0)
        {
            if (title==ligne)nouveau=false;
        };
        p++;
    };
    datab->close();
    if(nouveau)
    {
        datab->open(QFile::Append);

        out<<page->title()<<"\n"<<(page->url()).toString()<<"\n";
        statusBar()->showMessage("<< "+title+" >>est ajouté avec succès",1500);
        datab->close();
    }
    else
    {
        QMessageBox::information(tootbookmark,"information !!","ce bookmark est deja existant !\n voir bookmark:"+QString::number((p/2)+1)+".");
    }
}
void fenprincipale::afficherbookmark()
{
    if(listbook)delete(listbook);
    listbook=new QListWidget;
    datab->open(QFile::ReadOnly);
    QTextStream streamb(datab);
    QString line;
    int k=0;
    while( streamb.readLineInto(&line,190))
    {

        listbook->addItem(line);
        listbook->item(k)->setToolTip(streamb.readLine(200));
        listbook->item(k)->setTextColor(QColor(0,0,150));
        listbook->item(k)->setBackgroundColor(QColor(0,200,0,50));


        k++;
    }
    datab->close();
    if(!k)
    {
        listbook->addItem("..PAS DE BOOKMARK.. ");
        listbook->item(0)->setBackgroundColor(QColor(200,0,0,60));
        listbook->item(0)->setTextColor(QColor(0,0,0));
    };
    if(k)
    {
        listbook->setMinimumSize(200,200);
    }
    if (nbrbookm) delete(nbrbookm);
    nbrbookm= new QLabel("", this);
    nbrbookm->setText("Vous avez "+ QString::number(k)  +" boookmark");

    QPushButton *allerab = new QPushButton("aller", 0);
    connect(allerab,SIGNAL(clicked()),this,SLOT(openbookmark()));
    QPushButton *viderbook = new QPushButton("vider");
    connect(viderbook,SIGNAL(clicked()),this,SLOT(viderbookmark()));

    QPushButton *supprbook = new QPushButton("supprimer ce bookm.");
    connect(supprbook,SIGNAL(clicked()),this,SLOT(supprbookmark()));
    if(layoutbook)delete(layoutbook);
    layoutbook=new QVBoxLayout;
    layoutbook->addWidget(nbrbookm);
    layoutbook->addWidget(viderbook);
    layoutbook->addWidget(listbook);
    layoutbook->addWidget(supprbook);
    layoutbook->addWidget(allerab);

    tootbookmark->setLayout(layoutbook);
}
void fenprincipale:: viderbookmark()
{
    int faire=QMessageBox::warning(tootbookmark,"Attention !!","tout vos sites favoris seront pedues",QMessageBox::Yes,QMessageBox::No);
    if(faire==QMessageBox::Yes)
    {
        datab->open(QFile::WriteOnly);
        datab->close();

        afficherbookmark();
    };

}
void fenprincipale::openbookmark()
{
    if(listbook->currentItem()) ajoutertab(listbook->currentItem()->toolTip());
    else
    {
        QMessageBox::information(tootbookmark,"information !!","selectionner un bookmark !");
    }

}
void fenprincipale::supprbookmark()
{
    if(listbook->currentItem())
    {
        delete listbook->currentItem();

        datab->open(QFile::WriteOnly);
        QTextStream out(datab);
        for(int m=0; m<(listbook->count()); m++)
        {
            out<<listbook->item(m)->text()<<"\n"<<listbook->item(m)->toolTip()<<"\n";
        }
        datab->close();
        afficherbookmark();
    }
    else
    {
        QMessageBox::information(tootbookmark,"information !!","selectionner un bookmark !");
    }

}

/*void fenprincipale::gestiondetelechargement()

{
   setup(ui)
}*/

void fenprincipale::ouvrirdt()
{
    QString dossier;

    datadossier->open(QFile::ReadOnly);
    QTextStream in(datadossier);
    in.readLineInto(&dossier,300);
    if(dossier.length()==0)
    {
        dossier="/home/dh/téléchargements";
    };

    datadossier->close();
    QDesktopServices::openUrl(QUrl(dossier));

}
void fenprincipale::changerdossiertele()
{
    datadossier->open(QFile::WriteOnly);
    QTextStream out(datadossier);
    out<<QFileDialog::getExistingDirectory(0,"choisir la destination de telechargement","/home/dh");

    datadossier->close();
    statusBar()->showMessage("dossier de telechargement changé avec succès !");
}
