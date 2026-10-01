#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>

class Logger {
private:
    std::mutex m_mutex;
    Logger() { std::cout << "--- Logger Initialized ---\n"; }

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& msg, int thread_id) {
        std::lock_guard<std::mutex> lock(m_mutex); 
        std::cout << "Thread [" << thread_id << "] Log: " << msg << "\n";
    }
};

void runThread(int id) {
    Logger::getInstance().log("Processing polygon...", id);
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 1; i <= 4; ++i) {
        threads.push_back(std::thread(runThread, i));
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}
