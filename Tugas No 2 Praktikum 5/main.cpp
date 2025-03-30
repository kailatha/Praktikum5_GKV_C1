#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

double rx = 0.0;
double ry = 0.0;
float l[] = { 0.0, 80.0, 0.0 }; // koordinat sumber cahaya
float n[] = { 0.0, -40.0, 0.0 };
float e[] = { 0.0, -60.0, 0.0 };
// Tambahkan di bagian variabel global
int isDrawingShadow = 0; // 0 = mobil normal, 1 = bayangan
void help();

// Faktor skala untuk memperbesar mobil
float carScale = 10.0f; // Faktor skala, 2.0 berarti ukuran mobil 2x lebih besar


// Fungsi untuk membuat ban mobil
void Ban(float posX, float posY, float posZ) {
    // Ban luar (hitam)
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f); // Warna hitam
    glTranslatef(posX, posY, posZ);
    glRotatef(180, 0, 1, 0);
    glutSolidTorus(0.2f, 0.41f, 20, 20);
    glPopMatrix();
    
    // Velg (perak)
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f); // Warna perak
    glTranslatef(posX, posY, posZ);
    glRotatef(180, 0, 1, 0);
    glutSolidTorus(0.1f, 0.2f, 16, 16);
    
    // Pusat velg
    glColor3f(0.7f, 0.7f, 0.7f);
    glutSolidSphere(0.1f, 12, 12);
    
    // Jari-jari velg
    glColor3f(0.7f, 0.7f, 0.7f);
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glRotatef(i * 72, 0, 0, 1);
        glTranslatef(0.3f, 0.0f, 0.0f);
        glScalef(0.6f, 0.1f, 0.05f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    glPopMatrix();
}

// obyek yang akan digambar
void Mobil()
{
    // Badan bawah mobil (chassis)
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.9f);// Warna pink
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(5.0f, 0.5f, 2.4f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Badan tengah mobil
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.9f); // Warna pink
    glTranslatef(0.0f, 1.0f, 0.0f);
    glScalef(4.5f, 0.6f, 2.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Bagian depan (kap mesin)
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.9f); // Warna pink
    glTranslatef(1.8f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
        // Bagian atas kap
        glVertex3f(0.7f, 0.2f, 1.1f);
        glVertex3f(0.7f, 0.2f, -1.1f);
        glVertex3f(-1.8f, 0.2f, -1.1f);
        glVertex3f(-1.8f, 0.2f, 1.1f);
        
        // Bagian depan kap
        glVertex3f(0.7f, 0.2f, 1.1f);
        glVertex3f(0.7f, 0.2f, -1.1f);
        glVertex3f(0.7f, -0.3f, -1.1f);
        glVertex3f(0.7f, -0.3f, 1.1f);
        
        // Sisi kanan kap
        glVertex3f(0.7f, 0.2f, 1.1f);
        glVertex3f(-1.8f, 0.2f, 1.1f);
        glVertex3f(-1.8f, -0.3f, 1.1f);
        glVertex3f(0.7f, -0.3f, 1.1f);
        
        // Sisi kiri kap
        glVertex3f(0.7f, 0.2f, -1.1f);
        glVertex3f(-1.8f, 0.2f, -1.1f);
        glVertex3f(-1.8f, -0.3f, -1.1f);
        glVertex3f(0.7f, -0.3f, -1.1f);
    glEnd();
    glPopMatrix();
    
     // Bagian belakang mobil (trunk)
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.9f); // Warna pink
    glTranslatef(-1.8f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
        // Bagian atas
        glVertex3f(0.7f, 0.2f, 1.1f);
        glVertex3f(0.7f, 0.2f, -1.1f);
        glVertex3f(-0.7f, 0.2f, -1.1f);
        glVertex3f(-0.7f, 0.2f, 1.1f);
        
        // Bagian belakang
        glVertex3f(-0.7f, 0.2f, 1.1f);
        glVertex3f(-0.7f, 0.2f, -1.1f);
        glVertex3f(-0.7f, -0.3f, -1.1f);
        glVertex3f(-0.7f, -0.3f, 1.1f);
        
        // Sisi kanan
        glVertex3f(-0.7f, 0.2f, 1.1f);
        glVertex3f(0.7f, 0.2f, 1.1f);
        glVertex3f(0.7f, -0.3f, 1.1f);
        glVertex3f(-0.7f, -0.3f, 1.1f);
        
        // Sisi kiri
        glVertex3f(-0.7f, 0.2f, -1.1f);
        glVertex3f(0.7f, 0.2f, -1.1f);
        glVertex3f(0.7f, -0.3f, -1.1f);
        glVertex3f(-0.7f, -0.3f, -1.1f);
    glEnd();
    glPopMatrix();
    
    // Kabin mobil
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f); // Warna hitam
    glTranslatef(0.0f, 1.7f, 0.0f);
    glBegin(GL_QUADS);
        // Atap
        glVertex3f(-1.5f, 0.4f, 1.0f);
        glVertex3f(-1.5f, 0.4f, -1.0f);
        glVertex3f(1.0f, 0.4f, -1.0f);
        glVertex3f(1.0f, 0.4f, 1.0f);
        
        // Depan kaca (windshield)
        glVertex3f(1.0f, 0.4f, 1.0f);
        glVertex3f(1.0f, 0.4f, -1.0f);
        glVertex3f(1.8f, -0.7f, -1.0f);
        glVertex3f(1.8f, -0.7f, 1.0f);
        
        // Belakang kaca
        glVertex3f(-1.5f, 0.4f, 1.0f);
        glVertex3f(-1.5f, 0.4f, -1.0f);
        glVertex3f(-1.8f, -0.7f, -1.0f);
        glVertex3f(-1.8f, -0.7f, 1.0f);
        
        // Kiri kaca
        glVertex3f(-1.5f, 0.4f, -1.0f);
        glVertex3f(1.0f, 0.4f, -1.0f);
        glVertex3f(1.8f, -0.7f, -1.0f);
        glVertex3f(-1.8f, -0.7f, -1.0f);
        
        // Kanan kaca
        glVertex3f(-1.5f, 0.4f, 1.0f);
        glVertex3f(1.0f, 0.4f, 1.0f);
        glVertex3f(1.8f, -0.7f, 1.0f);
        glVertex3f(-1.8f, -0.7f, 1.0f);
    glEnd();
    glPopMatrix();
    
    // Panggil fungsi Ban untuk keempat ban
    Ban(1.8f, 0.35f, 1.2f);  // Depan kanan
    Ban(1.8f, 0.35f, -1.2f); // Depan kiri
    Ban(-1.8f, 0.35f, 1.2f); // Belakang kanan
    Ban(-1.8f, 0.35f, -1.2f); // Belakang kiri
    
    // Lampu depan kanan
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
    glTranslatef(2.5f, 0.6f, 0.8f);
    glScalef(0.15f, 0.15f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Lampu depan kiri
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
    glTranslatef(2.5f, 0.6f, -0.8f);
    glScalef(0.15f, 0.15f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Grille depan
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f); // Warna hitam
    glTranslatef(2.5f, 0.6f, 0.0f);
    glScalef(0.1f, 0.2f, 1.0f);
    glutSolidCube(1.0f);
    
    // Tambahan detail pada grille
    glColor3f(0.7f, 0.7f, 0.7f); // Warna perak
    for (int i = -4; i <= 4; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, i * 0.1f);
        glScalef(1.1f, 0.8f, 0.03f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    glPopMatrix();
    
    // Lampu belakang kanan
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Warna merah
    glTranslatef(-2.5f, 0.6f, 0.8f);
    glScalef(0.15f, 0.15f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Lampu belakang kiri
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Warna merah
    glTranslatef(-2.5f, 0.6f, -0.8f);
    glScalef(0.15f, 0.15f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Bumper depan
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f); // Warna abu-abu gelap
    glTranslatef(2.5f, 0.3f, 0.0f);
    glScalef(0.2f, 0.3f, 2.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Bumper belakang
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f); // Warna abu-abu gelap
    glTranslatef(-2.5f, 0.3f, 0.0f);
    glScalef(0.2f, 0.3f, 2.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Knalpot
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f); // Warna perak
    glTranslatef(-2.6f, 0.3f, -0.6f);
    glRotatef(90, 0, 1, 0);
    GLUquadricObj *quadratic = gluNewQuadric();
    gluCylinder(quadratic, 0.06, 0.06, 0.3, 10, 10);
    glPopMatrix();
}

// Fungsi untuk menggambar objek (mobil)
void draw(int isShadow) {
    glPushMatrix();
    glScalef(carScale, carScale, carScale); // Terapkan skala ke seluruh mobil
    
    if (isShadow) {
        // Jika bayangan, nonaktifkan material dan atur warna hitam
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.0, 0.0, 0.0);
    }
    
    Mobil();
    glPopMatrix();
}

//membuat proyeksi bayangan
void glShadowProjection(float * l, float * e, float * n)
{
float d, c;
float mat[16];
d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;

mat[0] = l[0]*n[0]+c; // membuat matrik. OpenGL menggunakan kolom matrik
mat[4] = n[1]*l[0];
mat[8] = n[2]*l[0];
mat[12] = -l[0]*c-l[0]*d;
mat[1] = n[0]*l[1];
mat[5] = l[1]*n[1]+c;
mat[9] = n[2]*l[1];
mat[13] = -l[1]*c-l[1]*d;
mat[2] = n[0]*l[2];
mat[6] = n[1]*l[2];
mat[10] = l[2]*n[2]+c;
mat[14] = -l[2]*c-l[2]*d;
mat[3] = n[0];
mat[7] = n[1];
mat[11] = n[2];
mat[15] = -d;
glMultMatrixf(mat); // kalikan matrik
}

void render()
{
    glClearColor(0.0,0.6,0.9,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0, GL_POSITION, l);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POINTS);
    glVertex3f(l[0],l[1],l[2]);
    glEnd();
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-1300.0,e[1]-0.1, 1300.0);
    glVertex3f( 1300.0,e[1]-0.1, 1300.0);
    glVertex3f( 1300.0,e[1]-0.1,-1300.0);
    glVertex3f(-1300.0,e[1]-0.1,-1300.0);
    glEnd();
    
    // Gambar mobil asli dengan pencahayaan
    glPushMatrix();
    glRotatef(ry,0,1,0);
    glRotatef(rx,1,0,0);
    glEnable(GL_LIGHTING); // Aktifkan pencahayaan untuk mobil asli
    draw(1);
    glPopMatrix();
    
    // Gambar bayangan
    glPushMatrix();
    glShadowProjection(l,e,n);
    glRotatef(ry,0,1,0);
    glRotatef(rx,1,0,0);
    glDisable(GL_LIGHTING);
    glColor3f(0.0,0.0,0.0); // Warna hitam untuk bayangan
    draw(1);
    glPopMatrix();
    
    glutSwapBuffers();
}

void keypress(unsigned char c, int a, int b)
{
if ( c==27 ) exit(0);
else if ( c=='s' ) l[1]-=5.0;
else if ( c=='w' ) l[1]+=5.0;
else if ( c=='a' ) l[0]-=5.0;
else if ( c=='d' ) l[0]+=5.0;
else if ( c=='q' ) l[2]-=5.0;
else if ( c=='e' ) l[2]+=5.0;
else if ( c=='h' ) help();
}

void help()
{
printf("proyeksi contoh bayangan sebuah obyek mobil\n");
printf("Tombol kontrol:\n");
printf("w/s: naikkan/turunkan posisi cahaya\n");
printf("a/d: geser cahaya ke kiri/kanan\n");
printf("q/e: geser cahaya ke depan/belakang\n");
printf("h: tampilkan bantuan ini\n");
printf("Esc: keluar dari program\n");
}

void idle()
{
rx+=0.1;
ry+=0.1;
render();
}

void resize(int w, int h)
{
glViewport(0, 0, w, h);
}

int main(int argc, char * argv[])
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowPosition(300,30);
glutCreateWindow("proyeksi bayangan mobil");
glutReshapeFunc(resize);
glutReshapeWindow(800,600);
glutKeyboardFunc(keypress);
glutDisplayFunc(render);
glutIdleFunc(idle);
glEnable(GL_NORMALIZE);
glEnable(GL_LIGHTING);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_DEPTH_TEST);
glEnable(GL_LIGHT0);
glEnable(GL_TEXTURE_2D);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0f, 1.0, 1.0, 400.0);
// Reset koordinat sebelum dimodifikasi/diubah
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0.0, 0.0, -150.0);
help();
glutMainLoop();
return 0;
}
