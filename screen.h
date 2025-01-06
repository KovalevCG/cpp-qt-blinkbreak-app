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
    void toggleLongBreaks(); // Slot for tray menu action

private:
    QTimer* timer;              // Main timer for triggering visibility
    QTimer* countdownTimer;     // Timer for updating the countdown display
    QLabel* countdownLabel;     // Label to display the remaining time
    QSystemTrayIcon* trayIcon;  // System tray icon
    QAction* toggleLongBreakAction; // Action to toggle long breaks

    int remainingTime;          // Time remaining for countdown
    int intervalCount = 0;      // Counter to track intervals
    bool longBreaksEnabled = true; // Flag for long break toggle

    const int intervalMs = 600000;       // 10 minutes in ms
    const int visibleDurationMs = 15000; // 15 seconds in ms
    const int extendedDurationMs = 300000; // 5 minutes in ms
    // const int intervalMs = 6000;
    // const int visibleDurationMs = 2000;
    // const int extendedDurationMs = 4000;
};

#endif // SCREEN_H
