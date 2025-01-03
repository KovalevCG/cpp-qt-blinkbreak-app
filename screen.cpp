#include "screen.h"
#include <QApplication>
#include <QPalette>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QLabel>
#include <iostream>
#include <QVBoxLayout>

// Constructor
ScreenManager::ScreenManager(QWidget *parent)
    : QWidget(parent),
      timer(new QTimer(this)),
      countdownTimer(new QTimer(this)),
      countdownLabel(new QLabel(this)),
      trayIcon(new QSystemTrayIcon(this)),
      remainingTime(visibleDurationMs / 1000)  // Initialize with 10 seconds
{
    // Set window size and properties
    resize(400, 200);
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
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

    // Ensure the label scales properly
    countdownLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    countdownLabel->setMinimumSize(200, 100); // Minimum size to ensure visibility
    countdownLabel->setWordWrap(true); // Ensure text wraps if needed

    // Layout to center the label
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(countdownLabel);
    setLayout(layout);

    // System tray icon
    QMenu* trayMenu = new QMenu(this);
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

    timer->start(intervalMs); // Start main timer with 10 min intervals
}

// Destructor
ScreenManager::~ScreenManager() {
    // Qt automatically cleans up child objects
}

// Toggle screen visibility with 10s or 5m behavior
void ScreenManager::toggleVisibility() {
    intervalCount++;  // Increment interval counter

    if (intervalCount % 3 == 0) {
        // Every third interval: 5 minutes
        std::cout << "Extended Interval: " << intervalCount << std::endl;
        remainingTime = extendedDurationMs / 1000; // 5 minutes in seconds
        countdownLabel->setText(QString::number(remainingTime));
        showFullScreen();
        countdownTimer->start(1000); // Update countdown every second

        QTimer::singleShot(extendedDurationMs, this, &ScreenManager::hide);
    } else {
        // Regular interval: 10 seconds
        std::cout << "Interval: " << intervalCount << std::endl;
        remainingTime = visibleDurationMs / 1000; // 10 seconds in seconds
        countdownLabel->setText(QString::number(remainingTime));
        showFullScreen();
        countdownTimer->start(1000); // Update countdown every second

        QTimer::singleShot(visibleDurationMs, this, &ScreenManager::hide);
    }
}

// Update countdown label each second
void ScreenManager::updateCountdown() {
    remainingTime--;
    countdownLabel->setText(QString::number(remainingTime));

    if (remainingTime <= 0) {
        countdownTimer->stop();
    }
}

// Main function
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ScreenManager screenManager;

    // Hide the main window on startup
    screenManager.hide();

    return app.exec();
}