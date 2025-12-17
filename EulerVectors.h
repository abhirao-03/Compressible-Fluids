#include <iostream>

class vec3 {
    public:
        double m_dVars[3];

        vec3() : m_dVars{0.0, 0.0, 0.0} {};
        vec3(double u_dVar0, double u_dVar1, double u_dVar2) : m_dVars{u_dVar0, u_dVar1, u_dVar2} {};

        double m_dRho() const {return m_dVars[0];};
        double m_dMomentum() const {return m_dVars[1];};
        double d_dEnergy() const {return m_dVars[2];}

        vec3 operator-() const {return vec3(-m_dVars[0], -m_dVars[1], -m_dVars[2]);}
        double operator[](int u_iInt) const {return m_dVars[u_iInt];}
        double& operator[](int u_iInt) {return m_dVars[u_iInt];}
        
        int size()
            {
                return sizeof(m_dVars) / sizeof(m_dVars[0]);
            }

        vec3& operator+=(const vec3& u_vVec)
            {
                m_dVars[0] += u_vVec[0];
                m_dVars[1] += u_vVec[1];
                m_dVars[2] += u_vVec[2];

                return *this;
            }
        
        vec3& operator*=(const double& t)
            {
                m_dVars[0] *= t;
                m_dVars[1] *= t;
                m_dVars[2] *= t;

                return *this;
            }
            
        vec3& operator/=(const double& t)
            {
                return *this *= 1/t;
            }
};

inline vec3 operator+(const vec3& u_vVector1, const vec3& u_vVector2)
    {
        return vec3(u_vVector1[0] + u_vVector2[0],
                    u_vVector1[1] + u_vVector2[1],
                    u_vVector1[2] + u_vVector2[2]);
    }

inline vec3 operator+(const double& u_dScalar, const vec3& u_vVector2)
    {
        return vec3(u_dScalar + u_vVector2[0],
                    u_dScalar + u_vVector2[1],
                    u_dScalar + u_vVector2[2]);
    }

inline vec3 operator+(const vec3& u_vVector1, const double& u_dScalar)
    {
        return u_dScalar + u_vVector1;
    }

inline vec3 operator-(const vec3& u_vVector1, const vec3& u_vVector2)
    {
        return vec3(u_vVector1[0] - u_vVector2[0],
                    u_vVector1[1] - u_vVector2[1],
                    u_vVector1[2] - u_vVector2[2]);
    }

inline vec3 operator*(const vec3& u_vVector1, const vec3& u_vVector2)
    {
        return vec3(u_vVector1[0]*u_vVector2[0], u_vVector1[1]*u_vVector2[1], u_vVector1[2]*u_vVector2[2]);
    }

inline vec3 operator*(const vec3& u_vVector, const double& u_dScalar)
    {
        return vec3(u_dScalar*u_vVector[0], u_dScalar*u_vVector[1], u_dScalar*u_vVector[2]);
    }

inline vec3 operator*(const double& u_dScalar, const vec3& u_vVector)
    { 
        return u_vVector * u_dScalar;
    }

inline vec3 operator/(const vec3& u_vVector1, const vec3& u_vVcetor2)
    {
        return vec3(u_vVector1[0] / u_vVcetor2[0], u_vVector1[1] / u_vVcetor2[1], u_vVector1[2] / u_vVcetor2[2]);
    }


inline vec3 operator/(const double& u_dScalar, const vec3& u_vVector)
    {
        return (1/u_dScalar) * u_vVector;
    }


inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
    os << v[0] << " " << v[1] << " " << v[2];
    return os;
}