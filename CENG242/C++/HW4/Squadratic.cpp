#include "Squadratic.h"

Squadratic::Squadratic(int _id, float eLength){
	micId=_id;
	edgeLength = eLength;
}

Squadratic::Squadratic(const Squadratic& rhs){
	micId = rhs.micId;
	edgeLength = rhs.edgeLength;
}

Squadratic::~Squadratic(){}

void Squadratic::ConnectToCell(Cell* const cell){
	connectedCell = cell;
}

bool Squadratic::DoesFitInto(const Cell& cell) const{
	vector<Wall*> cellWall = cell.GetCellWall();

	Cell cel2(-1234,cellWall,NULL);
  	cel2.StrengthenCellWall();
	vector<Wall*> cellWallStreng = cel2.GetCellWall();

	float l1,l2;

	l1 = cellWallStreng[0]->GetLength();
	l2 = edgeLength;
	if( (abs(l1-l2)<EPSILON) && abs((cellWallStreng[1]->FindAngleBetween(*cellWallStreng[0])) - 90)<EPSILON ){ //ilk duvar
		return true;
	}

	return false;

}

void Squadratic::React(){
	int connectedId = connectedCell->GetCellID();
	int newId ;
	if(connectedId ==123){
		newId = 123;
	}
	else{
		newId = 124;
	}
	float x1,x2,y1,y2;
	float x,y;
	vector<Particle> pv;
	vector<Wall*> w = connectedCell->GetCellWall();
	for(int i=0; i<w.size(); i++){
		x1 = w[i]->GetInitialParticle().X();
		y1 = w[i]->GetInitialParticle().Y();
		x2 = w[i]->GetFinalParticle().X();
		y2 = w[i]->GetFinalParticle().Y();
		x = (x1+x2) / 2; //find mid points
		y = (y1+y2) / 2;
		Particle p(x,y);
		pv.push_back(p);
	}

	Wall *w1 = new Wall(pv[0],pv[2]);
	Wall *w2 = new Wall(pv[1],pv[3]);
	//Wall *w1p = &w1;
	//Wall *w2p = &w2;
	vector<Wall*> newWall;
	//w.push_back(w1);
	//w.push_back(w2);
	newWall.push_back(w1);
	newWall.push_back(w2);
	connectedCell->RenewCellWall(newWall);
	//CurvyWall* cww = new CurvyWall(*pp1,*pp1,c);
	//vector<Wall*> neww;
	//connectedCell->RenewCellWall(w);
}

Squadratic& Squadratic::GetChild(float a, float b, float c, float d) const{
	//float *coord = connectedCell->GetTissue()->GetCoordinates();
	//if(coord[0]==a && coord[1]==b && coord[2]==c && coord[3]==d )

}
