#include <iostream>
#include <cmath>

// Digamos que tienes dos clases con interfaces compatibles:
// RoundHole (HoyoRedondo) y RoundPeg (PiezaRedonda).

class RoundHole {
public:
    RoundHole(double radius) : radius(radius) {}

    double getRadius() {
        // Devuelve el radio del agujero.
        return radius;
    }

    bool fits(class RoundPeg* peg);

private:
    double radius;
};

class RoundPeg {
public:
    RoundPeg(double radius) : radius(radius) {}

    double getRadius() {
        // Devuelve el radio de la pieza.
        return radius;
    }

private:
    double radius;
};

bool RoundHole::fits(RoundPeg* peg) {
    return this->getRadius() >= peg->getRadius();
}

// Pero hay una clase incompatible: TrianglePeg (PiezaTriangular).
class TrianglePeg {
public:
    TrianglePeg(double base, double height) : base(base), height(height) {}

    double getBase() {
        // Devuelve la base de la pieza triangular.
        return base;
    }

    double getHeight() {
        // Devuelve la altura de la pieza triangular.
        return height;
    }

private:
    double base;
    double height;
};

// Una clase adaptadora te permite encajar piezas triangulares en
// hoyos redondos. Extiende la clase RoundPeg para permitir a
// los objetos adaptadores actuar como piezas redondas.
class TrianglePegAdapter : public RoundPeg {
public:
    TrianglePegAdapter(TrianglePeg* peg) : RoundPeg(peg->getBase()* std::sqrt(3) / 3), peg(peg) {}

private:
    TrianglePeg* peg;
};

int main() {
    RoundHole hole(5);
    RoundPeg rpeg(5);
    std::cout << "Fits round peg: " << std::boolalpha << hole.fits(&rpeg) << std::endl;

    TrianglePeg small_tripeg(5, 8);
    TrianglePeg large_tripeg(10, 15);

    TrianglePegAdapter small_tripeg_adapter(&small_tripeg);
    TrianglePegAdapter large_tripeg_adapter(&large_tripeg);
    std::cout << "Fits small triangle peg: " << std::boolalpha << hole.fits(&small_tripeg_adapter) << std::endl;
    std::cout << "Fits large triangle peg: " << std::boolalpha << hole.fits(&large_tripeg_adapter) << std::endl;

    return 0;
}