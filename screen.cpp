




#include "screen.h"
#include <QApplication>
#include <QPalette>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QLabel>
#include <QVBoxLayout>
#include <iostream>

// Constructor
ScreenManager::ScreenManager(QWidget *parent)
    : QWidget(parent),
      timer(new QTimer(this)),
      countdownTimer(new QTimer(this)),
      countdownLabel(new QLabel(this)),
      trayIcon(new QSystemTrayIcon(this)),
      toggleLongBreakAction(new QAction("Disable Long Breaks", this)),
      resetBreaksAction(new QAction("Reset Breaks", this)),
      pauseBreaksAction(new QAction("Pause Breaks", this)),
      remainingTime(visibleDurationMs / 1000)
{
    // Set window properties
    resize(400, 200);
    setWindowFlags(Qt::Window |
                   Qt::CustomizeWindowHint |
                   Qt::WindowStaysOnTopHint |
                   Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setMinimumSize(400, 200);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::black);
    setPalette(palette);
    setAutoFillBackground(true);

    // Setup countdown label
    countdownLabel->setAlignment(Qt::AlignCenter);
    QFont font = countdownLabel->font();
    font.setPointSize(48);
    countdownLabel->setFont(font);
    countdownLabel->setStyleSheet("QLabel { color : grey; }");
    countdownLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    countdownLabel->setMinimumSize(200, 100);
    countdownLabel->setWordWrap(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(countdownLabel);
    setLayout(layout);

    // Setup system tray menu
    QMenu* trayMenu = new QMenu(this);

    // Pause Breaks
    connect(pauseBreaksAction, &QAction::triggered, this, &ScreenManager::pauseBreaks);
    trayMenu->addAction(pauseBreaksAction);

    // Toggle Long Breaks
    connect(toggleLongBreakAction, &QAction::triggered, this, &ScreenManager::toggleLongBreaks);
    trayMenu->addAction(toggleLongBreakAction);

    // Reset Breaks
    connect(resetBreaksAction, &QAction::triggered, this, &ScreenManager::resetBreaks);
    trayMenu->addAction(resetBreaksAction);

    // Quit Action
    QAction* quitAction = new QAction("Quit", this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    trayMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->setIcon(QIcon::fromTheme("system-run"));
    trayIcon->setToolTip("Screen Manager App");
    trayIcon->show();

    // Timer connections
    connect(timer, &QTimer::timeout, this, &ScreenManager::toggleVisibility);
    connect(countdownTimer, &QTimer::timeout, this, &ScreenManager::updateCountdown);

    timer->start(intervalMs);
}

// Destructor
ScreenManager::~ScreenManager() {}

// Toggle visibility
void ScreenManager::toggleVisibility() {
    if (breaksPaused) {
        // std::cout << "Breaks are paused. Skipping break." << std::endl;
        return;
    }

    intervalCount++;

    if (intervalCount % 3 == 0 && longBreaksEnabled) {
        remainingTime = extendedDurationMs / 1000;
    } else {
        remainingTime = visibleDurationMs / 1000;
    }

    countdownLabel->setText(QString::number(remainingTime));
    showFullScreen();
    countdownTimer->start(1000);

    QTimer::singleShot((intervalCount % 3 == 0 && longBreaksEnabled) ? extendedDurationMs : visibleDurationMs, this, &ScreenManager::hide);
}

// Update countdown
void ScreenManager::updateCountdown() {
    remainingTime--;
    countdownLabel->setText(QString::number(remainingTime));

    if (remainingTime <= 0) {
        countdownTimer->stop();
    }
}

// Toggle long breaks
void ScreenManager::toggleLongBreaks() {
    longBreaksEnabled = !longBreaksEnabled;
    toggleLongBreakAction->setText(longBreaksEnabled ? "Disable Long Breaks" : "Enable Long Breaks");
}

// Reset breaks
void ScreenManager::resetBreaks() {
    timer->stop();
    countdownTimer->stop();
    intervalCount = 0;
    remainingTime = visibleDurationMs / 1000;
    hide();
    timer->start(intervalMs);
    trayIcon->showMessage("Breaks Reset", "Timers have been reset.");
}

// Pause breaks
void ScreenManager::pauseBreaks() {
    if (breaksPaused) {
        timer->start(intervalMs);
        countdownTimer->start(1000);
        pauseBreaksAction->setText("Pause Breaks");
    } else {
        timer->stop();
        countdownTimer->stop();
        pauseBreaksAction->setText("Resume Breaks");
    }
    breaksPaused = !breaksPaused;
}

// // Handle system events
// bool ScreenManager::event(QEvent* event) {
//     if (event->type() == QEvent::ApplicationStateChange) {
//         Qt::ApplicationState state = QApplication::applicationState();
        
//         if (state == Qt::ApplicationActive) {
//             // System woke up or screen turned back on
//             std::cout << "System resumed from power-saving mode. Resetting breaks." << std::endl;
//             resetBreaks();
//         }
//     }
//     return QWidget::event(event);
// }

// Main function
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ScreenManager screenManager;

    // Hide the main window on startup
    screenManager.hide();

    return app.exec();
}