#include "HistoryTable.h"

#include <QHeaderView>

#include "failures.h"

namespace jbox {
namespace graphics {

HistoryTable::HistoryTable(QWidget* parent) : QTableView(parent) {
  model = new HistoryModel();
  setModel(model);

  // Set the horizontal header
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("Timestamp"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("Data"));

  // Hide vertical header
  verticalHeader()->hide();

  // Enable row selection
  setSelectionBehavior(QAbstractItemView::SelectRows);

  // Fill the space
  horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  // Align header left
  horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

  // Hide grid
  setShowGrid(false);
}

HistoryTable::~HistoryTable() {
  delete model;
}

void HistoryTable::add_data(std::time_t timestamp, failures::Failure failure) {
  QVariant data;
  data.setValue(HistoryTableItem(timestamp, failure));
  model->setData(model->index(-1, 0), data);
  model->layoutChanged();
}

void HistoryTable::add_data(std::time_t timestamp, results::Result result) {
  QVariant data;
  data.setValue(HistoryTableItem(timestamp, result));
  model->setData(model->index(-1, 0), data);
  model->layoutChanged();
}

void HistoryTable::selectionChanged(const QItemSelection& selected,
                      const QItemSelection& deselected) {
  model->layoutChanged();
  QList<QModelIndex> selectedIndexes = selected.indexes();
  if (!selectedIndexes.empty()) {
    QModelIndex selectedIndex = selectedIndexes[0];
    HistoryTableItem item =
        model->getList().at(selectedIndex.row()).value<HistoryTableItem>();
    if (item.type == "Failure") {
      const failures::Failure failure = item.data.value<jbox::failures::Failure>() ;
      emit onSelect(item.timestamp, &failure);
    } else {
      const results::Result result = item.data.value<jbox::results::Result>() ; 
      emit onSelect(item.timestamp, &result);
    }
  }
}

}  // namespace graphics
}  // namespace jbox
