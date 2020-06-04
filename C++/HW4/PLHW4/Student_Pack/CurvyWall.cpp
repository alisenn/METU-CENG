#include "CurvyWall.h"

CurvyWall::CurvyWall(float _len, float rad){
	len = _len;
	radius = rad;
}

CurvyWall::CurvyWall(const Particle& sp, const Particle& ep, const Particle& cp){
	p1 = sp;
	p2 = ep;
	centerP = cp;
	radius = p1.FindDistance(centerP);
	ComputeLength();
}

CurvyWall::CurvyWall(const CurvyWall& rhs){
	len = rhs.len;
	radius = rhs.radius;
	p1 = rhs.p1;
	p2 = rhs.p2;
	centerP = rhs.centerP;
}

float CurvyWall::GetRadius() const{
	return radius;
}

const Particle& CurvyWall::GetCenter() const{
	return centerP;
}

void CurvyWall::ComputeLength(){
	Wall w1(p1,centerP);
	Wall w2(p2,centerP);
	float ang = w1.FindAngleBetween(w2);
	float diameter = radius*2;
	len = (PI * diameter) * (ang / 360.0);

}

Wall* CurvyWall::Clone() const{
	return new CurvyWall(*this);
}

bool CurvyWall::IsContinuousLinear(const Wall& rhs) const{
	return false;
}

const Wall& CurvyWall::operator+(const Wall& rhs) const{
	CurvyWall *cw = new CurvyWall(p1,p2,centerP);
	try{
		if(centerP == rhs.centerP){
			if(p1 == rhs.p2)
				(*cw).p1 = rhs.p1;

			if(p2 == rhs.p1)
				(*cw).p2 = rhs.p2;
		}
		else
			throw ApplePearException();
		(*cw).len = len + rhs.len;

	}
	catch(ApplePearException& ap){
		cout<<ap.what()<<endl;
	}
	return *cw;

}
bool CurvyWall::canSum(const Wall& rhs){
	
	if( (centerP == rhs.centerP) && ( (p1 == rhs.p2) || (p2 == rhs.p1) )){
		return true;
	}
	return false;
}


CurvyWall::~CurvyWall(){

}
