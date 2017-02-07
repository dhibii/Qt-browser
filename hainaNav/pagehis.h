#ifndef PAGEHIS_H
#define PAGEHIS_H
#include <QWidget>
#include <QWebView>
#include "mainwindow.h"
class pagehis : public QWidget
{
      Q_OBJECT
public:

    pagehis(QWebView* page);
};

#endif // PAGEHIS_H
