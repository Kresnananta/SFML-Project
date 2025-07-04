#include "Leaderboard.h"
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

void Leaderboard::load(const string& filename){
    entries.clear();
    ifstream file(filename);
    string line;

    while(getline(file, line)){
        istringstream iss(line);
        LeaderboardEntry entry;
        getline(iss, entry.name, ',');
        string scoreStr;
        getline(iss, scoreStr, ',');
        try {
            entry.score = !scoreStr.empty() ? std::stoi(scoreStr) : 0;
        } catch (const std::exception&) {
            entry.score = 0;
        }
        getline(iss, entry.date, ',');
        getline(iss, entry.time, ',');
        string elapsedStr;
        getline(iss, elapsedStr, ',');
        try {
            entry.elapsed = !elapsedStr.empty() ? std::stof(elapsedStr) : 0.0f;
        } catch (const std::exception&) {
            entry.elapsed = 0.0f;
        }
        entries.push_back(entry);
    }
}

void Leaderboard::save(const std::string& filename) const{
    std::ofstream file(filename);
    for(const auto& entry : entries){
        file << entry.name << "," << entry.score << "," << entry.date <<"," << entry.time << "," << entry.elapsed << "\n";
    }
}

void Leaderboard::addEntry(const LeaderboardEntry& entry) {
    entries.push_back(entry);
    std::sort(entries.begin(), entries.end(), [](const LeaderboardEntry& a, const LeaderboardEntry& b){
        return a.score > b.score;
    });
    if (entries.size() > 10) // keep top 10
        entries.resize(10);
}

const std::vector<LeaderboardEntry>& Leaderboard::getEntries() const {
    return entries;
}