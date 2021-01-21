#ifndef OMENLINUX_MACRORECORDDIALOG_H
#define OMENLINUX_MACRORECORDDIALOG_H

#include <aio.h>
#include <linux/input.h>

#include <QDialog>
#include <QErrorMessage>
#include <QTableWidget>
#include <QPushButton>
#include <QList>

const int EVENTS_BUFFER_SIZE = 64;

typedef struct {
    uint32_t key;
    bool isBreak;
    uint64_t timestamp;
} InputEvent;

class MacroRecordDialog: public QDialog {
Q_OBJECT

public:
    explicit MacroRecordDialog(QWidget*);
    ~MacroRecordDialog() noexcept override;

protected:
    bool event(QEvent *) override;
    void showEvent(QShowEvent *) override;

public slots:
    void handleOkButtonClick(bool);
    void handleCancelButtonClick(bool);
    void handleRecordButtonClick(bool);

signals:
    void resultAvailable(bool macroRecorded, QList<InputEvent*> &recordedKeys);

private:
    bool findInputDevice();
    bool startRecordingInput();
    void stopRecordingInput();
    void clearRecordedKeys();
    void handleEventsReceived(int count);

    static void inputReadCallback(union sigval value);

private:
    QTableWidget *mRecordedKeysList;
    QPushButton *mRecordButton;
    QPushButton *mOkButton;
    QPushButton *mCancelButton;

    QErrorMessage *mErrorMessage;

    bool mRecording;
    bool mInputDeviceFound;
    QString mInputDevicePath;
    QList<InputEvent*> mRecordedKeys;

    struct aiocb mInputEventAio;
    struct input_event mInputEventsRaw[EVENTS_BUFFER_SIZE];
    InputEvent mInputEvents[EVENTS_BUFFER_SIZE];
};


#endif //OMENLINUX_MACRORECORDDIALOG_H
