#include <iostream>
#include <fstream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>
#include <list>
#include <chrono>

int counter = 0;
double total = 0;

using map_pair = std::pair<std::unordered_map<std::string, std::string>, std::unordered_map<std::string, std::string>>;

map_pair create_maps(std::string file) {

    auto startM = std::chrono::high_resolution_clock::now(); // uses chrono library to check the clock

    std::string northSide, southSide, line; // instantiates each side of the brick and line.

    std::unordered_map<std::string, std::string> mapSetA, mapSetB; // instantiates an unordered map of string for mapSetA and mapSetB

    std::ifstream pairs(file);


    while (getline(pairs, line)) {

        
        replace(line.begin(), line.end(), ',', ' '); // replaces all occurence of , with white-space
        std::stringstream sStream(line);

        sStream >> northSide;
        sStream >> southSide;

        mapSetA.insert(std::make_pair(northSide, southSide)); // inserts into mapA, north-side then south-side of the brick.
        mapSetB.insert(std::make_pair(southSide, northSide)); // inserts into mapB, in reverse of the above.

        counter++;
        
    }

    auto stopM = std::chrono::high_resolution_clock::now(); // uses chrono library again to check the clock again

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stopM - startM); // subtracts to get the total time in nano-seconds.

    total =  duration.count() / counter; // displays the calulation of insert in total and dividing by the total number of insertions.

    return (std::make_pair(mapSetA, mapSetB)); // returns the newly created map consisting of mapA + mapB
}

std::list<std::string> convert_maps_to_list(map_pair maps) {

    std::unordered_map<std::string, std::string> firstBrick = maps.first, secondBrick = maps.second; // refers to the map's key and value

    std::string previous, next;

    std::list<std::string> wall; // creates a list of type string

    wall.push_back(firstBrick.begin()->first); // adds the brick to the end of the container, effectively increasing it's size by one.

    while (true) {

        previous = wall.back(); // returns the reference at the end of the wall - unlike list.end() which returns the iterator just past the last element.

        if (firstBrick.find(previous) == firstBrick.end()) {
            break;
        }

        next = firstBrick.find(previous)->second;

        wall.push_back(next);
    }

    // iterates through the unordered map via its key/value pair. Assembling west to east respectively.
    wall.push_back(secondBrick.find(wall.front())->first);

    while (true) {
        previous = wall.front(); // returns a reference to the first element of the list, unlike list.begin() which returns an iterator to the same element.

        if (secondBrick.find(previous) == secondBrick.end()) {
            break;
        }

        next = secondBrick.find(previous)->second;
        wall.push_front(next);
    }

    wall.pop_back();

    return(wall);
}


void wallIterator(std::string file, map_pair map, std::list<std::string> completedWall) {

     completedWall = convert_maps_to_list(map);

    for (auto const& brick : completedWall) { // for loop iterating through each brick in the wall (list)
        std::cout << "-"  << brick << "\n";
    }

    std::cout << "\nElapsed time (" << total << " nano-seconds) per node insertion (" << counter << " nodes" << ")" << std::endl;
}


int main(int argc, char* argv[])
{
    std::string file;

    if (argc > 1) { // used to contain the count of arguments
        file = argv[1]; // argv[1] is the first command line argument, in this case, should be an array of strings/text file.
    }

    else {
        std::string input;

        std::cout << "To enable input-specified data-size - please ensure test-data folder resides in c:/Great_Wall_Problem-test_data/" << std::endl;

        std::cout << "\nPlease specify testing data size: " << std::endl;
        std::cout << "Data-size input: ";
        std::cin >> input;

        file = "c:/Great_Wall_Problem-test_data/" + input + "/input-pairs-" + input + ".txt";
    }
    
    map_pair map = create_maps(file); // calls the create map function, passing the file. During run-time, the code performs time analysis of the function to determine it's speed of execute per each insert.

    std::list<std::string> completedWall; // instantiates a list of strings.

    wallIterator(file, map, completedWall); // calls wallIterator, passing the file, the map and the completedWall list.
    

    



}


