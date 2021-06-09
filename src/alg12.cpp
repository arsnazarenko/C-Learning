#include <iostream>
#include <map>
#include <vector>

struct node {
    bool is_free;
    int64_t left;
    int64_t right;
    node* prev;
    node* next;
    node(bool isFree, int64_t left, int64_t right, node *prev, node *next)
            : is_free(isFree), left(left), right(right), prev(prev), next(next) {
        if (next) {
            next->prev = this;
        }
        if (prev) {
            prev->next = this;
        }
    }
};

using nodes_tree = std::multimap<int64_t, node*>;


node* erase_from_free(int64_t left, int64_t right, nodes_tree& free_nodes) {
    auto range = free_nodes.equal_range(right - left);
    node* del_node_ptr = nullptr;
    auto del_node_it = free_nodes.end();
    for (auto i = range.first; i != range.second; ++i) {
        if (i->second->left == left && i->second->right == right) {
            del_node_it = i;
            break;
        }
    }
    if (del_node_it != free_nodes.end()) {
        del_node_ptr = del_node_it->second;
        free_nodes.erase(del_node_it);
    }
    return del_node_ptr;
}

void merge_with_next(node* node_ptr, nodes_tree& free_nodes) {
    node* delete_node = erase_from_free(node_ptr->next->left, node_ptr->next->right, free_nodes);
    if (delete_node!= nullptr) {
        node_ptr->right = node_ptr->next->right;
        node_ptr->next = node_ptr->next->next;
        if (node_ptr->next) {
            node_ptr->next->prev = node_ptr;
        }
        delete delete_node;
    }
}
void merge_with_prev(node* node_ptr, nodes_tree& free_nodes) {
    //fixme: free_nodes.erase({node_ptr->prev->left, node_ptr->prev->right});
    node* delete_node = erase_from_free(node_ptr->prev->left, node_ptr->prev->right, free_nodes);
    //  delete from free_nodes
    if (delete_node != nullptr) {
        node_ptr->left = node_ptr->prev->left;
        node_ptr->prev = node_ptr->prev->prev;
        if (node_ptr->prev) {
            node_ptr->prev->next = node_ptr;
        }
        delete delete_node;
    }
}

void h_free(node* node_ptr, nodes_tree& free_nodes) {
    if (node_ptr != nullptr) {
        node_ptr->is_free = true;
        if (node_ptr->next && node_ptr->next->is_free) {
            merge_with_next(node_ptr, free_nodes);
        }
        if (node_ptr->prev && node_ptr->prev->is_free) {
            merge_with_prev(node_ptr, free_nodes);
        }
        //  add ro free nodes tree
        free_nodes.insert({node_ptr->right - node_ptr->left, node_ptr});
    }
}

void h_malloc(int64_t size, nodes_tree& nodes, std::vector<node*>& reqs, int64_t j) {
    if (!nodes.empty() && ((nodes.rbegin()->second -> right - nodes.rbegin()->second -> left) >= size)) {
        node* old = erase_from_free(nodes.rbegin()->second->left, nodes.rbegin()->second->right, nodes);
        if ((old->right - old->left) == size) {
            old->is_free = false;
            reqs[j] = old;
        } else {
            node* new_node = new node(false, old->left, old->left + size, old->prev, old);
            old->left = new_node->right;
            nodes.insert({old->right - old->left, old});
            reqs[j] = new_node;
        }
    } else {
        reqs[j] = nullptr;
    }
}
int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.precision(20);
    int64_t n;
    int64_t m;
    std::cin >> n >> m;
    nodes_tree free_nodes;
    std::vector<node*> reqs(m + 1);
    free_nodes.insert({n, new node(true, 1, n+1, nullptr, nullptr)});
    for (int64_t i = 1; i <= m; ++i) {
        int64_t req;
        std::cin >> req;
        if (req < 0) {
            h_free(reqs[std::abs(req)], free_nodes);
        } else {
            h_malloc(req, free_nodes, reqs, i);
            std::cout << (reqs[i] == nullptr ? -1 : reqs[i]->left) << "\n";
        }
    }
    return 0;
}