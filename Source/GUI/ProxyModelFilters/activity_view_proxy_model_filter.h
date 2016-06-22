#pragma once
#include <QSortFilterProxyModel>
#include <QTableView>
#include "../Models/activity_model.h"

class ActivityViewSortFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	ActivityViewSortFilterProxyModel(QTableView *view, ActivityModel *activity_model, QObject *parent= Q_NULLPTR);

	void sort(int column, Qt::SortOrder order);
};