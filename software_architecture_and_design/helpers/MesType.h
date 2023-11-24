#ifndef MESTYPE_H
#define MESTYPE_H

#include <map>
#include <string>

enum MesType {
    MS,
    FLE,
    SYS,
    EMT,
};

// Mapping from MesType to string
std::map<MesType, std::string> MesTypeToString = {
    {MS, "MS"},
    {FLE, "FLE"},
    {SYS, "SYS"},
    {EMT, "EMT"}
};

// Mapping from string to MesType
std::map<std::string, MesType> StringToMesType = {
    {"MS", MS},
    {"FLE", FLE},
    {"SYS", SYS},
    {"EMT", EMT}
};

#endif  //MESTYPE_H
