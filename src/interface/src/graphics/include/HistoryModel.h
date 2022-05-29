#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_HISTORYMODEL_INCLUDED_H_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_HISTORYMODEL_INCLUDED_H_

#include <QAbstractTableModel>
#include <QDesktopWidget>
#include <QWidget>

#include "HistoryTableItem.h"

namespace jbox {
namespace graphics {

class HistoryModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  HistoryModel(QObject *parent = nullptr);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  bool setHeaderData(int section, Qt::Orientation orientation,
                     const QVariant &value, int role = Qt::EditRole) override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

  std::map<int, QVariant> getList();

 private:
  // Stores data for the headers
  std::map<int, QVariant> header;
  // Stores data for the content
  std::map<int, QVariant> list;

  int row_count = 0;
  int column_count = 0;
};

}  // namespace graphics
}  // namespace jbox

#endif
