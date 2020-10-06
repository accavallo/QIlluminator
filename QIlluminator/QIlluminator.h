#ifndef QILLUMINATOR_H
#define QILLUMINATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_QIlluminator.h"

class QIlluminator : public QMainWindow
{
    Q_OBJECT

public:
    QIlluminator(QWidget *parent = 0);
    ~QIlluminator();

private:
    Ui::QIlluminatorClass ui;

    void ParsePRN(QString filename);

private slots:
    void LoadPRN();
};

#endif // QILLUMINATOR_H
