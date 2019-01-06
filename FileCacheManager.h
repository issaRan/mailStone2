//
// Created by issa on 1/4/19.
//

#ifndef MAILSTONE2_FILECACHEMANAGER_H
#define MAILSTONE2_FILECACHEMANAGER_H


#include <unordered_map>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include "CacheManger.h"
#define space " "
template<class P, class S>
class FileCacheManager : public CacheManger<P, S> {
private:
    unordered_map<string, string> problemsAndSolutions;
public:
    virtual bool isSolutionExist(P problem);

    virtual S getSolution(P problem);

    virtual void saveSolution(P problem, S solution);

    void loadMap();

    void saveOnFile(const string &problem, const string &solution);

    vector<string> splitValues(const string &line);
};

template<class P, class S>
bool FileCacheManager<P, S>::isSolutionExist(P problem) {
    this->problemsAndSolutions.count(problem) > 0;
}

template<class P, class S>
S FileCacheManager<P, S>::getSolution(P problem) {
    auto it = problemsAndSolutions.find(problem);
    while (it != problemsAndSolutions.end()) {
        if (it->first = problem) {
            return it->second;
        }
    }
    return NULL;
}

template<class P, class S>
void FileCacheManager<P, S>::saveSolution(P problem, S solution) {
    this->problemsAndSolutions(make_pair(problem, solution));
    saveOnFile(problem, solution);
}

template<class P, class S>
void FileCacheManager<P, S>::loadMap() {
    ifstream solutions;
    string line;
    vector<string> problemsAnsSolutions;
    while (getline(solutions, line)) {
        problemsAnsSolutions = splitValues(line);
        this->problemsAndSolutions.insert(make_pair(problemsAnsSolutions[0],problemsAnsSolutions[1]));
    }
}

template<class P, class S>
void FileCacheManager<P, S>::saveOnFile(const string &problem, const string &solution) {
    ofstream sol;
    sol.open("solutionToProblem.txt", ios::app);
    if (sol.is_open()) {
        sol << problem << space << solution << "\n";
        sol.close();
    }
}

template<class P, class S>
vector<string> FileCacheManager<P, S>::splitValues(const string &line) {
    //function to split the line by spaces.
    stringstream ss(line);
    istream_iterator <string> begin(ss);
    istream_iterator <string> end;
    vector<string> vstrings(begin, end);
    return vstrings;
}


#endif //MAILSTONE2_FILECACHEMANAGER_H
