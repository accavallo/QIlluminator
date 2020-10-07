#ifndef PRN_NODE_H
#define PRN_NODE_H

#include <QWidget>

class PRN_Node : public QWidget
{
   Q_OBJECT

public:
    PRN_Node(QObject *parent);
    PRN_Node(QObject *parent, QString info);
    ~PRN_Node();

    QString GetType();
    QString GetMnemonic();
    QString GetConnector();
    QString GetPin();
    int GetRow();
    QList<int> GetLinks();


private:
   QString type = "";
   QString mnemonic = "";
   QString connector = "";
   QString pin = "";
   int row = 0;
   QList<int> links;
   bool isGet = false;
   bool isSet = false;
};

#endif // PRN_NODE_H
