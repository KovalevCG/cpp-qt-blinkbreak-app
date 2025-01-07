



#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QVBoxLayout>
#include <QEvent>

class ScreenManager : public QWidget {
    Q_OBJECT
public:
    ScreenManager(QWidget *parent = nullptr);
    ~ScreenManager();

// protected:
//     bool event(QEvent* event) override; // Handle system events

private slots:
    void toggleVisibility();  // Handle screen visibility for breaks
    void updateCountdown();   // Update countdown display
    void toggleLongBreaks();  // Enable/disable long breaks
    void resetBreaks();       // Reset all timers and counters
    void pauseBreaks();       // Pause or resume timers

private:
    QTimer* timer;              // Main timer for triggering breaks
    QTimer* countdownTimer;     // Timer for updating countdown display
    QLabel* countdownLabel;     // Label to display the countdown
    QSystemTrayIcon* trayIcon;  // System tray icon
    QAction* toggleLongBreakAction; // Toggle long breaks
    QAction* resetBreaksAction;     // Reset breaks
    QAction* pauseBreaksAction;     // Pause/resume breaks

    int remainingTime;          // Countdown time in seconds
    int intervalCount = 0;      // Tracks number of intervals
    bool longBreaksEnabled = true; // Enable/disable long breaks
    bool breaksPaused = false;  // Track if breaks are paused

    const int intervalMs = 600000;       // 10 minutes in ms
    const int visibleDurationMs = 10000; // 10 seconds in ms
    const int extendedDurationMs = 300000; // 5 minutes in ms

    // const int intervalMs = 10000;
    // const int visibleDurationMs = 6000;
    // const int extendedDurationMs = 9000;
};

#endif // SCREEN_H