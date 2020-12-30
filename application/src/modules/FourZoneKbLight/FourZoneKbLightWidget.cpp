#include <QFormLayout>
#include <QLabel>
#include <QButtonGroup>

#include "FourZoneKbLightWidget.h"

FourZoneKbLightWidget::FourZoneKbLightWidget(rapidjson::Value &configuration):
        mLightOn(false), mZone1Color(0), mZone2Color(0), mZone3Color(0), mZone4Color(0) {
    auto layout = new QFormLayout(this);
    setLayout(layout);

    auto onOffGroupPanel = new QWidget(this);
    auto onOffGroupLayout = new QHBoxLayout();
    onOffGroupPanel->setLayout(onOffGroupLayout);

    mOnButton = new QRadioButton(QString("On"), onOffGroupPanel);
    onOffGroupLayout->addWidget(mOnButton);
    mOffButton = new QRadioButton(QString("Off"), onOffGroupPanel);
    onOffGroupLayout->addWidget(mOffButton);
    onOffGroupLayout->addStretch(1);

    mOnOffGroup = new QButtonGroup();
    mOnOffGroup->addButton(mOnButton, KB_LIGHT_ON);
    mOnOffGroup->addButton(mOffButton, KB_LIGHT_OFF);
    layout->addRow(new QLabel(QString("State")), onOffGroupPanel);

    mZone1ColorEdit = new ColorLineEditControl();
    layout->addRow(new QLabel(tr("Zone 1")), mZone1ColorEdit);

    mZone2ColorEdit = new ColorLineEditControl();
    layout->addRow(new QLabel(tr("Zone 2")), mZone2ColorEdit);

    mZone3ColorEdit = new ColorLineEditControl();
    layout->addRow(new QLabel(tr("Zone 3")), mZone3ColorEdit);

    mZone4ColorEdit = new ColorLineEditControl();
    layout->addRow(new QLabel(tr("Zone 4")), mZone4ColorEdit);

    initializeState();

    connect(mOnOffGroup, &QButtonGroup::idToggled, this, &FourZoneKbLightWidget::onOnOffChanged);
    connect(mZone1ColorEdit, &ColorLineEditControl::colorChanged, this, &FourZoneKbLightWidget::onZone1ColorChanged);
    connect(mZone2ColorEdit, &ColorLineEditControl::colorChanged, this, &FourZoneKbLightWidget::onZone2ColorChanged);
    connect(mZone3ColorEdit, &ColorLineEditControl::colorChanged, this, &FourZoneKbLightWidget::onZone3ColorChanged);
    connect(mZone4ColorEdit, &ColorLineEditControl::colorChanged, this, &FourZoneKbLightWidget::onZone4ColorChanged);

    // Load and apply configuration
    if (configuration.HasMember("on") && configuration["on"].IsBool()) {
        mLightOn = configuration["on"].GetBool();
    }
    if (configuration.HasMember("zone1") && configuration["zone1"].IsInt()) {
        mZone1Color = configuration["zone1"].GetInt();
    }
    if (configuration.HasMember("zone2") && configuration["zone2"].IsInt()) {
        mZone2Color = configuration["zone2"].GetInt();
    }
    if (configuration.HasMember("zone3") && configuration["zone3"].IsInt()) {
        mZone3Color = configuration["zone3"].GetInt();
    }
    if (configuration.HasMember("zone4") && configuration["zone4"].IsInt()) {
        mZone4Color = configuration["zone4"].GetInt();
    }

    updateOnOffControls();
    updateColorControls();
    applyState(false);
}

rapidjson::Value FourZoneKbLightWidget::SaveConfiguration(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    auto result = rapidjson::Value(rapidjson::kObjectType);
    result.AddMember("on", rapidjson::Value(mLightOn), allocator);
    result.AddMember("zone1", rapidjson::Value(mZone1Color), allocator);
    result.AddMember("zone2", rapidjson::Value(mZone2Color), allocator);
    result.AddMember("zone3", rapidjson::Value(mZone3Color), allocator);
    result.AddMember("zone4", rapidjson::Value(mZone4Color), allocator);
    return result;
}

void FourZoneKbLightWidget::onOnOffChanged(int id, bool checked) {
    auto state = (id == KB_LIGHT_ON && checked)? KB_LIGHT_ON : KB_LIGHT_OFF;
    mLightOn = (state == KB_LIGHT_ON);
    applyState(true);
}

void FourZoneKbLightWidget::onZone1ColorChanged(unsigned int color) {
    mZone1Color = color;
    applyState(true);
}

void FourZoneKbLightWidget::onZone2ColorChanged(unsigned int color) {
    mZone2Color = color;
    applyState(true);
}

void FourZoneKbLightWidget::onZone3ColorChanged(unsigned int color) {
    mZone3Color = color;
    applyState(true);
}

void FourZoneKbLightWidget::onZone4ColorChanged(unsigned int color) {
    mZone4Color = color;
    applyState(true);
}

void FourZoneKbLightWidget::initializeState() {
    auto state = KB_LIGHT_OFF;
    FourZoneKbLightDriver::DriverGetOnOff(&state);
    FourZoneKbLightDriver::DriverGetColors(&mZone1Color, &mZone2Color, &mZone3Color, &mZone4Color);

    mLightOn = (state == KB_LIGHT_ON);

    updateOnOffControls();
    updateColorControls();
}

void FourZoneKbLightWidget::updateOnOffControls() {
    auto state = mLightOn? KB_LIGHT_ON : KB_LIGHT_OFF;
    mOnButton->setChecked(state == KB_LIGHT_ON);
    mOffButton->setChecked(state == KB_LIGHT_OFF);
}

void FourZoneKbLightWidget::updateColorControls() {
    unsigned int colors[] = {mZone1Color, mZone2Color, mZone3Color, mZone4Color};
    ColorLineEditControl* textControls[] = {mZone1ColorEdit, mZone2ColorEdit, mZone3ColorEdit, mZone4ColorEdit};

    for (int i = 0; i < 4; ++i) {
        textControls[i]->setColor(colors[i]);
    }
}

void FourZoneKbLightWidget::applyState(bool publishEvent) {
    FourZoneKbLightDriver::DriverSetColors(mZone1Color, mZone2Color, mZone3Color, mZone4Color);
    FourZoneKbLightDriver::DriverSetOnOff(mLightOn? KB_LIGHT_ON : KB_LIGHT_OFF);

    if (publishEvent) {
        ConfigurationChanged();
    }
}
