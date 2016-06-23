#include "activity_view_proxy_model_filter.h"

#include <QAbstractItemModel>

#include <iostream>//TODO delete me

ActivityViewSortFilterProxyModel::ActivityViewSortFilterProxyModel(QTableView *view, 
	ActivityModel *activity_model, QObject *parent)
{
	this->activity_model_ = activity_model;
	this->setSourceModel(activity_model);
	view->setModel(this);
}

bool ActivityViewSortFilterProxyModel::setData(const QModelIndex &index, const QVariant &value, int role) {

	if (index.isValid() && role == Qt::EditRole) 
	{
		if (value.toString() == "") {}
		else if ((index.row() == activity_model_->tag_row_) && (value == "<Add new Activity>"))
		{
			activity_model_->insertRows(index.row(), 1);
			activity_model_->string_list_.replace(index.row(), value.toString());
			activity_model_->data(index, Qt::FontRole);
			activity_model_->data(index, Qt::ForegroundRole);
			activity_model_->data(index, Qt::TextAlignmentRole);

			emit dataChanged(index, index);
			return true;
		} else if (index.row() == activity_model_->tag_row_) 
		{
			bool is_successful = false;
			is_successful = activity_model_->removeRows(activity_model_->tag_row_, 1);
			is_successful &= this->activity_model_->setData(index, value, Qt::EditRole);
			is_successful &= setData(index, "<Add new Activity>", Qt::EditRole);

			return is_successful;
		} else
		{
			return this->activity_model_->setData(index, value, Qt::EditRole);
		}
	}
	return false;
}

void ActivityViewSortFilterProxyModel::sort(int column, Qt::SortOrder order) {
	//TODO: sort all activity items in model in ascending or descending order based on header arrow position, but keep
	//the <Add new Activity> tag position unchanged at row=0
	if (activity_model_->string_list_.count() != 0) {
		int first_row, last_row, index_row;
		first_row = 0;
		last_row = this->activity_model_->string_list_.count() - 1;

		//remove <Add New Activity> tag
		if (activity_model_->string_list_.at(first_row) == "<Add new Activity>")
		{
			this->removeRows(first_row, 1);
			last_row -= 1;
			index_row = 0;
		}
		else if (activity_model_->string_list_.at(last_row) == "<Add new Activity>")
		{
			this->removeRows(last_row, 1);
			last_row -= 1;
			index_row = last_row;
		}

		this->activity_model_->tag_row_ = index_row;

		//sort List
		QSortFilterProxyModel::sort(column, order);

		//Insert <Add new Activity> tag at the top of the list
		QModelIndex index = QAbstractItemModel::createIndex(index_row, 0);
		this->setData(index, "<Add new Activity>", Qt::EditRole);
	}
}

//TODO: Overlooad set data such that items inserted are automatically sorted