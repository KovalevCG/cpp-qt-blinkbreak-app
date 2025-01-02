// #ifndef SCREEN_H
// #define SCREEN_H

// #include <QWidget>
// #include <QTimer>
// #include <QLabel>
// #include <QSystemTrayIcon>  // Make sure this is included

// class ScreenManager : public QWidget {
//     Q_OBJECT
// public:
//     ScreenManager(QWidget *parent = nullptr);
//     ~ScreenManager();
// private slots:
//     void toggleVisibility();
//     void updateCountdown();
// private:
//     QTimer* timer;  // Main timer for triggering visibility
//     QTimer* countdownTimer;  // Timer for updating the countdown display
//     QLabel* countdownLabel;  // Label to display the remaining time
//     QSystemTrayIcon* trayIcon;  // Declare the tray icon here
//     int remainingTime;  // Time remaining in seconds
//     const int intervalMs = 600000;  // 10 minutes in milliseconds
//     const int visibleDurationMs = 10000;  // 10 seconds in milliseconds
// };

// #endif // SCREEN_H



#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QSystemTrayIcon>  // Ensure this is included

class ScreenManager : public QWidget {
    Q_OBJECT
public:
    ScreenManager(QWidget *parent = nullptr);
    ~ScreenManager();

private slots:
    void toggleVisibility();
    void updateCountdown();

private:
    QTimer* timer;              // Main timer for triggering visibility
    QTimer* countdownTimer;     // Timer for updating the countdown display
    QLabel* countdownLabel;     // Label to display the remaining time
    QSystemTrayIcon* trayIcon;  // System tray icon

    int remainingTime;          // Time remaining for countdown
    int intervalCount = 0;      // Counter to track intervals

    const int intervalMs = 600000;       // 10 minutes in ms
    const int visibleDurationMs = 10000; // 10 seconds in ms
    const int extendedDurationMs = 300000; // 5 minutes in ms
    // const int intervalMs = 16000;       // 10 minutes in ms
    // const int visibleDurationMs = 1000; // 10 seconds in ms
    // const int extendedDurationMs = 14000; // 5 minutes in ms
};

#endif // SCREEN_H
