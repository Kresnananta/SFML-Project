#pragma once
#include <string>
#include <vector>

struct LeaderboardEntry{
    std::string name;
    int score;
    std::string date;
    std::string time;
    int elapsed;
};

class Leaderboard{
public:
    void load(const std::string& filename);
    void save(const std::string& filename) const;
    void addEntry(const LeaderboardEntry& entry);
    const std::vector<LeaderboardEntry>& getEntries() const;

private:
    std::vector<LeaderboardEntry> entries;
};