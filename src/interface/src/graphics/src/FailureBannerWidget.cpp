#include "FailureBannerWidget.h"

namespace jbox {
namespace graphics {

FailureBannerWidget::FailureBannerWidget(QWidget* parent) : QWidget(parent) {
  // Create the spinner and hide it
  spinner = new WaitingSpinnerWidget(this, false, false);
  spinner->setRoundness(70.0);
  spinner->setMinimumTrailOpacity(15.0);
  spinner->setTrailFadePercentage(70.0);
  spinner->setNumberOfLines(12);
  spinner->setLineLength(5);
  spinner->setLineWidth(2);
  spinner->setInnerRadius(5);
  spinner->setRevolutionsPerSecond(1);
  spinner->setVisible(false);

  // Create the label
  label = new QLabel("");

  // Create the start and stop button and hide it
  start = new QPushButton("start");
  start->setVisible(false);
  start->setEnabled(false);
  stop = new QPushButton("stop");
  stop->setVisible(false);

  // Create the layout of the banner
  QHBoxLayout* layout = new QHBoxLayout();
  layout->setMargin(15);

  layout->addWidget(spinner);
  layout->addWidget(label);
  layout->addStretch(1);
  layout->addWidget(start);
  layout->addWidget(stop);

  setLayout(layout);

  // Change the banner background
  setAttribute(Qt::WA_StyledBackground, true);
  setObjectName("FailureBannerWidget");

  switchState(DEFAULT);

  // Connect the events
  connect(start, &QPushButton::clicked, this,
          &FailureBannerWidget::startClicked);
  connect(stop, &QPushButton::clicked, this, &FailureBannerWidget::stopClicked);
}

void FailureBannerWidget::setSelectedFailure(const failures::Failure* failure) {
  if (failure == nullptr) {
    switchState(DEFAULT);
  } else {
    selected = failure;
    switchState(SELECTED);
  }
}

void FailureBannerWidget::startClicked() {
  switchState(RUNNING);
  emit onStart();
}

void FailureBannerWidget::stopClicked() {
  switchState(SELECTED);
  emit onStop();
}

void FailureBannerWidget::switchState(State state) {
  std::string color;
  std::string background_color;
  switch (state) {
    case RUNNING: {
      // Change colors
      setStyleSheet(
          "#FailureBannerWidget { background-color: #fff3cd }"
          "#FailureBannerWidget QLabel { color: #664d03 }");
      // Show spinner
      spinner->start();
      spinner->setVisible(true);
      // Change text
      label->setText(QString("Failure %1 est en cours...")
                         .arg(QString::fromStdString(selected->name)));
      // Show stop
      start->setVisible(false);
      stop->setVisible(true);
      break;
    }
    case SELECTED: {
      // Change colors
      setStyleSheet(
          "#FailureBannerWidget { background-color: #cfe2ff }"
          "#FailureBannerWidget QLabel { color: #084298 }");
      // Hide spinner
      spinner->setVisible(false);
      spinner->stop();
      // Change text
      label->setText(QString("Failure %1 est sélectionnée")
                         .arg(QString::fromStdString(selected->name)));
      // Show start
      start->setVisible(true);
      stop->setVisible(false);
      break;
    }
    case DEFAULT: {
      // Change colors
      setStyleSheet(
          "#FailureBannerWidget { background-color: #e2e3e5 }"
          "#FailureBannerWidget QLabel { color: #41464b }");
      // Hide spinner
      spinner->setVisible(false);
      spinner->stop();
      // Change text
      label->setText("Aucune failure n'est sélectionnée...");
      // Hide start stop
      start->setVisible(false);
      stop->setVisible(false);
      break;
    }
  }
}

const failures::Failure* FailureBannerWidget::getSelected() {
  return selected;
}

void FailureBannerWidget::setEnabled(bool value) {
  start->setEnabled(value);
}

}  // namespace graphics
}  // namespace jbox
