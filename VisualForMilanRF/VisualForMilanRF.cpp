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
   
    middleColumn = 0;



    connect(ui.pushButtonCheckChannel, &QPushButton::clicked, this, &VisualForMilanRF::test1);

    connect(ui.pushButtonTest_2, &QPushButton::clicked, this, &VisualForMilanRF::test2);

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




void VisualForMilanRF::test1()
{
    
    QTreeWidgetItem* any = nullptr;

    if (ui.treeWidget->currentItem() == nullptr)
        any = new QTreeWidgetItem(ui.treeWidget);
    else
        any = new QTreeWidgetItem(ui.treeWidget->currentItem());

    int column = ui.treeWidget->currentColumn();

    offChanger = true;

    any->setText(0, "new");

    any->setText(2, "11111");

    any->setBackground(0, QColor(221, 221, 221, 255));
    any->setBackground(1, QColor(245, 216, 183, 255));
    any->setBackground(2, QColor(217, 225, 187, 255));

    offChanger = false;

    VisualForMilanRF::closeEditor(any);
    
}

void VisualForMilanRF::test2()
{
    /*
    QString savedFile = QFileDialog::getSaveFileName(0, "Save XML", "", "*.xml");
    QFile file(savedFile);
    file.open(QIODevice::WriteOnly);
   
   // QTextStream out(&file); // ����� ������������ ������ ���������� � ����
   // out << "12345" << Qt::endl;

    QXmlStreamWriter xmlWriter(&file); // �������������� ������ QXmlStreamWriter ������� �� ������ � ������� ����� ��������

    xmlWriter.setDevice(&file);
    xmlWriter.setAutoFormatting(true); // ���������� ��� ��������������� �������� �� ����� ������
    xmlWriter.setAutoFormattingIndent(2); // ����� ���������� �������� � ������� (�� ��������� 4)
    xmlWriter.writeStartDocument(); // ����� � ����� ��������� ���������

    xmlWriter.writeStartElement("General"); // ��������� ��������� ������� "��������" xml

   // QTreeWidgetItem* any = ui.treeWidget->currentItem(); // ����������� ��������� ��������� ������
   // int column = ui.treeWidget->currentColumn(); // ����������� ���������� ����� �������� ������� (������ ���������� � 0-���)

    QTreeWidgetItem* any = ui.treeWidget->topLevelItem(0);

    QString temporaryStr = ui.treeWidget->topLevelItem(0)->text(1);

    xmlWriter.writeAttribute("ID", temporaryStr); // ����������� �������� ������ ��������� ������� ��������

    temporaryStr = ui.treeWidget->topLevelItem(0)->text(2);

    xmlWriter.writeAttribute("Number", temporaryStr);
    */

    QTreeWidgetItem* any = ui.treeWidget->topLevelItem(0);

   // qDebug() << any->text(0);

    recursionXmlWriter(any);

    /*
    if (any->childCount())
    {
        int count = any->childCount();

        for (int x = 0; x < count; x++)
        {

            qDebug() << any->child(x)->text(0);

        }

    }
    else
    {
        qDebug() << any->text(0);
        return;
    }

    */

   // qDebug() << any->childCount();

   // qDebug() << any->child(0)->text(0);

   // xmlWriter.writeStartElement(ui.treeWidget->topLevelItem(2)->text(0));
   // xmlWriter.writeEndElement();


    /*
    if (any->childCount())
    {
        int counter = any->childCount();

        qDebug() << counter;

        for (int countOfElement = 1; countOfElement < counter; countOfElement++)
        {
            ui.treeWidget->topLevelItem(countOfElement);

            xmlWriter.writeStartElement(ui.treeWidget->topLevelItem(countOfElement)->text(0));

            xmlWriter.writeAttribute("ID", ui.treeWidget->topLevelItem(countOfElement)->text(1));

            xmlWriter.writeAttribute("Number", ui.treeWidget->topLevelItem(countOfElement)->text(2));

            xmlWriter.writeEndElement();
        }


    }
    */




    //xmlWriter.writeEndElement(); // General

   // xmlWriter.writeEndDocument();


   // file.close();

}

void VisualForMilanRF::recursionXmlWriter(QTreeWidgetItem* some)
{
    if (some->childCount())
    {
        qDebug() << some->text(0);

        int count = some->childCount();

        for (int x = 0; x < count; x++)
        {
            recursionXmlWriter(some->child(x));
        }
    }
    else
    {
        qDebug() << some->text(0);
        return;
    }
}