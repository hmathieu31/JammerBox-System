#include "StatusBarWidget.h"

namespace jbox {
namespace graphics {

StatusBarWidget::StatusBarWidget(QWidget* parent) : QStatusBar(parent) {
  setStyleSheet("QStatusBar::item { border: none; };");

  label = new QLabel("");
  QWidget * container = new QWidget(this);
  QHBoxLayout* layout = new QHBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  QWidget * circleContainer = new QWidget();
  QHBoxLayout * circleContainerLayout = new QHBoxLayout();
  circleContainerLayout->setMargin(10);
  circleWidget = new CircleStatusWidget();
  circleContainerLayout->addWidget(circleWidget);
  circleContainer->setLayout(circleContainerLayout);

  layout->addWidget(circleContainer);
  layout->addWidget(label);
  layout->addSpacing(1);

  container->setLayout(layout);
  addWidget(container);

  switchState(DISCONNECTED);
}

void StatusBarWidget::switchState(State state) {
  QColor color;
  switch (state) {
    case CONNECTED: {
      label->setText(QString("Connected to COM port"));
      color = QColor("#38A6EB");
      break;
    }
    case DISCONNECTED: {
      label->setText(QString("Not connected"));
      color = QColor(Qt::lightGray);
      break;
    }
  }
  circleWidget->updateColor(color);

  emit onSwitchState(state);
}

}  // namespace graphics
}  // namespace jbox

