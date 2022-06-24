#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 5
//  Netiva Hidayah (672020060)
//  David Aji Saputra (672020157)
//  Alfin Pendekan (672020160)
//  Dita Ayu Ramadiyanti (672020177)
//  Krisna Adi Saputra (672020178)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion {
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init() {
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3ub(2, 116, 4);
    glVertex3f(-1000.0, 0, -1000.0);
    glVertex3f(1000.0, 0, -1000.0);
    glVertex3f(1000.0, 0, 1000.0);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}

void tumpukan() {

    //Atas

    glColor3ub(169, 169, 169);
    glPushMatrix();
    glTranslatef(0.0, 100.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-500.0, 0.0, -500.0);
    glVertex3f(500.0, 0.0, -500.0);
    glVertex3f(500.0, 0.0, 500.0);
    glVertex3f(-500.0, 0.0, 500.0);
    glEnd();
    glPopMatrix();

    //Depan
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3f(-500.0, 100.0, 500.0);
    glVertex3f(500.0, 100.0, 500.0);
    glVertex3f(500.0, 0.0, 650.0);
    glVertex3f(-500.0, 0.0, 650.0);
    glEnd();
    glPopMatrix();

    //Belakang
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3f(-500.0, 100.0, -500.0);
    glVertex3f(500.0, 100.0, -500.0);
    glVertex3f(500.0, 0.0, -500.0);
    glVertex3f(-500.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    //Samping Kiri
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, 100.0, 500.0);
    glVertex3f(-500.0, 0.0, 650.0);
    glVertex3f(-500.0, 0.0, -500.0);
    glVertex3f(-500.0, 100.0, -500.0);
    glEnd();
    glPopMatrix();

    //Samping Kanan
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(500.0, 100.0, 500.0);
    glVertex3f(500.0, 0.0, 650.0);
    glVertex3f(500.0, 0.0, -500.0);
    glVertex3f(500.0, 100.0, -500.0);
    glEnd();
    glPopMatrix();

    //Tangga
    // 1
    glColor3ub(100, 100, 100);
    glPushMatrix();
    glTranslatef(0.0, -100.0, 417.0);
    //Depan
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, 100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, -100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping kiri
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(-495, 200, 100);
    glVertex3f(-495, 190, 100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping Kanan
    glBegin(GL_POLYGON);
    glVertex3f(500, 200, -100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(500, 190, -100);
    glEnd();
    //Atas dan bawah
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    glPopMatrix();
    //2
    glPushMatrix();
    glTranslatef(0, -113, 434);
    //Depan
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, 100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, -100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping kiri
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(-495, 200, 100);
    glVertex3f(-495, 190, 100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping Kanan
    glBegin(GL_POLYGON);
    glVertex3f(500, 200, -100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(500, 190, -100);
    glEnd();
    //Atas dan bawah
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    glPopMatrix();
    //3
    glPushMatrix();
    glTranslatef(0, -126, 449);
    //Depan
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, 100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, -100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping kiri
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(-495, 200, 100);
    glVertex3f(-495, 190, 100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping Kanan
    glBegin(GL_POLYGON);
    glVertex3f(500, 200, -100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(500, 190, -100);
    glEnd();
    //Atas dan bawah
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    glPopMatrix();
    //4
    glPushMatrix();
    glTranslatef(0.0, -137, 470);
    //Depan
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, 100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, -100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping kiri
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(-495, 200, 100);
    glVertex3f(-495, 190, 100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping Kanan
    glBegin(GL_POLYGON);
    glVertex3f(500, 200, -100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(500, 190, -100);
    glEnd();
    //Atas dan bawah
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    glPopMatrix();
    //5
    glPushMatrix();
    glTranslatef(0, -150, 490);
    //Depan
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, 100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, -100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping kiri
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(-495, 200, 100);
    glVertex3f(-495, 190, 100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping Kanan
    glBegin(GL_POLYGON);
    glVertex3f(500, 200, -100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(500, 190, -100);
    glEnd();
    //Atas dan bawah
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    glPopMatrix();
    //6
    glPushMatrix();
    glTranslatef(0, -164, 512);
    //Depan
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, 100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, -100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping kiri
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(-495, 200, 100);
    glVertex3f(-495, 190, 100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping Kanan
    glBegin(GL_POLYGON);
    glVertex3f(500, 200, -100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(500, 190, -100);
    glEnd();
    //Atas dan bawah
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    glPopMatrix();
    //7
    glPushMatrix();
    glTranslatef(0, -178, 532);
    //Depan
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, 100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, -100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping kiri
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(-495, 200, 100);
    glVertex3f(-495, 190, 100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping Kanan
    glBegin(GL_POLYGON);
    glVertex3f(500, 200, -100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(500, 190, -100);
    glEnd();
    //Atas dan bawah
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    glPopMatrix();
    //8
    glPushMatrix();
    glTranslatef(0, -191, 550);
    //Depan
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, 100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, -100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping kiri
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(-495, 200, 100);
    glVertex3f(-495, 190, 100);
    glVertex3f(-500, 190, -100);
    glEnd();
    //Samping Kanan
    glBegin(GL_POLYGON);
    glVertex3f(500, 200, -100);
    glVertex3f(495, 200, 100);
    glVertex3f(495, 190, 100);
    glVertex3f(500, 190, -100);
    glEnd();
    //Atas dan bawah
    glBegin(GL_POLYGON);
    glVertex3f(-500, 200, -100);
    glVertex3f(495, 200, -100);
    glVertex3f(495, 190, 100);
    glVertex3f(-500, 190, 100);
    glEnd();
    glPopMatrix();
}

void lantai1() {
    glColor3ub(242, 195, 151);
    //belakang l1
    glPushMatrix();
    glTranslatef(0, 99, 134);
    glBegin(GL_QUADS);
    glVertex3f(-380.0, 250.0, -500.0);
    glVertex3f(380.0, 250.0, -500.0);
    glVertex3f(380.0, 0.0, -500.0);
    glVertex3f(-380.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    //samping kiri l1
    glPushMatrix();
    glTranslatef(21, 99, -36);
    glBegin(GL_QUADS);
    glVertex3f(-400.0, 250.0, 330.0);
    glVertex3f(-400.0, 0.0, 330.0);
    glVertex3f(-400.0, 0.0, -330.0);
    glVertex3f(-400.0, 250.0, -330.0);
    glEnd();
    glPopMatrix();

    //samping kanan l1
    glPushMatrix();
    glTranslatef(779, 99, -36);
    glBegin(GL_QUADS);
    glVertex3f(-400.0, 250.0, 330.0);
    glVertex3f(-400.0, 0.0, 330.0);
    glVertex3f(-400.0, 0.0, -330.0);
    glVertex3f(-400.0, 250.0, -330.0);
    glEnd();
    glPopMatrix();

    //depan l1
    glPushMatrix();
    glTranslatef(0, 99, 794);
    glBegin(GL_QUADS);
    glVertex3f(-380.0, 250.0, -500.0);
    glVertex3f(380.0, 250.0, -500.0);
    glVertex3f(380.0, 0.0, -500.0);
    glVertex3f(-380.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    //atas l1
    glPushMatrix();
    glTranslatef(0, 350, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glVertex3f(480.0, 0.0, -430.0);
    glVertex3f(480.0, 0.0, 430.0);
    glVertex3f(-480.0, 0.0, 430.0);
    glEnd();
    glPopMatrix();

    //atas 2 l1
    glPushMatrix();
    glTranslatef(0, 330, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glVertex3f(480.0, 0.0, -430.0);
    glVertex3f(480.0, 0.0, 430.0);
    glVertex3f(-480.0, 0.0, 430.0);
    glEnd();
    glPopMatrix();

    //atas belakang  l1
    glPushMatrix();
    glTranslatef(0, 330, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-480.0, 20.0, -430.0);
    glVertex3f(480.0, 20.0, -430.0);
    glVertex3f(480.0, 0.0, -430.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glEnd();
    glPopMatrix();

    //atas depan  l1
    glPushMatrix();
    glTranslatef(0, 330, 860);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-480.0, 20.0, -430.0);
    glVertex3f(480.0, 20.0, -430.0);
    glVertex3f(480.0, 0.0, -430.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glEnd();
    glPopMatrix();

    //atas kiri l1
    glPushMatrix();
    glTranslatef(0, 330, 0);
    glBegin(GL_QUADS);
    glVertex3f(-480.0, 20.0, 430.0);
    glVertex3f(-480.0, 0.0, 430.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glVertex3f(-480.0, 20.0, -430.0);
    glEnd();
    glPopMatrix();

    //atas kanan l1
    glPushMatrix();
    glTranslatef(959, 330, 0);
    glBegin(GL_QUADS);
    glVertex3f(-480.0, 20.0, 430.0);
    glVertex3f(-480.0, 0.0, 430.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glVertex3f(-480.0, 20.0, -430.0);
    glEnd();
    glPopMatrix();
}
void lantai2() {
    glColor3ub(242, 195, 151);
    //belakang l2
    glPushMatrix();
    glTranslatef(0, 349, 190);
    glBegin(GL_QUADS);
    glVertex3f(-300.0, 300.0, -500.0);
    glVertex3f(300.0, 300.0, -500.0);
    glVertex3f(300.0, 0.0, -500.0);
    glVertex3f(-300.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    //depan l2
    glPushMatrix();
    glTranslatef(0, 349, 749);
    glBegin(GL_QUADS);
    glVertex3f(-300.0, 300.0, -500.0);
    glVertex3f(300.0, 300.0, -500.0);
    glVertex3f(300.0, 0.0, -500.0);
    glVertex3f(-300.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    //samping kiri l2
    glPushMatrix();
    glTranslatef(-50, 349, -31);
    glBegin(GL_QUADS);
    glVertex3f(-250.0, 300.0, 280.0);
    glVertex3f(-250.0, 0.0, 280.0);
    glVertex3f(-250.0, 0.0, -280.0);
    glVertex3f(-250.0, 300.0, -280.0);
    glEnd();
    glPopMatrix();

    //samping kanan l2
    glPushMatrix();
    glTranslatef(550, 349, -31);
    glBegin(GL_QUADS);
    glVertex3f(-250.0, 300.0, 280.0);
    glVertex3f(-250.0, 0.0, 280.0);
    glVertex3f(-250.0, 0.0, -280.0);
    glVertex3f(-250.0, 300.0, -280.0);
    glEnd();
    glPopMatrix();

    //atas 1 l2
    glPushMatrix();
    glTranslatef(0, 649, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-380.0, 0.0, -330.0);
    glVertex3f(380.0, 0.0, -330.0);
    glVertex3f(380.0, 0.0, 330.0);
    glVertex3f(-380.0, 0.0, 330.0);
    glEnd();
    glPopMatrix();

    //atas 2 l2
    glPushMatrix();
    glTranslatef(0, 669, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-380.0, 0.0, -330.0);
    glVertex3f(380.0, 0.0, -330.0);
    glVertex3f(380.0, 0.0, 330.0);
    glVertex3f(-380.0, 0.0, 330.0);
    glEnd();
    glPopMatrix();

    //atas belakang  l2
    glPushMatrix();
    glTranslatef(0, 649, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-380.0, 20.0, -330.0);
    glVertex3f(380.0, 20.0, -330.0);
    glVertex3f(380.0, 0.0, -330.0);
    glVertex3f(-380.0, 0.0, -330.0);
    glEnd();
    glPopMatrix();

    //atas depan  l2
    glPushMatrix();
    glTranslatef(1, 649, 660);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-380.0, 20.0, -330.0);
    glVertex3f(380.0, 20.0, -330.0);
    glVertex3f(380.0, 0.0, -330.0);
    glVertex3f(-380.0, 0.0, -330.0);
    glEnd();
    glPopMatrix();

    //atas kiri l2
    glPushMatrix();
    glTranslatef(0, 649, 0);
    glBegin(GL_QUADS);
    glVertex3f(-380.0, 20.0, 330.0);
    glVertex3f(-380.0, 0.0, 330.0);
    glVertex3f(-380.0, 0.0, -330.0);
    glVertex3f(-380.0, 20.0, -330.0);
    glEnd();
    glPopMatrix();

    //atas kanan l2
    glPushMatrix();
    glTranslatef(760, 649, 0);
    glBegin(GL_QUADS);
    glVertex3f(-380.0, 20.0, 330.0);
    glVertex3f(-380.0, 0.0, 330.0);
    glVertex3f(-380.0, 0.0, -330.0);
    glVertex3f(-380.0, 20.0, -330.0);
    glEnd();
    glPopMatrix();

}
void lantai3() {
    glColor3ub(242, 195, 151);
    //belakang l3
    glPushMatrix();
    glTranslatef(0, 667, 269);
    glBegin(GL_QUADS);
    glVertex3f(-270.0, 300.0, -500.0);
    glVertex3f(270.0, 300.0, -500.0);
    glVertex3f(270.0, 0.0, -500.0);
    glVertex3f(-270.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    //depan l3
    glPushMatrix();
    glTranslatef(1, 667, 692);
    glBegin(GL_QUADS);
    glVertex3f(-270.0, 300.0, -500.0);
    glVertex3f(270.0, 300.0, -500.0);
    glVertex3f(270.0, 0.0, -500.0);
    glVertex3f(-270.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    //samping kiri l3
    glPushMatrix();
    glTranslatef(-19, 667, -19);
    glBegin(GL_QUADS);
    glVertex3f(-250.0, 300.0, 212.0);
    glVertex3f(-250.0, 0.0, 212.0);
    glVertex3f(-250.0, 0.0, -212.0);
    glVertex3f(-250.0, 300.0, -212.0);
    glEnd();
    glPopMatrix();

    //samping kanan l3
    glPushMatrix();
    glTranslatef(520, 667, -20);
    glBegin(GL_QUADS);
    glVertex3f(-250.0, 300.0, 212.0);
    glVertex3f(-250.0, 0.0, 212.0);
    glVertex3f(-250.0, 0.0, -212.0);
    glVertex3f(-250.0, 300.0, -212.0);
    glEnd();
    glPopMatrix();

    //atas 1 l3
    glPushMatrix();
    glTranslatef(0, 967, -1);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-395.0, 0.0, -350.0);
    glVertex3f(395.0, 0.0, -350.0);
    glVertex3f(395.0, 0.0, 350.0);
    glVertex3f(-395.0, 0.0, 350.0);
    glEnd();
    glPopMatrix();

    //atas 2 l3
    glPushMatrix();
    glTranslatef(0, 987, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-395.0, 0.0, -350.0);
    glVertex3f(395.0, 0.0, -350.0);
    glVertex3f(395.0, 0.0, 350.0);
    glVertex3f(-395.0, 0.0, 350.0);
    glEnd();
    glPopMatrix();

    //atas belakang  l3
    glPushMatrix();
    glTranslatef(0, 967, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-395.0, 20.0, -350.0);
    glVertex3f(395.0, 20.0, -350.0);
    glVertex3f(395.0, 0.0, -350.0);
    glVertex3f(-395.0, 0.0, -350.0);
    glEnd();
    glPopMatrix();

    //atas depan  l3
    glPushMatrix();
    glTranslatef(1, 967, 700);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-395.0, 20.0, -350.0);
    glVertex3f(395.0, 20.0, -350.0);
    glVertex3f(395.0, 0.0, -350.0);
    glVertex3f(-395.0, 0.0, -350.0);
    glEnd();
    glPopMatrix();

    //atas kiri l3
    glPushMatrix();
    glTranslatef(-15, 967, 20);
    glBegin(GL_QUADS);
    glVertex3f(-380.0, 20.0, 330.0);
    glVertex3f(-380.0, 0.0, 330.0);
    glVertex3f(-380.0, 0.0, -330.0);
    glVertex3f(-380.0, 20.0, -330.0);
    glEnd();
    glPopMatrix();

    //atas kanan l3
    glPushMatrix();
    glTranslatef(775, 967, 20);
    glBegin(GL_QUADS);
    glVertex3f(-380.0, 20.0, 330.0);
    glVertex3f(-380.0, 0.0, 330.0);
    glVertex3f(-380.0, 0.0, -330.0);
    glVertex3f(-380.0, 20.0, -330.0);
    glEnd();
    glPopMatrix();
}
void lantai4() {
    glPushMatrix();
    glTranslatef(0, 320, 0);
    lantai3();
    //pintuL4();
    //BALOK LANTAI 3 4
//balok depan
    glPushMatrix();
    glTranslatef(-8, 864, 408);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-270.0, 23.0, -210.0);
    glVertex3f(270.0, 23.0, -210.0);
    glVertex3f(270.0, 0.0, -210.0);
    glVertex3f(-270.0, 0.0, -210.0);
    glEnd();
    glPopMatrix();

    //balok belakang
    glPushMatrix();
    glTranslatef(0, 854, -24);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-280.0, 23.0, -210.0);
    glVertex3f(280.0, 23.0, -210.0);
    glVertex3f(280.0, 0.0, -210.0);
    glVertex3f(-280.0, 0.0, -210.0);
    glEnd();
    glPopMatrix();


    //kiri
    glPushMatrix();
    glTranslatef(280, 864, -8);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 210.0);
    glVertex3f(-550.0, 0.0, 210.0);
    glVertex3f(-550.0, 0.0, -210.0);
    glVertex3f(-550.0, 23.0, -210.0);
    glEnd();
    glPopMatrix();

    //kanan
    glPushMatrix();
    glTranslatef(824, 864, -24);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 210.0);
    glVertex3f(-550.0, 0.0, 210.0);
    glVertex3f(-550.0, 0.0, -210.0);
    glVertex3f(-550.0, 23.0, -210.0);
    glEnd();
    glPopMatrix();

    //lapisan balok depan
    glPushMatrix();
    glTranslatef(-8, 830, 408);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-270.0, 23.0, -210.0);
    glVertex3f(270.0, 23.0, -210.0);
    glVertex3f(270.0, 0.0, -210.0);
    glVertex3f(-270.0, 0.0, -210.0);
    glEnd();
    glPopMatrix();

    //lapisan balok belakang
    glPushMatrix();
    glTranslatef(0, 820, -24);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-280.0, 23.0, -210.0);
    glVertex3f(280.0, 23.0, -210.0);
    glVertex3f(280.0, 0.0, -210.0);
    glVertex3f(-280.0, 0.0, -210.0);
    glEnd();
    glPopMatrix();


    //lapisan kiri
    glPushMatrix();
    glTranslatef(280, 830, -8);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 210.0);
    glVertex3f(-550.0, 0.0, 210.0);
    glVertex3f(-550.0, 0.0, -210.0);
    glVertex3f(-550.0, 23.0, -210.0);
    glEnd();
    glPopMatrix();

    //lapisan kanan
    glPushMatrix();
    glTranslatef(824, 830, -24);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 210.0);
    glVertex3f(-550.0, 0.0, 210.0);
    glVertex3f(-550.0, 0.0, -210.0);
    glVertex3f(-550.0, 23.0, -210.0);
    glEnd();
    glPopMatrix();

    //balok tengah kiri(depan)
    glPushMatrix();
    glTranslatef(-192, 728, 496);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-70.0, 23.0, -300.0);
    glVertex3f(70.0, 23.0, -300.0);
    glVertex3f(70.0, 0.0, -300.0);
    glVertex3f(-70.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok tengah kiri(depan)
    glPushMatrix();
    glTranslatef(184, 728, 496);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-70.0, 23.0, -300.0);
    glVertex3f(70.0, 23.0, -300.0);
    glVertex3f(70.0, 0.0, -300.0);
    glVertex3f(-70.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok tengah kiri(belakang)
    glPushMatrix();
    glTranslatef(208, 728, 64);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-70.0, 23.0, -300.0);
    glVertex3f(70.0, 23.0, -300.0);
    glVertex3f(70.0, 0.0, -300.0);
    glVertex3f(-70.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok tengah kiri(belakang)
    glPushMatrix();
    glTranslatef(-192, 728, 64);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-78.0, 23.0, -300.0);
    glVertex3f(78.0, 23.0, -300.0);
    glVertex3f(78.0, 0.0, -300.0);
    glVertex3f(-78.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok kanan 1
    glPushMatrix();
    glTranslatef(824, 728, 104);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();

    //balok kanan 2
    glPushMatrix();
    glTranslatef(824, 728, -136);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();

    //balok kiri 1
    glPushMatrix();
    glTranslatef(280, 728, 112);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();

    //balok kiri 2
    glPushMatrix();
    glTranslatef(280, 728, -144);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}
void pagar_lantai1() {
    //Pager Tangga Kiri
    // Atas
    glPushMatrix();
    glTranslatef(0, -100, -1);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-500, 250, 500);
    glVertex3f(-490, 250, 500);
    glVertex3f(-490, 200, 500);
    glVertex3f(-500, 200, 500);
    glEnd();
    glPopMatrix();
    // Bawah
    glPushMatrix();
    glTranslatef(-1, -200, 155);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-500, 250, 500);
    glVertex3f(-490, 250, 500);
    glVertex3f(-490, 200, 500);
    glVertex3f(-500, 200, 500);
    glEnd();
    glPopMatrix();
    // Nyamping Bwah
    glPushMatrix();
    glTranslatef(0, -100, -1);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-500, 250, 500);
    glVertex3f(-490, 250, 500);
    glVertex3f(-490, 149, 657);
    glVertex3f(-500, 149, 657);
    glEnd();
    glPopMatrix();
    //Pager Tangga Tengah 1
    glTranslatef(481, 0, 1);
    // Atas
    glPushMatrix();
    glTranslatef(0, -100, -1);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-500, 250, 500);
    glVertex3f(-490, 250, 500);
    glVertex3f(-490, 200, 500);
    glVertex3f(-500, 200, 500);
    glEnd();
    glPopMatrix();
    // Bawah
    glPushMatrix();
    glTranslatef(-1, -200, 155);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-500, 250, 500);
    glVertex3f(-490, 250, 500);
    glVertex3f(-490, 200, 500);
    glVertex3f(-500, 200, 500);
    glEnd();
    glPopMatrix();
    // Nyamping Bwah
    glPushMatrix();
    glTranslatef(0, -100, -1);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-500, 250, 500);
    glVertex3f(-490, 250, 500);
    glVertex3f(-490, 149, 657);
    glVertex3f(-500, 149, 657);
    glEnd();
    glPopMatrix();

    //Pager Tangga Kanan
    glTranslatef(510, 0, -1);
    // Atas
    glPushMatrix();
    glTranslatef(0, -100, -1);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-500, 250, 500);
    glVertex3f(-490, 250, 500);
    glVertex3f(-490, 200, 500);
    glVertex3f(-500, 200, 500);
    glEnd();
    glPopMatrix();
    // Bawah
    glPushMatrix();
    glTranslatef(-1, -200, 155);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-500, 250, 500);
    glVertex3f(-490, 250, 500);
    glVertex3f(-490, 200, 500);
    glVertex3f(-500, 200, 500);
    glEnd();
    glPopMatrix();
    // Nyamping Bwah
    glPushMatrix();
    glTranslatef(0, -100, -1);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-500, 250, 500);
    glVertex3f(-490, 250, 500);
    glVertex3f(-490, 149, 657);
    glVertex3f(-500, 149, 657);
    glEnd();
    glPopMatrix();

}
void pagar_besar() {

    //Kanan
    for (int a = 480; a >= -480; a -= 20) {
        glPushMatrix();
        glTranslatef(-500, 150, a);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 480; a >= -480; a -= 10) {
        glPushMatrix();
        glTranslatef(-500, 150, a);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    //Kiri

    for (int a = 480; a >= -480; a -= 20) {
        glPushMatrix();
        glTranslatef(-1480, 150, a);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 480; a >= -480; a -= 10) {
        glPushMatrix();
        glTranslatef(-1480, 150, a);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    //Belakang
    for (int a = -500; a >= -1480; a -= 20) {
        glPushMatrix();
        glTranslatef(a, 150, -480);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = -500; a >= -1480; a -= 10) {
        glPushMatrix();
        glTranslatef(a, 150, -480);
        glutSolidCube(10.0);
        glPopMatrix();
    }
}

void pagarlantai2() {

    //cilinder1
    glPushMatrix();
    glTranslatef(-143, 320, 417);
    glRotatef(90, 45, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 290.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder1
    glPushMatrix();
    glTranslatef(-146, 324, 298);
    glRotatef(45, 0, 0, 0);
    glColor3f(0.0, 0.0, 0.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 290.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder2
    glPushMatrix();
    glTranslatef(146, 320, 417);
    glRotatef(90, 45, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 290.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder2
    glPushMatrix();
    glTranslatef(146, 324, 295);
    glRotatef(45, 0, 0, 0);
    glColor3f(0.0, 0.0, 0.0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 290.0f, 32, 32);
    glEnd();
    glPopMatrix();
}

void gentenglantai4() {
    glPushMatrix();
    glTranslatef(0, 940, 0);
    //atas l1
    glPushMatrix();
    glTranslatef(0, 350, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glVertex3f(480.0, 0.0, -430.0);
    glVertex3f(480.0, 0.0, 430.0);
    glVertex3f(-480.0, 0.0, 430.0);
    glEnd();
    glPopMatrix();

    //atas 2 l1
    glPushMatrix();
    glTranslatef(0, 330, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glVertex3f(480.0, 0.0, -430.0);
    glVertex3f(480.0, 0.0, 430.0);
    glVertex3f(-480.0, 0.0, 430.0);
    glEnd();
    glPopMatrix();

    //atas belakang  l1
    glPushMatrix();
    glTranslatef(0, 330, 0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-480.0, 20.0, -430.0);
    glVertex3f(480.0, 20.0, -430.0);
    glVertex3f(480.0, 0.0, -430.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glEnd();
    glPopMatrix();

    //atas depan  l1
    glPushMatrix();
    glTranslatef(0, 330, 860);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-480.0, 20.0, -430.0);
    glVertex3f(480.0, 20.0, -430.0);
    glVertex3f(480.0, 0.0, -430.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glEnd();
    glPopMatrix();

    //atas kiri l1
    glPushMatrix();
    glTranslatef(0, 330, 0);
    glBegin(GL_QUADS);
    glVertex3f(-480.0, 20.0, 430.0);
    glVertex3f(-480.0, 0.0, 430.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glVertex3f(-480.0, 20.0, -430.0);
    glEnd();
    glPopMatrix();

    //atas kanan l1
    glPushMatrix();
    glTranslatef(959, 330, 0);
    glBegin(GL_QUADS);
    glVertex3f(-480.0, 20.0, 430.0);
    glVertex3f(-480.0, 0.0, 430.0);
    glVertex3f(-480.0, 0.0, -430.0);
    glVertex3f(-480.0, 20.0, -430.0);
    glEnd();
    glPopMatrix();
    // Genteng
    glPushMatrix();
    // Depan 
    glPushMatrix();
    glTranslated(0, 50, -50);
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 128, 128);
    glVertex3f(550, 300, 550);
    glVertex3f(-550, 300, 550);
    glVertex3f(0, 800, 0);
    glEnd();
    glPopMatrix();

    // Belakang
    glPushMatrix();
    glTranslated(0, 50, -50);
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 128, 128);
    glVertex3f(550, 300, -550);
    glVertex3f(-550, 300, -550);
    glVertex3f(0, 800, 0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glTranslated(10, 50, -50);
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 128, 128);
    glVertex3f(-550, 300, -550);
    glVertex3f(-550, 300, 550);
    glVertex3f(0, 800, 0);
    glEnd();
    glPopMatrix();

    //Kanan
    glPushMatrix();
    glRotatef(180, 0, 10, 0);
    glTranslated(0, 50, 50);
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 128, 128);
    glVertex3f(-550, 300, -550);
    glVertex3f(-550, 300, 550);
    glVertex3f(0, 800, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}
void pintuL1() {
    //pintu depan 
    glPushMatrix();
    glTranslatef(0, 100, 300);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-100, 0, 0);
    glVertex3f(-100, 200, 0);
    glVertex3f(100, 200, 0);
    glVertex3f(100, 0, 0);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 200, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //pintu belakang
    glPushMatrix();
    glTranslatef(0, 100, -370);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-100, 0, 0);
    glVertex3f(-100, 200, 0);
    glVertex3f(100, 200, 0);
    glVertex3f(100, 0, 0);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 200, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela
    //depan kanan 
    glPushMatrix();
    glTranslatef(315, 184, 300);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(204, 184, 303);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //depan kiri 
    glPushMatrix();
    glTranslatef(-315, 184, 300);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-204, 184, 303);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //kiri
    //pintu samping kiri
    glPushMatrix();
    glTranslatef(-380, 99, -41);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-60, 0, 0);
    glVertex3f(-60, 190, 0);
    glVertex3f(60, 190, 0);
    glVertex3f(60, 0, 0);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 190, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela samping kiri bagian kiri
    glPushMatrix();
    glTranslatef(-380, 173, -298);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-380, 172, -183);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela samping kiri bagian kanan
    glPushMatrix();
    glTranslatef(-380, 177, 101);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-380, 177, 230);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //kanan
    glPushMatrix();
    glTranslatef(759, 0, 10);

    //pintu samping kanan
    glPushMatrix();
    glTranslatef(-377, 100, -40);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-60, 0, 0);
    glVertex3f(-60, 180, 0);
    glVertex3f(60, 180, 0);
    glVertex3f(60, 0, 0);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 180, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela samping kanan bagian kanan
    glPushMatrix();
    glTranslatef(-377, 180, -300);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-377, 180, -185);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela samping kanan bagian kiri
    glPushMatrix();
    glTranslatef(-377, 180, 100);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(x_geser, y_geser, z_geser);
    glTranslatef(-377, 180, 220);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    //jendela
    //belakang kiri 
    glPushMatrix();
    glTranslatef(312, 168, -367);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(197, 168, -367);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela
   //belakang kanan 
    glPushMatrix();
    glTranslatef(-316, 172, -367);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-199, 172, -367);
    glBegin(GL_QUADS);
    glColor3ub(10, 41, 10);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();
}
void antena() {
    //kotak atas
    glPushMatrix();
    glTranslatef(0, 1730, -50);
    glBegin(GL_QUADS);
    glColor3ub(222, 184, 135);
    glVertex3f(-70.0, 0.0, -80.0);
    glVertex3f(70.0, 0.0, -80.0);
    glVertex3f(70.0, 0.0, 80.0);
    glVertex3f(-70.0, 0.0, 80.0);
    glEnd();
    glPopMatrix();

    //kotak bawah
    glPushMatrix();
    glTranslatef(0, 1770, -50);
    glBegin(GL_QUADS);
    glColor3ub(222, 184, 135);
    glVertex3f(-70.0, 0.0, -80.0);
    glVertex3f(70.0, 0.0, -80.0);
    glVertex3f(70.0, 0.0, 80.0);
    glVertex3f(-70.0, 0.0, 80.0);
    glEnd();
    glPopMatrix();

    //kotak depan
    glPushMatrix();
    glTranslatef(0, 1730, 110);
    glBegin(GL_QUADS);
    glColor3ub(222, 184, 135);
    glVertex3f(-70.0, 40.0, -80.0);
    glVertex3f(70.0, 40.0, -80.0);
    glVertex3f(70.0, 0.0, -80.0);
    glVertex3f(-70.0, 0.0, -80.0);
    glEnd();
    glPopMatrix();

    //kotak belakang
    glPushMatrix();
    glTranslatef(0, 1730, -50);
    glBegin(GL_QUADS);
    glColor3ub(222, 184, 135);
    glVertex3f(-70.0, 40.0, -80.0);
    glVertex3f(70.0, 40.0, -80.0);
    glVertex3f(70.0, 0.0, -80.0);
    glVertex3f(-70.0, 0.0, -80.0);
    glEnd();
    glPopMatrix();

    //kotak kiri
    glPushMatrix();
    glTranslatef(0, 1730, -50);
    glBegin(GL_QUADS);
    glColor3ub(222, 184, 135);
    glVertex3f(-70.0, 40.0, 80.0);
    glVertex3f(-70.0, 0.0, 80.0);
    glVertex3f(-70.0, 0.0, -80.0);
    glVertex3f(-70.0, 40.0, -80.0);
    glEnd();
    glPopMatrix();

    //kotak kanan
    glPushMatrix();
    glTranslatef(140, 1730, -50);
    glBegin(GL_QUADS);
    glColor3ub(222, 184, 135);
    glVertex3f(-70.0, 40.0, 80.0);
    glVertex3f(-70.0, 0.0, 80.0);
    glVertex3f(-70.0, 0.0, -80.0);
    glVertex3f(-70.0, 40.0, -80.0);
    glEnd();
    glPopMatrix();

    //tiang
    glPushMatrix();
    glTranslatef(0, 2100, -50);
    glColor3ub(222, 184, 135);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 12.0f, 12.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //lingkaran 1
    glPushMatrix();
    glTranslatef(0, 1790, -50);
    glColor3ub(222, 184, 135);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 30.0f, 30.0f, 50.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //lingkaran 2
    glPushMatrix();
    glTranslatef(0, 1850, -50);
    glColor3ub(0, 128, 128);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //lingkaran 2
    glPushMatrix();
    glTranslatef(0, 1880, -50);
    glColor3ub(0, 128, 128);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //lingkaran 4
    glPushMatrix();
    glTranslatef(0, 1910, -50);
    glColor3ub(0, 128, 128);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //lingkaran 5
    glPushMatrix();
    glTranslatef(0, 1940, -50);
    glColor3ub(0, 128, 128);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //lingkaran 6
    glPushMatrix();
    glTranslatef(0, 1970, -50);
    glColor3ub(0, 128, 128);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //lingkaran 7
    glPushMatrix();
    glTranslatef(0, 2000, -50);
    glColor3ub(0, 128, 128);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //lingkaran 8
    glPushMatrix();
    glTranslatef(0, 2030, -50);
    glColor3ub(0, 128, 128);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //lingkaran 9
    glPushMatrix();
    glTranslatef(0, 2060, -50);
    glColor3ub(0, 128, 128);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //pucuk
    glPushMatrix();
    glTranslatef(0, 2145, -50);
    glColor3ub(0, 128, 128);
    glutSolidSphere(11.0, 30, 30);
    glutWireSphere(11.0, 30, 30);
    glEnd();
    glPopMatrix();

    //tiang 2
    glPushMatrix();
    glTranslatef(0, 2150, -50);
    glColor3ub(222, 184, 135);
    glRotatef(90, 90, 0, 0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();
}
void gentenglantai2() {
    glPushMatrix();
    glTranslatef(0, -301, 0);
    //depan Atas
    //depan Atas
    glPushMatrix();
    glTranslated(0, 250, 240);
    glRotatef(-37, 10, 0, 0);
    glBegin(GL_QUADS);
    glColor3ub(0, 128, 128);
    glVertex3f(500, 300, 550);
    glVertex3f(-500, 300, 550);
    glVertex3f(-300, 600, 400);
    glVertex3f(300, 600, 400);
    glEnd();
    glPopMatrix();
    //kiri Atas
    glPushMatrix();
    glTranslated(0, 370, -40);
    glBegin(GL_QUADS);
    glColor3ub(0, 128, 128);
    glVertex3f(-500, 450, -550);
    glVertex3f(-500, 450, 550);
    glVertex3f(-300, 600, 250);
    glVertex3f(-300, 600, -250);
    glEnd();
    glPopMatrix();
    //Belakang
    glPushMatrix();
    glTranslated(0, 370, -40);
    glBegin(GL_QUADS);
    glColor3ub(0, 128, 128);
    glVertex3f(500, 450, -550);
    glVertex3f(-500, 450, -550);
    glVertex3f(-300, 600, -250);
    glVertex3f(300, 600, -250);
    glEnd();
    glPopMatrix();
    //Kanan
    //kiri Atas
    glPushMatrix();
    glTranslated(0, 370, -40);
    glBegin(GL_QUADS);
    glColor3ub(0, 128, 128);
    glVertex3f(500, 450, -550);
    glVertex3f(500, 450, 550);
    glVertex3f(300, 600, 250);
    glVertex3f(300, 600, -250);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}
void gentenglantai3() {
    //depan Atas
    glPushMatrix();
    glTranslated(0, 250, 240);
    glRotatef(-37, 10, 0, 0);
    glBegin(GL_QUADS);
    glColor3ub(0, 128, 128);
    glVertex3f(500, 300, 550);
    glVertex3f(-500, 300, 550);
    glVertex3f(-300, 600, 400);
    glVertex3f(300, 600, 400);
    glEnd();
    glPopMatrix();
    //kiri Atas
    glPushMatrix();
    glTranslated(0, 370, -40);
    glBegin(GL_QUADS);
    glColor3ub(0, 128, 128);
    glVertex3f(-500, 450, -550);
    glVertex3f(-500, 450, 550);
    glVertex3f(-300, 600, 250);
    glVertex3f(-300, 600, -250);
    glEnd();
    glPopMatrix();
    //Belakang
    glPushMatrix();
    glTranslated(0, 370, -40);
    glBegin(GL_QUADS);
    glColor3ub(0, 128, 128);
    glVertex3f(500, 450, -550);
    glVertex3f(-500, 450, -550);
    glVertex3f(-300, 600, -250);
    glVertex3f(300, 600, -250);
    glEnd();
    glPopMatrix();
    //Kanan
    //kiri Atas
    glPushMatrix();
    glTranslated(0, 370, -40);
    glBegin(GL_QUADS);
    glColor3ub(0, 128, 128);
    glVertex3f(500, 450, -550);
    glVertex3f(500, 450, 550);
    glVertex3f(300, 600, 250);
    glVertex3f(300, 600, -250);
    glEnd();
    glPopMatrix();
}
void pagarL2() {
    for (int a = 470; a >= -470; a -= 20) {
        glPushMatrix();
        glTranslatef(a, 400, 420);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 470; a >= -470; a -= 10) {
        glPushMatrix();
        glTranslatef(a, 400, 420);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    for (int a = 470; a >= -470; a -= 20) {
        glPushMatrix();
        glTranslatef(a, 400, -420);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 470; a >= -470; a -= 10) {
        glPushMatrix();
        glTranslatef(a, 400, -420);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    for (int a = 420; a >= -420; a -= 20) {
        glPushMatrix();
        glTranslatef(470, 400, a);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 420; a >= -420; a -= 10) {
        glPushMatrix();
        glTranslatef(470, 400, a);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    for (int a = 420; a >= -420; a -= 20) {
        glPushMatrix();
        glTranslatef(-470, 400, a);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 420; a >= -420; a -= 10) {
        glPushMatrix();
        glTranslatef(-470, 400, a);
        glutSolidCube(10.0);
        glPopMatrix();
    }
}
void pintuL2() {


    //pintu depan
    glPushMatrix();
    glTranslatef(0, 350, 250);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-120, 0, 0);
    glVertex3f(-120, 170, 0);
    glVertex3f(120, 170, 0);
    glVertex3f(120, 0, 0);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 170, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela
    //depan kiri 
    glPushMatrix();
    //glTranslatef(x_geser, y_geser, z_geser);
    glTranslatef(-245, 450, 250);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //depan kanan
    glPushMatrix();
    //glTranslatef(x_geser, y_geser, z_geser);
    glTranslatef(240, 450, 250);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glTranslatef(0, 0, -570);
    //pintu belakang
    glPushMatrix();
    glTranslatef(0, 350, 250);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-120, 0, 0);
    glVertex3f(-120, 170, 0);
    glVertex3f(120, 170, 0);
    glVertex3f(120, 0, 0);
    glEnd();
    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 170, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela
    //belakang kiri 
    glPushMatrix();
    glTranslatef(-240, 450, 250);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //belakang kanan
    glPushMatrix();
    glTranslatef(240, 450, 250);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    //kiri
    //pintu
    glPushMatrix();
    glRotatef(90, 0, 90, 0);
    glTranslatef(12, 350, -301);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-70, 0, 0);
    glVertex3f(-70, 170, 0);
    glVertex3f(70, 170, 0);
    glVertex3f(70, 0, 0);
    glEnd();
    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 170, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela kiri bagian kiri
    glPushMatrix();
    glTranslatef(-310, 450, -220);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela kiri bagian kanan
    glPushMatrix();
    glTranslatef(-305, 450, 160);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //kanan
    glPushMatrix();
    glTranslatef(616, 0, 10);
    //pintu
    glPushMatrix();
    glRotatef(90, 0, 90, 0);
    glTranslatef(25, 350, -305);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-70, 0, 0);
    glVertex3f(-70, 170, 0);
    glVertex3f(70, 170, 0);
    glVertex3f(70, 0, 0);
    glEnd();
    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 170, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela kiri bagian kiri
    glPushMatrix();
    glTranslatef(-310, 450, -220);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela kiri bagian kanan
    glPushMatrix();
    //glTranslatef(x_geser, y_geser, z_geser);
    glTranslatef(-315, 450, 155);
    glRotatef(90, 0, 90, 0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}
void pagerL3() {
    for (int a = 370; a >= -370; a -= 20) {
        glPushMatrix();
        glTranslatef(a, 720, 320);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 370; a >= -370; a -= 10) {
        glPushMatrix();
        glTranslatef(a, 720, 320);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    for (int a = 370; a >= -370; a -= 20) {
        glPushMatrix();
        glTranslatef(a, 720, -320);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 370; a >= -370; a -= 10) {
        glPushMatrix();
        glTranslatef(a, 720, -320);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    for (int a = 320; a >= -320; a -= 20) {
        glPushMatrix();
        glTranslatef(370, 720, a);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 320; a >= -320; a -= 10) {
        glPushMatrix();
        glTranslatef(370, 720, a);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    for (int a = 320; a >= -320; a -= 20) {
        glPushMatrix();
        glTranslatef(-370, 720, a);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 320; a >= -320; a -= 10) {
        glPushMatrix();
        glTranslatef(-370, 720, a);
        glutSolidCube(10.0);
        glPopMatrix();
    }
}
void pagerL4() {
    glPushMatrix();
    glTranslatef(0, 310, 0);
    for (int a = 370; a >= -370; a -= 20) {
        glPushMatrix();
        glTranslatef(a, 725, 320);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 370; a >= -370; a -= 10) {
        glPushMatrix();
        glTranslatef(a, 725, 320);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    for (int a = 370; a >= -370; a -= 20) {
        glPushMatrix();
        glTranslatef(a, 725, -320);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 370; a >= -370; a -= 10) {
        glPushMatrix();
        glTranslatef(a, 725, -320);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    for (int a = 320; a >= -320; a -= 20) {
        glPushMatrix();
        glTranslatef(370, 725, a);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 320; a >= -320; a -= 10) {
        glPushMatrix();
        glTranslatef(370, 725, a);
        glutSolidCube(10.0);
        glPopMatrix();
    }

    for (int a = 320; a >= -320; a -= 20) {
        glPushMatrix();
        glTranslatef(-370, 725, a);
        glRotatef(90, 1, 0, 0);
        glColor3f(0.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 50.0f, 32, 32);
        glEnd();
        glPopMatrix();
    }

    for (int a = 320; a >= -320; a -= 10) {
        glPushMatrix();
        glTranslatef(-370, 725, a);
        glutSolidCube(10.0);
        glPopMatrix();
    }
    glPopMatrix();
}
void pintuL3() {
    //lantai 3 (pintu) depan
    glPushMatrix();
    glTranslatef(0, 669, 194);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-60, 0, 0);
    glVertex3f(-60, 180, 0);
    glVertex3f(60, 180, 0);
    glVertex3f(60, 0, 0);
    glEnd();
    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 180, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela depan
    glPushMatrix();
    glTranslatef(190, 760, 194);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 760, 194);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela kiri
    glPushMatrix();
    glTranslatef(-274, 760, 109);
    glRotatef(90.0, 0.0, 90.0, 0.0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-270, 760, -128);
    glRotatef(90.0, 0.0, 90.0, 0.0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela kanan
    glPushMatrix();
    glTranslatef(545.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(-274, 760, 109);
    glRotatef(90.0, 0.0, 90.0, 0.0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-270, 760, -130);
    glRotatef(90.0, 0.0, 90.0, 0.0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    // belakang lt3
    glPushMatrix();
    glTranslatef(-10, -5, -426);
    //pintu
    glPushMatrix();
    glTranslatef(0, 669, 194);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-60, 0, 0);
    glVertex3f(-60, 180, 0);
    glVertex3f(60, 180, 0);
    glVertex3f(60, 0, 0);
    glEnd();
    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 180, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();
    //jendela
    glPushMatrix();
    glTranslatef(190, 760, 194);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 760, 194);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}
void pintuL4() {
    //lantai 4 (pintu) depan
    glPushMatrix();
    glTranslatef(0, 318, 0);
    glPushMatrix();
    glTranslatef(0, 669, 194);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-60, 0, 0);
    glVertex3f(-60, 180, 0);
    glVertex3f(60, 180, 0);
    glVertex3f(60, 0, 0);
    glEnd();
    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 180, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela depan
    glPushMatrix();
    glTranslatef(190, 760, 194);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 760, 194);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela kiri
    glPushMatrix();
    glTranslatef(-274, 760, 109);
    glRotatef(90.0, 0.0, 90.0, 0.0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-270, 760, -128);
    glRotatef(90.0, 0.0, 90.0, 0.0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    //jendela kanan
    glPushMatrix();
    glTranslatef(545.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(-274, 760, 109);
    glRotatef(90.0, 0.0, 90.0, 0.0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(280, 760, -150);
    glRotatef(90.0, 0.0, 90.0, 0.0);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    // belakang lt3
    glPushMatrix();
    //glTranslatef(6, -5, -426);
    //pintu
    glPushMatrix();
    glTranslatef(-8, 984, -232);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-60, 0, 0);
    glVertex3f(-60, 180, 0);
    glVertex3f(60, 180, 0);
    glVertex3f(60, 0, 0);
    glEnd();
    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 180, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();
    //jendela
    glPushMatrix();
    glTranslatef(190, 1070, -240);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-200, 1070, -240);
    glBegin(GL_QUADS);
    glColor3ub(10.0, 41.0, 10.0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-30, 60, 0);
    glVertex3f(30, 60, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();


}
void tambahan() {
    //1
    glPushMatrix();
    glTranslatef(-336, 120, 448);
    glColor3ub(0, 0, 0);
    glutSolidSphere(40.0, 30, 30);
    glutWireSphere(40.0, 30, 30);
    glEnd();
    glPopMatrix();

    //2
    glPushMatrix();
    glTranslatef(336, 120, 448);
    glColor3ub(0, 0, 0);
    glutSolidSphere(40.0, 30, 30);
    glutWireSphere(40.0, 30, 30);
    glEnd();
    glPopMatrix();
}
void selamatDatang() {
    //cilinder kiri
    glPushMatrix();
    glTranslatef(-496, 544, 920);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 550.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder kanan
    glPushMatrix();
    glTranslatef(488, 544, 920);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 550.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder bawah
    glPushMatrix();
    glTranslatef(-600, 544, 920);
    glRotatef(90, 90, 13080, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 1200.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder tengah tegak kiri
    glPushMatrix();
    glTranslatef(-496, 648, 920);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 100.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder tengah tegak tengah
    glPushMatrix();
    glTranslatef(0, 648, 920);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 100.0f, 32, 32);
    glEnd();
    glPopMatrix();
    //cilinder tengah tegak tengah
    glPushMatrix();
    glTranslatef(496, 648, 920);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 100.0f, 32, 32);
    glEnd();
    glPopMatrix();
    //cilinder atas
    glPushMatrix();
    glTranslatef(-728, 664, 920);
    glRotatef(90, 90, 13080, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 1500.0f, 32, 32);
    glEnd();
    glPopMatrix();
}
void tianglantai1() {
    //cilinder depan tengah kiri 1
    glPushMatrix();
    glTranslatef(0, 20, 0);
    //glTranslatef(x_geser, y_geser, z_geser);
    //cilinder depan tengah kiri 1
    glPushMatrix();
    glTranslatef(-144, 330, 298);
    glRotatef(90, 45, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kiri 2
    glPushMatrix();
    glTranslatef(-262, 330, 291);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kiri 3 
    glPushMatrix();
    glTranslatef(-367, 330, 288);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kanan 1
    glPushMatrix();
    glTranslatef(144, 330, 298);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kanan 2
    glPushMatrix();
    glTranslatef(262, 330, 291);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kanan 3
    glPushMatrix();
    glTranslatef(367, 330, 288);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 1
    glPushMatrix();
    glTranslatef(-381, 330, 156);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 2
    glPushMatrix();
    glTranslatef(-381, 330, 46);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 3
    glPushMatrix();
    glTranslatef(-382, 330, -129);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 4
    glPushMatrix();
    glTranslatef(-381, 330, -238);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 5 (belakang)
    glPushMatrix();
    glTranslatef(-379, 330, -359);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(760, 20, 10);
    //cilinder samping kanan 
    glPushMatrix();
    glTranslatef(-381, 330, 156);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kanan 2
    glPushMatrix();
    glTranslatef(-381, 330, 46);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kanan 3
    glPushMatrix();
    glTranslatef(-382, 330, -129);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kanan 4
    glPushMatrix();
    glTranslatef(-381, 330, -238);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kanan 5 (belakang)
    glPushMatrix();
    glTranslatef(-379, 330, -359);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    //cilinder belakang tengah kiri 1
    glPushMatrix();
    //glTranslatef(0, 20, 0);
    glTranslatef(0, 20, -660);
    //cilinder depan tengah kiri 1
    glPushMatrix();
    glTranslatef(-144, 330, 298);
    glRotatef(90, 45, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder belakang tengah kiri 2
    glPushMatrix();
    glTranslatef(-262, 330, 291);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kiri 3 
    glPushMatrix();
    glTranslatef(-367, 330, 288);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder belakang tengah kanan 1
    glPushMatrix();
    glTranslatef(144, 330, 298);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder belakang tengah kanan 2
    glPushMatrix();
    glTranslatef(262, 330, 291);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder belakang tengah kanan 3
    glPushMatrix();
    glTranslatef(367, 330, 288);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 250.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}
void tianglantai2() {
    //cilinder depan tengah kiri 1
    glPushMatrix();
    glTranslatef(0, 50, -10);
    //glTranslatef(x_geser, y_geser, z_geser);
    glPushMatrix();
    glTranslatef(-180, 600, 260);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kiri 2
    glPushMatrix();
    glTranslatef(-293, 600, 249);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kanan 1
    glPushMatrix();
    glTranslatef(180, 600, 260);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kanan 2
    glPushMatrix();
    glTranslatef(293, 600, 249);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 1
    glPushMatrix();
    glTranslatef(-310, 600, 90);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 2
    glPushMatrix();
    glTranslatef(-310, 600, -120);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 3
    glPushMatrix();
    glTranslatef(-300, 600, -300);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    //cilinder samping kanan 1
    glPushMatrix();
    glTranslatef(610, 50, 0);
    glPushMatrix();
    glTranslatef(-310, 600, 90);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kanan 2
    glPushMatrix();
    glTranslatef(-310, 600, -120);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kanan 3
    glPushMatrix();
    glTranslatef(-300, 600, -300);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 50, -570);
    //cilinder belakang tengah kiri 1
    //glPushMatrix();
    glPushMatrix();
    glTranslatef(-180, 600, 260);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder belakang tengah kiri 2
    glPushMatrix();
    glTranslatef(-293, 600, 249);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder belakang tengah kanan 1
    glPushMatrix();
    glTranslatef(180, 600, 260);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder belakang tengah kanan 2
    glPushMatrix();
    glTranslatef(293, 600, 249);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 300.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}
void tianglantaiL3() {
    //cilinder depan tengah kiri 1
    glPushMatrix();
    glTranslatef(0, 430, 0);
    glPushMatrix();
    glTranslatef(-260, 840, 180);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kiri 2
    glPushMatrix();
    glTranslatef(-120, 840, 200);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 1
    glPushMatrix();
    glTranslatef(-280, 840, 50);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 2
    glPushMatrix();
    glTranslatef(-280, 840, -70);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 3
    glPushMatrix();
    glTranslatef(-280, 840, -220);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kanan 1
    glPushMatrix();
    glTranslatef(260, 840, 180);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder depan tengah kanan 2
    glPushMatrix();
    glTranslatef(120, 840, 200);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, 430, -430);
    //cilinder belakang tengah kiri 1
    glPushMatrix();
    glTranslatef(-260, 840, 180);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder belakang tengah kiri 2
    glPushMatrix();
    glTranslatef(-120, 840, 200);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder belakang tengah kanan 1
    glPushMatrix();
    glTranslatef(260, 840, 180);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder belakang tengah kanan 2
    glPushMatrix();
    glTranslatef(120, 840, 200);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(550, 430, -10);
    //cilinder samping kiri 1
    glPushMatrix();
    glTranslatef(-280, 840, 50);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 2
    glPushMatrix();
    glTranslatef(-280, 840, -70);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //cilinder samping kiri 3
    glPushMatrix();
    glTranslatef(-280, 840, -220);
    glRotatef(90, 90, 0, 0);
    glColor3ub(148, 22, 0);
    gluCylinder(gluNewQuadric(), 16.0f, 16.0f, 600.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}
void miring() {
    //BALOK LANTAI 1
//kiri
    //balok atas lantai 1
    glPushMatrix();
    glTranslatef(0, 300, 610);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-410.0, 25.0, -300.0);
    glVertex3f(410.0, 25.0, -300.0);
    glVertex3f(410.0, 0.0, -300.0);
    glVertex3f(-410.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok atas lapisan 2
    glPushMatrix();
    glTranslatef(0, 300, 580);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-410.0, 25.0, -300.0);
    glVertex3f(410.0, 25.0, -300.0);
    glVertex3f(410.0, 0.0, -300.0);
    glVertex3f(-410.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok atas lapisan samping kiri
    glPushMatrix();
    glTranslatef(-400, 300, 300);
    glBegin(GL_QUADS);
    glVertex3f(-10.0, 25.0, 20.0);
    glVertex3f(-10.0, 0.0, 20.0);
    glVertex3f(-10.0, 0.0, -20.0);
    glVertex3f(-10.0, 25.0, -20.0);
    glEnd();
    glPopMatrix();

    //balok atas lapisan samping kanan
    glPushMatrix();
    glTranslatef(420, 300, 290);
    glBegin(GL_QUADS);
    glVertex3f(-10.0, 25.0, 20.0);
    glVertex3f(-10.0, 0.0, 20.0);
    glVertex3f(-10.0, 0.0, -20.0);
    glVertex3f(-10.0, 25.0, -20.0);
    glEnd();
    glPopMatrix();

    //balok tengah lantai 1
    glPushMatrix();
    glTranslatef(-270, 250, 620);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok lapisan tengah
    glPushMatrix();
    glTranslatef(-270, 250, 590);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok tengah lapisan samping kiri
    glPushMatrix();
    glTranslatef(-400, 250, 300);
    glBegin(GL_QUADS);
    glVertex3f(-10.0, 22.0, 20.0);
    glVertex3f(-10.0, 0.0, 20.0);
    glVertex3f(-10.0, 0.0, -20.0);
    glVertex3f(-10.0, 22.0, -20.0);
    glEnd();
    glPopMatrix();

    //balok tengah lapisan samping kanan
    glPushMatrix();
    glTranslatef(-130, 250, 300);
    glBegin(GL_QUADS);
    glVertex3f(-8.0, 22.0, 20.0);
    glVertex3f(-8.0, 0.0, 20.0);
    glVertex3f(-8.0, 0.0, -20.0);
    glVertex3f(-8.0, 22.0, -20.0);
    glEnd();
    glPopMatrix();

    //balok bawah lantai 1
    glPushMatrix();
    glTranslatef(-270, 160, 620);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok lapisan bawah
    glPushMatrix();
    glTranslatef(-270, 160, 590);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok bawah lapisan samping kiri
    glPushMatrix();
    glTranslatef(-330, 160, 300);
    glBegin(GL_QUADS);
    glVertex3f(-80.0, 22.0, 20.0);
    glVertex3f(-80.0, 0.0, 20.0);
    glVertex3f(-80.0, 0.0, -20.0);
    glVertex3f(-80.0, 22.0, -20.0);
    glEnd();
    glPopMatrix();

    //balok bawah lapisan samping kanan
    glPushMatrix();
    glTranslatef(-130, 160, 300);
    glBegin(GL_QUADS);
    glVertex3f(-8.0, 22.0, 20.0);
    glVertex3f(-8.0, 0.0, 20.0);
    glVertex3f(-8.0, 0.0, -20.0);
    glVertex3f(-8.0, 22.0, -20.0);
    glEnd();
    glPopMatrix();

    //kanan
    //balok tengah lantai 1
    glPushMatrix();
    glTranslatef(270, 250, 620);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok lapisan tengah
    glPushMatrix();
    glTranslatef(270, 250, 590);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok tengah lapisan samping kiri
    glPushMatrix();
    glTranslatef(420, 250, 300);
    glBegin(GL_QUADS);
    glVertex3f(-10.0, 22.0, 20.0);
    glVertex3f(-10.0, 0.0, 20.0);
    glVertex3f(-10.0, 0.0, -20.0);
    glVertex3f(-10.0, 22.0, -20.0);
    glEnd();
    glPopMatrix();

    //balok tengah lapisan samping kanan
    glPushMatrix();
    glTranslatef(140, 250, 300);
    glBegin(GL_QUADS);
    glVertex3f(-8.0, 22.0, 20.0);
    glVertex3f(-8.0, 0.0, 20.0);
    glVertex3f(-8.0, 0.0, -20.0);
    glVertex3f(-8.0, 22.0, -20.0);
    glEnd();
    glPopMatrix();

    //balok bawah lantai 1
    glPushMatrix();
    glTranslatef(270, 160, 620);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok lapisan bawah
    glPushMatrix();
    glTranslatef(270, 160, 590);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok bawah lapisan samping kiri
    glPushMatrix();
    glTranslatef(490, 160, 300);
    glBegin(GL_QUADS);
    glVertex3f(-80.0, 22.0, 20.0);
    glVertex3f(-80.0, 0.0, 20.0);
    glVertex3f(-80.0, 0.0, -20.0);
    glVertex3f(-80.0, 22.0, -20.0);
    glEnd();
    glPopMatrix();

    //balok bawah lapisan samping kanan
    glPushMatrix();
    glTranslatef(140, 160, 300);
    glBegin(GL_QUADS);
    glVertex3f(-8.0, 22.0, 20.0);
    glVertex3f(-8.0, 0.0, 20.0);
    glVertex3f(-8.0, 0.0, -20.0);
    glVertex3f(-8.0, 22.0, -20.0);
    glEnd();
    glPopMatrix();

    //samping kiri bagian kanan
    //balok samping kiri
    glPushMatrix();
    glTranslatef(220, 300, -30);
    glBegin(GL_QUADS);
    glVertex3f(-600.0, 25.0, 360.0);
    glVertex3f(-600.0, 0.0, 360.0);
    glVertex3f(-600.0, 0.0, -360.0);
    glVertex3f(-600.0, 25.0, -360.0);
    glEnd();
    glPopMatrix();

    //balok lapisan tengah
    glPushMatrix();
    glTranslatef(-240, 240, 190);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, 145.0);
    glVertex3f(-140.0, 0.0, 145.0);
    glVertex3f(-140.0, 0.0, -145.0);
    glVertex3f(-140.0, 22.0, -145.0);
    glEnd();
    glPopMatrix();

    //balok lapisan bawah
    glPushMatrix();
    glTranslatef(-240, 150, 190);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, 145.0);
    glVertex3f(-140.0, 0.0, 145.0);
    glVertex3f(-140.0, 0.0, -145.0);
    glVertex3f(-140.0, 22.0, -145.0);
    glEnd();
    glPopMatrix();

    //bagian kiri
    //balok lapisan tengah
    glPushMatrix();
    glTranslatef(-250, 240, -260);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, 145.0);
    glVertex3f(-140.0, 0.0, 145.0);
    glVertex3f(-140.0, 0.0, -145.0);
    glVertex3f(-140.0, 22.0, -145.0);
    glEnd();
    glPopMatrix();

    //balok lapisan bawah
    glPushMatrix();
    glTranslatef(-250, 150, -270);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, 145.0);
    glVertex3f(-140.0, 0.0, 145.0);
    glVertex3f(-140.0, 0.0, -145.0);
    glVertex3f(-140.0, 22.0, -145.0);
    glEnd();
    glPopMatrix();

    //balok belakang lantai 1
    glPushMatrix();
    glTranslatef(0, 296, -72);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-410.0, 25.0, -300.0);
    glVertex3f(410.0, 25.0, -300.0);
    glVertex3f(410.0, 0.0, -300.0);
    glVertex3f(-410.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok samping kanan
    glPushMatrix();
    glTranslatef(792, 296, -32);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-410.0, 25.0, 330.0);
    glVertex3f(-410.0, 0.0, 330.0);
    glVertex3f(-410.0, 0.0, -330.0);
    glVertex3f(-410.0, 25.0, -330.0);
    glEnd();
    glPopMatrix();

    //balok belakang kanan 1
    glPushMatrix();
    glTranslatef(272, 240, -80);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok belakang kanan 2
    glPushMatrix();
    glTranslatef(272, 136, -80);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok belakang kiri 1
    glPushMatrix();
    glTranslatef(-264, 144, -88);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok belakang kiri 2
    glPushMatrix();
    glTranslatef(-272, 240, -72);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, -300.0);
    glVertex3f(140.0, 22.0, -300.0);
    glVertex3f(140.0, 0.0, -300.0);
    glVertex3f(-140.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok belakang kanan 1
    glPushMatrix();
    glTranslatef(520, 144, 160);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, 140.0);
    glVertex3f(-140.0, 0.0, 140.0);
    glVertex3f(-140.0, 0.0, -140.0);
    glVertex3f(-140.0, 22.0, -140.0);
    glEnd();
    glPopMatrix();

    //balok belakang kanan 2
    glPushMatrix();
    glTranslatef(520, 248, 160);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, 140.0);
    glVertex3f(-140.0, 0.0, 140.0);
    glVertex3f(-140.0, 0.0, -140.0);
    glVertex3f(-140.0, 22.0, -140.0);
    glEnd();
    glPopMatrix();

    //balok belakang kanan 3
    glPushMatrix();
    glTranslatef(520, 248, -256);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, 140.0);
    glVertex3f(-140.0, 0.0, 140.0);
    glVertex3f(-140.0, 0.0, -140.0);
    glVertex3f(-140.0, 22.0, -140.0);
    glEnd();
    glPopMatrix();

    //balok belakang kanan 4
    glPushMatrix();
    glTranslatef(528, 144, -256);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-140.0, 22.0, 140.0);
    glVertex3f(-140.0, 0.0, 140.0);
    glVertex3f(-140.0, 0.0, -140.0);
    glVertex3f(-140.0, 22.0, -140.0);
    glEnd();
    glPopMatrix();


    //BALOK LANTAI 2
    //balok depan
    glPushMatrix();
    glTranslatef(0, 550, 550);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-300.0, 23.0, -300.0);
    glVertex3f(300.0, 23.0, -300.0);
    glVertex3f(300.0, 0.0, -300.0);
    glVertex3f(-300.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glTranslatef(240, 550, -20);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 280.0);
    glVertex3f(-550.0, 0.0, 280.0);
    glVertex3f(-550.0, 0.0, -280.0);
    glVertex3f(-550.0, 23.0, -280.0);
    glEnd();
    glPopMatrix();

    //kanan
    glPushMatrix();
    glTranslatef(860, 550, -20);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 280.0);
    glVertex3f(-550.0, 0.0, 280.0);
    glVertex3f(-550.0, 0.0, -280.0);
    glVertex3f(-550.0, 23.0, -280.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glTranslatef(0, 550, -20);
    glBegin(GL_QUADS);
    glVertex3f(-300.0, 23.0, -300.0);
    glVertex3f(300.0, 23.0, -300.0);
    glVertex3f(300.0, 0.0, -300.0);
    glVertex3f(-300.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //lapisan balok depan
    glPushMatrix();
    glTranslatef(0, 520, 550);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-300.0, 23.0, -300.0);
    glVertex3f(300.0, 23.0, -300.0);
    glVertex3f(300.0, 0.0, -300.0);
    glVertex3f(-300.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //lapisan kiri
    glPushMatrix();
    glTranslatef(240, 520, -20);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 280.0);
    glVertex3f(-550.0, 0.0, 280.0);
    glVertex3f(-550.0, 0.0, -280.0);
    glVertex3f(-550.0, 23.0, -280.0);
    glEnd();
    glPopMatrix();

    //lapisan kanan
    glPushMatrix();
    glTranslatef(860, 520, -20);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 280.0);
    glVertex3f(-550.0, 0.0, 280.0);
    glVertex3f(-550.0, 0.0, -280.0);
    glVertex3f(-550.0, 23.0, -280.0);
    glEnd();
    glPopMatrix();

    //lapisan belakang
    glPushMatrix();
    glTranslatef(0, 520, -20);
    glBegin(GL_QUADS);
    glVertex3f(-300.0, 23.0, -300.0);
    glVertex3f(300.0, 23.0, -300.0);
    glVertex3f(300.0, 0.0, -300.0);
    glVertex3f(-300.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok tengah kiri(depan)
    glPushMatrix();
    glTranslatef(-230, 420, 550);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-50.0, 23.0, -300.0);
    glVertex3f(50.0, 23.0, -300.0);
    glVertex3f(50.0, 0.0, -300.0);
    glVertex3f(-50.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok tengah kanan(depan)
    glPushMatrix();
    glTranslatef(230, 420, 550);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-50.0, 23.0, -300.0);
    glVertex3f(50.0, 23.0, -300.0);
    glVertex3f(50.0, 0.0, -300.0);
    glVertex3f(-50.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok belakang kiri(depan)
    glPushMatrix();
    glTranslatef(-210, 410, -20);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-100.0, 23.0, -300.0);
    glVertex3f(100.0, 23.0, -300.0);
    glVertex3f(100.0, 0.0, -300.0);
    glVertex3f(-100.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok belakang kanan(depan)
    glPushMatrix();
    glTranslatef(220, 410, -20);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-100.0, 23.0, -300.0);
    glVertex3f(100.0, 23.0, -300.0);
    glVertex3f(100.0, 0.0, -300.0);
    glVertex3f(-100.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok kiri 1
    glPushMatrix();
    glTranslatef(245, 420, 170);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 70.0);
    glVertex3f(-550.0, 0.0, 70.0);
    glVertex3f(-550.0, 0.0, -70.0);
    glVertex3f(-550.0, 23.0, -70.0);
    glEnd();
    glPopMatrix();

    //balok kiri 2
    glPushMatrix();
    glTranslatef(245, 424, -208);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();

    //balok kanan 1
    glPushMatrix();
    glTranslatef(856, 424, 176);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();

    //balok kanan 2
    glPushMatrix();
    glTranslatef(856, 424, -216);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();



    //BALOK LANTAI 3 4
    //balok depan
    glPushMatrix();
    glTranslatef(-8, 864, 408);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-270.0, 23.0, -210.0);
    glVertex3f(270.0, 23.0, -210.0);
    glVertex3f(270.0, 0.0, -210.0);
    glVertex3f(-270.0, 0.0, -210.0);
    glEnd();
    glPopMatrix();

    //balok belakang
    glPushMatrix();
    glTranslatef(0, 854, -24);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-280.0, 23.0, -210.0);
    glVertex3f(280.0, 23.0, -210.0);
    glVertex3f(280.0, 0.0, -210.0);
    glVertex3f(-280.0, 0.0, -210.0);
    glEnd();
    glPopMatrix();


    //kiri
    glPushMatrix();
    glTranslatef(280, 864, -8);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 210.0);
    glVertex3f(-550.0, 0.0, 210.0);
    glVertex3f(-550.0, 0.0, -210.0);
    glVertex3f(-550.0, 23.0, -210.0);
    glEnd();
    glPopMatrix();

    //kanan
    glPushMatrix();
    glTranslatef(824, 864, -24);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 210.0);
    glVertex3f(-550.0, 0.0, 210.0);
    glVertex3f(-550.0, 0.0, -210.0);
    glVertex3f(-550.0, 23.0, -210.0);
    glEnd();
    glPopMatrix();

    //lapisan balok depan
    glPushMatrix();
    glTranslatef(-8, 830, 408);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-270.0, 23.0, -210.0);
    glVertex3f(270.0, 23.0, -210.0);
    glVertex3f(270.0, 0.0, -210.0);
    glVertex3f(-270.0, 0.0, -210.0);
    glEnd();
    glPopMatrix();

    //lapisan balok belakang
    glPushMatrix();
    glTranslatef(0, 820, -24);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-280.0, 23.0, -210.0);
    glVertex3f(280.0, 23.0, -210.0);
    glVertex3f(280.0, 0.0, -210.0);
    glVertex3f(-280.0, 0.0, -210.0);
    glEnd();
    glPopMatrix();


    //lapisan kiri
    glPushMatrix();
    glTranslatef(280, 830, -8);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 210.0);
    glVertex3f(-550.0, 0.0, 210.0);
    glVertex3f(-550.0, 0.0, -210.0);
    glVertex3f(-550.0, 23.0, -210.0);
    glEnd();
    glPopMatrix();

    //lapisan kanan
    glPushMatrix();
    glTranslatef(824, 830, -24);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 210.0);
    glVertex3f(-550.0, 0.0, 210.0);
    glVertex3f(-550.0, 0.0, -210.0);
    glVertex3f(-550.0, 23.0, -210.0);
    glEnd();
    glPopMatrix();

    //balok tengah kiri(depan)
    glPushMatrix();
    glTranslatef(-192, 728, 496);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-70.0, 23.0, -300.0);
    glVertex3f(70.0, 23.0, -300.0);
    glVertex3f(70.0, 0.0, -300.0);
    glVertex3f(-70.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok tengah kiri(depan)
    glPushMatrix();
    glTranslatef(184, 728, 496);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-70.0, 23.0, -300.0);
    glVertex3f(70.0, 23.0, -300.0);
    glVertex3f(70.0, 0.0, -300.0);
    glVertex3f(-70.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok tengah kiri(belakang)
    glPushMatrix();
    glTranslatef(208, 728, 64);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-70.0, 23.0, -300.0);
    glVertex3f(70.0, 23.0, -300.0);
    glVertex3f(70.0, 0.0, -300.0);
    glVertex3f(-70.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok tengah kiri(belakang)
    glPushMatrix();
    glTranslatef(-192, 728, 64);
    glBegin(GL_QUADS);
    glColor3ub(148, 22, 0);
    glVertex3f(-78.0, 23.0, -300.0);
    glVertex3f(78.0, 23.0, -300.0);
    glVertex3f(78.0, 0.0, -300.0);
    glVertex3f(-78.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    //balok kanan 1
    glPushMatrix();
    glTranslatef(824, 728, 104);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();

    //balok kanan 2
    glPushMatrix();
    glTranslatef(824, 728, -136);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();

    //balok kiri 1
    glPushMatrix();
    glTranslatef(280, 728, 112);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();

    //balok kiri 2
    glPushMatrix();
    glTranslatef(280, 728, -144);
    glBegin(GL_QUADS);
    glVertex3f(-550.0, 23.0, 80.0);
    glVertex3f(-550.0, 0.0, 80.0);
    glVertex3f(-550.0, 0.0, -80.0);
    glVertex3f(-550.0, 23.0, -80.0);
    glEnd();
    glPopMatrix();
}

void draw() {
    // Mulai tuliskan isi pikiranmu disini
    glPushMatrix();
    glTranslatef(0, 0, 0);
    tumpukan();
    pagar_lantai1();
    pagar_besar();
    glPushMatrix();
    glTranslatef(-997, 1, -52);
    lantai1();
    lantai2();
    lantai3();
    lantai4();
    tianglantai1();
    tianglantai2();
    tianglantaiL3();
    //tianglantaiL4();
    pagarlantai2();
    antena();
    pagarL2();
    pagerL3();
    pagerL4();
    gentenglantai4();
    gentenglantai3();
    gentenglantai2();
    pintuL1();
    pintuL2();
    pintuL3();
    pintuL4();
    tambahan();
    selamatDatang();
    miring();
    glPopMatrix();
    glPopMatrix();

    ground();

    cout << "X_GESER = " << x_geser << "		Y_GESER = " << y_geser << "		Z_GESER = " << z_geser << endl;
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera() {
    if (motion.Forward) {
        camX += cos((yaw + 90) * TO_RADIANS) * 10;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 10;
    }
    if (motion.Backward) {
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 10;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 10;
    }
    if (motion.Left) {
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 10;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 10;
    }
    if (motion.Right) {
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 10;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 10;
    }
    if (motion.Naik) {
        terbang -= 10.0;
    }
    if (motion.Turun) {
        terbang += 10.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case '6':
        x_geser += 10.0;
        break;
    case '4':
        x_geser -= 10.0;
        break;
    case '8':
        y_geser += 10.0;
        break;
    case '2':
        y_geser -= 10.0;
        break;
    case '9':
        z_geser -= 10.0;
        break;
    case '1':
        z_geser += 10.0;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM KELOMPOK 5");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
    return 0;
}