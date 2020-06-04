#include "Wall.h"

Wall::Wall(float l){
	len = l;
}

Wall::Wall(const Particle& rhsp1, const Particle& rhsp2){
	p1 = rhsp1;
	p2 = rhsp2;
	len = p1.FindDistance(p2);
	radius = -1;
	//centerP = p1;
}

Wall::Wall(const Wall& rhs){
	p1 = rhs.p1;
	p2 = rhs.p2;
	len = rhs.len;
	radius = rhs.radius;
	centerP = rhs.centerP;
}

const Particle& Wall::GetInitialParticle() const{
	return p1;
}

const Particle& Wall::GetFinalParticle() const{
	return p2;
}

float Wall::FindAngleBetween(const Wall& rhs) const{
	float PI = 3.14159265;
	Particle endPt1,endPt2,connectingPt;
	if(p1 == rhs.p1 ) {connectingPt = p1; endPt2 = rhs.p2; endPt1 = p2;}
	else if( p1 == rhs.p2 ){connectingPt = p1; endPt2 = rhs.p1; endPt1 = p2;}
	else if( p2 == rhs.p1 ){connectingPt = p2; endPt2 = rhs.p2; endPt1 = p1;}
	else {connectingPt = p2; endPt2 = rhs.p1; endPt1 = p1;}

	float x1 = endPt1.X() - connectingPt.X(); //Wall 1 - x
    float y1 = endPt1.X() - connectingPt.Y(); //Wall 1 - y

    float x2 = endPt2.X() - connectingPt.X(); //Wall 2 - x
    float y2 = endPt2.Y() - connectingPt.Y(); //Wall 2 - y

    float angle = atan2(x1, y1) - atan2(x2, y2); //counter clockwise angle
    angle = angle * 360 / (2*PI);

    if(angle < 0) {
        angle += 360;
    }

    return angle;
}

float Wall::GetLength() const{
	return len;
}

void Wall::ComputeLength(){
	len =p1.FindDistance(p2);
}

Wall* Wall::Clone() const{
	return new Wall(*this);
}

bool Wall::IsContinuousLinear(const Wall& rhs) const{
	float m1,m2;
	float p = (p2.X() - p1.X());
	float rhsp = (rhs.p2.X() - rhs.p1.X());
	//avoid dividing by zero
	if(p!=0) m1 = (p2.Y() - p1.Y()) / p;
	else m1 = 10000000;
	if(rhsp != 0) m2 = (rhs.p2.Y() - rhs.p1.Y()) / rhsp;
	else m2 = 10000000;

	if( abs(m1-m2)<EPSILON && ( (p1 == rhs.p2) || (rhs.p1==p2) ) ){ //one starts where the other ends
		return true;
	}
	return false;
}

const Wall& Wall::operator+(const Wall& rhs) const{
	Wall *w = new Wall(p1,p2);

	try{
		if((*w).IsContinuousLinear(rhs)){ //if straight wall
			if( p2 ==rhs.p1 )
				(*w).p2 = rhs.p2;

			if( p1 == rhs.p2)
				(*w).p1 = rhs.p1;
		}
		else
			throw ApplePearException();

		(*w).len = (*w).p1.FindDistance((*w).p2);
	}

	catch(ApplePearException& ap){
		cout<<ap.what()<<endl;
	}

	return *w;
}

bool Wall::canSum(const Wall& rhs){
	Wall *w = new Wall(p1,p2);
	bool res = false;
	if( (*w).IsContinuousLinear(rhs) ){
		res = true;
	}
	delete w;
	return res;
}

Wall::~Wall(){

}
