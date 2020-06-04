#include "Particle.h"

Particle::Particle(float x,float y){
	x_coord = x;
	y_coord = y;
}

Particle::Particle(const Particle& rhs){
	x_coord = rhs.x_coord;
	y_coord = rhs.y_coord;
}

float Particle::X() const{
	return x_coord;
}

float Particle::Y() const{
	return y_coord;
}

float Particle::FindDistance(const Particle& p) const{
	float x = x_coord - p.x_coord;
	float y = y_coord - p.y_coord;
	return sqrt(pow(x, 2) + pow(y, 2));
}

bool Particle::operator== (const Particle& p) const{
	if( (abs(p.x_coord - x_coord) < EPSILON) && (abs(p.y_coord - y_coord) < EPSILON) )
		return true;
	return false;
}

ostream& operator<<(ostream& os, const Particle& p){
	os<<'('<<p.X()<<','<<p.Y()<<')';
	return os;
}

