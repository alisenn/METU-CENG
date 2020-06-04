#include "MicroOrganism.h"

MicroOrganism::MicroOrganism(int id, const vector<Wall*>& edges){
	micId = id;
	wallEdges = edges;
}

ostream& operator<<(ostream& os, const MicroOrganism& mic){
	if(mic.connectedCell){
		os<<"The microorganism "<< mic.micId <<" was successfully placed into the cell "<< mic.connectedCell->GetCellID()<<'.';
		return os;
	}
	os<<"The microorganism "<< mic.micId <<" could not be placed into any cell!";
	return os;
}

bool MicroOrganism::DoesFitInto(const Cell&) const {}
void MicroOrganism::ConnectToCell(Cell* const cell) {}
void MicroOrganism::React() {}
MicroOrganism::~MicroOrganism() {}
