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
    connect(ui.pushButtonTest, &QPushButton::clicked, this, &VisualForMilanRF::refresh);
    connect(ui.pushButtonBrowse, &QPushButton::clicked, this, &VisualForMilanRF::browse);
    
    middleColumn = 0;

    connect(ui.pushButtonReport, &QPushButton::clicked, this, &VisualForMilanRF::report);



    
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

void VisualForMilanRF::setData() // в случае двойного клика в ячейку открываем редактор
{
    QTreeWidgetItem* any = ui.treeWidget->currentItem(); // присваиваем указателю выбранную ячейку
    int column = ui.treeWidget->currentColumn(); // присваиваем переменной номер текущего столбца (отсчёт начинается с 0-ого)

    if (column > 2) return; // не даём редактировать дальше третьего столбца

    qDebug() << "OPEN EDITOR";
    
    middleColumn = column;
    middleItem = any;

    ui.treeWidget->openPersistentEditor(any, column); // разрешаем редактирование ячейки
    ui.treeWidget->editItem(any, column); // открываем редактор
}

void VisualForMilanRF::closeEditor(QTreeWidgetItem* any) // слот закрытия редактора в случае внесения изменений (после нажатия Enter)
{
    if (offChanger) return; // препятствуем многократному исполнению этой функции при изменении цветов

    QString temporary = any->text(2).trimmed(); // убираем пробелы
    any->setText(2, temporary);

    if (any->text(2) != "") // красим если что-то написано в серийнике
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

        any->setBackground(3, QColor("white"));
        any->setText(3, "");

        any->setBackground(4, QColor("white"));
        any->setData(4, Qt::CheckStateRole, QVariant());
        any->setText(4, "");

        any->setBackground(5, QColor("white"));
        any->setData(5, Qt::CheckStateRole, QVariant());
        any->setText(5, "");

        any->setBackground(6, QColor("white"));
        any->setData(6, Qt::CheckStateRole, QVariant());
        any->setText(6, "");

        any->setBackground(7, QColor("white"));
        any->setData(7, Qt::CheckStateRole, QVariant());
        any->setText(7, "");

        offChanger = false;
    }
    ui.treeWidget->closePersistentEditor(middleItem, middleColumn); // закрываем редактор

    qDebug() << "CLOSE EDITOR";
}

void VisualForMilanRF::otherItemWasChecked(QTreeWidgetItem* any) // закрываем открытый редактор в случае переключения на другой элемент
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

void VisualForMilanRF::adressFinder() // поиск в третьем столбце совпадающих значений с последующей записью в массив. Потом выводим полный адрес в первом столбце до найденного сопадения.
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

    QXmlStreamWriter xmlWriter(&file); // инициализируем объект QXmlStreamWriter ссылкой на объект с которым будем работать

    xmlWriter.setDevice(&file);
    xmlWriter.setAutoFormatting(true); // необходимо для автоматического перехода на новую строку
    xmlWriter.setAutoFormattingIndent(2); // задаём количество пробелов в отступе (по умолчанию 4)
    xmlWriter.writeStartDocument(); // пишет в шапке кодировку документа

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
        someXmlWriter.writeStartElement(some->text(0)); // отркывает начальный элемент "лестницы" xml

        someXmlWriter.writeAttribute("ID", some->text(1)); // присваиваем атрибуты внутри открытого первого элемента

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
        someXmlWriter.writeStartElement(some->text(0)); // отркывает начальный элемент "лестницы" xml

        someXmlWriter.writeAttribute("ID", some->text(1)); // присваиваем атрибуты внутри открытого первого элемента

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
	/* Открываем файл для Чтения с помощью пути, указанного в lineEditWrite */

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





void VisualForMilanRF::refresh()
{
    if (connectDB())
    {
        QTreeWidgetItem* some = ui.treeWidget->topLevelItem(0);

        recursionDbSqlReader(some);    

        mw_db.removeDatabase(mw_db.connectionName());
    }
}

void VisualForMilanRF::recursionDbSqlReader(QTreeWidgetItem* some)
{
    QSqlQuery query;
    QString queryString;

    QDate curDate = QDate::currentDate();

    if (some->childCount())
    {
        if (some->text(2) != nullptr)
        {
            queryString = "select date, channelFirst, channelSecond, channelThird, channelFour from channelTable where number = " + some->text(2) + " order by date desc";

			query.exec(queryString); // Отправляем запрос на количество записей

            query.next();

            for (int count = 3; count <= 7; count++)
            {
                queryString = query.value(count - 3).toString(); // ID с показаниями на единицу меньше чем мы выявили по номеру счётчика.
                some->setText((count), queryString);

                if (count == 3 && queryString == (curDate.toString("dd-MM-yyyy")))
                {
                    some->setBackground(3, QColor(125, 255, 116, 255));
                    continue;
                }
                if (count == 3 && queryString == (curDate.addDays(-1).toString("dd-MM-yyyy")))
                {
                    some->setBackground(3, QColor(255, 250, 119, 255));
                    continue;
                }

                if (count == 3)
                    some->setBackground(3, QColor(255, 143, 143, 255));
            }
        }

        int count = some->childCount();

        for (int x = 0; x < count; x++)
        {
            recursionDbSqlReader(some->child(x));
        }

    }
	else
	{
		if (some->text(2) != nullptr)
		{
			queryString = "select date, channelFirst, channelSecond, channelThird, channelFour from channelTable where number = " + some->text(2) + " order by date desc"; // запрашиваем нужный нам ID поо номеру прибора

			query.exec(queryString); // Отправляем запрос на количество записей

			query.next();

			for (int count = 3; count <= 7; count++)
			{

				queryString = query.value(count - 3).toString(); // ID с показаниями на единицу меньше чем мы выявили по номеру счётчика.
				some->setText((count), queryString);

                if (count == 3 && queryString == (curDate.toString("dd-MM-yyyy")))
                {
                    some->setBackground(3, QColor(125, 255, 116, 255));
                    continue;
                }
                if (count == 3 && queryString == (curDate.addDays(-1).toString("dd-MM-yyyy")))
                {
                    some->setBackground(3, QColor(255, 250, 119, 255));
                    continue;
                }
                if(count == 3)
                    some->setBackground(3, QColor(255, 143, 143, 255));
			}
		}
		return;
	}
}

bool VisualForMilanRF::connectDB()
{
    // почему то добавление имени подключения не даёт делать запросы.
    QFile file("browse.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Don't find browse file. Add a directory with a database.";
        return true;
    }

	QTextStream out(&file);

	line = out.readLine(); // метод readLine() считывает одну строку из потока

    mw_db = QSqlDatabase::addDatabase("QSQLITE"); // указываем какой использовать драйвер для подключения к БД и имя подключения. Если имя не задано то по умолчанию подключаемся к этой базе. Вроде так.
    //mw_db.setDatabaseName("//ENERGOSFERA-GES//Release//DataBaseMilanRF"); // Указываем с какой БД взаимодействовать. Если такого имени не найдёт то файл БД с указанным именем будет создан.
    
   // mw_db.setDatabaseName("C://Users//admin//source//repos//PortListening//x64//Release//DataBaseMilanRF");
    mw_db.setDatabaseName(line);
    // mw_db.setHostName("\\ENERGOSFERA-GES\Release");
    //mw_db.setPort(8080);
    //mw_db.setDatabaseName("//10.86.142.14//Release//DataBaseMilanRF"); // Указываем с какой БД взаимодействовать. Если такого имени не найдёт то файл БД с указанным именем будет создан.
    // mw_db.setUserName("Администратор");
    // mw_db.setPassword("RootToor#");

    mw_db.setConnectOptions("QSQLITE_OPEN_READONLY");

    if (!mw_db.open())
    {
        qDebug() << "Cannot open database: " << mw_db.lastError();
        return false;
    }
    else
    {
        qDebug() << "DataBase was OPEN";
    }

    file.close();
}

void VisualForMilanRF::browse()
{
    QFile file("browse.txt");

    if (!(file.open(QIODevice::WriteOnly | QIODevice::Truncate))) // Truncate - для очистки содержимого файла
    {
        qDebug() << "Don't find browse file. Add a directory with a database.";
        return;
    }

    QTextStream in(&file);

    QString addFileDonor = QFileDialog::getOpenFileName(0, "Choose directory with a database", "", "");

    in << addFileDonor << Qt::endl;

    if (addFileDonor == "")
        file.remove();

    file.close();
}


void VisualForMilanRF::report()
{
   // QString savedFile = "C://Users//admin//Desktop//12345.xlsx";
    QString savedFile = QFileDialog::getOpenFileName(0, "Save Excel file", "", "*.xls *.xlsx");
   // QFile file(savedFile);
   // file.open(QIODevice::WriteOnly);
   // file.close();

    if (savedFile == "")
    {
        return;
    }


    excelDonor = new QAxObject("Excel.Application", 0);
    workbooksDonor = excelDonor->querySubObject("Workbooks");
    workbookDonor = workbooksDonor->querySubObject("Open(const QString&)", savedFile); // 
    sheetsDonor = workbookDonor->querySubObject("Worksheets");
    int listDonor = sheetsDonor->property("Count").toInt();
    sheetDonor = sheetsDonor->querySubObject("Item(int)", listDonor);// Тут определяем лист с которым будем работаь

   
    QTreeWidgetItem* some = ui.treeWidget->topLevelItem(0);



    recursionXlsWriter(some);

    countRow = 1;

    delete cell;
    workbookDonor->dynamicCall("Close()"); // обязательно используем в работе с Excel иначе документы будет фbоном открыт в системе
    excelDonor->dynamicCall("Quit()");
    delete workbookDonor;
    delete excelDonor;
}



void VisualForMilanRF::recursionXlsWriter(QTreeWidgetItem* some)
{


    if (some->childCount())
    {
        if (some->text(1) != nullptr)
        {
            for (int column = 1; column <= 8; column++) {

               // if (column == 2 || column == 3) continue;

                cell = sheetDonor->querySubObject("Cells(&int,&int)", countRow, column); // так указываем с какой ячейкой работать

                cell->dynamicCall("SetValue(QString)", some->text(column));

            }
            countRow++;
        }

        int count = some->childCount();

        for (int x = 0; x < count; x++)
        {
            recursionXlsWriter(some->child(x));
        }

    }
    else
    {
        if (some->text(1) != nullptr)
        {
            for (int column = 1; column <= 8; column++) {
                
               // if (column == 2 || column == 3) continue;

				cell = sheetDonor->querySubObject("Cells(&int,&int)", countRow, column); // так указываем с какой ячейкой работать

                cell->dynamicCall("SetValue(QString)", some->text(column));
                
            }
            countRow++;
        }
        return;
    }
}