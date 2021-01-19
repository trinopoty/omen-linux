#include "MacroRecordDialog.h"

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

/* InputReadThread */

InputReadThread::InputReadThread(QObject *parent): QThread(parent), mShouldQuit(false) {
}

void InputReadThread::setDevicePath(QString &devicePath) {
    mInputDevice = devicePath;
}

void InputReadThread::stopListening() {
    mShouldQuit = true;
}

void InputReadThread::run() {
    memset(&mInputEvents[0], 0, sizeof(struct input_event) * EVENTS_BUFFER_SIZE);
    memset(&mEvents[0], 0, sizeof(InputEvent) * EVENTS_BUFFER_SIZE);

    mShouldQuit = false;

    const int fd = open(mInputDevice.toStdString().c_str(), O_RDONLY);
    if (fd > 0) {
        while (!mShouldQuit) {
            const int rd = read(fd, &mInputEvents[0], sizeof(struct input_event) * EVENTS_BUFFER_SIZE);
            if (rd < sizeof(struct input_event)) {
                // Unrecoverable error
                break;
            }

            const int readCount = rd / (int) sizeof(struct input_event);
            int eventCount = 0;

            memset(&mEvents[0], 0, sizeof(InputEvent) * readCount);

            for (int i = 0; i < readCount; i++) {
                if (mInputEvents[i].type == EV_KEY && mInputEvents[i].value != 2) {
                    mEvents[eventCount].key = mInputEvents[i].code;
                    mEvents[eventCount].isBreak = mInputEvents[i].value == 0;
                    mEvents[eventCount].timestamp = (mInputEvents[i].time.tv_sec * 1000) + mInputEvents[i].time.tv_usec;
                    eventCount += 1;
                }
            }

            if (eventCount > 0 && !mShouldQuit) {
                emit eventsReceived(eventCount, mEvents);
            }
        }

        close(fd);
    }
}

/* MacroRecordDialog */

MacroRecordDialog::MacroRecordDialog(): mRecording(false), mInputDeviceFound(false), mInputDevicePath(""),
        mInputReadThread(this) {
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
    mCancelButton = new QPushButton(tr("Cancel"));
    mRecordButton = new QPushButton(tr("Record"));

    layout->addWidget(mCancelButton, 4, 0, 1, 1);
    layout->addWidget(mRecordButton, 4, 1, 1, 1);
    layout->addWidget(mOkButton, 4, 2, 1, 1);

    connect(mRecordButton, &QAbstractButton::clicked, this, &MacroRecordDialog::handleRecordButtonClick);
    connect(&mInputReadThread, &InputReadThread::eventsReceived, this, &MacroRecordDialog::handleEventsReceived);
}

bool MacroRecordDialog::event(QEvent *event) {
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        event->accept();
        return true;
    } else {
        return QDialog::event(event);
    }
}

void MacroRecordDialog::handleRecordButtonClick(bool) {
    if (!mInputDeviceFound && !findInputDevice()) {
        mErrorMessage->showMessage(tr("Unable to locate input device."));
    } else {
        if (mRecording) {
            mRecording = false;
            mRecordButton->setText(tr("Record"));
            mInputReadThread.stopListening();
        } else {
            mRecording = true;
            mRecordButton->setText(tr("Stop Recording"));
            mInputReadThread.setDevicePath(mInputDevicePath);
            mInputReadThread.start();
        }
    }
}

void MacroRecordDialog::handleEventsReceived(int count, InputEvent *events) {
    for (int i = 0; i < count; i++) {
        auto it = keys.find(events[i].key);
        if (it != keys.end()) {
            // Valid key detected
            auto key = it->second;
            auto event = events[i];

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
