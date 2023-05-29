#pragma warning(disable : 4996)

// c++ program to search and find the shortest path between to given cities
//The App is concerned about finding a relatively perfect Path form a given starting city to another goal city by :
//
//Building a Breadth - first search algorithm(BFS) to find the fastest, 
//shortest path of all available path optionsand calculate the final distance(path cost),
//Regardless of the total cost of the chosen path compared to other alternatives.
//
//	By implementing linked listsand circular linked list concepts of stackand queue to store the cities to be processed in the frontierand 
//the already visited cities in the visited stack.

//unordered map used to store the dataset of the map of romania
//cstring and string to enable function like string() and strcpy() to copy values of char array

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <cstring>

using namespace std;






struct graph_Node* check_graph_Node(int index);



struct linked_cities {
    int index;
    struct linked_cities* next;
};

struct graph_Node {
    int index;
    char Name[15];
    struct linked_cities* lc_Head;
    struct linked_cities* lc_Rear;
    struct graph_Node* next;
};

struct graph_Node* Graph_front = NULL;
struct graph_Node* Graph_rear = NULL;



void push_edges(int vertex_city, int linked_city) {

    struct graph_Node* vertex_city_Node = (struct graph_Node*)malloc(sizeof(struct graph_Node));
    vertex_city_Node = check_graph_Node(vertex_city);
    cout << "city vertex : " << vertex_city_Node->Name << "\n";

    struct linked_cities* newNode = (struct linked_cities*)malloc(sizeof(struct linked_cities));

    if (newNode) {




        if (!vertex_city_Node->lc_Rear) {

            newNode->index = linked_city;
            vertex_city_Node->lc_Head = newNode;
            vertex_city_Node->lc_Rear = newNode;
            newNode->next = vertex_city_Node->lc_Head;

            cout << vertex_city_Node->Name << "city head after : " << vertex_city_Node->lc_Head << "\n";
            cout << vertex_city_Node->Name << "city rear after : " << vertex_city_Node->lc_Rear << "\n";
            cout << "city added : " << vertex_city << "<<" << vertex_city_Node->lc_Rear->index << "\n";
        }
        else {

            newNode->index = linked_city;
            newNode->next = vertex_city_Node->lc_Head;
            vertex_city_Node->lc_Rear->next = newNode;
            vertex_city_Node->lc_Rear = newNode;

            cout << vertex_city_Node->Name << "city head after : " << vertex_city_Node->lc_Head << "\n";
            cout << vertex_city_Node->Name << "city rear after : " << vertex_city_Node->lc_Rear << "\n";
            cout << "city added : " << vertex_city << "<<" << vertex_city_Node->lc_Rear->index << "\n";



        }
        cout << vertex_city_Node->lc_Head->index << "|| pushed to  city lists : " << vertex_city_Node->lc_Rear->index << "\n||\n";
    }
}






// pushes new cities to the visited cicular linked list

void push_graph_Node(int index, char* value) {

    struct graph_Node* newNode = (struct graph_Node*)malloc(sizeof(struct graph_Node));

    if (newNode) {




        if (!Graph_rear) {


            strcpy(newNode->Name, value);
            newNode->index = index;
            newNode->lc_Head = NULL;
            newNode->lc_Rear = NULL;

            Graph_front = newNode;
            Graph_rear = newNode;
            newNode->next = Graph_front;
        }
        else {

            newNode->index = index;
            newNode->lc_Head = NULL;
            newNode->lc_Rear = NULL;
            newNode->next = Graph_front;
            Graph_rear->next = newNode;
            Graph_rear = newNode;


            strcpy(newNode->Name, value);


        }
        cout << value << "|| pushed to country graph : " << Graph_rear->Name << "\n||\n";
    }
}

// check function to find if the city is already visited befrore

struct graph_Node* check_graph_Node(int index) {

    cout << "|| value entered to be checked if in grapg : " << index << "\n";
    struct graph_Node* checkNode = (struct graph_Node*)malloc(sizeof(struct graph_Node));
    checkNode = Graph_front;
    if (checkNode == NULL) {
        cout << index << " Not visisted in graph" << endl;

    }
    else {
        do {
            if (checkNode->index == index) {
                cout << index << " found " << endl;
                return checkNode;
            }
            else {
                checkNode = checkNode->next;
            }
        } while (checkNode != Graph_front);
        cout << "did not find the city in graph";

    }

}




// the structure and implementation of a visited stack for the visited cities 


struct Visited_Node {
    char Name[15];
    struct Visited_Node* next;
};

struct Visited_Node* Head = NULL;
struct Visited_Node* Last = NULL;

// pushes new cities to the visited cicular linked list

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
        cout << value   << "|| pushed to visited stack : "  << Last->Name << "\n||\n";
    }
}

// check function to find if the city is already visited befrore

bool check_Visited(char* value) {

    cout << "|| value entered to be checked : " << value << "\n";
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


//---------------------------------------------------------------------------------------------------------------------------------------------


// the structure and implementation of path stack for the visited cities before the current one 

//
struct Path_Node {
    char city_name[15];
    struct Path_Node* next;
};

// pushes new values to the linked list of the city node in queue

void Path_push(Path_Node*& start, char* value) {
    cout << "|| values pushed in path : "  << value << "\n";
    struct Path_Node* newNode = (struct Path_Node*)malloc(sizeof(struct Path_Node));


    if (newNode) {
        if (!start) {
            strcpy(newNode->city_name, value);
            newNode->next = NULL;
            start = newNode;
            cout << "|| values added in first node : "  << start->city_name <<  "\n";
        }
        else {
            cout << "|| added node to the start : " << value  << "\n";
            strcpy(newNode->city_name, value);
            newNode->next = start;
            start = newNode;
        }
    }
    cout << "|| out of path push added values : " << value << "\n";
}






// the structure and implementation of a queue for the cities to be verified. 



struct Queue_Node {
    struct Path_Node* start = NULL;
    int total_cost;
    struct Queue_Node* next;
};


struct Queue_Node* Queue_Head = NULL;

struct Queue_Node* Queue_Last = NULL;


void push_Queue(Queue_Node* queue_node, char* value, int city_cost) {
    cout << "\n|| values passed in push queue : city => "  << value << " and cost => " << city_cost << "\n";
    struct Queue_Node* newNode = (struct Queue_Node*)malloc(sizeof(struct Queue_Node));

    if (newNode) {


        if (!Queue_Last) {


            cout << "|| Queue is empty, this is a first element : city => "  << value << " and cost => " << city_cost << "\n";
            
            
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




            cout << "|| value added in empty queue is : value => " << Queue_Last->start->city_name << " with cost => " << Queue_Last->total_cost << "\n";
            cout << "|| out of first queue element \n||\n";
        }
        else {

            cout << "|| Queue have values, this value is being added : city => " << value << " with cost => " << city_cost << "\n";
            newNode->total_cost = queue_node->total_cost + city_cost;
            newNode->start = queue_node->start;
            Path_push(newNode->start, value);
            newNode->next = NULL;
            Queue_Last->next = newNode;
            Queue_Last = newNode;
            cout << "|| value added to end of queue : city => " << Queue_Last->start->city_name << " with cost => " << Queue_Last->total_cost << "\n||\n";


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
    cout << string(goal_node->start->city_name);
    do{
        cout << " ===>> ";
        goal_node->start = goal_node->start->next;
        cout << string(goal_node->start->city_name);
    }while (goal_node->start->next != NULL);
    cout << "\n||\n||\n||       ---------------------------------------------------------------------------------------------------  \n\n\n\n";
}



//void BFS(unordered_map<string, unordered_map<string, int> > graph, char* goal, char* root) {
//
//    cout << "\n\n\n|| Displaying Program LOG... : \n||\n"
//        << "|| Processing retrieved Data to find the shortest Path from : " << goal
//        << " TO " << root;
//
//
//    cout << "|| values entered in BFS : " << "root => " << goal << " goal => " << root << "\n";
//    if (string(root) == string(goal)) {
//        cout << root << "is the choosen goal" << endl;
//    }
//    else {
//        struct Queue_Node* newNode = (struct Queue_Node*)malloc(sizeof(struct Queue_Node));
//        push_Queue(newNode, root, 0);
//
//
//
//
//
//
//        do {
//            struct Queue_Node* current_node = (struct Queue_Node*)malloc(sizeof(struct Queue_Node));
//            current_node = pop_Queue();
//            cout << "|| value of current poped node from queue : " << current_node->start->city_name << "\n";
//
//            string current_city = string(current_node->start->city_name);
//
//            if (current_city == string(goal)) {
//                cout << "\n||\n||\n||\n||   ---------------------------------------------------------------------------------------------------    \n||\n||\n"
//                    << "||     ===>>    goal reached : ";
//                print_path(current_node);
//                break;
//            }
//
//            if (!check_Visited(current_node->start->city_name)) {
//
//                cout << "|| " << current_node->start->city_name << " is Not visited yet." << "\n";
//
//                push_Visited(current_node->start->city_name);
//                string current_city = string(current_node->start->city_name);
//
//                unordered_map<string, unordered_map<string, int> >::iterator itr;
//                unordered_map<string, int> sub_map;
//
//                for (itr = graph.begin(); itr != graph.end(); ++itr) {
//                    if (itr->first == current_city) {
//                        sub_map = itr->second;
//                    }
//                }
//
//                unordered_map<string, int>::iterator sub_itr;
//
//
//                for (sub_itr = sub_map.begin(); sub_itr != sub_map.end(); ++sub_itr) {
//
//                    const int length = sub_itr->first.length();
//                    char* char_array = new char[length + 1];
//                    strcpy(char_array, sub_itr->first.c_str());
//                    push_Queue(current_node, char_array, sub_itr->second);
//                }
//            }
//
//            cout << "|| run ends - end of one LOOP. \n"
//                << "|| another one is waiting to run \n||\n";
//
//        } while (Queue_Head->next != NULL);
//
//    }
//
//
//
//
//
//}






void BFS(graph_Node*& graph_front, char* goal, char* root) {

    cout << "\n\n\n|| Displaying Program LOG... : \n||\n"
        << "|| Processing retrieved Data to find the shortest Path from : " << goal
        << " TO " << root;


    cout << "|| values entered in BFS : " << "root => " << goal << " goal => " << root << "\n";
    if (string(root) == string(goal)) {
        cout << root << "is the choosen goal" << endl;
    }
    else {
        struct Queue_Node* newNode = (struct Queue_Node*)malloc(sizeof(struct Queue_Node));
        push_Queue(newNode, root, 0);






        do {
            struct Queue_Node* current_node = (struct Queue_Node*)malloc(sizeof(struct Queue_Node));
            current_node = pop_Queue();
            cout << "|| value of current poped node from queue : " << current_node->start->city_name << "\n";

            string current_city = string(current_node->start->city_name);

            if (current_city == string(goal)) {
                cout << "\n||\n||\n||\n||   ---------------------------------------------------------------------------------------------------    \n||\n||\n"
                    << "||     ===>>    goal reached : ";
                print_path(current_node);
                break;
            }

            if (!check_Visited(current_node->start->city_name)) {

                cout << "|| " << current_node->start->city_name << " is Not visited yet." << "\n";

                push_Visited(current_node->start->city_name);
                string current_city = string(current_node->start->city_name);

                struct graph_Node* GHead_cp = (struct graph_Node*)malloc(sizeof(struct graph_Node));
                GHead_cp = graph_front;
                    if (!GHead_cp) {
                    cout << "|| warnning:  =>  the graph is empty: you missed to enter the data\n";
                    }
                    else {
                        while (current_city != string(GHead_cp->Name)) {
                            GHead_cp = GHead_cp->next;
                            cout << "searching gor : " << current_city << "\n";
                        }
                        cout << "found : " << current_city << "\n";
                        cout << "found in : " << GHead_cp->Name << "\n";
                        struct linked_cities* newNode_index = (struct linked_cities*)malloc(sizeof(struct linked_cities));
                        newNode_index = GHead_cp->lc_Head;
                        cout << "searching for successors of : " << newNode_index << "\n";

                        do {
                            cout << "searching for successors of : " << current_city << "\n";
                            int city_index = newNode_index->index;
                            cout << "found this index : " << city_index << "\n";
                            struct graph_Node* vertex_city_Node = check_graph_Node(city_index);

                            cout << "city in index : " << vertex_city_Node->Name << "\n";

                            push_Queue(current_node, vertex_city_Node->Name,1);
                            newNode_index = newNode_index->next;
                        } while (newNode_index != GHead_cp->lc_Head);
                    }

                /*unordered_map<string, unordered_map<string, int> >::iterator itr;
                unordered_map<string, int> sub_map;

                for (itr = graph.begin(); itr != graph.end(); ++itr) {
                    if (itr->first == current_city) {
                        sub_map = itr->second;
                    }
                }*/

                /*unordered_map<string, int>::iterator sub_itr;


                for (sub_itr = sub_map.begin(); sub_itr != sub_map.end(); ++sub_itr) {

                    const int length = sub_itr->first.length();
                    char* char_array = new char[length + 1];
                    strcpy(char_array, sub_itr->first.c_str());
                    push_Queue(current_node, char_array, sub_itr->second);
                }*/
            }

            cout << "|| run ends - end of one LOOP. \n"
                << "|| another one is waiting to run \n||\n";

        } while (Queue_Head->next != NULL);

    }





}




void auto_Graph() {
    char city1[] = "Arad";
    push_graph_Node(1,city1);
    push_edges(1, 2);
    push_edges(1,4);
    push_edges(1, 5);

    char city2[] = "Zerind";
    push_graph_Node(2, city2);
    push_edges(2, 1);
    push_edges(2, 3);

    char city3[] = "Oradea";
    push_graph_Node(3, city3);
    push_edges(3, 2);
    push_edges(3, 4);

    char city4[] = "Sibiu";
    push_graph_Node(4, city4);
    push_edges(4, 1);
    push_edges(4, 3);
    push_edges(4, 10);
    push_edges(4, 11);

    char city5[] = "Timisoara";
    push_graph_Node(5, city5);
    push_edges(5, 1);
    push_edges(5, 6);

    char city6[] = "Lugoj";
    push_graph_Node(6, city6);
    push_edges(6, 5);
    push_edges(6, 7);

    char city7[] = "Mehadia";
    push_graph_Node(7, city7);
    push_edges(7, 6);
    push_edges(7, 8);

    char city8[] = "Drobeta";
    push_graph_Node(8, city8);
    push_edges(8, 7);
    push_edges(8, 9);

    char city9[] = "Craiova";
    push_graph_Node(9, city9);
    push_edges(9, 8);
    push_edges(9, 10);
    push_edges(9, 12);

    char city10[] = "Rimnicu";
    push_graph_Node(10, city10);
    push_edges(10, 4);
    push_edges(10, 9);
    push_edges(10, 12);

    char city11[] = "Fagaras";
    push_graph_Node(11, city11);
    push_edges(11, 4);
    push_edges(11, 13);

    char city12[] = "Pitesti";
    push_graph_Node(12, city12);
    push_edges(12, 10);
    push_edges(12, 9);
    push_edges(12, 13);

    char city13[] = "Bucharest";
    push_graph_Node(13, city13);
    push_edges(13,11);
    push_edges(13, 12);
    push_edges(13, 14);
    push_edges(13, 15);

    char city14[] = "Giurgiu";
    push_graph_Node(14, city14);
    push_edges(14, 13);

    char city15[] = "Urziceni";
    push_graph_Node(15, city15);
    push_edges(15, 18);
    push_edges(15, 13);
    push_edges(15, 16);

    char city16[] = "Hirsova";
    push_graph_Node(16, city16);
    push_edges(16, 15);
    push_edges(16, 17);

    char city17[] = "Eforie";
    push_graph_Node(17, city17);
    push_edges(17, 16);

    char city18[] = "Vaslui";
    push_graph_Node(18, city18);
    push_edges(18, 15);
    push_edges(18, 19);

    char city19[] = "Iasi";
    push_graph_Node(19, city19);
    push_edges(19, 18);
    push_edges(19, 20);

    char city20[] = "Neamt";
    push_graph_Node(20, city20);
    push_edges(20, 19);

}








int main()
{

    
    unordered_map<string, unordered_map<string, int> > graph = {

        {"Arad",
            {   {"Zerind", 175}, {"Sibiu" , 140}, {"Timisoara" , 118}    }
        },
        {"Zerind",
            {   {"Arad", 275}, {"Oradea" , 71}   }
        },
        {"Oradea",
            {   {"Zerind", 371}, {"Sibiu" , 151} }
        },
        {"Sibiu",
            {   {"Arad", 4140}, {"Oradea" , 151}, {"Fagaras" , 99},{"Rimnicu" , 80}  }
        },
        {"Timisoara",
            {   {"Arad", 5118}, {"Lugoj" , 111}  }
        },
        {"Lugoj",
            {   {"Timisoara", 6111}, {"Mehadia" , 70}    }
        },
        {"Mehadia",
            {   {"Lugoj", 770}, {"Drobeta" , 75}   }
        },
        {"Drobeta",
            {   {"Mehadia", 875}, {"Craiova", 120}   }
        },
        {"Craiova",
            {   {"Drobeta", 9120}, {"Rimnicu", 146}, {"Pitesti" , 138}   }
        },
        {"Rimnicu",
            {   {"Sibiu", 1080}, {"Craiova", 146}, {"Pitesti" , 97}   }
        },
        {"Fagaras",
            {   {"Sibiu", 1199}, {"Bucharest", 211}   }
        },
        {"Pitesti",
            {   {"Rimnicu", 1297}, {"Craiova", 138}, {"Bucharest" , 101}  }
        },
        {"Bucharest",
            {   {"Fagaras", 13211}, {"Pitesti", 101}, {"Giurgiu" , 90}, {"Urziceni" , 85}  }
        },
        {"Giurgiu",
            {   {"Bucharest", 1490}   }
        },
        {"Urziceni",
            {   {"Bucharest", 1585}, {"Vaslui", 142}, {"Hirsova" , 98}    }
        },
        {"Hirsova",
            {   {"Urziceni", 1698}, {"Eforie", 86}    }
        },
        {"Eforie",
            {   {"Hirsova", 1786}    }
        },
        {"Vaslui",
            {   {"Urziceni", 18142}, {"Iasi", 92}    }
        },
        {"Iasi",
            {   {"Vaslui", 1992}, {"Neamt", 87}   }
        },
        {"Neamt",
            {   {"Iasi", 2087}    }
        }
    };


 
    int choice;

    char Root[15];
    char Goal[15];

    cout << "\n\n                                           < Welcome the shortest search APP >\n\n"
        << "                        Using the Breadth-Fitst Search Algorithm to help you find the shortest path on map\n\n"
        << "    choose from the following options: \n"
        << "    1 -- Find Directions on Romania's map.\n"
        << "    2 -- EXIT...\n"
        << "    Your Choice (1 or 2)...  : ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "\n         --- Enter the Starting point: ";
        cin >> Root;
        cout << "\n         --- Enter the Goal point: ";
        cin >> Goal;

        auto_Graph();
        //BFS(graph, Root, Goal);
        BFS(Graph_front, Root, Goal);
        break;
    case 2:
        cout << "\n\n           Thanks for joining ;) \n";
        break;
    default:
        cout << "\n                 ---- Sorry, Could not recognize the input ---- \n";
    }

    
    

}



