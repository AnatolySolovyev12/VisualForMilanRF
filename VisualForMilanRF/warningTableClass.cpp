#include "warningTableClass.h"

warningTableClass::warningTableClass(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.closeButton, SIGNAL(clicked()), this, SLOT(close()));
	//QString filterStr = "number = '" + number + "'" + " ORDER BY date desc, channelFirst desc"; // фильтр начинаетс€ с "where" SQL синтаксиса без самого слова "where"

	model.setTable("warningTable"); // задаЄм таблицу с которой работаем

	//model.setFilter(filterStr); // лучше примен€ть фильтр до команды select
	model.select(); // заполн€ем модель значени€ми из таблицы
	model.setEditStrategy(QSqlTableModel::OnManualSubmit);// OnManualSubmit // OnFieldChange // OnRowChange // измен€€ значени€ в отображении
	
	ui.tableView->setModel(&model);
	ui.tableView->setColumnWidth(3, 600);

	countOfRows = model.rowCount();
	ui.statusBar->showMessage("Count of messeges: " + QString::number(countOfRows), 10000);

	connect(ui.clearButton, &QPushButton::clicked, this, &warningTableClass::clearTable);
}



void warningTableClass::clearTable()
{
	if (countOfRows > 0)
	{
		if (model.removeRows(0, countOfRows))
		{
			if (model.submitAll())
				ui.statusBar->showMessage("All rows was delete", 10000);
			else
			{
				ui.statusBar->showMessage("submitAll() wasnt done: " + model.lastError().text(), 10000);
				model.revertAll();
			}
		}
		else
			ui.statusBar->showMessage("removeRows() wasnt done: " + model.lastError().text(), 10000);
	}
}

