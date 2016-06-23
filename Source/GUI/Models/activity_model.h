#pragma once
#include <QtCore\QAbstractListModel>

#include "../../Source/Core/core.h"

class ActivityModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	int tag_row_;
	QStringList string_list_;

	ActivityModel(Core *core_, QObject *parent = Q_NULLPTR);
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const Q_DECL_OVERRIDE;

	bool insertRows(int position, int count, const QModelIndex &parent = QModelIndex());

	bool removeRows(int position, int count, const QModelIndex &index = QModelIndex());

	Qt::ItemFlags flags(const QModelIndex &index) const;

	bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole);
	bool setDataSql(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole, 
		Request sql_request = UPDATE);

private:
	Core *core_;
};