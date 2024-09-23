#include "VisualForMilanRF.h"

VisualForMilanRF::VisualForMilanRF(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButtonAdd, &QPushButton::clicked, this, &VisualForMilanRF::addItemInList);
    connect(ui.pushButtonAddMinus, &QPushButton::clicked, this, &VisualForMilanRF::deleteItemInList);

    connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(setData()));
    connect(ui.treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(closeEditor(QTreeWidgetItem*)));
    connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(otherItemWasChecked(QTreeWidgetItem*)));
    connect(ui.pushButtonFinder, &QPushButton::clicked, this, &VisualForMilanRF::adressFinder);
    connect(ui.pushButtonExport, &QPushButton::clicked, this, &VisualForMilanRF::exportXml);
    connect(ui.pushButtonImport, &QPushButton::clicked, this, &VisualForMilanRF::importXml);



    connect(ui.pushButtonTest, &QPushButton::clicked, this, &VisualForMilanRF::test);
    

   

    middleColumn = 0;


}

VisualForMilanRF::~VisualForMilanRF()
{}

void VisualForMilanRF::addItemInList()
{
    QTreeWidgetItem* any = nullptr;

    if(ui.treeWidget->currentItem() == nullptr)
        any = new QTreeWidgetItem(ui.treeWidget);
    else
        any = new QTreeWidgetItem(ui.treeWidget->currentItem());
  
    int column = ui.treeWidget->currentColumn();

    offChanger = true;

    any->setText(0, "new");
    
    any->setBackground(0, QColor(221, 221, 221, 255));
    any->setBackground(1, QColor(245, 216, 183, 255));
    any->setBackground(2, QColor(217, 225, 187, 255));

    offChanger = false;
}

void VisualForMilanRF::deleteItemInList()
{
    QTreeWidgetItem* taked = ui.treeWidget->currentItem();
    QTreeWidgetItem* parentTaked = taked->parent();

    if (parentTaked == nullptr)
        return;

    parentTaked->takeChild(parentTaked->indexOfChild(taked));
}

void VisualForMilanRF::setData() // � ������ �������� ����� � ������ ��������� ��������
{
    QTreeWidgetItem* any = ui.treeWidget->currentItem(); // ����������� ��������� ��������� ������
    int column = ui.treeWidget->currentColumn(); // ����������� ���������� ����� �������� ������� (������ ���������� � 0-���)

    if (column > 2) return; // �� ��� ������������� ������ �������� �������

    qDebug() << "OPEN EDITOR";
    
    middleColumn = column;
    middleItem = any;

    ui.treeWidget->openPersistentEditor(any, column); // ��������� �������������� ������
    ui.treeWidget->editItem(any, column); // ��������� ��������
}

void VisualForMilanRF::closeEditor(QTreeWidgetItem* any) // ���� �������� ��������� � ������ �������� ��������� (����� ������� Enter)
{
    if (offChanger) return; // ������������ ������������� ���������� ���� ������� ��� ��������� ������

    QString temporary = any->text(2).trimmed(); // ������� �������
    any->setText(2, temporary);

    if (any->text(2) != "") // ������ ���� ���-�� �������� � ���������
    {
        offChanger = true;

        any->setBackground(4, QColor(213, 176, 176, 255));
        any->setCheckState(4, any->checkState(4));

        any->setBackground(5, QColor(213, 176, 176, 255));
        any->setCheckState(5, any->checkState(5));

        any->setBackground(6, QColor(156, 203, 213, 255));
        any->setCheckState(6, any->checkState(6));

        any->setBackground(7, QColor(156, 203, 213, 255));
        any->setCheckState(7, any->checkState(7));

        offChanger = false;
    }
    else
    {
        offChanger = true;

        any->setBackground(4, QColor("white"));
        any->setData(4, Qt::CheckStateRole, QVariant());

        any->setBackground(5, QColor("white"));
        any->setData(5, Qt::CheckStateRole, QVariant());

        any->setBackground(6, QColor("white"));
        any->setData(6, Qt::CheckStateRole, QVariant());

        any->setBackground(7, QColor("white"));
        any->setData(7, Qt::CheckStateRole, QVariant());

        offChanger = false;
    }
    ui.treeWidget->closePersistentEditor(middleItem, middleColumn); // ��������� ��������

    qDebug() << "CLOSE EDITOR";
}

void VisualForMilanRF::otherItemWasChecked(QTreeWidgetItem* any) // ��������� �������� �������� � ������ ������������ �� ������ �������
{
    if (offChanger) return;

    int column = ui.treeWidget->currentColumn();
    qDebug() << "Checked " << any->text(column);

    if (any == middleItem && column == middleColumn)
        return;

    QString temporary = any->text(2).trimmed();
    any->setText(2, temporary);

    if (any->text(2) != "")
    {
        offChanger = true;
        any->setBackground(4, QColor(213, 176, 176, 255));
        any->setBackground(5, QColor(213, 176, 176, 255));
        any->setBackground(6, QColor(156, 203, 213, 255));
        any->setBackground(7, QColor(156, 203, 213, 255));
        offChanger = false;
    }

    ui.treeWidget->closePersistentEditor(middleItem, middleColumn);
    middleItem = nullptr;

    qDebug() << "CLOSE EDITOR";
}

void VisualForMilanRF::adressFinder() // ����� � ������� ������� ����������� �������� � ����������� ������� � ������. ����� ������� ������ ����� � ������ ������� �� ���������� ���������.
{
    QInputDialog inputDialog;

    int number = inputDialog.getInt(this, "Add number", "Serial number", QLineEdit::Normal);
   
    QString strNumber;

    strNumber = strNumber.setNum(number);

    QList <QTreeWidgetItem*> myList = ui.treeWidget->findItems(strNumber, Qt::MatchRecursive, ui.treeWidget->currentColumn());
    
    for (auto& val : myList)
    {
        if (val->parent() == nullptr)
        {
            qDebug() << ui.treeWidget->topLevelItem(0)->text(0);
            break;
        }

        QTreeWidgetItem* temporary = val->parent();

        int index = temporary->indexOfChild(val);

        strNumber = " / " + temporary->child(index)->text(0);

        do {

            strNumber.push_front(" / " + temporary->text(0));
            temporary = temporary->parent();

        } while (temporary != nullptr);

        strNumber.remove(0, 3);

        qDebug() << strNumber;

        strNumber = "";
    }
}

void VisualForMilanRF::exportXml()
{
    QString savedFile = QFileDialog::getSaveFileName(0, "Save XML", "", "*.xml");
    QFile file(savedFile);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file); // �������������� ������ QXmlStreamWriter ������� �� ������ � ������� ����� ��������

    xmlWriter.setDevice(&file);
    xmlWriter.setAutoFormatting(true); // ���������� ��� ��������������� �������� �� ����� ������
    xmlWriter.setAutoFormattingIndent(2); // ����� ���������� �������� � ������� (�� ��������� 4)
    xmlWriter.writeStartDocument(); // ����� � ����� ��������� ���������

    QTreeWidgetItem* any = ui.treeWidget->topLevelItem(0);

    recursionXmlWriter(any, xmlWriter);

    xmlWriter.writeEndElement(); // General
    xmlWriter.writeEndDocument();

    file.close();
}

void VisualForMilanRF::recursionXmlWriter(QTreeWidgetItem* some, QXmlStreamWriter& someXmlWriter)
{
    if (some->childCount())
    {
        someXmlWriter.writeStartElement(some->text(0)); // ��������� ��������� ������� "��������" xml

        someXmlWriter.writeAttribute("ID", some->text(1)); // ����������� �������� ������ ��������� ������� ��������

        someXmlWriter.writeAttribute("Number", some->text(2));

        if (some->text(2) != nullptr)
        {
            for (int count = 4; count <= 7; count++)
            {
                QString temporary = "checkChannel";
                QString middleStr;
                middleStr.setNum(count -3);
                temporary += middleStr;

                if (some->checkState(count) == Qt::Unchecked)
                    someXmlWriter.writeAttribute(temporary, "0");
                else
                    someXmlWriter.writeAttribute(temporary, "1");
            }
        }

        int count = some->childCount();

        for (int x = 0; x < count; x++)
        {
            recursionXmlWriter(some->child(x), someXmlWriter);
        }
        
        someXmlWriter.writeEndElement();
    }
    else
    {
        someXmlWriter.writeStartElement(some->text(0)); // ��������� ��������� ������� "��������" xml

        someXmlWriter.writeAttribute("ID", some->text(1)); // ����������� �������� ������ ��������� ������� ��������

        someXmlWriter.writeAttribute("Number", some->text(2));

        if (some->text(2) != nullptr)
        {
            for (int count = 4; count <= 7; count++)
            {
                QString temporary = "checkChannel";
                QString middleStr;
                middleStr.setNum(count - 3);
                temporary += middleStr;

                if (some->checkState(count) == Qt::Unchecked)
                    someXmlWriter.writeAttribute(temporary, "0");
                else
                    someXmlWriter.writeAttribute(temporary, "1");
            }
        }

        someXmlWriter.writeEndElement();

        return;
    }
}

void VisualForMilanRF::importXml()
{
	/* ��������� ���� ��� ������ � ������� ����, ���������� � lineEditWrite */

    QString addFileDonor = QFileDialog::getOpenFileName(0, "Choose XML for import", "", "*.xml");

    if (addFileDonor == "")
    {
        return;
    }

	QFile file(addFileDonor);
    QXmlStreamReader xmlReader(&file);

    file.open(QFile::ReadWrite);

    QTreeWidgetItem* any = ui.treeWidget->topLevelItem(0);

    loopXmlReader(any, xmlReader);
}


void VisualForMilanRF::loopXmlReader(QTreeWidgetItem* some, QXmlStreamReader &xmlReader)
{
    QList <QTreeWidgetItem*> myList;

    myList.push_back(some);

    while (!xmlReader.atEnd())
    {
        xmlReader.readNextStartElement();

        if (xmlReader.isStartElement())
        {
            if (some == ui.treeWidget->topLevelItem(0))
            {
                some = new QTreeWidgetItem(ui.treeWidget);
            }
            else
                some = new QTreeWidgetItem(myList.constLast());

            myList.push_back(some);

            offChanger = true;

            some->setBackground(0, QColor(221, 221, 221, 255));
            some->setBackground(1, QColor(245, 216, 183, 255));
            some->setBackground(2, QColor(217, 225, 187, 255));

            some->setText(0, xmlReader.name().toString());

            for (QXmlStreamAttribute& val : xmlReader.attributes())
            {
                if (val.name().toString() == "ID") some->setText(1, val.value().toString());

                if (val.name().toString() == "Number") some->setText(2, val.value().toString());

                if (val.name().toString() == "checkChannel1")
                {
                    if (val.value().toString() == "1")
                        some->setCheckState(4, Qt::Checked);
                    else
                        some->setCheckState(4, Qt::Unchecked);
                }

                if (val.name().toString() == "checkChannel2")
                {
                    if (val.value().toString() == "1")
                        some->setCheckState(5, Qt::Checked);
                    else
                        some->setCheckState(5, Qt::Unchecked);
                }

                if (val.name().toString() == "checkChannel3")
                {
                    if (val.value().toString() == "1")
                        some->setCheckState(6, Qt::Checked);
                    else
                        some->setCheckState(6, Qt::Unchecked);
                }

                if (val.name().toString() == "checkChannel4")
                {
                    if (val.value().toString() == "1")
                        some->setCheckState(7, Qt::Checked);
                    else
                        some->setCheckState(7, Qt::Unchecked);
                }
            }

            offChanger = false;

            VisualForMilanRF::closeEditor(some);
        }

        if (xmlReader.isEndElement())
            myList.pop_back();
    }

    ui.treeWidget->takeTopLevelItem(0);
}

void VisualForMilanRF::test()
{
    connectDB();
}

bool VisualForMilanRF::connectDB()
{
    mw_db = QSqlDatabase::addDatabase("QSQLITE", "ReadOnlyFromGUI"); // ��������� ����� ������������ ������� ��� ����������� � �� � ��� �����������. ���� ��� �� ������ �� �� ��������� ������������ � ���� ����. ����� ���.
   // mw_db.setHostName("\\ENERGOSFERA-GES\Release");
   //mw_db.setPort(8080);
    mw_db.setDatabaseName("//ENERGOSFERA-GES//Release//DataBaseMilanRF"); // ��������� � ����� �� �����������������. ���� ������ ����� �� ����� �� ���� �� � ��������� ������ ����� ������.
   //mw_db.setDatabaseName("//10.86.142.14//Release//DataBaseMilanRF"); // ��������� � ����� �� �����������������. ���� ������ ����� �� ����� �� ���� �� � ��������� ������ ����� ������.
   // mw_db.setUserName("�������������");
   // mw_db.setPassword("RootToor#");

    mw_db.setConnectOptions("QSQLITE_OPEN_READONLY");

    if (!mw_db.open()) // ��������� ��. ���� �� ��������� �� ����� false
    {
        qDebug() << "Cannot open database: " << mw_db.lastError();
        return false;
    }
    else
    {
        qDebug() << "DB OPEN";
    }

    return true;
}