
#ifndef GPS_H
#define GPS_H

class gps
{
    friend std::ostream & operator<<(std::ostream &os, const gps &gp);

    /* Decimal format */
    double degrees;
public:
    gps(double d):degrees(d){}
};

std::ostream & operator<<(std::ostream &os, const gps &gp) {
    return os << gp.degrees;
}

#endif