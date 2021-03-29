#include <iostream>
#include "src/lib/trojanmap.h"

// #define NCURSES
#ifdef NCURSES
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <ncurses.h>
#include "src/lib/UI.h"
/**
 * DynamicPrintMenu: Create the dynamic menu
 * 
 */
void DynamicPrintMenu(TrojanMap& trojan_map) {
  UI ui;
  initscr();      // Start curses mode
  start_color();  // Start color
                  // Initialize some color pairs (foreground, background)
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);

  std::string menu =
      "Torjan Map\n"
      "**************************************************************\n"
      "* Select the function you want to execute.                    \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Cycle Detection                                          \n"
      "* 6. Topological Sort                                         \n"
      "* 7. Exit                                                     \n"
      "**************************************************************\n"
      "Please select 1 - 7: ";
  std::string s = menu;
  ui.ScrollLongText(menu);
  char number = getch();
  clear();
  refresh();
  int y=0;
  char input[100];
  switch (number)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Autocomplete                                             \n"
        "**************************************************************\n";
    y = ui.ScrollLongText(menu);
    menu = "Please input a partial location:";
    y = ui.ScrollLongText(menu,10,y);
    scanw("%s",input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = trojan_map.Autocomplete(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    clear();
    menu = "*************************Results******************************";
    y = ui.ScrollLongText(menu);
    if (results.size() != 0) {
      for (auto x : results) y = ui.ScrollLongText(x,10,y);
    } else {
      ui.ScrollLongText("No matched locations./n",10,y);
    }
    menu = "**************************************************************\n";
    y=ui.ScrollLongText(menu,10,y);
    y=ui.ScrollLongText("Time taken by function: " + std::to_string(duration.count()) + " microseconds",10,y);
    y=ui.ScrollLongText("Press any keys to continue.",10,y);
    getchar();
    clear();
    DynamicPrintMenu(trojan_map);
    break;
  }
  case '2':
  {
    menu =
        "**************************************************************\n"
        "* 2. Find the position                                        \n"
        "**************************************************************\n";
    y = ui.ScrollLongText(menu);
    menu = "Please input a location:";
    y = ui.ScrollLongText(menu,10,y);
    scanw("%s",input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = trojan_map.GetPosition(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    clear();
    menu = "*************************Results******************************";
    y = ui.ScrollLongText(menu);
    if (results.first != -1) {
      y = ui.ScrollLongText("Latitude: " + std::to_string(results.first), 10, y);
      y = ui.ScrollLongText("Longitude: " + std::to_string(results.second), 10, y);
      trojan_map.PlotPoint(results.first, results.second);
    } else {
      y = ui.ScrollLongText("No matched location.",10,y);
    }
    menu = "**************************************************************\n";
    y=ui.ScrollLongText(menu,10,y);
    y=ui.ScrollLongText("Time taken by function: " + std::to_string(duration.count()) + " microseconds",10,y);
    y=ui.ScrollLongText("Press any keys to continue.",10,y);
    getchar();
    clear();
    DynamicPrintMenu(trojan_map);
    break;
  }
  case '3':
  {
    menu =
        "**************************************************************\n"
        "* 3. CalculateShortestPath                                    \n"
        "**************************************************************\n";
    y = ui.ScrollLongText(menu);
    menu = "Please input the start location:";
    y = ui.ScrollLongText(menu, 10, y);
    char input1[100];
    scanw("%s",input1);
    menu = "Please input the destination:";
    y = ui.ScrollLongText(menu, 10, y);
    char input2[100];
    scanw("%s",input2);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = trojan_map.CalculateShortestPath(input1, input2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    clear();
    menu = "*************************Results******************************";
    y = ui.ScrollLongText(menu);
    if (results.size() != 0) {
      // for (auto x : results) y = ui.ScrollLongText(x, 10, y);
      y = ui.ScrollLongText("The distance of the path is:" + std::to_string(trojan_map.CalculatePathLength(results)) + " miles", 10, y);
      trojan_map.PlotPath(results);
    } else {
      y = ui.ScrollLongText("No route from the start point to the destination.", 10, y);
    }
    menu = "**************************************************************\n";
    y=ui.ScrollLongText(menu,10,y);
    y=ui.ScrollLongText("Time taken by function: " + std::to_string(duration.count()) + " microseconds",10,y);
    y=ui.ScrollLongText("Press any keys to continue.",10,y);
    getchar();
    clear();
    DynamicPrintMenu(trojan_map);
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Travelling salesman problem                              \n"
        "**************************************************************\n";
    y = ui.ScrollLongText(menu);
    menu = "In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.";
    y = ui.ScrollLongText(menu, 10, y);
    menu = "Please input the number of the places:";
    y = ui.ScrollLongText(menu, 10, y);
    scanw("%s",input);
    int num = std::stoi(input);
    std::vector<std::string> keys;
    for (auto x : trojan_map.data) {
      keys.push_back(x.first);
    }
    std::vector<std::string> locations;
    srand(time(NULL));
    for (int i = 0; i < num; i++)
      locations.push_back(keys[rand() % keys.size()]);
    trojan_map.PlotPoints(locations);
    y = ui.ScrollLongText("Calculating ...", 10, y);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = trojan_map.TravellingTrojan(locations);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    trojan_map.CreateAnimation(results.second);
    clear();
    menu = "*************************Results******************************";
    y = ui.ScrollLongText(menu);
    if (results.second.size() != 0) {
      // for (auto x : results.second[results.second.size()-1]) std::cout << x << std::endl;
      y = ui.ScrollLongText("The distance of the path is:" + std::to_string(results.first) + " miles", 10, y);
      trojan_map.PlotPath(results.second[results.second.size()-1]);
    } else {
      y = ui.ScrollLongText("The size of the path is 0", 10, y);
    }
    menu = "**************************************************************\n"
           "You could find your animation at src/lib/output.avi.          \n";
    y=ui.ScrollLongText(menu,10,y);
    y=ui.ScrollLongText("Time taken by function: " + std::to_string(duration.count()) + " microseconds",10,y);
    y=ui.ScrollLongText("Press any keys to continue.",10,y);
    getchar();
    clear();
    DynamicPrintMenu(trojan_map);
    break;
  }
  case '5':
  {
    menu =
        "**************************************************************\n"
        "* 5. Cycle Detection                                          \n"
        "**************************************************************\n";
    y = ui.ScrollLongText(menu);
    menu = "Please input the left bound longitude(between -118.299 and -118.264):";
    y = ui.ScrollLongText(menu, 10, y);
    scanw("%s",input);
    std::vector<double> square;
    square.push_back(atof(input));

    menu = "Please input the right bound longitude(between -118.299 and -118.264):";
    y = ui.ScrollLongText(menu, 10, y);
    scanw("%s",input);
    square.push_back(atof(input));

    menu = "Please input the upper bound latitude(between 34.011 and 34.032):";
    y = ui.ScrollLongText(menu, 10, y);
    scanw("%s",input);
    square.push_back(atof(input));

    menu = "Please input the lower bound latitude(between 34.011 and 34.032):";
    y = ui.ScrollLongText(menu, 10, y);
    scanw("%s",input);
    square.push_back(atof(input));

    auto start = std::chrono::high_resolution_clock::now();
    auto results = trojan_map.CycleDetection(square);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    clear();
    menu = "*************************Results******************************";
    y = ui.ScrollLongText(menu);
    if (results == true)
      y = ui.ScrollLongText("There exists cycle in the subgraph.", 10, y);
    else
      y = ui.ScrollLongText("There is no cycle in the subgraph.", 10, y);
    menu = "**************************************************************\n";
    y=ui.ScrollLongText(menu,10,y);
    y=ui.ScrollLongText("Time taken by function: " + std::to_string(duration.count()) + " microseconds",10,y);
    y=ui.ScrollLongText("Press any keys to continue.",10,y);
    getchar();
    clear();
    DynamicPrintMenu(trojan_map);
    break;
  }
  case '6':
  {
    menu =
        "**************************************************************\n"
        "* 6. Topological Sort                                         \n"
        "**************************************************************\n";
    y = ui.ScrollLongText(menu);

    // Read location names from CSV file
    std::vector<std::string> location_names_from_csv;
    std::fstream fin;
    fin.open("src/lib/topologicalsort_locations.csv", std::ios::in);
    std::string line, word;
    getline(fin, line);
    while (getline(fin, line)) {
      std::stringstream s(line);
      while (getline(s, word, ',')) {
        location_names_from_csv.push_back(word);
      }
    }
    fin.close();

    // Read dependencies from CSV file
    std::vector<std::vector<std::string>> dependencies_from_csv;
    fin.open("src/lib/topologicalsort_dependencies.csv", std::ios::in);
    getline(fin, line);
    while (getline(fin, line)) {
      std::stringstream s(line);
      std::vector<std::string> dependency;
      while (getline(s, word, ',')) {
        dependency.push_back(word);
      }
      dependencies_from_csv.push_back(dependency);
    }
    fin.close();

    // std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    // std::vector<std::vector<std::string>> dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    auto start = std::chrono::high_resolution_clock::now();
    auto result = trojan_map.DeliveringTrojan(location_names_from_csv, dependencies_from_csv);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    clear();
    menu = "*************************Results******************************";
    y=ui.ScrollLongText(menu);
    y=ui.ScrollLongText("Topological Sorting Reults:", 10, y);
    for (auto x : result) y=ui.ScrollLongText(x, 10, y);
    std::vector<std::string> node_ids;
    for (auto x: result) {
      Node node = trojan_map.GetNode(x);
      node_ids.push_back(node.id);
    }
    trojan_map.PlotPointsOrder(node_ids);
    menu = "**************************************************************\n";
    y=ui.ScrollLongText(menu,10,y);
    y=ui.ScrollLongText("Time taken by function: " + std::to_string(duration.count()) + " microseconds",10,y);
    y=ui.ScrollLongText("Press any keys to continue.",10,y);
    getchar();
    clear();
    DynamicPrintMenu(trojan_map);
    break;
  }
  case '7':
  {
    
    endwin();  // End curses mode
    break;
    // return EXIT_SUCCESS;
  }
  default:
  {
    DynamicPrintMenu(trojan_map);
    break;
  }
  }
}

#endif
int main() {
  TrojanMap x;
  x.CreateGraphFromCSVFile();
  #ifdef NCURSES
    DynamicPrintMenu(x);
  #else
    x.PrintMenu();
  #endif
  return 0;
}