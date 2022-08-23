#include "ColorSphere.h"
#include <math.h>
#include <memory>

ColorSphere::ColorSphere(int sphere_center_X,
                int sphere_center_Y,
                int sphere_center_Z,
                int sphere_radius,
                int sphere_theta_start,
                int sphere_phi_start):
                sphere_center_X(sphere_center_X),
                sphere_center_Y(sphere_center_Y),
                sphere_center_Z(sphere_center_Z),
                sphere_radius(sphere_radius),
                sphere_theta_start(sphere_theta_start),
                sphere_phi_start(sphere_phi_start)
{
    srand ( time(NULL) );
    this->sphere_theta_vel = (rand() % 3 + 1) * 0.05;
    this->sphere_phi_vel = (rand() % 3 + 1) * 0.05;
        
    this->theta = sphere_theta_start;
    this->phi = sphere_phi_start;
}

ColorSphere::~ColorSphere()
{

}

void ColorSphere::update()
{
    this->phi += this->sphere_phi_vel;
    if(this->phi - 2*M_PI > 0){
        //this->phi -= 2*M_PI;
        this->sphere_phi_vel = (rand() % 3 + 1) * 0.05;
    }
    this->theta += this->sphere_theta_vel;
    if(this->theta - M_PI > 0){
        //this->theta -= M_PI;
        this->sphere_theta_vel = -(rand() % 3 + 1) * 0.05;
    }
}

int ColorSphere::getR()
{
    return this->sphere_center_X + this->sphere_radius * sin(this->theta) * cos(this->phi);
}

int ColorSphere::getG()
{
    return this->sphere_center_Y + this->sphere_radius * sin(this->theta) * sin(this->phi);
}

int ColorSphere::getB()
{
    return this->sphere_center_Z + this->sphere_radius * cos(this->theta);
}

float ColorSphere::getDistanceToBlack()
{
    return sqrt(this->getR()*this->getR()+this->getB()*this->getB() + this->getG()*this->getG());
}