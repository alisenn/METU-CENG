#include "Tissue.h"

Tissue::Tissue(){
	min_x_border = 0; max_x_border = 0;
	min_y_border = 0; max_y_border = 0;
    
}

Tissue::Tissue(float minXb, float maxXb, float minYb, float maxYb){
	min_x_border = minXb; max_x_border = maxXb;
	min_y_border = minYb; max_y_border = maxYb;
}

Tissue::Tissue(const Tissue& rhs){
	(*this) = rhs;
	/*min_x_border = rhs.min_x_border; max_x_border = rhs.max_x_border;
	min_y_border = rhs.min_y_border; max_y_border = rhs.max_y_border;
	cells = rhs.cells;*/
}

Tissue::~Tissue(){
	cells.clear();

}

float* Tissue::GetCoordinates(){
	float *res = new float[4];
	res[0] = min_x_border;
	res[1] = max_x_border;
	res[2] = min_y_border;
	res[3] = max_y_border;
	return res;
}

void Tissue::AddCell(Cell& rhsC){
	cells.push_back(rhsC);
}

void Tissue::RemoveCell(Cell& rhsC){

	int s = cells.size();
	for(int i=0; i<s; i++){
		if((cells[i]) == rhsC){
			erasedCells.push_back(cells[i]);
			//cells.erase(cells.begin()+i);
			break;
		}
	}
}

const Cell& Tissue::GetCell(int _id) const{
	for(int i=0; i<erasedCells.size(); i++){
		if(erasedCells[i].GetCellID() == _id){
			throw DeadCellException();
		}
	}
	for(int i=0; i<cells.size(); i++){
		if( cells[i].GetCellID() == _id )
			return cells[i];
	}

}

void Tissue::Interact(const vector<MicroOrganism*>& mics){
	for(int i=0; i<mics.size(); i++){
		for(int j=0; j<cells.size(); j++){
			if(mics[i]->DoesFitInto(cells[j])){
				mics[i]->ConnectToCell( &cells[j]);
				break;
			}
		}
	}

}

void Tissue::CreatePartitions(const vector<MicroOrganism*>&){

}

void Tissue::TreatByPlasma(Tissue){

}
