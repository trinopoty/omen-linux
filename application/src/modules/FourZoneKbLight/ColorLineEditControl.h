#ifndef OMENLINUX_COLORLINEEDITCONTROL_H
#define OMENLINUX_COLORLINEEDITCONTROL_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QColorDialog>

class ColorLineEditControl: public QWidget {
Q_OBJECT

public:
    ColorLineEditControl();
    ~ColorLineEditControl() override = default;

    void setColor(unsigned int color);

signals:
    void colorChanged(unsigned int color);

public slots:
    void selectButtonClick(bool checked);
    void colorSelected(const QColor &color);

private:
    QLineEdit* mEditBox;
    QPushButton* mSelectButton;
    QColorDialog* mColorDialog;

    unsigned int mColor;
};


#endif //OMENLINUX_COLORLINEEDITCONTROL_H
