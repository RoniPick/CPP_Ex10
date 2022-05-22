#include "OrgChart.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <queue>
#include <stack>

using namespace std;

namespace ariel{

        OrgChart::iterator::iterator(){
            this->curIndex = 0;
           // this->list = vector<Node*>(); //creeating new vector
            this->cur =nullptr;
            
        }

        OrgChart::iterator::iterator(Node* head, int flag){
            if(head == nullptr){
                throw invalid_argument("Head is NULL");
            }

            this->curIndex = 0;
            this->cur = head;
            //this->list = vector<Node*>(); //creeating new vector
            
            //lEVEL ORDER
            if(flag == 0){ 
              init_level_order(head);
            }

            //REVERSE lEVEL ORDER
            else if(flag == 1){
                init_reverse_level_order(head); 
            }

            //PREORDER
            else if(flag == 2){ 
                init_preorder(head);
            }
        }
        

        //flag = 0
        void OrgChart::iterator::init_level_order(Node* head){
            if(head == nullptr)
                throw invalid_argument("Empty tree");
            
            // Create an empty queue
            queue<Node*> q;
            
            // Enqueue head 
            q.push(head);
            
            while (!q.empty()){
                // Adding front of queue to the vector and remove it from queue
                Node* node = q.front();
                this->list.push_back(node);
                q.pop();
                    
                for(size_t i=0; i<node->children.size(); i++){
                    q.push(node->children[i]);
                }
            }
            Node* temp = nullptr;
        }

        //flag = 1
        void OrgChart::iterator::init_reverse_level_order(Node* head){
            if(head == nullptr)
                throw invalid_argument("Empty tree");
                    
            stack<Node*> s;
            queue<Node*> q;
            q.push(head);

            while (q.empty() == false){
                // Dequeue node and make it root 
                Node* node = q.front();
                q.pop();
                s.push(node);

                //adding the childrens from right to left
                for(int i=(node->children.size()-1); i >= 0; i--){
                        q.push(node->children[(size_t)i]);
                    }
                
            }
        
            // Removing all the items from stack and adding them to the list
            while(s.empty() == false){
                Node* node = s.top();
                this->list.push_back(node);
                s.pop();
            }

        }

        //flag = 2
        void OrgChart::iterator::init_preorder(Node* head){
            if(head == nullptr)
                throw invalid_argument("Empty tree");
        
            // create an empty stack and push the root node
            stack<Node*> stack;
            stack.push(head);
        
            // loop till stack is empty
            while (!stack.empty()){
                // pop a node from the stack and adding the it to the list
                Node* node = stack.top();
                stack.pop();
                this->list.push_back(node);
        
                //adding the childrens from right to left
                for(int i=(node->children.size()-1); i >= 0; i--){
                        stack.push(node->children[(size_t)i]);
                    }
                }
        }
            

        bool OrgChart::iterator::operator!=(const iterator &it) const{
            return !(it.cur == this->cur);
        }

        bool OrgChart::iterator::operator==(const iterator &it) const{
            return it.cur == this->cur;
        }

        //returning the current node
        string* OrgChart::iterator::operator->() const{
            return &(this->list[curIndex]->name);
        }

        //returning a pointer to the current node
        string& OrgChart::iterator::operator*() const{
            return this->list[curIndex]->name;
        }

        //adding 1 directed to the index
        OrgChart::iterator& OrgChart::iterator::operator++(){
            if(this->curIndex+1 == this->list.size()){
                this->cur=nullptr;
                return *this;
            }
            this->curIndex++;
            this->cur = this->list[curIndex];
            return *this;
        }

        /*
            Creating a copy of the Orgchart, incoming the current Orgchart by 1
            and returning the copy of the Orgchart we created
        */
        OrgChart::iterator OrgChart::iterator::operator++(int){
            iterator ch = *this;
            ++(*this);
            return ch;
        }
        
        Node::Node(){

        }

        Node::Node(Node* prev, string person){
            this->parent = prev;
            this->name = person;
            this->children = vector<Node*>();

        }

        OrgChart::OrgChart(){
            this->head = NULL;
            this->organization.resize(0);
        }

        OrgChart& OrgChart::add_root(string root){
            if(root == ""){
                throw invalid_argument("Invalid name");
            }
            if(this->head == NULL){
                this->head = new Node(nullptr, root);
                this->head->parent = nullptr;
                this->organization.push_back(head);
            }

            else{
                this->head->name = root;
            }
            return *this;
        }

        OrgChart& OrgChart::add_sub(string person1, string person2){
            if(this->organization.empty()){
                throw invalid_argument("The list is empty");
            }
            if(person1 == "" || person2 == ""){
                throw invalid_argument("Invalid name");
            }

            Node* ans = search(this->head, person1);
            if(ans == nullptr){
                throw invalid_argument("Worker doesn't exist");
            }

            //creating new node
            Node* child = new Node(ans, person2);
            //adding the new node into the person1 list of children
            ans->children.push_back(child);
            return *this;
        }

        /*
            A function that help to find the node, if it doesn't exist it will return null
            else it will return the pointer to the node
        */
        Node* OrgChart::search(Node* head, string person){
            if(head->name == person){
                return head;
            }

            if(head->children.empty()){
                return nullptr;
            }
            
            for(size_t i=0; i<head->children.size(); i++){
                Node* ans = search(head->children[i], person);
                if(ans!=nullptr){
                    return ans;
                } 
            }

            return nullptr;
        }

        OrgChart::iterator OrgChart::begin(){
            return iterator(this->head, 0);
        }

        OrgChart::iterator OrgChart::end(){
            return iterator();
        }

        /*
        For this function we use the init_level_order function by creating a new
        iterator with flag = 0
        */
        OrgChart::iterator OrgChart::begin_level_order(){
            return iterator(this->head, 0);
        }

        OrgChart::iterator OrgChart::end_level_order(){
            if(this->head == nullptr){
                throw invalid_argument("Empty tree");
            }
            return iterator();
        }

        /*
        For this function we use the init_reverse_level_order function by creating a new
        iterator with flag = 1
        */
        OrgChart::iterator OrgChart::begin_reverse_order(){
           return iterator(this->head, 1);
        }

        OrgChart::iterator OrgChart::end_reverse_order(){
            if(this->head == nullptr){
                throw invalid_argument("Empty tree");
            }
            return iterator();
        }
        
        OrgChart::iterator OrgChart::reverse_order(){
            if(this->head == nullptr){
                throw invalid_argument("Empty tree");
            }
            return iterator();
        }

        /*
        For this function we use the init_preorder function by creating a new iterator 
        with flag = 2
        */
        OrgChart::iterator OrgChart::begin_preorder(){
            return iterator(this->head, 2);
        }

        OrgChart::iterator OrgChart::end_preorder(){
            if(this->head == nullptr){
                throw invalid_argument("Empty tree");
            }
            return iterator();
        }

        string OrgChart::get_root(){
            return this->head->name;
        }

        // Output function for the node
        ostream& operator<<(ostream &out, const Node &node){
            out << node.name;
            return out;
        }

        // Output function for the organization
        ostream& operator<<(ostream &out, const OrgChart &chart){
            queue<Node*> q;
            q.push(chart.head);
            
            while (q.empty() == false){
                // Adding front of queue to the vector and remove it from queue
                Node* node = q.front();
                out << node->name;
                out << ' ';
                q.pop();
                    
                for(int i=0; i<node->children.size(); i++){
                    q.push(node->children[(size_t)i]);
                }
            }

            return out;
        }
}