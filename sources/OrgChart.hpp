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
        // ~OrgChart();
        vector<Node*> organization;
        Node* head;

        OrgChart& add_root(string root);
        OrgChart& add_sub(string person1, string person2);
        iterator begin();
        iterator end();

        iterator begin_level_order();
        iterator end_level_order();
        iterator begin_reverse_order();
        iterator reverse_order();
        iterator end_reverse_order();
        iterator begin_preorder();
        iterator end_preorder();

        Node* search(Node* head, string person);
        string get_root();
        

        friend ostream& operator<<(ostream &out, const OrgChart &chart);


    };
    
    
}