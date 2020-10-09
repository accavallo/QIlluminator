/********************************************************************************
** Form generated from reading UI file 'QIlluminator.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QILLUMINATOR_H
#define UI_QILLUMINATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QIlluminatorClass
{
public:
    QAction *actionLoad_PRN;
    QAction *actionLoad_PRNs;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *prnLbl;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *QIlluminatorClass)
    {
        if (QIlluminatorClass->objectName().isEmpty())
            QIlluminatorClass->setObjectName(QStringLiteral("QIlluminatorClass"));
        QIlluminatorClass->resize(600, 400);
        actionLoad_PRN = new QAction(QIlluminatorClass);
        actionLoad_PRN->setObjectName(QStringLiteral("actionLoad_PRN"));
        actionLoad_PRNs = new QAction(QIlluminatorClass);
        actionLoad_PRNs->setObjectName(QStringLiteral("actionLoad_PRNs"));
        centralWidget = new QWidget(QIlluminatorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 25, 13));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        prnLbl = new QLabel(centralWidget);
        prnLbl->setObjectName(QStringLiteral("prnLbl"));
        prnLbl->setGeometry(QRect(40, 0, 561, 13));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 50, 575, 330));
        QIlluminatorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QIlluminatorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        QIlluminatorClass->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad_PRN);
        menuFile->addAction(actionLoad_PRNs);

        retranslateUi(QIlluminatorClass);
        QObject::connect(actionLoad_PRN, SIGNAL(triggered()), QIlluminatorClass, SLOT(LoadPRN()));
        QObject::connect(actionLoad_PRNs, SIGNAL(triggered()), QIlluminatorClass, SLOT(LoadPRNs()));

        QMetaObject::connectSlotsByName(QIlluminatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *QIlluminatorClass)
    {
        QIlluminatorClass->setWindowTitle(QApplication::translate("QIlluminatorClass", "QIlluminator", nullptr));
        actionLoad_PRN->setText(QApplication::translate("QIlluminatorClass", "Load PRN...", nullptr));
        actionLoad_PRNs->setText(QApplication::translate("QIlluminatorClass", "Load PRNs...", nullptr));
        label->setText(QApplication::translate("QIlluminatorClass", "PRN:", nullptr));
        prnLbl->setText(QString());
        menuFile->setTitle(QApplication::translate("QIlluminatorClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QIlluminatorClass: public Ui_QIlluminatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QILLUMINATOR_H
