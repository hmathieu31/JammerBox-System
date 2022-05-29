#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_FAILURE_CONFIGURE_WIDGET_H_INCLUDED_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_FAILURE_CONFIGURE_WIDGET_H_INCLUDED_

#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

#include "failures.h"

namespace jbox {
namespace graphics {

class FailureConfigureWidget : public QDockWidget {
  Q_OBJECT

 public:
  FailureConfigureWidget(QWidget* parent = 0);

  /**
   * Change le layout pour affiche les paramètres de la failure
   *
   * @param failure la failure
   */
  void setFailure(const failures::Failure* failure);

  std::vector<jbox::failures::ParamData> getParams();

  int getCamChoice();

 private:
  std::vector<QWidget*> fields;

  QGroupBox* box;
  QFormLayout* layout = nullptr;

  QLabel* notSelectedLabel;
  QLabel* noParamsLabel;

  QSpinBox* camChoice ;

  const failures::Failure * failure = nullptr;

  void clear();
};

}  // namespace graphics
}  // namespace jbox

#endif
