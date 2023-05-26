#ifndef LOG_HPP
#define LOG_HPP
#include <iostream>
#include <fstream>
#include <ctime>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR };

class Logger {
public:
    Logger(const std::string& filename)
    {
        file.open(filename, std::ios::app);
    }

    ~Logger()
    {
        if (file.is_open())
            file.close();
    }

    void Log(LogLevel level, const std::string& message)
    {
        std::string timestamp = GetTimestamp();
        std::string levelString = GetLogLevelString(level);
        std::string logLine = "[" + timestamp + "] " + "[" + levelString + "] " + message + "\n";

        std::cout << logLine;  // 输出到控制台
        if (file.is_open())
            file << logLine;  // 输出到日志文件
    }

private:
    std::ofstream file;

    std::string GetTimestamp()
    {
        std::time_t now = std::time(nullptr);
        std::tm* tm = std::localtime(&now);

        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);

        return buffer;
    }

    std::string GetLogLevelString(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::ERROR:
                return "ERROR";
            default:
                return "";
        }
    }
};


#endif