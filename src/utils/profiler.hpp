#pragma once
#include <chrono>
#include <map>
#include <stack>
#include <string>
#include <iostream>

#include "../data.hpp"

struct Profiler {
    Profiler() {
        scope.emplace("GLOBAL");
    }

    std::map<std::string, double> accumulated_times;
    std::map<std::string, int> call_counts;
    std::map<std::string, std::string> parent;
    std::map<std::string, std::chrono::high_resolution_clock::time_point> start_times;
    std::stack<std::string> scope;

    void startScope(const std::string& name) {
        parent[name] = scope.top();
        scope.push(name);
        start_times[name] = std::chrono::high_resolution_clock::now();
    }

    void endScope() {
        std::string name = scope.top();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start_times[name];
        accumulated_times[name] += duration.count();
        call_counts[name]++;
        scope.pop();
    }

    void print_profiler_stats() {
    std::cout << "\n=== Profiler Statistics ===" << std::endl;
    std::cout << "+ GLOBAL" << std::endl;
    print_tree("GLOBAL", 1);
    std::cout << "==========================\n" << std::endl;
    }
    
private:
    void print_tree(const std::string& name, int depth) {
        for (const auto& [child_name, parent_name] : parent) {
            if (parent_name == name) {
                std::string indent = "";
                for (int i = 1; i < depth; i++) {
                    indent += "|   ";
                }
                
                std::string branch = "+-- ";
                
                double total_time = accumulated_times[child_name];
                int count = call_counts[child_name];
                double avg_time = total_time / count;
                
                std::cout << indent << branch << child_name 
                        << " | Total: " << total_time << " ms"
                        << " | Calls: " << count
                        << " | Avg: " << avg_time << " ms" << std::endl;
                
                print_tree(child_name, depth + 1);
            }
        }
    }
};

Profiler profiler;

#ifdef DEBUG
#define PROFILE(NAME, ...) \
{ \
    profiler.startScope(NAME); \
    __VA_ARGS__; \
    profiler.endScope(); \
}

#define PRINT_PROFILER_STATS() \
{ \
    profiler.print_profiler_stats(); \
}
#else
#define PROFILE(NAME, ...) \
{ \
    __VA_ARGS__; \
}

#define PRINT_PROFILER_STATS()
#endif