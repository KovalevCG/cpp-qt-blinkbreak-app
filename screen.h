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
    const int visibleDurationMs = 15000; // 15 seconds in ms
    const int extendedDurationMs = 300000; // 5 minutes in ms
    // const int intervalMs = 6000;       // 10 minutes in ms
    // const int visibleDurationMs = 2000; // 10 seconds in ms
    // const int extendedDurationMs = 5000; // 5 minutes in ms
};

#endif // SCREEN_H
