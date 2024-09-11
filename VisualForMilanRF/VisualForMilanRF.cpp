#include "VisualForMilanRF.h"

#include <QInputDialog>

VisualForMilanRF::VisualForMilanRF(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButtonAdd, &QPushButton::clicked, this, &VisualForMilanRF::addItemInList);
    connect(ui.pushButtonAddMinus, &QPushButton::clicked, this, &VisualForMilanRF::deleteItemInList);

    connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(setData()));
    connect(ui.treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(closeEditor(QTreeWidgetItem*)));
    connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(otherItemWasChecked(QTreeWidgetItem*)));

    middleColumn = 0;






    connect(ui.pushButtonTest, &QPushButton::clicked, this, &VisualForMilanRF::test);
}

VisualForMilanRF::~VisualForMilanRF()
{}

void VisualForMilanRF::addItemInList()
{
    //ui.treeWidget->expandItem(ui.treeWidget->currentItem()); // ��������� ��������

    QTreeWidgetItem* any = nullptr;

    if(ui.treeWidget->currentItem() == nullptr)
        any = new QTreeWidgetItem(ui.treeWidget);
    else
        any = new QTreeWidgetItem(ui.treeWidget->currentItem());
  
    int column = ui.treeWidget->currentColumn();

    any->setText(0, "new");
}

void VisualForMilanRF::deleteItemInList()
{
    QTreeWidgetItem* taked = ui.treeWidget->currentItem();
    QTreeWidgetItem* parentTaked = taked->parent();

    if (parentTaked == nullptr)
        return;

    parentTaked->takeChild(parentTaked->indexOfChild(taked));
    
   // ui.treeWidget->collapseItem(ui.treeWidget->currentItem()); // �������� ��������

    //  ui.treeWidget->clear(); // ������ ������� �������
}

void VisualForMilanRF::setData() // � ������ �������� ����� � ������ ��������� ��������
{
    QTreeWidgetItem* any = ui.treeWidget->currentItem(); // ����������� ��������� ��������� ������
    int column = ui.treeWidget->currentColumn(); // ����������� ���������� ����� �������� ������� (������ ���������� � 0-���)

    if (column > 1) return; // �� ��� ������������� ������ ������� �������

    qDebug() << "OPEN EDITOR";
    


    middleColumn = column;
    middleItem = any;

    ui.treeWidget->openPersistentEditor(any, column); // ��������� �������������� ������
    ui.treeWidget->editItem(any, column); // ��������� ��������



    /*
    QInputDialog inputDialog;

    int number = inputDialog.getInt(this, "Add number", "Serial number", QLineEdit::Normal);
    QString strNumber;

    any->setText(0, any->text(0));
    any->setText(1, strNumber.setNum(number));
    */
}

void VisualForMilanRF::closeEditor(QTreeWidgetItem* any) // ���� �������� ��������� � ��������� ������
{
    ui.treeWidget->closePersistentEditor(middleItem, middleColumn); // ��������� ��������

    qDebug() << "CLOSE EDITOR";
}

void VisualForMilanRF::otherItemWasChecked(QTreeWidgetItem* any)
{
    int column = ui.treeWidget->currentColumn();
    qDebug() << "Checked " << any->text(column);

    if (any == middleItem && column == middleColumn)
        return;

    ui.treeWidget->closePersistentEditor(middleItem, middleColumn);
    middleItem = nullptr;

    qDebug() << "CLOSE EDITOR";
}


void VisualForMilanRF::test() // ����� �� ������ ������� ����������� �������� � ����������� ������� � ������. ����� ������� �������� ����� ������� ������� �������� ������� ���� ����������.
{
    QList<QTreeWidgetItem*> myList = ui.treeWidget->findItems("12", Qt::MatchRecursive, 1);

    qDebug() << myList.size();

    for (auto& val : myList)
    {
        QTreeWidgetItem* temporary = val->parent();

        int index = temporary->indexOfChild(val);

        QTreeWidgetItem* general = ui.treeWidget->topLevelItem(0);

        temporary = general->child(index);

        qDebug() << temporary->text(0);

    }
}