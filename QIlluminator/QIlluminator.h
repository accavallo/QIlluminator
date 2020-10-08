#ifndef QILLUMINATOR_H
#define QILLUMINATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_QIlluminator.h"

QT_FORWARD_DECLARE_CLASS(QGraphicsView)
QT_FORWARD_DECLARE_CLASS(QSlider)

QT_FORWARD_DECLARE_CLASS(PRN_Node);

class QIlluminator : public QMainWindow
{
    Q_OBJECT

public:
    QIlluminator(QWidget *parent = 0);
    ~QIlluminator();

private:
    Ui::QIlluminatorClass ui;

    QList<PRN_Node*> prnList;

    QStringList connectors;

    QGraphicsView* view;

    QSlider* zoomSlider;

    QToolButton* zoomInBtn;
    QToolButton* zoomOutBtn;

    void DisplayPRN();
    void ParsePRN(QString filename);

private slots:
    void LoadPRN();
    void LoadPRNs();
    void SetupMatrix();
    void ZoomIn();
    void ZoomOut();
};

#endif // QILLUMINATOR_H
