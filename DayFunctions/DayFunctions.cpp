// DayOfTheYear.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <array>
#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

constexpr std::array<int, 12> months = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

enum month_enum
{
    January = 0,
    February = 1,
    March = 2,
    April = 3,
    May = 4,
    June = 5,
    July = 6,
    August = 7,
    September = 8,
    October = 9,
    November = 10,
    December = 11,
};

auto get_next_month(const month_enum this_month) -> month_enum
{
    return static_cast<month_enum>(static_cast<int>(this_month) + 1);
}

struct date_t
{
    month_enum month{};
    int day{};
    int year{};

    explicit date_t(month_enum month_, int day_, int year_)
        : month{month_}, day{day_}, year{year_}
    {}
};

auto operator<(const date_t& lhs, const date_t& rhs) -> bool
{
    if (lhs.year < rhs.year)
        return true;
    if (lhs.month < rhs.month)
        return true;
    if (lhs.day < rhs.day)
        return true;

    return false;
}

auto print_month(const month_enum month) -> std::string
{
    switch (month)
    {
    case month_enum::January:
        return "January";
    case month_enum::February:
        return "February";
    case month_enum::March:
        return "March";
    case month_enum::April:
        return "April";
    case month_enum::May:
        return "May";
    case month_enum::June:
        return "June";
    case month_enum::July:
        return "July";
    case month_enum::August:
        return "August";
    case month_enum::September:
        return "September";
    case month_enum::October:
        return "October";
    case month_enum::November:
        return "November";
    case month_enum::December:
        return "December";
    default:
        assert(false);
        return "INVALID";
    }
}

auto operator<<(std::ostream& os, const month_enum month) -> std::ostream&
{
    return os << print_month(month);
}

auto print_month(const date_t dt) -> std::string
{
    return print_month(dt.month);
}

auto operator<<(std::ostream& os, const date_t& rhs) -> std::ostream&
{
    return os << rhs.month << " " << rhs.day << ", " << rhs.year;
}

auto is_leap_year(const int year) -> bool
{
    if (year % 4 == 0)
    {
        return true;
    }

    return false;
}

auto is_leap_year(const date_t dt) -> bool
{
    return is_leap_year(dt.year);
}

auto add_day_if_leap_year(const int month, const int year, int& day)
{
    if (month == 1)
    {
        /*  february */
        if (is_leap_year(year))
        {
            ++day;
        }
    }
}

auto get_day_of_month(const int day, const int year) -> date_t
{
    auto month = January;
    auto days_so_far = months[month];
    auto day_of_month = day;
    while (day > days_so_far)
    {
        day_of_month = day - days_so_far;
        days_so_far += months[get_next_month(month)];
        add_day_if_leap_year(month, year, days_so_far);
    }

    return date_t{month, day, year};
}

auto get_day_of_year(const date_t dt) -> const int
{
    auto day_of_year = 0;
    auto current_month = 0;
    while (current_month < dt.month)
    {
        day_of_year += months[current_month++];
        add_day_if_leap_year(current_month, dt.year, day_of_year);
    }

    return day_of_year + dt.day;
}

auto get_total_days_in_year(const int year) -> const int
{
    if (is_leap_year(year))
    {
        return 366;
    }
    else
    {
        return 365;
    }
}

auto get_total_days_in_year(const date_t dt) -> const int
{
    return get_total_days_in_year(dt.year);
}

auto difference_between_earlier_and_later_date(const date_t earlier_date, const date_t later_date) -> int
{
    const auto earlier_day_of_year = get_day_of_year(earlier_date);
    const auto later_day_of_year = get_day_of_year(later_date);

    if (later_date.year > earlier_date.year)
    {
        auto days_so_far = get_total_days_in_year(earlier_date) - earlier_day_of_year;
        auto year = earlier_date.year + 1;

        while (year < later_date.year)
        {
            days_so_far += get_total_days_in_year(year++);
        }
        return days_so_far + later_day_of_year;
    }
    else
    {
        assert(later_date.year == earlier_date.year);
        return later_day_of_year - earlier_day_of_year;
    }
}

auto difference_between_two_dates(const date_t lhs_date, const date_t rhs_date) -> int
{
    if (lhs_date < rhs_date)
    {
        return difference_between_earlier_and_later_date(lhs_date, rhs_date);
    }
    else if (rhs_date < lhs_date)
    {
        return difference_between_earlier_and_later_date(rhs_date, lhs_date);
    }
    else
    {
        return 0;
    }
}

auto print_difference(const date_t lhs, const date_t rhs) -> void
{
    std::cout << "the number of days between " << lhs << " and " << rhs
        << " is " << difference_between_two_dates(lhs, rhs) << " days\n";
}

enum weekday_enum
{
    Sunday = 0,
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6,
};

auto print_weekday(const weekday_enum weekday) -> std::string
{
    switch (weekday)
    {
    case Sunday:
        return "Sunday";
    case Monday:
        return "Monday";
    case Tuesday:
        return "Tuesday";
    case Wednesday:
        return "Wednesday";
    case Thursday:
        return "Thursday";
    case Friday:
        return "Friday";
    case Saturday:
        return "Saturday";
    default:
        assert(false);
        return "INVALID";
    }
}

auto operator<<(std::ostream& os, const weekday_enum weekday) -> std::ostream&
{
    return os << print_weekday(weekday);
}

auto advance_weekday(weekday_enum weekday, const int days_to_advance) -> weekday_enum
{
    const auto weekday_as_int = static_cast<int>(weekday);
    return static_cast<weekday_enum>((weekday_as_int + days_to_advance) % 7);
}

const auto baseline_date = date_t{January, 1, 1000};
const auto baseline_weekday = Wednesday;

auto day_of_the_week(const date_t dt) -> weekday_enum
{
    if (baseline_date < dt)
    {
        const auto days_since_baseline = difference_between_two_dates(dt, baseline_date) - 1;

        return advance_weekday(baseline_weekday, days_since_baseline);
    }
    else
    {
        assert(false);
    }
}

auto print_day_of_the_week(const date_t dt) -> void
{
    std::cout << dt << " is a " << day_of_the_week(dt) << "\n";
}

struct week_t
{
    std::bitset<7> days{};

    explicit week_t(weekday_enum first_day_of_week, weekday_enum last_day_of_week)
    {
        auto i = 0;
        while (i < first_day_of_week)
        {
            days.reset(i++);
        }
        while (i <= last_day_of_week)
        {
            days.set(i++);
        }
    }
};

struct month_t
{
    std::vector<week_t> weeks{};

    explicit month_t(weekday_enum first_weekday_of_month, month_enum month)
    {
        const auto days_in_month = months[month];
        weeks.emplace_back(first_weekday_of_month, Saturday);
        
        auto days_added_so_far = weeks.back().days.count();
        while (days_added_so_far < (days_in_month - 7))
        {
            weeks.emplace_back(Sunday, Saturday);
            days_added_so_far += weeks.back().days.count();
        }
        const auto days_remaining = days_in_month - days_added_so_far - 1;
        assert(days_remaining < 8);
        weeks.emplace_back(Sunday, advance_weekday(Sunday, days_remaining));
    }
};

auto print_calendar(const date_t dt) -> void
{
    int month_day = 0;
    std::cout << "\t" << dt.month << "\n";
    for (const week_t& week : month_t{day_of_the_week(date_t{dt.month, 1, dt.year}), dt.month}.weeks)
    {
        for (int day = 0; day < 7; ++day)
        {
            if (week.days.test(day))
            {
                std::cout << std::setw(3) << std::right << ++month_day;
            }
            else
            {
                std::cout << std::setw(3) << std::right << "-";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

int main()
{
    const auto first = date_t(March, 27, 1991);
    const auto second = date_t(March, 28, 1991);
    const auto third = date_t(March, 27, 1990);
    const auto fourth = date_t(March, 27, 1992);
    const auto fifth = date_t(January, 1, 1992);
    const auto sixth = date_t(December, 31, 1996);

    std::cout << std::endl;

    print_difference(first, second);
    print_difference(first, third);
    print_difference(first, fourth);
    print_difference(third, fourth);
    print_difference(fifth, sixth);

    std::cout << std::endl;

    print_day_of_the_week(date_t(January, 2, 1000));
    print_day_of_the_week(date_t(June, 4, 2016));

    std::cout << std::endl;

    print_calendar(date_t(May, 4, 2016));
    print_calendar(date_t(June, 4, 2016));
    print_calendar(date_t(July, 4, 2016));

    std::cout << std::endl;
}

/*
January - 31 days
February - 28 days in a common year and 29 days in Leap Years
March - 31 days
April - 30 days
May - 31 days
June - 30 days
July - 31 days
August - 31 days
September - 30 days
October - 31 days
November - 30 days
December - 31 days
*/

