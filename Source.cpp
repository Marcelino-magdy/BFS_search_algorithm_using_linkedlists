#pragma warning(disable : 4996)


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <cstring>

using namespace std;



// the structure and implementation of a visited stack for the visited cities 



struct Visited_Node {
    char Name[15];
    struct Visited_Node* next;
};

struct Visited_Node* Head = NULL;
struct Visited_Node* Last = NULL;



void push_Visited(char* value) {

    struct Visited_Node* newNode = (struct Visited_Node*)malloc(sizeof(struct Visited_Node));

    if (newNode) {



        if (!Last) {


            strcpy(newNode->Name, value);
            Head = newNode;
            Last = newNode;
            newNode->next = Head;
        }
        else {

            newNode->next = Head;
            Last->next = newNode;
            Last = newNode;


            strcpy(newNode->Name, value);


        }
        cout << value   << " pushed to visited stack : "  << Last->Name << "\n";
    }
}

bool check_Visited(char* value) {

    cout << "value entered to be checked : " << value << "\n";
    struct Visited_Node* checkNode = (struct Visited_Node*)malloc(sizeof(struct Visited_Node));
    checkNode = Head;
    if (checkNode == NULL) {
        cout << value << " Not visisted in stack" << endl;
        return false;
    }
    else {
        do {
            if (string(checkNode->Name) == string(value)) {
                return true;
            }
            else {
                checkNode = checkNode->next;
            }
        } while (checkNode != Head);
        return false;

    }

}



struct Path_Node {
    char city_name[15];
    struct Path_Node* next;
};


void Path_push(Path_Node*& start, char* value) {
    cout << "values pushed in path : "  << value << " addr : " << start << "\n";
    struct Path_Node* newNode = (struct Path_Node*)malloc(sizeof(struct Path_Node));


    if (newNode) {
        if (!start) {
            strcpy(newNode->city_name, value);
            newNode->next = NULL;
            start = newNode;
            cout << "values added in first node : "  << start->city_name << " next addr : " << start->next << "\n";
        }
        else {
            cout << "added node to the start : " << value << " addr : " << start << "\n";
            strcpy(newNode->city_name, value);
            newNode->next = start;
            start = newNode;
        }
    }
    cout << "out of path push added values : " << value << " addr : " << start << "\n";
}


//void copy_path(Path_Node* old_start, Path_Node* updated_start) {
//    while (old_start->next != NULL) {
//        updated_start->
//    }
//}



// the structure and implementation of a visited stack for the visited cities 



struct Queue_Node {
    struct Path_Node* start = NULL;
    int total_cost;
    struct Queue_Node* next;
};


struct Queue_Node* Queue_Head = NULL;

struct Queue_Node* Queue_Last = NULL;


void push_Queue(Queue_Node* queue_node, char* value, int city_cost) {
    cout << "values passed in push queue : "  << value << " cost : " << city_cost << "\n";
    struct Queue_Node* newNode = (struct Queue_Node*)malloc(sizeof(struct Queue_Node));

    if (newNode) {


        if (!Queue_Last) {


            cout << "Queue is empty, this is first value : "  << value << " cost : " << city_cost << "\n";
            
            
            if (city_cost == 0) {
                newNode->total_cost = city_cost;
                newNode->start = NULL;
                Path_push(newNode->start, value);
            }
            else {
                newNode->total_cost = queue_node->total_cost + city_cost;
                newNode->start = queue_node->start;
                Path_push(newNode->start, value);
            }
            Queue_Head = newNode;
            Queue_Last = newNode;
            newNode->next = NULL;




            cout << "value added in empty queue is : " << Queue_Last->start->city_name << " with cost : " << Queue_Last->total_cost << "\n";
            cout << " out of first queue value " << "\n";
        }
        else {

            cout << "Queue have values, this value is being added : " << value << " cost : " << city_cost << "\n";
            newNode->total_cost = queue_node->total_cost + city_cost;
            newNode->start = queue_node->start;
            Path_push(newNode->start, value);
            newNode->next = NULL;
            Queue_Last->next = newNode;
            Queue_Last = newNode;
            cout << "value added to end of queue : " << Queue_Last->start->city_name << " cost : " << Queue_Last->total_cost << "\n";


        }
    }
}


Queue_Node* pop_Queue() {
    struct Queue_Node* queue_node = (struct Queue_Node*)malloc(sizeof(struct Queue_Node));
    if (Queue_Head != NULL) {
        queue_node = Queue_Head;
        if (Queue_Head->next == NULL) {
            Queue_Head = NULL;
            Queue_Last = NULL;
            return queue_node;
        }
        Queue_Head = Queue_Head->next;
        return queue_node;
    }

}



void print_path(Queue_Node* goal_node) {
    do{
        cout << string(goal_node->start->city_name) << " then ";
        goal_node->start = goal_node->start->next;
    }while (goal_node->start->next != NULL);
}



void BFS(unordered_map<string, unordered_map<string, int> > graph, char* root, char* goal) {

    cout << "values entered in bfs : " << "root : " << root << " goal : " << goal << "\n";
    if (string(root) == string(goal)) {
        cout << root << "is the choosen goal" << endl;
    }
    else {
        struct Queue_Node* newNode = (struct Queue_Node*)malloc(sizeof(struct Queue_Node));
        push_Queue(newNode, root, 0);






        do {
            cout << "values in bfs while loop: " << "root : " << root << "goal : " << goal << "\n";
            struct Queue_Node* current_node = (struct Queue_Node*)malloc(sizeof(struct Queue_Node));
            current_node = pop_Queue();
            cout << "value of current poped node from queue : " << current_node->start->city_name << "\n";

            string current_city = string(current_node->start->city_name);

            if (current_city == string(goal)) {
                cout << "goal reached : ";
                print_path(current_node);
                break;
            }

            if (!check_Visited(current_node->start->city_name)) {

                cout << current_node->start->city_name  << " is Not visited yet" << "\n";

                push_Visited(current_node->start->city_name);
                string current_city = string(current_node->start->city_name);

                unordered_map<string, unordered_map<string, int> >::iterator itr;
                unordered_map<string, int> sub_map;

                for (itr = graph.begin(); itr != graph.end(); ++itr) {
                    if (itr->first == current_city) {
                        sub_map = itr->second;
                    }
                }

                unordered_map<string, int>::iterator sub_itr;


                for (sub_itr = sub_map.begin(); sub_itr != sub_map.end(); ++sub_itr) {

                    const int length = sub_itr->first.length();
                    char* char_array = new char[length + 1];
                    strcpy(char_array, sub_itr->first.c_str());
                    push_Queue(current_node, char_array, sub_itr->second);
                }
            }

            cout << " run ends - end of bfs while : " << Queue_Head->next;

        } while (Queue_Head->next != NULL);

    }





}


//
//
//
//void push_Visited(string value) {
//    struct Visited_Node* newNode = (struct Visited_Node*)malloc(sizeof(struct Visited_Node));
//    newNode->Name = value;
//    if (!Head) {
//
//        Head = newNode;
//
//        newNode->next = NULL;
//    }
//    else {
//        struct Visited_Node* current = Head;
//
//        while (current->next != Head) {
//            current = current->next;
//
//        }
//
//        newNode->next = Head;
//        current->next = newNode;
//
//        Head = newNode;
//
//    }
//
//}





int main()
{

    unordered_map<string, unordered_map<string, int> > graph = {

        {"Arad",
            {   {"Zerind", 75}, {"Sibiu" , 140}, {"Timisoara" , 118}    }
        },
        {"Zerind",
            {   {"Arad", 75}, {"Oradea" , 71}   }
        },
        {"Oradea",
            {   {"Zerind", 71}, {"Sibiu" , 151} }
        },
        {"Sibiu",
            {   {"Arad", 140}, {"Oradea" , 151}, {"Fagaras" , 99},{"Rimnicu" , 80}  }
        },
        {"Timisoara",
            {   {"Arad", 118}, {"Lugoj" , 111}  }
        },
        {"Lugoj",
            {   {"Timisoara", 111}, {"Mehadia" , 70}    }
        },
        {"Mehadia",
            {   {"Lugoj", 70}, {"Drobeta" , 75}   }
        },
        {"Drobeta",
            {   {"Mehadia", 75}, {"Craiova", 120}   }
        },
        {"Craiova",
            {   {"Drobeta", 120}, {"Rimnicu", 146}, {"Pitesti" , 138}   }
        },
        {"Rimnicu",
            {   {"Sibiu", 80}, {"Craiova", 146}, {"Pitesti" , 97}   }
        },
        {"Fagaras",
            {   {"Sibiu", 99}, {"Bucharest", 211}   }
        },
        {"Pitesti",
            {   {"Rimnicu", 97}, {"Craiova", 138}, {"Bucharest" , 101}  }
        },
        {"Bucharest",
            {   {"Fagaras", 211}, {"Pitesti", 101}, {"Giurgiu" , 90}, {"Urziceni" , 85}  }
        },
        {"Giurgiu",
            {   {"Bucharest", 90}   }
        },
        {"Urziceni",
            {   {"Bucharest", 85}, {"Vaslui", 142}, {"Hirsova" , 98}    }
        },
        {"Hirsova",
            {   {"Urziceni", 98}, {"Eforie", 86}    }
        },
        {"Eforie",
            {   {"Hirsova", 86}    }
        },
        {"Vaslui",
            {   {"Urziceni", 142}, {"Iasi", 92}    }
        },
        {"Iasi",
            {   {"Vaslui", 92}, {"Neamt", 87}   }
        },
        {"Neamt",
            {   {"Iasi", 87}    }
        }
    };


    /*char arr[] = "aaa";
    char www[] = "www";
    char qqq[] = "qqq";
    char uuu[] = "uuu";
    char sss[] = "ttt";
    push_Visited(arr);
    push_Visited(www);
    push_Visited(qqq);
    push_Visited(uuu);
    cout << check_Visited(sss) << endl;
    cout << check_Visited(uuu) << endl;*/


    char Root[15] = "Arad";
    char Goal[15] = "Fagaras";
    BFS(graph, Root, Goal);

}



