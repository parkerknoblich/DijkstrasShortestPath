#include "nodedata.h"

// --------------------------- default constructor ----------------------------
NodeData::NodeData() {
    data = "";
}

// ------------------------ parameterized constructor -------------------------
NodeData::NodeData(const string& s) {
    data = s;   
}

// ----------------------------- copy constructor -----------------------------
NodeData::NodeData(const NodeData& other) {
    data = other.data;
}

// -------------------------------- destructor --------------------------------
NodeData::~NodeData() {

}

// -------------------------------- operator= ---------------------------------
NodeData& NodeData::operator=(const NodeData& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

// -------------------------------- operator== --------------------------------
bool NodeData::operator==(const NodeData& other) const {
    return data == other.data;
}

// -------------------------------- operator!= --------------------------------
bool NodeData::operator!=(const NodeData& other) const {
    return data != other.data;
}

// -------------------------------- operator< ---------------------------------
bool NodeData::operator<(const NodeData& other) const {
    return data < other.data;
}

// -------------------------------- operator> ---------------------------------
bool NodeData::operator>(const NodeData& other) const {
    return data > other.data;
}

// -------------------------------- operator<= --------------------------------
bool NodeData::operator<=(const NodeData& other) const {
    return data <= other.data;
}

// -------------------------------- operator>= --------------------------------
bool NodeData::operator>=(const NodeData& other) const {
    return data >= other.data;
}

// ---------------------------------- setData ---------------------------------
bool NodeData::setData(istream& infile) {
    getline(infile, data);
    return !infile.eof();
}

// -------------------------------- operator<< --------------------------------
ostream& operator<<(ostream& output, const NodeData& toPrint) {
    output << toPrint.data;
    return output;
}