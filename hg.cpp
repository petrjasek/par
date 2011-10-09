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
    unsigned int n;
    vector< vector<bool> > edge;

    public:

    /**
     * Load graph from file
     *
     * @param const char *file
     */
    Graph(const char *file)
    {
        ifstream input(file);
        input >> n;
        for (unsigned int i = 0; i < n; i++) {
            vector<bool> current_line;
            for (unsigned int j = 0; j < n; j++) {
                char tmp;
                input >> tmp;
                current_line.push_back(tmp == '1');
            }
            edge.push_back(current_line);
        }
    }

    /**
     * Get size
     *
     * @return unsigned 
     */
    unsigned int size()
    {
        return n;
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
    vector<unsigned int> nodes;
    vector<statusType> status;

    /**
     * Init status vector
     *
     * @param unsigned n
     * @return void
     */
    void init(unsigned int n)
    {
        for (unsigned int i = 0; i < n; i++) {
            status.push_back(FRESH);
        }
    }

    public:

    /**
     * @param unsigned n
     */
    Config(unsigned int n)
    {
        init(n);
    }

    /**
     * @param unsigned n
     * @param Config parent
     */
    Config(unsigned int n, Config parent)
    {
        init(n);
        for (unsigned int i = 0; i < parent.size(); i++) {
            nodes.push_back(parent.nodes.at(i));
            status[parent.nodes.at(i)] = OPEN;
        }
    }

    /**
     * Get size
     *
     * @return unsigned
     */
    unsigned int size()
    {
        return nodes.size();
    }

    /**
     * Print nodes
     *
     * @return void
     */
    void print()
    {
        for (unsigned int i = 0; i < nodes.size(); i++) {
            cout << " " << nodes.at(i);
        }
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
     * Append node
     *
     * @param unsigned node
     * @return void
     */
    void push(unsigned int node)
    {
        nodes.push_back(node);
    }

    /**
     * Get last node
     *
     * @return unsigned
     */
    unsigned int back()
    {
        return nodes.back();
    }

    /**
     * Get next possible node
     *
     * @param Graph graph
     * @return unsigned
     */
    unsigned int next(Graph graph)
    {
        for (unsigned int i = 1; i < graph.size(); i++) {
            if (status.at(i) == FRESH && graph.has_edge(nodes.back(), i)) {
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
    stack.push(Config(n));
    stack.top().open(FIRST);
    stack.top().push(FIRST);

    while (!stack.empty()) {
        Config current = stack.top();
        if (current.size() == graph.size()) { // end state
            if (graph.has_edge(current.back(), FIRST)) { // valid state
                cout << "Yes!";
                current.print();
                cout << endl;
                return 0;
            } else { // invalid state
                stack.pop();
                stack.top().close(current.back());
            }
        } else {
            unsigned int next = current.next(graph);
            if (next) {
                current.open(next);
                stack.push(Config(n, current));
                stack.top().push(next);
            } else {
                stack.pop();
                if (!stack.empty()) {
                    stack.top().close(current.back());
                }
            }
        }
    }

    cout << "No way.." << endl;
    return 0;
}
