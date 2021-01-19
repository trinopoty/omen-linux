#include "MacrosWidget.h"

#include <iostream>
#include <QVBoxLayout>
#include <QPushButton>

#include "MacroRecordDialog.h"

MacrosWidget::MacrosWidget() {
    auto layout = new QVBoxLayout();
    setLayout(layout);

    auto button = new QPushButton(tr("Click Me"));
    layout->addWidget(button);

    connect(button, &QAbstractButton::clicked, this, &MacrosWidget::handleClick);
}

void MacrosWidget::handleClick(bool checked) {
    auto wnd = new MacroRecordDialog();
    wnd->show();
}
