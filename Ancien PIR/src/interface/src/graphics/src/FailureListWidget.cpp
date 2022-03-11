#include "FailureListWidget.h"

namespace jbox {
namespace graphics {

FailureListWidget::FailureListWidget(QWidget *parent)
    : QDockWidget(tr(""), parent) {
  setFeatures(QDockWidget::NoDockWidgetFeatures);
  setTitleBarWidget(new QWidget());

  model = new FailureListModel({});
  view = new QTreeView();
  view->setModel(model);
  view->expandAll();

  setWidget(view);

  connect(view->selectionModel(), &QItemSelectionModel::selectionChanged, this,
          &FailureListWidget::selectionChanged);
}

void FailureListWidget::selectionChanged(const QItemSelection &selected,
                                         const QItemSelection &deselected) {
  QList<QModelIndex> selectedIndexes = selected.indexes();
  if (selectedIndexes.empty()) {
    emit onSelect(nullptr);
  } else {
    // Si un élément est sélectionné, on cherche lequel
    // Un seul élément peut être sélectionné à la fois
    QModelIndex selectedIndex = selectedIndexes[0];
    // Seule une failure peut être sélectionnée, pas une catégorie, donc le parent de l'index doit toujours être défini
    QModelIndex parentIndex = model->parent(selectedIndex);
    // On récupère un pointeur vers l'item parent
    FailureListItem * parent = model->rootItem()->child(parentIndex.row());
    FailureListItem * selected = parent->child(selectedIndex.row());

    // On emit l'élément sélectionné
    emit onSelect(selected->failure());
  }
}

void FailureListWidget::setDisabled(bool value) {
  model->setDisabled(value); 
  // Update the model
  model->layoutChanged();
}

}  // namespace graphics
}  // namespace jbox
