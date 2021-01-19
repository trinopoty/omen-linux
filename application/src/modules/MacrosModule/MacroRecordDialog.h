#ifndef OMENLINUX_MACRORECORDDIALOG_H
#define OMENLINUX_MACRORECORDDIALOG_H

#include <linux/input.h>

#include <QDialog>
#include <QErrorMessage>
#include <QTableWidget>
#include <QPushButton>
#include <QList>
#include <QThread>

#ifndef EV_SYN
#define EV_SYN 0
#endif

const int EVENTS_BUFFER_SIZE = 64;

typedef struct {
    uint32_t key;
    bool isBreak;
    uint64_t timestamp;
} InputEvent;

class InputReadThread: public QThread {
Q_OBJECT

public:
    InputReadThread(QObject *parent);
    ~InputReadThread() override = default;

    void setDevicePath(QString &devicePath);
    void stopListening();

    void run() override;

signals:
    void eventsReceived(int count, InputEvent* events);

private:
    QString mInputDevice;
    bool mShouldQuit;
    struct input_event mInputEvents[EVENTS_BUFFER_SIZE];
    InputEvent mEvents[EVENTS_BUFFER_SIZE];
};

class MacroRecordDialog: public QDialog {
Q_OBJECT

public:
    MacroRecordDialog();
    ~MacroRecordDialog() override = default;

protected:
    bool event(QEvent *) override;

public slots:
    void handleRecordButtonClick(bool);
    void handleEventsReceived(int count, InputEvent* events);

private:
    bool findInputDevice();

private:
    QTableWidget *mRecordedKeysList;
    QPushButton *mRecordButton;
    QPushButton *mOkButton;
    QPushButton *mCancelButton;

    QErrorMessage *mErrorMessage;

    bool mRecording;
    bool mInputDeviceFound;
    QString mInputDevicePath;
    InputReadThread mInputReadThread;
    QList<InputEvent*> mRecordedKeys;
};


#endif //OMENLINUX_MACRORECORDDIALOG_H
