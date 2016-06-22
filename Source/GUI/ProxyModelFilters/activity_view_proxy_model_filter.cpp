#include "activity_view_proxy_model_filter.h"

#include <QAbstractItemModel>

ActivityViewSortFilterProxyModel::ActivityViewSortFilterProxyModel(QTableView *view, 
	ActivityModel *activity_model, QObject *parent)
{
	this->setSourceModel(activity_model);
	view->setModel(this);
}

void ActivityViewSortFilterProxyModel::sort(int column, Qt::SortOrder order) {
	//TODO: sort all activity items in model in ascending or descending order based on header arrow position, but keep
	//the <Add new Activity> tag position unchanged at row=0

	//remove <Add New Activity> tag
	//TODO

	//sort List
	QSortFilterProxyModel::sort(column, order);

	//Insert <Add New Activity tag at row = 0>
	//TODO
}

//TODO: Overlooad set data such that items inserted are automatically sorted