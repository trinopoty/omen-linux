#include <iomanip>
#include <sstream>

#include <QHBoxLayout>

#include "ColorLineEditControl.h"

ColorLineEditControl::ColorLineEditControl(): mColor(0) {
    auto layout = new QHBoxLayout();
    this->setLayout(layout);

    this->mEditBox = new QLineEdit();
    this->mEditBox->setDisabled(true);
    layout->addWidget(this->mEditBox, 1);

    this->mSelectButton = new QPushButton(QString("..."));
    layout->addWidget(this->mSelectButton);

    this->mColorDialog = new QColorDialog(this);

    connect(this->mSelectButton, &QPushButton::clicked, this, &ColorLineEditControl::selectButtonClick);
    connect(this->mColorDialog, &QColorDialog::colorSelected, this, &ColorLineEditControl::colorSelected);
}

void ColorLineEditControl::selectButtonClick(bool checked) {
    this->mColorDialog->setCurrentColor(QColor(this->mColor));
    this->mColorDialog->show();
}

void ColorLineEditControl::colorSelected(const QColor &color) {
    unsigned int colorInt = color.rgb() & 0x00ffffff;
    this->setColor(colorInt);
    this->colorChanged(colorInt);
}

void ColorLineEditControl::setColor(unsigned int color) {
    this->mColor = color;

    std::ostringstream stream;
    stream << "0x"
           << std::setfill ('0') << std::setw(sizeof(unsigned int)*2)
           << std::hex << this->mColor;
    this->mEditBox->setText(QString(stream.str().c_str()));
}
