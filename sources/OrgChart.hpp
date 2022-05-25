#include <string>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

namespace ariel{

    class Node{
     public:
        Node* parent;
        vector<Node*> children;
        string name;
        Node(Node* prev, string person);
        Node();
        ~Node(){
            for(Node *node: children){
                delete node;
            }
        }
        Node(Node& n) = default;
        Node(Node&& n) = default;
        Node& operator=(Node&&) = default;
        Node& operator=(const Node& n) = default;
        
        friend ostream& operator<<(ostream &out, const Node &node);        
    };


    class OrgChart{


    class iterator{
    private:
        vector<Node*> list;
        size_t curIndex;
        Node* cur;
        void init_level_order(Node* head);
        void init_reverse_level_order(Node* head);
        void init_preorder(Node* head);

    public:
        iterator();
        iterator(Node* head, int flag);
        bool operator!=(const iterator &it) const;
        bool operator==(const iterator &it) const;

        string *operator->() const;
        string &operator*() const;

        OrgChart::iterator &operator++();
        OrgChart::iterator operator++(int);
        
    };

    private:
        
    public:
        OrgChart();
        ~OrgChart(){
            delete this->head;
        }

        OrgChart(OrgChart& org) = default;
        OrgChart(OrgChart&& org) = default;
        OrgChart& operator=(OrgChart&&) = default;
        OrgChart& operator=(const OrgChart& org) = default;
        
        vector<Node*> organization;
        Node* head;

        OrgChart& add_root(const string &root);
        OrgChart& add_sub(const string &person1, const string &person2);
        iterator begin() const;
        static iterator end();

        iterator begin_level_order() const;
        iterator end_level_order() const;
        iterator begin_reverse_order() const;
        iterator reverse_order() const;
        iterator end_reverse_order() const;
        iterator begin_preorder() const;
        iterator end_preorder() const;

        Node* search(Node* head, const string &person);
        string get_root() const;
        

        friend ostream& operator<<(ostream &out, const OrgChart &chart);
        static void printChart(Node* head, string tab);

    };
    
    
}