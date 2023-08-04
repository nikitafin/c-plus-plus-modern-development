// TODO(Nikita): use std module
module;
#include <map>
#include <string>
#include <unordered_map>
export module secondary_index; // TODO(Nikita): IDE broken if modern_cxx

export namespace modern_cxx::brown {

struct Record {
  std::string id;
  std::string title;
  std::string user;
  int         timestamp;
  int         karma;
};

class Database {
public:
  using Id        = std::string;
  using UserName  = std::string;
  using TimeStamp = int;
  using Karma     = int;

  using TimeStampIndex = std::multimap<TimeStamp, Record const *>;
  using KarmaIndex     = std::multimap<Karma, Record const *>;
  using UserNameIndex  = std::unordered_multimap<UserName, Record const *>;

public:
  bool Put(Record const &record) {
    if (Contains(record.id)) {
      return false;
    }

    try {
      auto const &elem = (m_Data[record.id] = record);

      m_TimeStampIndex.insert({record.timestamp, &elem});
      m_KarmaIndex.insert({record.karma, &elem});
      m_UserNameIndex.insert({record.user, &elem});
    } catch (std::exception const &err) {
      RemoveTimeStamp(record);
      RemoveKarma(record);
      RemoveUserName(record);

      m_Data.erase(record.id);
    }

    return true;
  }

  const Record *GetById(const std::string &id) const {
    if (!Contains(id)) {
      return nullptr;
    }

    return &m_Data.at(id);
  }

  bool Erase(const std::string &id) {
    if (!Contains(id)) {
      return false;
    }

    auto const &elem = m_Data.at(id);
    RemoveTimeStamp(elem);
    RemoveKarma(elem);
    RemoveUserName(elem);

    m_Data.erase(id);

    return true;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const {
    auto lit = m_TimeStampIndex.lower_bound(low);
    if (lit == m_TimeStampIndex.end()) {
      return;
    }
    auto rit = m_TimeStampIndex.upper_bound(high);
    for (; lit != rit; ++lit) {
      if (!callback(*(lit->second))) {
        return;
      }
    }
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const {
    auto lit = m_KarmaIndex.lower_bound(low);
    if (lit == m_KarmaIndex.end()) {
      return;
    }
    auto rit = m_KarmaIndex.upper_bound(high);
    for (; lit != rit; ++lit) {
      if (!callback(*(lit->second))) {
        return;
      }
    }
  }

  template <typename Callback>
  void AllByUser(const std::string &user, Callback callback) const {
    auto [l, r] = m_UserNameIndex.equal_range(user);
    for (; l != r; ++l) {
      if (!callback(*(l->second))) {
        return;
      }
    }
  }

private:
  bool Contains(std::string const &id) const { return (m_Data.count(id) > 0); }

  void RemoveTimeStamp(Record const &record) {
    auto [begin, end] = m_TimeStampIndex.equal_range(record.timestamp);
    auto it = std::find_if(begin, end, [&r = record](auto const &elem) {
      return elem.second->id == r.id;
    });

    m_TimeStampIndex.erase(it);
  }

  void RemoveKarma(Record const &record) {
    auto [begin, end] = m_KarmaIndex.equal_range(record.karma);
    auto it = std::find_if(begin, end, [&r = record](auto const &elem) {
      return elem.second->id == r.id;
    });

    m_KarmaIndex.erase(it);
  }

  void RemoveUserName(Record const &record) {
    auto [begin, end] = m_UserNameIndex.equal_range(record.user);
    auto it = std::find_if(begin, end, [&r = record](auto const &elem) {
      return elem.second->id == r.id;
    });

    m_UserNameIndex.erase(it);
  }

private:
  std::unordered_map<Id, Record> m_Data;

  TimeStampIndex m_TimeStampIndex;
  KarmaIndex     m_KarmaIndex;
  UserNameIndex  m_UserNameIndex;
};

} // namespace modern_cxx::brown
