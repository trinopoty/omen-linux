#include <QFormLayout>
#include <QLabel>
#include <QButtonGroup>

#include "FourZoneKbLightWidget.h"

FourZoneKbLightWidget::FourZoneKbLightWidget(): mDriver(),
        mZone1Color(0), mZone2Color(0), mZone3Color(0), mZone4Color(0) {
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

    this->mZone1ColorEdit = new ColorLineEditControl();
    layout->addRow(new QLabel(tr("Zone 1")), this->mZone1ColorEdit);

    this->mZone2ColorEdit = new ColorLineEditControl();
    layout->addRow(new QLabel(tr("Zone 2")), this->mZone2ColorEdit);

    this->mZone3ColorEdit = new ColorLineEditControl();
    layout->addRow(new QLabel(tr("Zone 3")), this->mZone3ColorEdit);

    this->mZone4ColorEdit = new ColorLineEditControl();
    layout->addRow(new QLabel(tr("Zone 4")), this->mZone4ColorEdit);

    this->initializeState();

    connect(this->mOnOffGroup, &QButtonGroup::idToggled, this, &FourZoneKbLightWidget::onOnOffChanged);
    connect(this->mZone1ColorEdit, &ColorLineEditControl::colorChanged, this, &FourZoneKbLightWidget::onZone1ColorChanged);
    connect(this->mZone2ColorEdit, &ColorLineEditControl::colorChanged, this, &FourZoneKbLightWidget::onZone2ColorChanged);
    connect(this->mZone3ColorEdit, &ColorLineEditControl::colorChanged, this, &FourZoneKbLightWidget::onZone3ColorChanged);
    connect(this->mZone4ColorEdit, &ColorLineEditControl::colorChanged, this, &FourZoneKbLightWidget::onZone4ColorChanged);
}

void FourZoneKbLightWidget::onOnOffChanged(int id, bool checked) {
    auto state = (id == KB_LIGHT_ON && checked)? KB_LIGHT_ON : KB_LIGHT_OFF;
    this->applyState(state);
}

void FourZoneKbLightWidget::onZone1ColorChanged(unsigned int color) {
    mZone1Color = color;
    this->mDriver.DriverSetColors(this->mZone1Color, this->mZone2Color, this->mZone3Color, this->mZone4Color);
}

void FourZoneKbLightWidget::onZone2ColorChanged(unsigned int color) {
    mZone2Color = color;
    this->mDriver.DriverSetColors(this->mZone1Color, this->mZone2Color, this->mZone3Color, this->mZone4Color);
}

void FourZoneKbLightWidget::onZone3ColorChanged(unsigned int color) {
    mZone3Color = color;
    this->mDriver.DriverSetColors(this->mZone1Color, this->mZone2Color, this->mZone3Color, this->mZone4Color);
}

void FourZoneKbLightWidget::onZone4ColorChanged(unsigned int color) {
    mZone4Color = color;
    this->mDriver.DriverSetColors(this->mZone1Color, this->mZone2Color, this->mZone3Color, this->mZone4Color);
}

void FourZoneKbLightWidget::initializeState() {
    auto state = KB_LIGHT_OFF;
    this->mDriver.DriverGetOnOff(&state);
    this->mOnButton->setChecked(state == KB_LIGHT_ON);
    this->mOffButton->setChecked(state == KB_LIGHT_OFF);

    this->mDriver.DriverGetColors(&this->mZone1Color, &this->mZone2Color, &this->mZone3Color, &this->mZone4Color);
    this->updateColorControls();
}

void FourZoneKbLightWidget::updateColorControls() {
    unsigned int colors[] = {this->mZone1Color, this->mZone2Color, this->mZone3Color, this->mZone4Color};
    ColorLineEditControl* textControls[] = {this->mZone1ColorEdit, this->mZone2ColorEdit, this->mZone3ColorEdit, this->mZone4ColorEdit};

    for (int i = 0; i < 4; ++i) {
        textControls[i]->setColor(colors[i]);
    }
}

void FourZoneKbLightWidget::applyState(FourZoneKbLightState state) {
    this->mDriver.DriverSetColors(this->mZone1Color, this->mZone2Color, this->mZone3Color, this->mZone4Color);
    this->mDriver.DriverSetOnOff(state);
}
