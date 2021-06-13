#include "airline_ticket.h"
#include "test_runner.h"

std::ostream &
operator<<(std::ostream &out, const Date &date)
{
    out << date.year << "-" << date.month << "-" << date.day;
    return out;
}

std::istream &
operator>>(std::istream &in, Date &date)
{
    in >> date.year;
    in.ignore(1);
    in >> date.month;
    in.ignore(1);
    in >> date.day;

    return in;
}

bool
operator<(const Date &lhs, const Date &rhs)
{
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool
operator==(const Date &lhs, const Date &rhs)
{
    return std::tie(lhs.year, lhs.month, lhs.day)==std::tie(rhs.year, rhs.month, rhs.day);
}

bool
operator!=(const Date &lhs, const Date &rhs)
{
    return !(lhs==rhs);
}

std::ostream &
operator<<(std::ostream &out, const Time &time)
{
    out << time.hours << ":" << time.minutes;
    return out;
}

std::istream &
operator>>(std::istream &in, Time &time)
{
    in >> time.hours;
    in.ignore(1);
    in >> time.minutes;
    return in;
}

bool
operator<(const Time &lhs, const Time &rhs)
{
    return std::tie(lhs.hours, lhs.minutes) < std::tie(rhs.hours, rhs.minutes);
}

bool
operator==(const Time &lhs, const Time &rhs)
{
    return std::tie(lhs.hours, lhs.minutes)==std::tie(rhs.hours, rhs.minutes);
}

bool
operator!=(const Time &lhs, const Time &rhs)
{
    return !(lhs==rhs);
}

#define UPDATE_FIELD(ticket, field, values){ \
  if (values.count(#field)){                   \
    std::stringstream is;                   \
    is << values.at(#field);                                        \
    is >> ticket.field;            \
  }                                             \
}  // Реализуйте этот макрос, а также необходимые операторы для классов Date и Time

void
TestUpdate()
{
    AirlineTicket t;
    t.price = 0;

    const std::map<std::string, std::string> updates1 = {
        {"departure_date", "2018-2-28"},
        {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const std::map<std::string, std::string> updates2 = {
        {"price", "12550"},
        {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int
main()
{
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
