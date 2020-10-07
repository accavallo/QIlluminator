#include "PRN_Node.h"

#include <QRegularExpression>

#include <QDebug>

PRN_Node::PRN_Node(QObject *parent)
{

}

PRN_Node::PRN_Node(QObject *parent, QString info)
{
   /*
      |   TYPE   |        MNEMONIC          | ROW |                   LINKS                   |
   GET|LRU_JACK  |C_1B_R067_J1, PIN_A       |1    |2                                          |
      |LATCH     |1P-R067                   |2    |1,3                                        |
      |PLUG      |1P-R067,A                 |3    |2,4                                        |
      |PLUG      |52P-M835,G                |4    |3,5                                        |
      |LATCH     |52P-M835                  |5    |4,6                                        |
      |JACK      |52J-M835,G                |6    |5,7                                        |
      |PLUG      |52P-C007C,4               |7    |6,8                                        |
      |LATCH     |52P-C007C                 |8    |7,9                                        |
   SET|LRU_JACK  |C_52J_C007C, PIN_4        |9    |8                                          |
   */

   if (info.contains("GET|", Qt::CaseInsensitive))
   {
      isGet = true;
   }
   else if (info.contains("SET|", Qt::CaseInsensitive))
   {
      isSet = true;
   }

   info.remove(QRegularExpression("^\\s+(GET|SET)?\\|"));

   int ind = info.indexOf("|");
   type = info.left(ind);
   type.remove(QRegularExpression("\\s+"));
   info.remove(0, ind + 1);

   ind = info.indexOf("|");
   mnemonic = info.left(ind);
   mnemonic.remove(QRegularExpression("\\s+"));
   connector = mnemonic.split(",")[0];
   connector.remove(QRegularExpression("^C_"));
   connector.remove(QRegularExpression("_J(\\d+)?$"));
   connector.replace(QRegularExpression("_"), "-");
   if (QString::compare("LATCH", type, Qt::CaseInsensitive) != 0)
   {
      pin = mnemonic.split(",")[1];
   }
   info.remove(0, ind + 1);

   ind = info.indexOf("|");
   QString temp = info.left(ind);
   temp.remove(QRegularExpression("\\s+"));
   row = temp.toInt(Q_NULLPTR);
   info.remove(0, ind + 1);

   ind = info.indexOf("|");
   info.remove(QRegularExpression("\\s+(\\|)?"));
   QStringList tempList = info.split(",");
   foreach(QString rowLink, tempList)
   {
      links.append(rowLink.toInt(Q_NULLPTR));
   }
}

PRN_Node::~PRN_Node()
{

}

QString PRN_Node::GetType()
{
   return type;
}

QString PRN_Node::GetMnemonic()
{
   return mnemonic;
}

QString PRN_Node::GetConnector()
{
   return connector;
}

QString PRN_Node::GetPin()
{
   return pin;
}

int PRN_Node::GetRow()
{
   return row;
}

QList<int> PRN_Node::GetLinks()
{
   return links;
}
