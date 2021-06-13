
#ifndef GPS_H
#define GPS_H

class gps
{
    friend std::ostream & operator<<(std::ostream &os, const gps &gp);

public:
    /* Decimal format */
    double degrees;
    gps(double d):degrees(d){}
};

std::ostream & operator<<(std::ostream &os, const gps &gp) {
    return os << gp.degrees;
}

#endif