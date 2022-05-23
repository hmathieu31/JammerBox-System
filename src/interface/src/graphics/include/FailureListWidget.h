#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_FAILURE_LIST_WIDGET_H_INCLUDED_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_FAILURE_LIST_WIDGET_H_INCLUDED_

#include <QDockWidget>
#include <QTreeView>

#include "FailureListModel.h"

namespace jbox {
namespace graphics {

class FailureListWidget : public QDockWidget {
  Q_OBJECT

 public:
  FailureListWidget(QWidget* parent = 0);

  void setDisabled(bool value);

 signals:
  void onSelect(const failures::Failure* selected);

 private:
  QTreeView* view;
  FailureListModel* model;
  void selectionChanged(const QItemSelection& selected,
                        const QItemSelection& deselected);
};

}  // namespace graphics
}  // namespace jbox

#endif
