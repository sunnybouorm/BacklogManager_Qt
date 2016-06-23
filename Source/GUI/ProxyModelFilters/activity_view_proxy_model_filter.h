#pragma once
#include <QSortFilterProxyModel>
#include <QTableView>
#include "../Models/activity_model.h"

class ActivityViewSortFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	ActivityModel *activity_model_;
	ActivityViewSortFilterProxyModel(QTableView *view, ActivityModel *activity_model, QObject *parent= Q_NULLPTR);

	void sort(int column, Qt::SortOrder order);

	bool setData(const QModelIndex &index, const QVariant &value, int role);
};