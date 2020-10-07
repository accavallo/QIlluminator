#ifndef QILLUMINATOR_H
#define QILLUMINATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_QIlluminator.h"

QT_FORWARD_DECLARE_CLASS(PRN_Node);

class QIlluminator : public QMainWindow
{
    Q_OBJECT

public:
    QIlluminator(QWidget *parent = 0);
    ~QIlluminator();

private:
    Ui::QIlluminatorClass ui;

    void DisplayPRN();
    void ParsePRN(QString filename);

    QList<PRN_Node*> prnList;
    QStringList connectors;

private slots:
    void LoadPRN();
};

#endif // QILLUMINATOR_H
