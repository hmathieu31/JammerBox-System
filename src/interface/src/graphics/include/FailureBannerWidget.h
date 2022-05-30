#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_FAILURE_BANNER_WIDGET_H_INCLUDED_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_FAILURE_BANNER_WIDGET_H_INCLUDED_

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "failures.h"
#include "waitingspinnerwidget.h"

namespace jbox {
namespace graphics {

class FailureBannerWidget : public QWidget {
  Q_OBJECT

 public:
  FailureBannerWidget(QWidget* parent = 0);

  enum State { RUNNING, SELECTED, DEFAULT };
  /**
   * Change d'état par parmis les State
   *
   * @param state le nouvel état
   */
  void switchState(State state);

  const failures::Failure * getSelected();

  void setEnabled(bool value);

 public slots:
  void setSelectedFailure(const failures::Failure* failure);

 signals:
  void onStart();
  void onStop();

 private:
  WaitingSpinnerWidget* spinner;
  QLabel* label;
  QPushButton* start;
  QPushButton* stop;

  void startClicked();
  void stopClicked();

  const failures::Failure * selected;
};

}  // namespace graphics
}  // namespace jbox

#endif
