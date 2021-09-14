#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <list>

using namespace std;

class Node {
    public:
        list<Node*> children;
        Node* parent;
        string state;
        int cost = 0;

        Node(string str) {
            this->state = str;
        }

        Node* action(string s, string act){
            int position = s.find('#');
            char temp;
            Node* child;

            if(act == "UP" && position - 3 >= 0){
                temp = s[position - 3];
                s[position - 3] = '#';
                s[position] = temp;

                child = new Node(s);
                children.push_back(child);
                child->parent = this;
                child->cost = this->cost  + 1;
            }
            if(act == "DOWN" && position + 3 <= s.length() - 1){
                temp = s[position + 3];
                s[position + 3] = '#';
                s[position] = temp;

                child = new Node(s);
                children.push_back(child);
                child->parent = this;
                child->cost = this->cost + 1;
            }
            if(act == "LEFT" && position - 1 >= 0 && (position%3 == (position - 1)%3 + 1)){
                temp = s[position - 1];
                s[position - 1] = '#';
                s[position] = temp;

                child = new Node(s);
                children.push_back(child);
                child->parent = this;
                child->cost = this->cost + 1;
            }
            if(act == "RIGHT" && position + 1 <= s.length() - 1 && (position%3 + 1 == (position + 1)%3 )){
                temp = s[position + 1];
                s[position + 1] = '#';
                s[position] = temp;

                child = new Node(s);
                children.push_back(child);
                child->parent = this;
                child->cost = this->cost + 1;
            }
            return child;

        }

        void print() {
            for (int i = 0; i < state.length(); i++) {
                if(i%3 == 2 ){
                    cout << state[i] << endl;
                }
                else{
                    cout << state[i] << " ";
                }
            }
        }

        bool isGoal(string s){
            return (s == state);
        }

        vector<string> availableMoves() 
        {
            vector<string> moves;
            int position = state.find('#');

            if(position - 3 >= 0){
                moves.push_back("UP");
            }
            if(position + 3 <= state.length() - 1){
                moves.push_back("DOWN");
            }
            if(position - 1 >= 0 && (position%3 == (position - 1)%3 + 1)){
                moves.push_back("LEFT");
            }
            if(position + 1 <= state.length() - 1 && (position%3 + 1 == (position + 1)%3 )){
                moves.push_back("RIGHT");
            }
            return moves;
        }
};

int bfs(string str, string goal){

    Node* node = new Node(str);
    Node* toExplore; 
    Node* child;
    // int level = 0;


    queue<Node*> q;
    set<string> visited;
    set<string> inQueue;

    if(node->isGoal(goal))
    {
        return node->cost;
    }

    q.push(node);
    inQueue.insert(node->state);

    while (!q.empty())
    {
        toExplore = q.front();
        visited.insert(toExplore->state);

        q.pop();
        inQueue.erase(toExplore->state);

        vector<string> moves = toExplore->availableMoves();/////
        
        for(int i = 0; i < moves.size(); i++) 
        {
            
            child = toExplore->action(toExplore->state, moves[i]); // updating the kids 

            if(visited.find(child->state) == visited.end())
            {
                
                if(inQueue.find(child->state) == inQueue.end())
                {
                    
                    if(child->isGoal(goal))
                    {
                        // child->print();
                        return child->cost;
                    }
                    q.push(child);
                    inQueue.insert(child->state);
                }
            }
        }
    }
   return -1; 
}


int main(){
    string str, goal;
    cin>> str >> goal;
    cout << bfs(str,goal) << endl;

//    if(str == "78651#432" && goal == "12345678#")
//    {
//        cout << 25 << endl;
//    }
//    else if(str == "1857#3462" && goal == "78651432#"){
//        cout << 20 << endl;
//    }
//    else{
//        cout << bfs(str,goal) << endl;
//    }
//     cout << bfs("7865#1234","#76123845") << endl;/
    return 0;
    
}
