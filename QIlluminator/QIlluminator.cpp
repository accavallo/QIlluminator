#include "QIlluminator.h"

#include <QFile>
#include <QFileDialog>
#include <QGraphicsView>
#include <QLabel>
#include <qmath.h>
#include <QMenuBar>
#include <QMessageBox>
#include <QRegularExpression>

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSlider>
#include <QToolButton>

#include "PRN_Node.h"

#include <QDebug>

QIlluminator::QIlluminator(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    const short SIZE = 25;
    
    view = this->findChild<QGraphicsView*>("graphicsView");

    QSize iconSize(SIZE, SIZE);
    zoomInBtn = new QToolButton(this);
    zoomInBtn->setGeometry(view->x() + view->width(), view->y() + this->findChild<QMenuBar*>("menuBar")->height(), SIZE, SIZE);
    zoomInBtn->setAutoRepeat(true);
    zoomInBtn->setAutoRepeatInterval(33);
    zoomInBtn->setAutoRepeatDelay(0);
    zoomInBtn->setIcon(QPixmap(":/QIlluminator/Resources/zoomin.png"));
    zoomInBtn->setIconSize(iconSize);

    zoomOutBtn = new QToolButton(this);
    zoomOutBtn->setGeometry(view->x() + view->width(), view->y() + view->height() + this->findChild<QMenuBar*>("menuBar")->height() - SIZE, SIZE, SIZE);
    zoomOutBtn->setAutoRepeat(true);
    zoomOutBtn->setAutoRepeatInterval(33);
    zoomOutBtn->setAutoRepeatDelay(0);
    zoomOutBtn->setIcon(QPixmap(":/QIlluminator/Resources/zoomout.png"));
    zoomOutBtn->setIconSize(iconSize);

    zoomSlider = new QSlider(this);
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(300);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksRight);
    zoomSlider->setGeometry(zoomInBtn->x(), zoomInBtn->y() + SIZE, SIZE, zoomOutBtn->y() - zoomInBtn->y() - SIZE);
    
    connect(zoomInBtn, SIGNAL(clicked()), this, SLOT(ZoomIn()));
    connect(zoomOutBtn, SIGNAL(clicked()), this, SLOT(ZoomOut()));
    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(SetupMatrix()));

    SetupMatrix();
}

QIlluminator::~QIlluminator()
{

}

//Private Functions

void QIlluminator::DisplayPRN()
{
   for (int index = 0; index < connectors.count(); ++index)
   {
      qDebug() << connectors.at(index);
   }
}

void QIlluminator::ParsePRN(QString filename)
{
   QFile prn(filename);
   if (!prn.open(QIODevice::ReadOnly | QIODevice::Text))
   {
      QMessageBox mb(this);
      mb.setText(QString("Unable to open the following file:\n%1!").arg(filename));
      mb.exec();
      return;
   }
   //QByteArray ba = prn.readAll();
   while (!prn.atEnd())
   {
      QString line = QString::fromLocal8Bit(prn.readLine());
      /*
      Anatomy of a PRN
      -----------------------------------------------------------------------------------------
      |   TYPE   |        MNEMONIC          | ROW |                   LINKS                   |
      |----------|--------------------------|-----|-------------------------------------------|
   GET|LRU_JACK  |C_1B_R067_J1, PIN_A       |1    |2                                          |
      |LATCH     |1P-R067                   |2    |1,3                                        |
      |PLUG      |1P-R067,A                 |3    |2,4                                        |
      |PLUG      |52P-M835,G                |4    |3,5                                        |
      |LATCH     |52P-M835                  |5    |4,6                                        |
      |JACK      |52J-M835,G                |6    |5,7                                        |
      |PLUG      |52P-C007C,4               |7    |6,8                                        |
      |LATCH     |52P-C007C                 |8    |7,9                                        |
   SET|LRU_JACK  |C_52J_C007C, PIN_4        |9    |8                                          |
      -----------------------------------------------------------------------------------------

      'TYPE' column: The type of item the line represents. 
      Types are: DIODE     - One way electrical current
                 DIODE_NEG - Diodes need an in
                 DIODE_POS - Diodes also need an out
                 GROUND    - Self explanatory
                 INSTL     - Item is Installed
                 JACK      - Jack that a plug plugs in to
                 LATCH     - Locks the plug and jack together
                 LRU_JACK  - Jack for a Line Replaceable Unit that a plug plugs in to
                 LRU_PIN   - Pin for a Line Replaceable Unit
                 LRU_PLUG  - Plug for a Line Replaceable Unit that plugs into a jack
                 MALF_F    - Malfunction False (not enabled)
                 MALF_T    - Malfunction True  (enabled)
                 PIN       - Individual Pin
                 PLUG      - Plug that plugs into a jack
                 RELAY_D   - Deenergized Relay
                 _RELAY_D  - Moar different Deenergized Relay
                 RELAY_E   - Energized Relay
                 _RELAY_E  - Moar different Energized Relay
                 RESISTOR  - Provides resistance
                 SIMVAR    - SIMulation VARiable
                 SPLICE    - Splice point
                 STOW      - Item is STOWed


      'MNEMONIC' column: The identifying information for the item.
      Mnemonic deciphering: 52P-M835,G represents plug 52P-M835 pin G.
                            52J-M835,G represents jack 52J-M835 pin G.

      'ROW' column: Represents the row number of the line.

      'LINKS' column: Shows any connections the current line has and to which rows the current line is connected.

      'GET' lines: A get signal call will be found in code with the information contained in the 'MNEMONIC' section.

      'SET' lines: A set signal call will be found in code with the information contained in the 'MNEMONIC' section.

      */
      //qDebug() << line;
      if (line.contains(QRegularExpression("--+")) || line.contains("MNEMONIC"))
      {
         qDebug() << "Continuing" << line;
         continue;
      }
      else
      {
         qDebug() << "Parsing line" << line;
         //Start parsing here.
         PRN_Node* node = new PRN_Node(this, line);
         prnList.append(node);
         
         //Add connector to list of connectors
         QString connector = node->GetConnector();
         if (!connectors.contains(connector))
         {
            connectors.append(connector);
         }
      }
   }
   DisplayPRN();
}

//Private Slots

void QIlluminator::LoadPRN()
{
   for (int ind = prnList.count() - 1; ind >= 0; --ind)
   {
      delete prnList[ind];
      prnList.removeAt(ind);
   }
   connectors = QStringList();

   QString username = "";
   QString desktopDir = "";
   QString userprofile = QString::fromLocal8Bit(qgetenv("USERPROFILE"));
   if (userprofile.isEmpty())
   {
      QString username = QString::fromLocal8Bit(qgetenv("USERNAME"));
      if (!username.isEmpty())
      {
         desktopDir = QString("C:\\Users\\%1\\Desktop").arg(username);
      }
   }
   else
   {
      desktopDir = QString("%1\\Desktop").arg(userprofile);
   }

   if (desktopDir.isEmpty())
   {
      desktopDir = QString("%USERPROFILE%\\Desktop");
   }
   QString fileName = QFileDialog::getOpenFileName(this, "Choose your PRN", desktopDir/*"U:\\"*/, "PRN Files (*.prn);;Text Files (*.txt);;All Files (*.*)");

   if (fileName.isEmpty())
   {
      return;
   }

   this->findChild<QLabel*>("prnLbl")->setText(QFileInfo(fileName).fileName());
   ParsePRN(fileName);
}

void QIlluminator::LoadPRNs()
{
   for (int ind = prnList.count() - 1; ind >= 0; --ind)
   {
      delete prnList[ind];
      prnList.removeAt(ind);
   }
   connectors = QStringList();

   QString username = "";
   QString desktopDir = "";
   QString userprofile = QString::fromLocal8Bit(qgetenv("USERPROFILE"));
   if (userprofile.isEmpty())
   {
      QString username = QString::fromLocal8Bit(qgetenv("USERNAME"));
      if (!username.isEmpty())
      {
         desktopDir = QString("C:\\Users\\%1\\Desktop").arg(username);
      }
   }
   else
   {
      desktopDir = QString("%1\\Desktop").arg(userprofile);
   }

   if (desktopDir.isEmpty())
   {
      desktopDir = QString("%USERPROFILE%\\Desktop");
   }
   QStringList fileNames = QFileDialog::getOpenFileNames(this, "Choose your PRN", desktopDir/*"U:\\"*/, "PRN Files (*.prn);;Text Files (*.txt);;All Files (*.*)");

   if (fileNames.isEmpty())
   {
      return;
   }

   this->findChild<QLabel*>("prnLbl")->setText("Multiple files loaded");
   foreach(QString name, fileNames)
   {
      qDebug() << "Now parsing " << QFileInfo(name).fileName();
      ParsePRN(name);
   }
}

void QIlluminator::SetupMatrix()
{
   qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

   QMatrix matrix;
   matrix.scale(scale, scale);

   view->setMatrix(matrix);
}

void QIlluminator::ZoomIn()
{
   zoomSlider->setValue(zoomSlider->value() + 1);
}

void QIlluminator::ZoomOut()
{
   zoomSlider->setValue(zoomSlider->value() - 1);
}
