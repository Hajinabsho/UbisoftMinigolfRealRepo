#pragma once
#include <vector>

/// <summary>
/// This class is where I will store the array info of each map and I can 'Parse' with TileMap class
/// Later Edit: I'm an idiot I could've used Text file and parse it. 
/// </summary>
class MapConfigs
{
public:
    //static std::vector<std::vector<int>> data;
   

    
    static  std::vector<std::vector<int>> Level1();
    static  std::vector<std::vector<int>> Level2();
    static  std::vector<std::vector<int>> Level3();


};

//This is Defined in the TileMap.h
//// Define the tile types
//enum TileType {
//    Empty = 0,
//    Ground = 1,
//    Wall = 2,
//    Hole = 3,
//    Flag = 4,
//    AirPowerUp = 5,
//    GravityBox = 6
//};