#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int n = 5; // number of edges
const int k = 3; // edges value

// dfs statuses
enum { FRESH, OPEN, CLOSED } typedef status_t;

// edges vector
vector<int> typedef vector_t;

// config type
struct {
    vector_t edges;
    status_t statuses[n];
} typedef config_t;

// config stack
stack<config_t> typedef stack_t;

// edges
int edges[n][n] = {
    {0, 1, 1, 1, 0},
    {1, 0, 1, 1, 1},
    {1, 1, 0, 1, 1},
    {1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0},
};

/**
 * Get valid if is valid state
 *
 * @param config_t config
 * @return int
 */
int get_next(config_t config)
{
    for (int i = 1; i < n; i++) {
        if (config.statuses[i] == FRESH && edges[config.edges.back()][i]) {
            return i;
        }
    }

    return 0;
}

/**
 * Main
 *
 * @return int
 */
int main()
{
    stack_t stack;
    config_t config;

    for (int i = 0; i < n; i++) {
        config.statuses[i] = FRESH;
    }

    config.statuses[0] = OPEN;
    config.edges.push_back(0);
    stack.push(config);

    while (!stack.empty()) {
        config_t current = stack.top();

        if ((int) current.edges.size() == n) { // end state
            if (edges[current.edges.back()][0]) { // valid state
                cout << "Yes";
                for (int i = 0; i < (int) current.edges.size(); i++) {
                    cout << " " << current.edges.at(i);
                }
                cout << endl;
                return 0;
            } else { // invalid state
                stack.pop();
                stack.top().statuses[current.edges.back()] = CLOSED;
            }
        } else {
            int next = get_next(current);
            if (next) {
                current.statuses[next] = OPEN;

                config_t next_config;
                for (int i = 0; i < n; i++) {
                    next_config.statuses[i] = FRESH;
                }

                for (int i = 0; i < (int) current.edges.size(); i++) {
                    next_config.edges.push_back(current.edges.at(i));
                    next_config.statuses[current.edges.at(i)] = OPEN;
                }

                next_config.edges.push_back(next);
                stack.push(next_config);
            } else {
                stack.pop();
                stack.top().statuses[current.edges.back()] = CLOSED;
            }
        }
    }

    cout << "No way" << endl;
    return 0;
}
