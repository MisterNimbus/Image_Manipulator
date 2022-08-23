
class ColorSphere
{
private:
    int sphere_center_X;
    int sphere_center_Y;
    int sphere_center_Z;
    int sphere_radius;
    int sphere_theta_start;
    int sphere_phi_start;
    float sphere_theta_vel;
    float sphere_phi_vel;
    float phi;
    float theta;
public:
    ColorSphere(int sphere_center_X,
                int sphere_center_Y,
                int sphere_center_Z,
                int sphere_radius,
                int sphere_theta_start,
                int sphere_phi_start);
    ~ColorSphere();
    void update();
    int getR();
    int getG();
    int getB();
    float getDistanceToBlack();
};

