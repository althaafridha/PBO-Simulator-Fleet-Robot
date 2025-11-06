#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

class Vehicle {
public:
    struct Position {
        double x, y, z;
    };

protected:
    string id;
    Position pos;
    double battery;

public:
    Vehicle(string i, double x, double y, double z, double b) {
        id = i;
        pos.x = x;
        pos.y = y;
        pos.z = z;
        battery = b;
    }

    virtual void move(double dx, double dy, double dz) = 0;

    virtual void status() {
        cout << "[" << id << "] Pos("
             << fixed << setprecision(2)
             << pos.x << "," << pos.y << "," << pos.z
             << ") Battery=" << battery << "%" << endl;
    }

    bool consumeBattery(double amount) {
        if (battery <= 0) {
            cout << "[" << id << "] Baterai habis.\n";
            return false;
        }
        battery -= amount;
        if (battery < 0) battery = 0;
        return true;
    }

    Position getPos() { return pos; }
    string getId() { return id; }
};

/**
 * GroundRobot
*/
class GroundRobot : public Vehicle {
public:
    double obstacleX[2] = {3.0, 6.0};
    double obstacleY[2] = {3.0, 1.5};

    GroundRobot(string i, double x, double y, double z, double b)
        : Vehicle(i, x, y, z, b) {}

    bool obstacleAhead(double range) {
        for (int i = 0; i < 2; i++) {
            double dist = sqrt(pow(obstacleX[i] - pos.x, 2) +
                               pow(obstacleY[i] - pos.y, 2));
            if (dist <= range) return true;
        }
        return false;
    }

    void move(double dx, double dy, double dz) {
        double dist = sqrt(dx * dx + dy * dy);
        cout << "> " << id << ": move(" << dx << "," << dy << "," << dz << ")\n";
        if (obstacleAhead(1.0)) {
            cout << "[" << id << "] Ada rintangan di depan! Gerak dibatalkan.\n";
            status();
            return;
        }

        if (!consumeBattery(dist * 0.8)) return;

        pos.x += dx;
        pos.y += dy;
        cout << "[" << id << "] Bergerak ke (" 
             << pos.x << "," << pos.y << "," << pos.z << ")\n";
        status();
    }

    void move(double headingDeg, double distance) {
        double rad = headingDeg * 3.14159 / 180.0;
        double dx = cos(rad) * distance;
        double dy = sin(rad) * distance;
        move(dx, dy, 0);
    }
};

/**
 * AerialDrone
*/
class AerialDrone : public Vehicle {
public:
    AerialDrone(string i, double x, double y, double z, double b)
        : Vehicle(i, x, y, z, b) {}

    void move(double dx, double dy, double dz) {
        double dist = sqrt(dx * dx + dy * dy + dz * dz);
        cout << "> " << id << ": move(" << dx << "," << dy << "," << dz << ")\n";
        if (!consumeBattery(dist * 1.5)) return;

        pos.x += dx;
        pos.y += dy;
        pos.z += dz;

        cout << "[" << id << "] Drone ke (" 
             << pos.x << "," << pos.y << "," << pos.z << ")\n";
        status();
    }

    void move(Position target) {
        cout << "> " << id << ": move(targetPosition)\n";
        double dx = target.x - pos.x;
        double dy = target.y - pos.y;
        double dz = target.z - pos.z;
        move(dx, dy, dz);
    }
};

/**
 * Amphibious
*/
class Amphibious : public Vehicle {
    bool airMode;

public:
    Amphibious(string i, double x, double y, double z, double b)
        : Vehicle(i, x, y, z, b), airMode(false) {}

    void move(double dx, double dy, double dz) {
        if (dz != 0) {
            airMode = true;
            cout << "[" << id << "] Mode udara aktif.\n";
            double dist = sqrt(dx * dx + dy * dy + dz * dz);
            if (!consumeBattery(dist * 1.8)) return;
            pos.x += dx; pos.y += dy; pos.z += dz;
        } else {
            airMode = false;
            cout << "[" << id << "] Mode darat aktif.\n";
            double dist = sqrt(dx * dx + dy * dy);
            if (dist > 5) {
                cout << "[" << id << "] Rintangan di depan! Beralih ke udara.\n";
                move(dx, dy, 1.0);
                return;
            }
            if (!consumeBattery(dist * 1.2)) return;
            pos.x += dx; pos.y += dy;
        }

        status();
    }

    void status() {
        cout << "[" << id << "] Amphibious Pos("
             << pos.x << "," << pos.y << "," << pos.z
             << ") Mode=" << (airMode ? "Air" : "Ground")
             << " Battery=" << battery << "%" << endl;
    }
};

void executeMove(Vehicle* v, double dx, double dy, double dz) {
    v->move(dx, dy, dz);
}

int main() {
    cout << "=== Simulator Fleet Robot Polymorfik ===\n\n";

    GroundRobot g1("GR1", 0, 0, 0, 50);
    AerialDrone d1("AD1", 0, 0, 5, 70);
    Amphibious a1("AM1", 0, -2, 0, 80);

    Vehicle* fleet[3] = {&g1, &d1, &a1};

    cout << "--- Kondisi Awal ---\n";
    for (int i = 0; i < 3; i++) fleet[i]->status();

    cout << "\n Case 1: GroundRobot move(1.0,0.0,0.0)\n";
    g1.move(1.0, 0.0, 0.0);

    cout << "\n2️Case 2: GroundRobot coba ke obstacle (jarak dekat)\n";
    g1.move(2.0, 1.0, 0.0);

    cout << "\n Case 3: AerialDrone move(targetPosition)\n";
    Vehicle::Position target = {5.0, 5.0, 10.0};
    d1.move(target);

    cout << "\n Case 4: Fleet jalankan misi 3 Waypoints\n";
    Vehicle::Position wp[3] = {
        {2, 1, 0},
        {5, 3, 2},
        {8, 0, 0}
    };

    for (int w = 0; w < 3; w++) {
        cout << "\nWaypoint " << (w + 1)
             << " (" << wp[w].x << "," << wp[w].y << "," << wp[w].z << ")\n";

        g1.move(wp[w].x - g1.getPos().x, wp[w].y - g1.getPos().y, 0);
        d1.move(wp[w].x - d1.getPos().x, wp[w].y - d1.getPos().y, wp[w].z - d1.getPos().z);
        a1.move(wp[w].x - a1.getPos().x, wp[w].y - a1.getPos().y, wp[w].z - a1.getPos().z);
    }

    cout << "\n--- Kondisi Akhir Setelah Semua Case ---\n";
    for (int i = 0; i < 3; i++) fleet[i]->status();

    cout << "\n===Semua Case Selesai Diuji===\n";
    return 0;
}
