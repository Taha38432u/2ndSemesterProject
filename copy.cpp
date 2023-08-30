#include <iostream>
#include <ctime>

int days_between_dates(int date1, int month1, int date2, int month2)
{
    std::tm time1 = {0};
    time1.tm_mday = date1;
    time1.tm_mon = month1 - 1;

    std::tm time2 = {0};
    time2.tm_mday = date2;
    time2.tm_mon = month2 - 1;

    // Assume both dates are in the same year (e.g., 2023)
    int current_year = 2023;

    time1.tm_year = current_year - 1900;
    time2.tm_year = current_year - 1900;

    std::time_t time1_secs = std::mktime(&time1);
    std::time_t time2_secs = std::mktime(&time2);

    double difference_secs = std::difftime(time2_secs, time1_secs);
    int difference_days = static_cast<int>(difference_secs / (60 * 60 * 24));

    return difference_days;
}

int main()
{
    int date1 = 1;
    int month1 = 3;

    int date2 = 5;
    int month2 = 3;

    int days_difference = days_between_dates(date1, month1, date2, month2);
    std::cout << "The number of days between " << date1 << "-" << month1 << " and " << date2 << "-" << month2 << " is: " << days_difference << " days.\n";

    return 0;
}
