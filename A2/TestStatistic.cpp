/**
 * EN.605.604.82 : Object-Oriented Programming with C++
 * Assignment #2: Statistical Class
 * Authors: Alayna Peterson and Ryan Peterson
 * Due: 09/12/2021
 * Description: This program provides some automated test cases for Statistic.cpp.
 **/

#include <iostream>
#include "Statistic.h"
using namespace std;

int main()
{
    // Instance of statistic that will be used for testing
    Statistic statistic;

    // invalid empty sequence
    cout << "Statistics for sequence {}:\n";
    cout << "Average: " << statistic.average() << endl;
    cout << "STD: " << statistic.STD() << endl << endl;

    // one element sequence, here: average = 2.0, std = 0.0
    statistic.add(2.0);
    cout << "Statistics for sequence {2.0}:\n";
    cout << "Average: " << statistic.average() << endl;
    cout << "STD: " << statistic.STD() << endl << endl;

    // multi-element sequence, here: average = 2.675, std = 2.299818...
    statistic.add(0.0);
    statistic.add(5.5);
    statistic.add(3.2);
    cout << "Statistics for sequence {2.0, 0.0, 5.5, 3.2}:\n";
    cout << "Average: " << statistic.average() << endl;
    cout << "STD: " << statistic.STD() << endl << endl;

    // Alayna's discussion #1 sequence, here: average = 7.166666..., std = 5.946988...
    Statistic statisticAlayna;
    statisticAlayna.add(1.0);
    statisticAlayna.add(2.0);
    statisticAlayna.add(4.0);
    statisticAlayna.add(8.0);
    statisticAlayna.add(12.0);
    statisticAlayna.add(16.0);
    cout << "Statistics for sequence {1.0, 2.0, 4.0, 8.0, 12.0, 16.0}:\n";
    cout << "Average: " << statisticAlayna.average() << endl;
    cout << "STD: " << statisticAlayna.STD() << endl << endl;

    // Ryan's discussion #1 sequence, here: average = 9.189946e+15, std = 2.054934e+16
    Statistic statisticRyan;
    statisticRyan.add(11.0);
    statisticRyan.add(121.0);
    statisticRyan.add(14641.0);
    statisticRyan.add(214358881.0);
    statisticRyan.add(45949729863572161.0);
    cout << "Statistics for sequence {11.0, 121.0, 14641.0, 214358881.0, 45949729863572161.0}:\n";
    cout << "Average: " << statisticRyan.average() << endl;
    cout << "STD: " << statisticRyan.STD() << endl << endl;
    
    return 0;
}