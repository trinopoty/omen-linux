#include "MacroRecordDialog.h"

#include <csignal>
#include <memory>
#include <string>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include <QEvent>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "KeyInfo.h"

/* MacroRecordDialog */

MacroRecordDialog::MacroRecordDialog(QWidget* parent): QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint),
                                                       mRecording(false), mInputDeviceFound(false), mInputDevicePath(""),
                                                       mInputEventAio({0}), mInputEventsRaw(), mInputEvents() {
    setWindowTitle(tr("Edit Macro"));
    setFixedSize(450, 250);

    mErrorMessage = new QErrorMessage(this);

    auto layout = new QGridLayout();
    setLayout(layout);

    layout->addWidget(new QLabel(tr("Recorded keys:")), 0, 0, 1, 3);

    mRecordedKeysList = new QTableWidget(0, 3);
    mRecordedKeysList->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Key")));
    mRecordedKeysList->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Type")));
    mRecordedKeysList->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Delay (ms)")));
    layout->addWidget(mRecordedKeysList, 1, 0, 3, 3);

    mOkButton = new QPushButton(tr("OK"));
    mOkButton->setEnabled(false);

    mCancelButton = new QPushButton(tr("Cancel"));
    mRecordButton = new QPushButton(tr("Record"));

    layout->addWidget(mOkButton, 4, 2, 1, 1);
    layout->addWidget(mCancelButton, 4, 0, 1, 1);
    layout->addWidget(mRecordButton, 4, 1, 1, 1);

    connect(mOkButton, &QAbstractButton::clicked, this, &MacroRecordDialog::handleOkButtonClick);
    connect(mCancelButton, &QAbstractButton::clicked, this, &MacroRecordDialog::handleCancelButtonClick);
    connect(mRecordButton, &QAbstractButton::clicked, this, &MacroRecordDialog::handleRecordButtonClick);
}

MacroRecordDialog::~MacroRecordDialog() noexcept = default;

bool MacroRecordDialog::event(QEvent *event) {
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        event->accept();
        return true;
    } else {
        return QDialog::event(event);
    }
}

void MacroRecordDialog::showEvent(QShowEvent *) {
    clearRecordedKeys();
}

void MacroRecordDialog::handleOkButtonClick(bool) {
    resultAvailable(true, mRecordedKeys);
    clearRecordedKeys();
    close();
}

void MacroRecordDialog::handleCancelButtonClick(bool) {
    if (mRecording) {
        handleRecordButtonClick(false);
    }
    resultAvailable(false, mRecordedKeys);
    clearRecordedKeys();
    close();
}

void MacroRecordDialog::handleRecordButtonClick(bool) {
    if (!mInputDeviceFound && !findInputDevice()) {
        mErrorMessage->showMessage(tr("Unable to locate input device."));
    } else {
        if (mRecording) {
            mRecording = false;
            mOkButton->setEnabled(!mRecordedKeys.empty());
            mRecordButton->setText(tr("Record"));
            stopRecordingInput();
        } else {
            mRecording = true;
            mOkButton->setEnabled(false);
            mRecordButton->setText(tr("Stop Recording"));
            startRecordingInput();
        }
    }
}

/**
 * Try to find the laptop's keyboard.
 *
 * @return Value indicating success or failure.
 */
bool MacroRecordDialog::findInputDevice() {
    std::string sysInputDir("/sys/class/input");
    bool result = false;
    DIR *dirp;

    do {
        dirp = opendir("/sys/class/input");
        if (dirp == nullptr)
            break;

        bool foundInput = false;
        struct dirent *entry;
        std::unique_ptr<char[]> buffer(new char[256]);

        while ((entry = readdir(dirp)) != nullptr) {
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                continue;

            if (foundInput) {
                if (strncmp("event", entry->d_name, strlen("event")) != 0)
                    continue;

                // Take first event
                std::string devicePath("/dev/input/");
                devicePath.append(entry->d_name);

                mInputDeviceFound = true;
                mInputDevicePath = QString(strdup(devicePath.c_str()));
                result = true;
                break;
            } else {
                if (strncmp("input", entry->d_name, strlen("input")) != 0)
                    continue;

                std::string inputPath(sysInputDir);
                inputPath.append("/");
                inputPath.append(entry->d_name);

                std::string nameFilePath(inputPath);
                nameFilePath.append("/name");

                const int fd = ::open(nameFilePath.c_str(), O_RDONLY);

                if (fd > 0) {
                    if (read(fd, buffer.get(), 256) >= 0) {
                        if (strncmp("AT Translated Set 2 keyboard", buffer.get(),
                                    strlen("AT Translated Set 2 keyboard")) == 0) {
                            foundInput = true;
                        }
                    }

                    ::close(fd);
                }

                if (foundInput) {
                    closedir(dirp);
                    dirp = opendir(inputPath.c_str());
                }
            }
        }
    } while (false);

    if (dirp != nullptr) {
        closedir(dirp);
    }

    return result;
}

bool MacroRecordDialog::startRecordingInput() {
    memset(&mInputEventAio, 0, sizeof(struct aiocb));
    memset(&mInputEventsRaw, 0, sizeof(struct input_event) * EVENTS_BUFFER_SIZE);

    const int fd = ::open(mInputDevicePath.toStdString().c_str(), O_RDONLY);
    if (fd > 0) {
        mInputEventAio.aio_fildes = fd;
        mInputEventAio.aio_offset = 0;
        mInputEventAio.aio_buf = mInputEventsRaw;
        mInputEventAio.aio_nbytes = sizeof(struct input_event) * EVENTS_BUFFER_SIZE;
        mInputEventAio.aio_sigevent.sigev_notify = SIGEV_THREAD;
        mInputEventAio.aio_sigevent.sigev_value.sival_ptr = this;
        mInputEventAio.aio_sigevent._sigev_un._sigev_thread._function = &MacroRecordDialog::inputReadCallback;

        const int result = aio_read(&mInputEventAio);
        if (result != 0) {
            ::close(fd);
        }

        return (result == 0);
    } else {
        return false;
    }
}

void MacroRecordDialog::stopRecordingInput() {
    aio_cancel(mInputEventAio.aio_fildes, &mInputEventAio);
    ::close(mInputEventAio.aio_fildes);
}

void MacroRecordDialog::clearRecordedKeys() {
    for (auto & item : mRecordedKeys) {
        delete item;
    }
    mRecordedKeys.clear();
}

void MacroRecordDialog::handleEventsReceived(int count) {
    for (int i = 0; i < count; i++) {
        auto event = mInputEvents[i];
        auto it = keys.find(event.key);
        if (it != keys.end()) {
            // Valid key detected
            auto key = it->second;

            QString delayText(mRecordedKeys.empty()? "-" : "%1");
            if (!mRecordedKeys.empty()) {
                delayText = delayText.arg(event.timestamp - mRecordedKeys.last()->timestamp);
            }

            auto row = mRecordedKeysList->rowCount();
            mRecordedKeysList->setRowCount(row + 1);
            mRecordedKeysList->setItem(row, 0, new QTableWidgetItem(QString(key.label)));
            mRecordedKeysList->setItem(row, 1, new QTableWidgetItem(QString(event.isBreak? "Release" : "Press")));
            mRecordedKeysList->setItem(row, 2, new QTableWidgetItem(delayText));

            auto item = new InputEvent();
            memcpy(item, &event, sizeof(InputEvent));
            mRecordedKeys.append(item);
        }
    }
}

void MacroRecordDialog::inputReadCallback(union sigval value) {
    auto dialog = reinterpret_cast<MacroRecordDialog*>(value.sival_ptr);
    const int result = aio_return(&dialog->mInputEventAio);
    if (result > sizeof(struct input_event)) {
        const int readCount = result / (int) sizeof(struct input_event);
        int eventCount = 0;
        for (int i = 0; i < readCount; i++) {
            if (dialog->mInputEventsRaw[i].type == EV_KEY && dialog->mInputEventsRaw[i].value != 2) {
                dialog->mInputEvents[eventCount].key = dialog->mInputEventsRaw[i].code;
                dialog->mInputEvents[eventCount].isBreak = dialog->mInputEventsRaw[i].value == 0;
                dialog->mInputEvents[eventCount].timestamp = (dialog->mInputEventsRaw[i].time.tv_sec * 1000) + (dialog->mInputEventsRaw[i].time.tv_usec / 1000);
                eventCount += 1;
            }
        }

        dialog->handleEventsReceived(readCount);

        dialog->mInputEventAio.aio_offset = 0;
        dialog->mInputEventAio.aio_buf = dialog->mInputEventsRaw;
        dialog->mInputEventAio.aio_nbytes = sizeof(struct input_event) * EVENTS_BUFFER_SIZE;
        aio_read(&dialog->mInputEventAio);
    }
}
