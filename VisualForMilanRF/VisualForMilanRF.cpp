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
   
    connect(ui.pushButtonTest, &QPushButton::clicked, this, &VisualForMilanRF::adressFinder);
   
    middleColumn = 0;

}

VisualForMilanRF::~VisualForMilanRF()
{}

void VisualForMilanRF::addItemInList()
{
    //ui.treeWidget->expandItem(ui.treeWidget->currentItem()); // раскрытие элемента

    QTreeWidgetItem* any = nullptr;

    if(ui.treeWidget->currentItem() == nullptr)
        any = new QTreeWidgetItem(ui.treeWidget);
    else
        any = new QTreeWidgetItem(ui.treeWidget->currentItem());
  
    int column = ui.treeWidget->currentColumn();

    any->setText(0, "new");
    
    any->setBackground(0, QColor(221, 221, 221, 255));
    any->setBackground(1, QColor(245, 216, 183, 255));
    any->setBackground(2, QColor(217, 225, 187, 255));
}

void VisualForMilanRF::deleteItemInList()
{
    QTreeWidgetItem* taked = ui.treeWidget->currentItem();
    QTreeWidgetItem* parentTaked = taked->parent();

    if (parentTaked == nullptr)
        return;

    parentTaked->takeChild(parentTaked->indexOfChild(taked));
    
   // ui.treeWidget->collapseItem(ui.treeWidget->currentItem()); // закрытие элемента

    //  ui.treeWidget->clear(); // полна€ очистка виджета
}

void VisualForMilanRF::setData() // в случае двойного клика в €чейку открываем редактор
{
    QTreeWidgetItem* any = ui.treeWidget->currentItem(); // присваиваем указателю выбранную €чейку
    int column = ui.treeWidget->currentColumn(); // присваиваем переменной номер текущего столбца (отсчЄт начинаетс€ с 0-ого)

    if (column > 2) return; // не даЄм редактировать дальше третьего столбца

    qDebug() << "OPEN EDITOR";
    
    middleColumn = column;
    middleItem = any;

    ui.treeWidget->openPersistentEditor(any, column); // разрешаем редактирование €чейки
    ui.treeWidget->editItem(any, column); // открываем редактор
}

void VisualForMilanRF::closeEditor(QTreeWidgetItem* any) // слот закрыти€ редактора в случае внесени€ изменений (после нажати€ Enter)
{
    QString temporary = any->text(2).trimmed(); // убираем пробелы
    any->setText(2, temporary);

    if (any->text(2) != "") // красим если что-то написано в серийнике
    {
        any->setBackground(4, QColor(213, 176, 176, 255));
        any->setBackground(5, QColor(213, 176, 176, 255));
        any->setBackground(6, QColor(156, 203, 213, 255));
        any->setBackground(7, QColor(156, 203, 213, 255));
    }
    else
    {
        any->setBackground(4, QColor("white"));
        any->setBackground(5, QColor("white"));
        any->setBackground(6, QColor("white"));
        any->setBackground(7, QColor("white"));
    }
    ui.treeWidget->closePersistentEditor(middleItem, middleColumn); // закрываем редактор

    qDebug() << "CLOSE EDITOR";
}

void VisualForMilanRF::otherItemWasChecked(QTreeWidgetItem* any) // закрываем открытый редактор в случае переключени€ на другой элемент
{
    int column = ui.treeWidget->currentColumn();
    qDebug() << "Checked " << any->text(column);

    if (any == middleItem && column == middleColumn)
        return;

    QString temporary = any->text(2).trimmed();
    any->setText(2, temporary);

    if (any->text(2) != "")
    {
        any->setBackground(4, QColor(213, 176, 176, 255));
        any->setBackground(5, QColor(213, 176, 176, 255));
        any->setBackground(6, QColor(156, 203, 213, 255));
        any->setBackground(7, QColor(156, 203, 213, 255));
    }

    ui.treeWidget->closePersistentEditor(middleItem, middleColumn);
    middleItem = nullptr;

    qDebug() << "CLOSE EDITOR";
}


void VisualForMilanRF::adressFinder() // поиск в третьем столбце совпадающих значений с последующей записью в массив. ѕотом выводим полный адрес в первом столбце до найденного сопадени€.
{
    QInputDialog inputDialog;

    int number = inputDialog.getInt(this, "Add number", "Serial number", QLineEdit::Normal);
   
    QString strNumber;

    strNumber = strNumber.setNum(number);

    QList <QTreeWidgetItem*> myList = ui.treeWidget->findItems(strNumber, Qt::MatchRecursive, 2);
    
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