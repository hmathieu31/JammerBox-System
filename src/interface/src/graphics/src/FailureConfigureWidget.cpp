#include "FailureConfigureWidget.h"

namespace jbox {
namespace graphics {

FailureConfigureWidget::FailureConfigureWidget(QWidget* parent)
    : QDockWidget(tr("Configurer"), parent) {
  setFeatures(QDockWidget::NoDockWidgetFeatures);

  QWidget* widget = new QWidget();
  QVBoxLayout* vlayout = new QVBoxLayout();
  vlayout->addSpacing(10);
  // Affiché lorsque la fenêtre est ouverte mais qu'aucune failure n'est
  // sélectionnée
  notSelectedLabel = new QLabel(tr("Aucune failure n'est sélectionnée"));
  notSelectedLabel->setVisible(false);
  vlayout->addWidget(notSelectedLabel);
  // Affiché lorsque la fenêtre est ouverte mais que la failure sélectionnée n'a
  // pas de paramètres
  noParamsLabel =
      new QLabel(tr("La failure sélectionnée n'est pas configurable"));
  noParamsLabel->setVisible(false);
  vlayout->addWidget(noParamsLabel);

  box = new QGroupBox();
  box->setVisible(false);
  layout = new QFormLayout();
  layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
  box->setLayout(layout);
  vlayout->addWidget(box);

  vlayout->addSpacing(20);
  vlayout->addStretch(1);

  widget->setLayout(vlayout);
  setWidget(widget);
}

void FailureConfigureWidget::setFailure(const failures::Failure* failure) {
  this->failure = failure;

  clear();

  if (failure == nullptr) {
    // On cache le widget
    notSelectedLabel->setVisible(true);
    noParamsLabel->setVisible(false);
    box->setVisible(false);
    return;
  }

  notSelectedLabel->setVisible(false);

  // On affiche seulement un label si il n'y a pas de params
  if (failure->type.type == failures::CAM){
    box->setVisible(true);
  }else {
    noParamsLabel->setVisible(failure->params.empty());
    box->setVisible(!failure->params.empty());
  }

  box->setTitle(QString::fromStdString(failure->name));

  std::vector<failures::FailureParam>::const_iterator it =
      failure->params.cbegin();
  if (failure->type.type == failures::CAM) {
    camChoice = new QSpinBox();
    camChoice->setRange(0,1);
    fields.push_back(camChoice);
    layout->addRow("CAM", camChoice);
  }
  while (it != failure->params.cend()) {
    QWidget* field;
    switch (it->value.type) {
      case failures::INT: {
        field = new QSpinBox();
        break;
      }
      case failures::FLOAT: {
        field = new QDoubleSpinBox();
        break;
      }
      case failures::CHAR: {
        QLineEdit* lineEdit = new QLineEdit();
        lineEdit->setMaxLength(1);
        field = lineEdit;
        break;
      }
      default: {
        field = new QLineEdit();
        break;
      }
    }
    fields.push_back(field);

    layout->addRow(QString::fromStdString(it->name), field);
    it++;
  }
}

std::vector<jbox::failures::ParamData> FailureConfigureWidget::getParams() {
  std::vector<jbox::failures::ParamData> params;
  if (failure == nullptr) {
    return params;
  }

  QSpinBox* spinBox;
  QDoubleSpinBox* doubleSpinBox;
  QLineEdit* lineEdit;
  for (size_t i = 0; i < failure->params.size(); i++) {
    switch (failure->params[i].value.type) {
      case failures::INT: {
        spinBox = dynamic_cast<QSpinBox*>(fields[i]);
        params.push_back(jbox::failures::ParamData(spinBox->value()));
        break;
      }
      case failures::FLOAT: {
        doubleSpinBox = dynamic_cast<QDoubleSpinBox*>(fields[i]);
        params.push_back(
            jbox::failures::ParamData((float)(doubleSpinBox->value())));
        break;
      }
      case failures::CHAR: {
        lineEdit = dynamic_cast<QLineEdit*>(fields[i]);
        params.push_back(
            jbox::failures::ParamData(lineEdit->text().data()[0].toLatin1()));
        break;
      }
      default:
        break;
    }
  }

  return params;
}

int FailureConfigureWidget::getCamChoice(){
  return camChoice->value() ;

}

void FailureConfigureWidget::clear() {
  if (layout != nullptr) {
    // On supprime l'ancien layout
    for (int i = 0; i < layout->count(); i++) {
      QWidget* w = layout->itemAt(i)->widget();
      layout->removeWidget(w);
      delete w;
    }

    for (auto f : fields) {
      delete f;
    }
    fields.clear();
  }
}

}  // namespace graphics
}  // namespace jbox
