#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <cstdlib>

using namespace std;

const unsigned int FIRST = 0;

// dfs status
enum {
    FRESH, OPEN, CLOSED
} typedef statusType;

/**
 * Graph class
 */
class Graph
{
    vector< vector<bool> > edge;

    public:

    unsigned int size;

    /**
     * @param const char *file
     */
    Graph(const char *file)
    {
        ifstream input(file);
        input >> size;
        for (unsigned int i = 0; i < size; i++) {
            vector<bool> current_line;
            for (unsigned int j = 0; j < size; j++) {
                char tmp;
                input >> tmp;
                current_line.push_back(tmp == '1');
            }
            edge.push_back(current_line);
        }
    }

    /**
     * Test if graph has edge
     *
     * @param unsigned from
     * @param unsigned to
     * @return bool
     */
    bool has_edge(unsigned int from, unsigned int to)
    {
        return edge.at(from).at(to);
    }
};

/**
 * Config class
 */
class Config
{
    vector<statusType> status;

    public:

    unsigned int node;
    unsigned int size;

    /**
     * @param unsigned n
     */
    Config(unsigned int n)
    {
        size = 0;
        status.insert(status.begin(), n, FRESH);
    }

    /**
     * @param unsigned n
     * @param Config prev
     */
    Config(unsigned int n, Config prev)
    {
        node = n;
        size = prev.size + 1;
        for (unsigned int i = 0; i < prev.status.size(); i++) {
            if (prev.status.at(i) == OPEN) {
                status.push_back(OPEN);
            } else {
                status.push_back(FRESH);
            }
        }
        status.at(node) = OPEN;
    }

    /**
     * Set status to open
     *
     * @param unsigned node
     * @return void
     */
    void open(unsigned int node)
    {
        status.at(node) = OPEN;
    }

    /**
     * Set status to closed
     *
     * @param unsigned node
     * @return void
     */
    void close(unsigned int node)
    {
        status.at(node) = CLOSED;
    }

    /**
     * Get next possible node
     *
     * @param Graph graph
     * @return unsigned
     */
    unsigned int next(Graph graph)
    {
        for (unsigned int i = 1; i < graph.size; i++) {
            if (status.at(i) == FRESH && graph.has_edge(node, i)) {
                return i;
            }
        }

        return 0;
    }
};

/**
 * Main
 *
 * @return int
 */
int main(int argc, char **argv)
{
    if (argc != 4) {
        cout << "usage: hg n k input" << endl;
        return 0;
    }

    unsigned int n = (unsigned int) atoi(argv[1]);
    //unsigned int k = (unsigned int) atoi(argv[2]);
    Graph graph(argv[3]);

    stack<Config> stack;
    stack.push(Config(FIRST, Config(n)));
    while (!stack.empty()) {
        Config current = stack.top();
        if (current.size == graph.size) { // end state
            if (graph.has_edge(current.node, FIRST)) { // valid state
                cout << "Yes!";
                while (!stack.empty()) {
                    cout << " " << stack.top().node;
                    stack.pop();
                }
                cout << endl;
                return 0;
            } else { // invalid state
                stack.pop();
                stack.top().close(current.node);
            }
        } else {
            unsigned int next = current.next(graph);
            if (next) {
                current.open(next);
                stack.push(Config(next, current));
            } else {
                stack.pop();
                if (!stack.empty()) {
                    stack.top().close(current.node);
                }
            }
        }
    }

    cout << "No way.." << endl;
    return 0;
}
