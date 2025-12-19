#include "RangeTableValue.h"

RangeTableValue::RangeTableValue(QWidget* parent, QString numberAny)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.applyButton->hide();

	connect(ui.closeButton, SIGNAL(clicked()), this, SLOT(close()));

	connect(ui.applyButton, SIGNAL(clicked()), this, SLOT(applyFunc()));

	connect(ui.xlsButton, SIGNAL(clicked()), this, SLOT(getXlsReport()));

	connect(&model, &QAbstractItemModel::dataChanged, this, &RangeTableValue::dataChangedCheck);

	this->number = numberAny;

	QString filterStr = "number = '" + number + "'" + " ORDER BY date desc, channelFirst desc"; // фильтр начинается с "where" SQL синтаксиса без самого слова "where"

	if (number.length() > 6)
		model.setTable("channelTable"); // задаём таблицу с которой работаем
	else
		model.setTable("counterTable"); // задаём таблицу с которой работаем

	model.setFilter(filterStr); // лучше применять фильтр до команды select
	model.select(); // заполняем модель значениями из таблицы
	model.setEditStrategy(QSqlTableModel::OnManualSubmit);// OnManualSubmit // OnFieldChange // OnRowChange // изменяя значения в отображении

	ui.tableView->setModel(&model);
}

RangeTableValue::~RangeTableValue()
{}

void RangeTableValue::applyFunc()
{
	if (!model.submitAll())
		qDebug() << model.lastError();
	ui.applyButton->hide();
}

void RangeTableValue::dataChangedCheck()
{
	if (model.isDirty())
		ui.applyButton->show();
}

void RangeTableValue::getXlsReport()
{
	int countOfRowFromModel = model.rowCount();
	qDebug() << "All count = " << countOfRowFromModel;
	qDebug() << model.record(1).value(1).toString() << " " << model.record(1).value(2).toString() << " " << model.record(1).value(3).toString();

	//	Извлекайте значения по имени или индексу столбца из QSqlRecord : record.value("column_name").toString() или record.value(columnIndex).toString().

	

	/*
	QString savedFile = QFileDialog::getSaveFileName(0, "Save Excel file", "", "*.xls");
	QFile file(savedFile);
	file.open(QIODevice::WriteOnly);
	file.close();

	if (savedFile == "")
	{
		return;
	}

	QAxObject *excelDonor = new QAxObject("Excel.Application", 0);
	QAxObject *workbooksDonor = excelDonor->querySubObject("Workbooks");
	QAxObject *workbookDonor = workbooksDonor->querySubObject("Open(const QString&)", savedFile); // 
	QAxObject *sheetsDonor = workbookDonor->querySubObject("Worksheets");
	int listDonor = sheetsDonor->property("Count").toInt();
	QAxObject *sheetDonor = sheetsDonor->querySubObject("Item(int)", listDonor);// Тут определяем лист с которым будем работаь

	for (int countOfTop = 0; countOfTop < ui.treeWidget->topLevelItemCount(); countOfTop++)
	{
		QTreeWidgetItem* some = ui.treeWidget->topLevelItem(countOfTop);
		recursionXlsWriter(some);
		some = nullptr;
	}

	countRow = 1;

	workbookDonor->dynamicCall("Save()");
	workbookDonor->dynamicCall("Close()"); // обязательно используем в работе с Excel иначе документы будет фbоном открыт в системе
	excelDonor->dynamicCall("Quit()");
	delete excelDonor;
	*/

}
/*
void xlsWriterFuncForSqLiteTable(QAxObject* some)
{
	if (some->childCount())
	{
		if (some->text(1) != nullptr)
		{
			for (int column = 1; column <= 8; column++) {

				cell = sheetDonor->querySubObject("Cells(&int,&int)", countRow, column); // так указываем с какой ячейкой работать

				if ((some->checkState(column) == Qt::Unchecked) && (column > 3) && (some->text(2).length() > 6)) continue;

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
}
*/