#include "VisualForMilanRF.h"

VisualForMilanRF::VisualForMilanRF(QWidget* parent)
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
	connect(ui.pushButtonReport, &QPushButton::clicked, this, &VisualForMilanRF::report);
	connect(ui.pushButtonRange, &QPushButton::clicked, this, &VisualForMilanRF::showRangeTable);
	connect(ui.pushButtonSort, &QPushButton::clicked, this, &VisualForMilanRF::sortTable);

	middleColumn = 0;
	sBar = new QStatusBar();
	QMainWindow::setStatusBar(sBar);

	startingImportXml();
}

VisualForMilanRF::~VisualForMilanRF()
{}


void VisualForMilanRF::addItemInList()
{
	QTreeWidgetItem* any = nullptr;

	if (ui.treeWidget->currentItem() == nullptr)
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

	if (column == 3 || column == 4 || column == 5 || column == 6 || column == 7) return; // �� ��� ������������� ������ �������� �������            

   // qDebug() << "OPEN EDITOR";

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

		any->setBackground(4, QColor(156, 203, 213, 255));
		any->setCheckState(4, any->checkState(4));

		any->setBackground(5, QColor(156, 203, 213, 255));
		any->setCheckState(5, any->checkState(5));

		any->setBackground(6, QColor(213, 176, 176, 255));
		any->setCheckState(6, any->checkState(6));

		any->setBackground(7, QColor(213, 176, 176, 255));
		any->setCheckState(7, any->checkState(7));

		any->setBackground(8, QColor(221, 221, 221, 255));
		any->setBackground(9, QColor(221, 221, 221, 255));

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

		any->setBackground(7, QColor("white"));
		any->setText(8, "");

		any->setBackground(7, QColor("white"));
		any->setText(9, "");

		offChanger = false;
	}
	ui.treeWidget->closePersistentEditor(middleItem, middleColumn); // ��������� ��������
}


void VisualForMilanRF::otherItemWasChecked(QTreeWidgetItem* any) // ��������� �������� �������� � ������ ������������ �� ������ �������
{
	if (offChanger) return;

	int column = ui.treeWidget->currentColumn();
	// qDebug() << "Checked " << any->text(column);

	if (any == middleItem && column == middleColumn)
		return;

	QString temporary = any->text(2).trimmed();
	any->setText(2, temporary);

	if (any->text(2) != "")
	{
		offChanger = true;
		any->setBackground(4, QColor(156, 203, 213, 255));
		any->setBackground(5, QColor(156, 203, 213, 255));
		any->setBackground(6, QColor(213, 176, 176, 255));
		any->setBackground(7, QColor(213, 176, 176, 255));
		any->setBackground(8, QColor(221, 221, 221, 255));
		any->setBackground(9, QColor(221, 221, 221, 255));
		offChanger = false;
	}

	ui.treeWidget->closePersistentEditor(middleItem, middleColumn);
	middleItem = nullptr;
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
			// qDebug() << ui.treeWidget->topLevelItem(0)->text(0);
			sBar->showMessage(ui.treeWidget->topLevelItem(0)->text(0), 10000);
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

		sBar->showMessage(strNumber, 10000);

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
		someXmlWriter.writeStartElement("Point"); // ��������� ��������� ������� "��������" xml

		someXmlWriter.writeAttribute("Adress", some->text(0)); // ����������� �������� ������ ��������� ������� ��������  

		someXmlWriter.writeAttribute("ID", some->text(1));

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

		someXmlWriter.writeAttribute("StartingValueCold", some->text(8));
		someXmlWriter.writeAttribute("StartingValueHot", some->text(9));

		int count = some->childCount();

		for (int x = 0; x < count; x++)
		{
			recursionXmlWriter(some->child(x), someXmlWriter);
		}

		someXmlWriter.writeEndElement();
	}
	else
	{
		someXmlWriter.writeStartElement("Point"); // ��������� ��������� ������� "��������" xml  

		someXmlWriter.writeAttribute("Adress", some->text(0)); // ����������� �������� ������ ��������� ������� ��������   

		someXmlWriter.writeAttribute("ID", some->text(1)); //

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

		someXmlWriter.writeAttribute("StartingValueCold", some->text(8));
		someXmlWriter.writeAttribute("StartingValueHot", some->text(9));

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

	file.close();

	QFile txtFile("tree.txt");

	if (!(txtFile.open(QIODevice::WriteOnly | QIODevice::Truncate))) // Truncate - ��� ������� ����������� �����
	{
		// qDebug() << "Don't find browse file. Add a directory with a tree.";
		sBar->showMessage("Don't find browse file. Add a directory with a tree.", 10000);
		return;
	}

	QTextStream in(&txtFile);

	in << addFileDonor << Qt::endl;

	if (addFileDonor == "")
		txtFile.remove();

	txtFile.close();
}


void VisualForMilanRF::loopXmlReader(QTreeWidgetItem* some, QXmlStreamReader& xmlReader)
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
				if (val.name().toString() == "Adress") some->setText(0, val.value().toString());

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

				if (val.name().toString() == "StartingValueCold") some->setText(8, val.value().toString());
				if (val.name().toString() == "StartingValueHot") some->setText(9, val.value().toString());
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
	bool ok;
	double middleValue;
	QDate curDate = QDate::currentDate();

	if (some->childCount())
	{
		if (some->text(2) != nullptr)
		{
			if (some->text(2).length() > 5)
				queryString = "select date, channelFirst, channelSecond, channelThird, channelFour from channelTable where number = " + some->text(2) + " order by date desc";
			else
				queryString = "select date, channelFirst, channelSecond, channelThird, channelFour from counterTable where number = " + some->text(2) + " order by date desc";


			query.exec(queryString); // ���������� ������ �� ���������� �������

			query.next();

			for (int count = 3; count <= 7; count++)
			{
				queryString = query.value(count - 3).toString(); // ID � ����������� �� ������� ������ ��� �� ������� �� ������ ��������.

				if (count == 3)
				{
					some->setText((count), queryString);
				}
				else
				{
					if (count == 4 || count == 5)
					{
						middleValue = (queryString.toDouble(&ok) / 100) + some->text(8).toDouble(&ok);
					}
					else
					{
						middleValue = (queryString.toDouble(&ok) / 100) + some->text(9).toDouble(&ok);
					}

					if (some->checkState(count) == Qt::Checked)
					{
						some->setText((count), queryString.setNum(middleValue));
					}
					else
					{
						some->setText((count), queryString);
					}
				}

				if (count == 3 && queryString == (curDate.toString("yyyy-MM-dd")))
				{
					some->setBackground(3, QColor(125, 255, 116, 255));
					continue;
				}
				if (count == 3 && queryString == (curDate.addDays(-1).toString("yyyy-MM-dd")))
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
			if (some->text(2).length() > 5)
				queryString = "select date, channelFirst, channelSecond, channelThird, channelFour from channelTable where number = " + some->text(2) + " order by date desc";
			else
				queryString = "select date, channelFirst, channelSecond, channelThird, channelFour from counterTable where number = " + some->text(2) + " order by date desc";

			query.exec(queryString); // ���������� ������ �� ���������� �������

			query.next();

			for (int count = 3; count <= 7; count++)
			{

				queryString = query.value(count - 3).toString(); // ID � ����������� �� ������� ������ ��� �� ������� �� ������ ��������.

				if (count == 3)
				{
					some->setText((count), queryString);
				}
				else
				{
					if (count == 4 || count == 5)
					{
						middleValue = (queryString.toDouble(&ok) / 100) + some->text(8).toDouble(&ok);
					}
					else
					{
						middleValue = (queryString.toDouble(&ok) / 100) + some->text(9).toDouble(&ok);
					}

					if (some->checkState(count) == Qt::Checked)
					{
						some->setText((count), queryString.setNum(middleValue));
					}
					else
					{
						some->setText((count), queryString);
					}
				}

				if (count == 3 && queryString == (curDate.toString("yyyy-MM-dd")))
				{
					some->setBackground(3, QColor(125, 255, 116, 255));
					continue;
				}
				if (count == 3 && queryString == (curDate.addDays(-1).toString("yyyy-MM-dd")))
				{
					some->setBackground(3, QColor(255, 250, 119, 255));
					continue;
				}
				if (count == 3)
					some->setBackground(3, QColor(255, 143, 143, 255));
			}
		}
		return;
	}
}


bool VisualForMilanRF::connectDB()
{
	// ������ �� ���������� ����� ����������� �� ��� ������ �������.
	QFile file("browse.txt");

	if (!file.open(QIODevice::ReadOnly))
	{
		sBar->showMessage("Don't find browse file. Add a directory with a database.", 10000);
		return true;
	}

	QTextStream out(&file);

	line = out.readLine(); // ����� readLine() ��������� ���� ������ �� ������

	mw_db = QSqlDatabase::addDatabase("QSQLITE"); // ��������� ����� ������������ ������� ��� ����������� � �� � ��� �����������. ���� ��� �� ������ �� �� ��������� ������������ � ���� ����. ����� ���.

	mw_db.setDatabaseName(line);

	mw_db.setConnectOptions("QSQLITE_OPEN_READONLY");

	if (!mw_db.open())
	{
		QString errorStr = "Cannot open database: " + mw_db.lastError().text();
		sBar->showMessage(errorStr, 10000);
		return false;
	}
	else
	{
		sBar->showMessage("DataBase was OPEN", 10000);
	}
	file.close();
}


void VisualForMilanRF::browse()
{
	QString addFileDonor = QFileDialog::getOpenFileName(0, "Choose directory with a database", "", "");

	if (addFileDonor == "")
		return;

	QFile file("browse.txt");

	if (!(file.open(QIODevice::WriteOnly | QIODevice::Truncate))) // Truncate - ��� ������� ����������� �����
	{
		sBar->showMessage("Don't find browse file. Add a directory with a database.", 10000);
		return;
	}

	QTextStream in(&file);

	in << addFileDonor << Qt::endl;

	file.close();
}


void VisualForMilanRF::report()
{
	QString savedFile = QFileDialog::getSaveFileName(0, "Save Excel file", "", "*.xls");
	QFile file(savedFile);
	file.open(QIODevice::WriteOnly);
	file.close();

	if (savedFile == "")
	{
		return;
	}

	excelDonor = new QAxObject("Excel.Application", 0);
	workbooksDonor = excelDonor->querySubObject("Workbooks");
	workbookDonor = workbooksDonor->querySubObject("Open(const QString&)", savedFile); // 
	sheetsDonor = workbookDonor->querySubObject("Worksheets");
	int listDonor = sheetsDonor->property("Count").toInt();
	sheetDonor = sheetsDonor->querySubObject("Item(int)", listDonor);// ��� ���������� ���� � ������� ����� �������

	QTreeWidgetItem* some = ui.treeWidget->topLevelItem(0);

	recursionXlsWriter(some);

	countRow = 1;

	workbookDonor->dynamicCall("Close()"); // ����������� ���������� � ������ � Excel ����� ��������� ����� �b���� ������ � �������
	excelDonor->dynamicCall("Quit()");
	delete excelDonor;
}


void VisualForMilanRF::recursionXlsWriter(QTreeWidgetItem* some)
{
	if (some->childCount())
	{
		if (some->text(1) != nullptr)
		{
			for (int column = 1; column <= 8; column++) {

				cell = sheetDonor->querySubObject("Cells(&int,&int)", countRow, column); // ��� ��������� � ����� ������� ��������

				if ((some->checkState(column) == Qt::Unchecked) && (column > 3) && (some->text(2).length() >5)) continue;

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

				cell = sheetDonor->querySubObject("Cells(&int,&int)", countRow, column); // ��� ��������� � ����� ������� ��������

				if ((some->checkState(column) == Qt::Unchecked) && (column > 3) && (some->text(2).length() > 5)) continue;

				cell->dynamicCall("SetValue(QString)", some->text(column));
			}
			countRow++;
		}
		return;
	}
}


void VisualForMilanRF::startingImportXml()
{
	/* ��������� ���� ��� ������ � ������� ����, ���������� � lineEditWrite */

	QFile file("tree.txt");

	if (!file.open(QIODevice::ReadOnly))
	{
		sBar->showMessage("Don't find browse file. Add a directory with a tree.", 10000);
		return;
	}

	QTextStream out(&file);

	QString myLine = out.readLine(); // ����� readLine() ��������� ���� ������ �� ������

	if (myLine == "")
	{
		sBar->showMessage("Don't find browse file. Add a directory with a tree.", 10000);
		return;
	}

	file.close();

	QFile xmlFile(myLine);

	if (xmlFile.exists())
	{
		xmlFile.open(QFile::ReadWrite);
	}
	else
	{
		sBar->showMessage("Don't find browse file. Add a directory with a tree.", 10000);
		return;
	}

	QXmlStreamReader xmlReader(&xmlFile);

	QTreeWidgetItem* any = ui.treeWidget->topLevelItem(0);

	loopXmlReader(any, xmlReader);

	xmlFile.close();
}


void VisualForMilanRF::showRangeTable()
{
	QTreeWidgetItem* taked = ui.treeWidget->currentItem();

	connectDB();
	myRange = new RangeTableValue(this, taked->text(2));
	myRange->show();
	mw_db.removeDatabase(mw_db.connectionName());
}


void VisualForMilanRF::sortTable()
{
	if (sortBool)
	{
		ui.treeWidget->currentItem()->sortChildren(ui.treeWidget->currentColumn(), Qt::AscendingOrder);
		sortBool = !sortBool;
	}
	else
	{
		ui.treeWidget->currentItem()->sortChildren(ui.treeWidget->currentColumn(), Qt::DescendingOrder);
		sortBool = !sortBool;
	}
}