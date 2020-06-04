#include "Cell.h"

Cell::Cell(int _id, const vector<Wall*>& _shape, Tissue* _tissue){
	id = _id;
	for(int i=0; i<_shape.size(); i++){
		shape.push_back(new Wall(*_shape[i]));
	}
	tissue = _tissue;
}

Cell::Cell(const Cell& rhs){
	id = rhs.id;
	//shape = rhs.shape;
	for(int i=0; i<rhs.shape.size(); i++){
		shape.push_back(new Wall(*rhs.shape[i]));
	}
	tissue = rhs.tissue;
}

int Cell::GetCellID() const{
	return id;
}

Tissue* Cell::GetTissue() const{
	return tissue;
}

const vector<Wall*>& Cell::GetCellWall() const{
	return shape;
}

void Cell::RenewCellWall(vector<Wall*>& rhsShape){
	shape.clear();
	shape = rhsShape;
}

void Cell::StrengthenCellWall(){
	int size = shape.size();
	for(int i=0; i<(size-1); i++){
		for(int j=(i+1); j<size; j++){
			if( (*shape[i]).canSum((*shape[j])) ){
				(*shape[i]) = (*shape[i]) + (*shape[j]);
				shape.erase(shape.begin()+j);
				j--;
				size--;
			}
		}
	}
}

Cell::~Cell(){
	for(int i=0; i<shape.size(); i++){
		delete shape[i];
	}
	//shape.clear();
}

ostream& operator<<(ostream& os, const Cell& rhsC){
	vector<Wall*> v = rhsC.GetCellWall();
	int i;
	for( i=0; i<v.size(); i++)
		if(i!=0)
			os<<"-"<<v[i]->GetInitialParticle();
		else
			os<<v[i]->GetInitialParticle();
	return os;
}
