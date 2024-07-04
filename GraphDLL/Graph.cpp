#include "pch.h"
#include "Graph.h"

// ����������� ����� ���������� ������ ��� ���������
Graph::Graph() {}

// ���������� ��� ������� ������������������ ������
Graph::~Graph() {
    // ������� ������ ������ � ����
    for (Node* node : nodes_) {
        delete node;
    }
    nodes_.clear();

    for (Edge* edge : edges_) {
        delete edge;
    }
    edges_.clear();

    // ������� ������ ���������
    for (auto& pair : adjacencyList_) {
        delete pair.second;
    }
    adjacencyList_.clear();
}

// ���������� ������� � ����
void Graph::addNode(Node* node) {
    nodes_.push_back(node);
}

// ���������� ����� � ����
void Graph::addEdge(Edge* edge) {
    edges_.push_back(edge);

    Node* source = edge->getSource();
    if (adjacencyList_.find(source) == adjacencyList_.end()) {
        adjacencyList_[source] = new std::vector<Edge*>();
    }
    adjacencyList_[source]->push_back(edge);
}

// �������� ������ ������ � �����
std::vector<Node*> Graph::getNodes() const {
    return nodes_;
}

// �������� ������ ���� � �����
std::vector<Edge*> Graph::getEdges() const {
    return edges_;
}

// �������� ������� �� � �����
Node* Graph::getNode(const std::string& name) const {
    for (Node* node : nodes_) {
        if (node->getName() == name) {
            return node;
        }
    }
    return nullptr;
}

// �������� ����� �� ���� � ������ (��������)
Edge* Graph::getEdge(Node* start, Node* destination) const {
    for (Edge* edge : edges_) {
        if (edge->getSource() == start && edge->getDestination() == destination) {
            return edge;
        }
    }
    return nullptr;
}

// �������� ������� �� �����
void Graph::removeNode(Node* node) {
    nodes_.erase(std::remove(nodes_.begin(), nodes_.end(), node), nodes_.end());

    for (auto it = edges_.begin(); it != edges_.end(); ) {
        if ((*it)->getSource() == node || (*it)->getDestination() == node) {
            delete* it;
            it = edges_.erase(it);
        }
        else {
            ++it;
        }
    }

    auto it = adjacencyList_.find(node);
    if (it != adjacencyList_.end()) {
        delete it->second;
        adjacencyList_.erase(it);
    }
}

// �������� ����� �� �����
void Graph::removeEdge(Edge* edge) {
    edges_.erase(std::remove(edges_.begin(), edges_.end(), edge), edges_.end());

    auto it = adjacencyList_.find(edge->getSource());
    if (it != adjacencyList_.end()) {
        auto& adjEdges = *(it->second);
        adjEdges.erase(std::remove(adjEdges.begin(), adjEdges.end(), edge), adjEdges.end());
    }

    delete edge;
}

// ������ ������ ���� ���������� ������ ���������� ������ ���������� ����
// ���� ���� �� ������, �� ����� ����� ������ �� ����� ��������� �������

// ����� ������ ����������� ���� (��������)
std::vector<Node*> Graph::DijkstraShortestPath(Node* source, Node* destination) {
    std::map<Node*, double> distance;
    std::map<Node*, Node*> previous;

    for (Node* node : nodes_) {
        distance[node] = INT_MAX;
    }
    distance[source] = 0.0;
    std::queue<Node*> queue;
    queue.push(source);

    while (!queue.empty()) {
        Node* u = queue.front();
        queue.pop();
        if (adjacencyList_.count(u)) {
            for (Edge* edge : *(adjacencyList_[u])) {
                Node* v = edge->getDestination();
                double alt = distance[u] + edge->getWeight();

                if (alt < distance[v]) {
                    distance[v] = alt;
                    previous[v] = u;
                    queue.push(v);
                }
            }
        }
    }

    std::vector<Node*> path;
    Node* current = destination;
    while (previous.count(current)) {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());

    return path;
}

// ����� ������ ����������� ���� (A-star)
std::vector<Node*> Graph::AStarShortestPath(Node* source, Node* destination) {
    std::vector<Node*> path;
    std::map<Node*, double> distance;
    std::map<Node*, Node*> previous;
    std::vector<Node*> unvisited;

    for (Node* node : nodes_) {
        distance[node] = INT_MAX;
        unvisited.push_back(node);
    }
    distance[source] = 0.0;

    while (!unvisited.empty()) {
        Node* u = nullptr;
        double minDistance = INT_MAX;

        for (Node* node : unvisited) {
            if (distance[node] < minDistance) {
                u = node;
                minDistance = distance[node];
            }
        }
        if (!u || u == destination) break;
        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), u), unvisited.end());

        if (adjacencyList_.count(u)) {
            for (Edge* edge : *(adjacencyList_[u])) {
                Node* v = edge->getDestination();
                double alt = distance[u] + edge->getWeight();

                if (alt < distance[v]) {
                    distance[v] = alt;
                    previous[v] = u;
                }
            }
        }
    }

    Node* current = destination;
    while (previous.count(current)) {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());

    return path;
}

// ����� ������ ����������� ���� (BFS)
std::vector<Node*> Graph::BFS(Node* source, Node* destination) {
    std::queue<Node*> queue;
    std::map<Node*, bool> visited;
    std::map<Node*, Node*> previous;
    queue.push(source);
    visited[source] = true;

    while (!queue.empty()) {
        Node* u = queue.front();
        queue.pop();
        if (u == destination) {
            break;
        }

        if (adjacencyList_.count(u)) {
            for (Edge* edge : *(adjacencyList_[u])) {
                Node* v = edge->getDestination();

                if (!visited.count(v)) {
                    queue.push(v);
                    visited[v] = true;
                    previous[v] = u;
                }
            }
        }
    }

    std::vector<Node*> path;
    Node* current = destination;
    while (previous.count(current)) {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());

    return path;
}

// Equal_range �����, ������������ ������ ���� � ��������� �����
std::vector<Edge*> Graph::EqualRangeEdges(int weight) {
    // ���������� ������ ���� �� ���� (����������� ����������)
    int n = edges_.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (edges_[j]->getWeight() > edges_[j + 1]->getWeight()) {
                // ������ ������� ����
                Edge* temp = edges_[j];
                edges_[j] = edges_[j + 1];
                edges_[j + 1] = temp;
            }
        }
    }

    // ����� ���� � ����������� �����
    std::vector<Edge*> matchingEdges;
    for (Edge* edge : edges_) {
        if (edge->getWeight() == weight) {
            matchingEdges.push_back(edge);
        }
    }

    return matchingEdges;
}

// Set_Intersection ����� ���������� ������ ������, ������� ���������� ��� � ������, ��� � �� ������ ������ ������
std::vector<Node*> Graph::SetIntersectionNodes(const std::vector<Node*>& nodes1, const std::vector<Node*>& nodes2) {
    std::vector<Node*> intersectionNodes;

    for (Node* node1 : nodes1) {
        for (Node* node2 : nodes2) {
            if (node1 == node2) {
                intersectionNodes.push_back(node1);
                break; // �� ����� ����������� ��� ����� �����, ��������� � ���������� ����� �� nodes1
            }
        }
    }
    return intersectionNodes;
}