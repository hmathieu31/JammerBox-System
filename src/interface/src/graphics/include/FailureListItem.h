#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_FAILURE_LIST_ITEM_H_INCLUDED_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_FAILURE_LIST_ITEM_H_INCLUDED_

#include <QVariant>
#include <QVector>

#include "failures.h"

namespace jbox {
namespace graphics {

class FailureListItem {
 public:
  explicit FailureListItem(const QVector<QVariant> &data,
                           const failures::Failure *failure = nullptr,
                           FailureListItem *parentItem = nullptr);
  ~FailureListItem();

  /**
   * Ajoute une fils à ce noeud
   *
   * @param child le pointeur vers le fils
   * @return l'adresse du fils
   */
  FailureListItem *appendChild(FailureListItem *child);

  /**
   * Récupère le row ieme fils
   *
   * @param int indice du fils
   * @return un pointeur vers le fils
   */
  FailureListItem *child(int row);

  /**
   * Récupère le nombre de fils
   *
   * @return le nombre de fils
   */
  int childCount() const;

  /**
   * Récupère le nombre de données à afficher
   *
   * @return le nombre de colonnes
   */
  int columnCount() const;

  /**
   * Récupère la donnée column ieme
   *
   * @param column l'indice de la donnée
   * @return la donnée
   */
  QVariant data(int column) const;

  /**
   * Retourne l'indice de cet élément dans la liste des childs du parent
   *
   * @return l'indice de l'élément
   */
  int row() const;

  /**
   * Retourne un pointeur vers le parent
   *
   * @param le pointeur vers le parent
   */
  FailureListItem *parentItem();

  /**
   * Retourne un pointeur vers la failure qu'il représente
   *
   * @return un pointeur vers la failure
   */
  const failures::Failure * failure() {
    return m_failure;
  }

 private:
  const failures::Failure * m_failure;
  QVector<FailureListItem *> m_childItems;
  QVector<QVariant> m_itemData;
  FailureListItem *m_parentItem;
};

}  // namespace graphics
}  // namespace jbox

#endif
