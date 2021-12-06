#include "Particle.h"

Particle::Particle(void) : x(0), y(0), vx(0), vy(0), ax(0), ay(0), omega(0), phi(0), radius(0), mx(0), my(0), lastupdate(0), life(0), color(0), exist(false){}
Particle::~Particle(void) {

}
void Particle::init(void) {
	x = rand() * 800;
	y = 0;
	vx = 0;
	vy = 24.5;
	ax = 0;
	ay = 0.98;
	radius = 5;
	life = rand() * 5 + 15;
	color = RGB(255, 255, 255);
	timer.reset();
	lastupdate = 0;
	exist = static_cast<int>(rand() * 800) == 8;
}
void Particle::clean(void) {

}
void Particle::update(void) {
	double t = timer.get();
	if (t < life && y <= 600 && exist) {
		double dt = t - lastupdate;
		vx += ax * dt;
		vy += ay * dt;
		x += vx * dt;
		y += vy * dt;
		//radius = (-10 / life) * t + 10;
		//double RG = 255 * t / life;
		//color = RGB(RG, RG, 0xFF);
		lastupdate = timer.get();
	}
	else {
		clean();
		init();
	}
}
void Particle::draw(void) {
	if (exist) {
		SelectObject(hdc, GetStockObject(DC_PEN));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCPenColor(hdc, color);
		SetDCBrushColor(hdc, color);
		Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	}
}
void Particle::setCursorPos(int mx, int my) {
	this->mx = mx;
	this->my = my;
}
void Particle::setHDC(HDC hdc) {
	this->hdc = hdc;
}
void Particle::setBlow(int ax) {
	this->ax = ax;
}
double Particle::rand(void) {
	return static_cast<double>(::rand()) / RAND_MAX;
}