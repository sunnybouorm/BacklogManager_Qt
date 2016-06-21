#pragma once
#include <QtCore\QAbstractListModel>

#include "../../Source/Core/core.h"

class ActivityModel : public QAbstractListModel
{
	Q_OBJECT

public:
	ActivityModel(Core *core_, QObject *parent = Q_NULLPTR);
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private:
	Core *core_;
	QStringList string_list_;
};