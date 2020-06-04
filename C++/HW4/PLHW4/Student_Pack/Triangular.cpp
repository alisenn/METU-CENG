#include "Triangular.h"

Triangular::Triangular(int _id, const vector<Wall*>& ed, const NucleoBase& n){
	micId=_id;
	for(int i=0; i<ed.size(); i++){
		wallEdges.push_back(new Wall(*ed[i]));
	}
	nucleobase =new NucleoBase(n); 
	string rna=nucleobase->getStringRna();
	nucleobase = new NucleoBase(rna,NULL);

}

Triangular::~Triangular(){
	wallEdges.clear();
}

void Triangular::ConnectToCell(Cell* const cell){
	connectedCell = cell;
}

bool Triangular::DoesFitInto(const Cell& cell) const{
	vector<Wall*> cellWall = cell.GetCellWall(); //not added already exitst

	Cell cel2(-122,cellWall,NULL);
  	cel2.StrengthenCellWall();
	vector<Wall*> cellWallStreng = cel2.GetCellWall();

	int count = 0, cws = cellWallStreng.size(), wes = wallEdges.size();
	if(cws>3) cws = 3;
	if(wes>3) wes = 3;
	int nevervisitagain[3] = {-1,-1,-1};
	float l1,l2;
	for(int i=0; i<cws; i++){
		for(int j=0; j<wes; j++){
			l1 = cellWallStreng[i]->GetLength();
			l2 = wallEdges[j]->GetLength();
			if( (j != nevervisitagain[0]) && (j != nevervisitagain[1]) && (j!= nevervisitagain[2]) && abs(l1-l2)<EPSILON){
				nevervisitagain[i] = j;
				count++;
				break;
			}
		}
	}
	if(count == 3) {
		return true;
	}
	return false;
}

void Triangular::React(){
	connectedCell->GetTissue()->RemoveCell(*connectedCell);
}

const NucleoBase& Triangular::GetRNA() const{
	return *nucleobase;

}

void Triangular::Mutate(Triangular& tr){

	NucleoBase* firstNucleoBase = nucleobase;
	NucleoBase* secondNucleoBase = tr.nucleobase;

	/*cout<<"Before"<<endl;
	cout <<*firstNucleoBase<<endl;
	cout <<*secondNucleoBase<<endl;*/
	NucleoBase* bastan1 = firstNucleoBase->head, *bastan2 = secondNucleoBase->head;
	NucleoBase* sondan1 = firstNucleoBase->tail, *sondan2 = secondNucleoBase->tail;

	
	while(bastan1->data == bastan2->data){

		bastan1 = bastan1->next;
		bastan2 = bastan2->next;
	}

	while(sondan1->data == sondan2->data){
		sondan1 = sondan1->prev;
		sondan2 = sondan2->prev;
	}

	//G-S and A-U
	while( (bastan1 != sondan1->next) ){
		if(bastan1->data == 'A' && bastan2->data =='U'){
			bastan1->data = 'U'; bastan2->data = 'A';
		}
		else if(bastan1->data == 'U' && bastan2->data =='A'){
			bastan1->data = 'A'; bastan2->data = 'U';
		}

		else if(bastan1->data == 'G' && bastan2->data =='S'){
			bastan1->data = 'S'; bastan2->data = 'G';
		}
		else if(bastan1->data == 'S' && bastan2->data =='G'){
			bastan1->data = 'G'; bastan2->data = 'S';
		}
		else{
			bastan1->remove(bastan1); bastan2->remove(bastan2);
		}
		bastan1 = bastan1->next;
		bastan2 = bastan2->next;
	}
	/*cout<<"AFTER"<<endl;
	cout <<*firstNucleoBase<<endl;
	cout <<*secondNucleoBase<<endl;*/



}
