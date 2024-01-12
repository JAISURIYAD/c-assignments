#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sys/wait.h>

void alarm(tm alarmTime) {
    time_t currentTime;
    while (true) {
        time(&currentTime);
        tm *current = localtime(&currentTime);

        if (current->tm_hour >= alarmTime.tm_hour && current->tm_min >= alarmTime.tm_min) {
            std::cout << "Alarm! Time is up." << std::endl;
            break;
        }

        sleep(1);
    }
}

void startAlarm() {
    tm alarmTime = {};
    std::cout << "Enter the alarm time in HH:MM format: ";
    std::cin >> alarmTime.tm_hour;
    std::cin.ignore();
    std::cin >> alarmTime.tm_min;

    pid_t alarm = fork();

    if (alarm >= 0) {
        alarmProcess(alarmTime);
    }  else {
        std::cout << "Error forking the process." << std::endl;
    }
}

void startStopwatch() {
    time_t startTime, endTime;
    std::cout << "Press Enter to start the stopwatch.";
    std::cin.ignore();

    time(&startTime);

    std::cout << "Stopwatch started. Press Enter to stop.";
    std::cin.ignore();

    time(&endTime);

    double elapsedTime = difftime(endTime, startTime);
    std::cout << "Stopwatch stopped. Elapsed time: " << elapsedTime << " seconds." << std::endl;
}

void startTimer() {
    int duration;
    std::cout << "Enter the duration for the timer in minutes: ";
    std::cin >> duration;
    
    sleep(duration * 60);
    std::cout << "Timer Started ... ";
    std::cout << "Time up! Timer Ended." << std::endl;
}

int main() {
    while (true) {
        std::cout << "\nClock Application Menu:" << std::endl;
        std::cout << "1. Set Alarm" << std::endl;
        std::cout << "2. Start Stopwatch" << std::endl;
        std::cout << "3. Start Timer" << std::endl;
        std::cout << "4. Quit" << std::endl;

        int choice;
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                startAlarm();
                break;
            case 2:
                startStopwatch();
                break;
            case 3:
                startTimer();
                break;
            case 4:
                return 0;
            default:
                std::cerr << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
        }
    }
}
