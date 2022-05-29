#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_FAILURE_LIST_MODEL_INCLUDED_H_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_FAILURE_LIST_MODEL_INCLUDED_H_

#include <QAbstractItemModel>
#include "FailureListItem.h"
#include "failures.h"

namespace jbox {
namespace graphics {

class FailureListModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  explicit FailureListModel(const std::vector<failures::Failure> failures, QObject *parent = nullptr);
  ~FailureListModel();

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  FailureListItem * rootItem();
  void setDisabled(bool value);

 private:
  FailureListItem * m_rootItem;
  bool m_disabled = false;
};

}  // namespace graphics
}  // namespace jbox
#endif
