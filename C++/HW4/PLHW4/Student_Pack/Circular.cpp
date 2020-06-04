#include "Circular.h"


Circular::Circular(int id, float rad){
	micId = id;
	radius = rad;
}

Circular::~Circular(){

}

void Circular::ConnectToCell(Cell* const cell){
	connectedCell = cell;
}

bool Circular::DoesFitInto(const Cell& cell) const{

	vector<Wall*> cellWall = cell.GetCellWall(); 
	Cell cel2(-12723,cellWall,NULL);
	cel2.StrengthenCellWall();

	vector<Wall*> cellWall1 = cel2.GetCellWall();

	float r = cellWall1[0]->radius;
	if(abs(radius-r) <EPSILON){
		return true; 
	} 
	return false;

}

void Circular::React(){
	vector<Wall*> w = connectedCell->GetCellWall();
	CurvyWall* cw = (CurvyWall*)w[0];
	
	float rad = cw->GetRadius();
	float newRad = rad*2;
	float len = 3;
	cw->ComputeLength();
	Particle c = cw->GetCenter();

	float a1,a2,b1,b2;
	if(c.X()>0) a1 = c.X();
	else a1 = c.X();
	if(c.Y()>0) a2 = c.Y()+newRad;
	else a2 = c.Y()-newRad;

	Particle* pp1 = new Particle(a1,a2); 

	CurvyWall* cww = new CurvyWall(*pp1,*pp1,c);
	vector<Wall*> newWall;
	newWall.push_back(cww);
	connectedCell->RenewCellWall(newWall);
	

}

bool Circular::DoesContain(const Particle& particle) const{
	vector<Wall*> w = connectedCell->GetCellWall();
	CurvyWall* cw = (CurvyWall*)(w[0]);
	float rad = cw->GetRadius();
	Particle center = cw->GetCenter();

	float x,y; x = particle.X(); y = particle.Y(); //parameter particle
	float center_x,center_y; center_x = center.X(); center_y = center.Y(); //center
	if( ( ( (x - center_x) * (x - center_x) ) + ( (y - center_y) * (y - center_y) ) ) < (rad*rad) )
		return true;
	return false;


}
