#include <iostream>


// Point on cartesian plane
class Point{
    public:
        /* @brief   Initialize the point at origin (0, 0)
         */
        Point();
        /* @brief   Initialize the point at given coords
         * @param   _x  Horizontal position from the origin (0, 0)
         * @param   _y  Vertical position from the origin (0, 0)
         */
        Point(double _x, double _y);

        /* @brief   Set point's coords to given coords
         * @param   _x  New horizontal position
         * @param   _y  New vertical position
         */
        void Set(double _x, double _y);
        /* @brief   Add given values to point's coords respectively
         * @param   dx  Change added to x coordinate value of the point
         * @param   dy  Change added to y coordinate value of the point
         */
        void Move(double dx, double dy);
        // @brief   Rotate point around the origion 90 degrees clockwise
        void Rotate90();

        // @brief   Get x coordinate of the point
        double GetX() const;
        // @brief   Get y coordinate of the point
        double GetY() const;
    private:
        double x;   // Horizontal position of the point
        double y;   // Vertical position of the point
};



int main(){

    // Initialize some points
    Point a(3, 4), b(2, 7), c(-4, -4), d;

    // Print point a
    std::cout << a.GetX() << " " << a.GetY() << std::endl;
    std::cout << d.GetX() << " " << d.GetY() << std::endl;

    // Move point a by horizontal position of point b in horizontal and by vertical position of point c in vertical
    a.Move(b.GetX(), c.GetY());
    std::cout << a.GetX() << " " << a.GetY() << std::endl;  // Print the result

    // Rotate point a 90 degrees clocwise
    a.Rotate90();
    std::cout << a.GetX() << " " << a.GetY() << std::endl;  // Print the result

    // Set horizontal and vertical position of point a to 14 and 53 respectively
    a.Set(14, 53);
    std::cout << a.GetX() << " " << a.GetY() << std::endl;  // Print the result

    return 0;
}



// Call other constructor method with values 0 and 0 to set point to origin
Point::Point() : Point(0, 0) {}
Point::Point(double _x, double _y) : x(_x), y(_y) {}

void Point::Set(double _x, double _y){
    x = _x;
    y = _y;
}

void Point::Move(double dx, double dy){
    x += dx;
    y += dy;
}

void Point::Rotate90(){
    double temp = x;    // Temporary variable to store intial x coordinate of the point to swap with y afterwards
    x = y;
    y = -temp;
}

double Point::GetX() const{
    return x;
}

double Point::GetY() const{
    return y;
}
