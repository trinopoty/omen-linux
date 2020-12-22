#include <QFormLayout>
#include <QLabel>
#include <QButtonGroup>

#include "FourZoneKbLightWidget.h"

FourZoneKbLightWidget::FourZoneKbLightWidget(): mDriver() {
    mDriver.DriverDetect();

    auto layout = new QFormLayout(this);
    this->setLayout(layout);

    auto onOffGroupPanel = new QWidget(this);
    auto onOffGroupLayout = new QHBoxLayout();
    onOffGroupPanel->setLayout(onOffGroupLayout);

    this->mOnButton = new QRadioButton(QString("On"), onOffGroupPanel);
    onOffGroupLayout->addWidget(this->mOnButton);
    this->mOffButton = new QRadioButton(QString("Off"), onOffGroupPanel);
    onOffGroupLayout->addWidget(this->mOffButton);
    onOffGroupLayout->addStretch(1);

    this->mOnOffGroup = new QButtonGroup();
    this->mOnOffGroup->addButton(this->mOnButton, KB_LIGHT_ON);
    this->mOnOffGroup->addButton(this->mOffButton, KB_LIGHT_OFF);
    layout->addRow(new QLabel(QString("State")), onOffGroupPanel);

    this->initializeState();

    connect(this->mOnOffGroup, &QButtonGroup::idToggled, this, &FourZoneKbLightWidget::onOnOffChanged);
}

FourZoneKbLightWidget::~FourZoneKbLightWidget() {
}

void FourZoneKbLightWidget::onOnOffChanged(int id, bool checked) {
    auto state = (id == KB_LIGHT_ON && checked)? KB_LIGHT_ON : KB_LIGHT_OFF;
    this->mDriver.DriverSetOnOff(state);
}

void FourZoneKbLightWidget::initializeState() {
    auto state = KB_LIGHT_OFF;
    this->mDriver.DriverGetOnOff(&state);
    this->mOnButton->setChecked(state == KB_LIGHT_ON);
    this->mOffButton->setChecked(state == KB_LIGHT_OFF);
}
