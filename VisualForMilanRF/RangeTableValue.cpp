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

	QString savedFile = QFileDialog::getSaveFileName(0, "Save Excel file", "", "*.xls");
	QFile file(savedFile);
	file.open(QIODevice::WriteOnly);
	file.close();

	if (savedFile == "")
	{
		return;
	}

	excelDonorRanged = new QAxObject("Excel.Application", 0);
	workbooksDonorRanged = excelDonorRanged->querySubObject("Workbooks");
	workbookDonorRanged = workbooksDonorRanged->querySubObject("Open(const QString&)", savedFile); // 
	sheetsDonorRanged = workbookDonorRanged->querySubObject("Worksheets");
	int listDonor = sheetsDonorRanged->property("Count").toInt();
    sheetDonorRanged = sheetsDonorRanged->querySubObject("Item(int)", listDonor);// Тут определяем лист с которым будем работаь

	for (int rowCount = 0; rowCount < countOfRowFromModel; rowCount++)
	{
		QString temp;

		for (int columnCount = 0; columnCount <= 5; columnCount++)
		{
			xlsUnit = sheetDonorRanged->querySubObject("Cells(&int,&int)", rowCount+1, columnCount+1); // так указываем с какой ячейкой работать
			xlsUnit->dynamicCall("SetValue(QString)", model.record(rowCount).value(columnCount).toString());
			temp += model.record(rowCount).value(columnCount).toString() + "  ";
			xlsUnit = nullptr;
		}

		qDebug() << temp;
	}

	workbookDonorRanged->dynamicCall("Save()");
	workbookDonorRanged->dynamicCall("Close()"); // обязательно используем в работе с Excel иначе документы будет фbоном открыт в системе
	excelDonorRanged->dynamicCall("Quit()");
	delete excelDonorRanged;
}