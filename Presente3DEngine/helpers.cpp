void MakePulsar(void)
{
    #define DTOR            0.0174532925
#define RTOD            57.2957795
#define TWOPI           6.283185307179586476925287
#define PI              3.141592653589793238462643
#define PID2            1.570796326794896619231322

   int i,j,k;
   double cradius = 1;            /* Final radius of the cone */
   double clength = 5;            /* Cone length */
   double sradius = 1.3;         /* Final radius of sphere */
   double r1=1.4,r2=1.8;         /* Min and Max radius of field lines */
   double x,y,z;
   Vertex p[4],n[4];
   static double rotateangle = 0.0;

   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

   /* Top level rotation  - spin */
   glPushMatrix();
   glRotatef(rotateangle,0.0f,1.0f,0.0f);

   /* Rotation about spin axis */
   glPushMatrix();
   glRotatef(45.0,0.0,0.0,1.0);

   /* Light in center */
   //glutSolidSphere(0.9,16,8);

   /* Spherical center */
   for (i=0;i<360;i+=5) {
      for (j=-80;j<80;j+=5) {

         p[0].x = sradius * cos(j*DTOR) * cos(i*DTOR);
         p[0].y = sradius * sin(j*DTOR);
         p[0].z = sradius * cos(j*DTOR) * sin(i*DTOR);
         n[0] = p[0];

         p[1].x = sradius * cos((j+5)*DTOR) * cos(i*DTOR);
         p[1].y = sradius * sin((j+5)*DTOR);
         p[1].z = sradius * cos((j+5)*DTOR) * sin(i*DTOR);
         n[1] = p[1];

         p[2].x = sradius * cos((j+5)*DTOR) * cos((i+5)*DTOR);
         p[2].y = sradius * sin((j+5)*DTOR);
         p[2].z = sradius * cos((j+5)*DTOR) * sin((i+5)*DTOR);
         n[2] = p[2];

         p[3].x = sradius * cos(j*DTOR) * cos((i+5)*DTOR);
         p[3].y = sradius * sin(j*DTOR);
         p[3].z = sradius * cos(j*DTOR) * sin((i+5)*DTOR);
         n[3] = p[3];

         glBegin(GL_POLYGON);
         if (i % 20 == 0)
            glColor4f(1.0,1.0,1.0, 0.5f);
         else
            glColor4f(0.5,0.5,0.5, 0.5f);
         for (k=0;k<4;k++) {
            glNormal3f(n[k].x,n[k].y,n[k].z);
            glVertex3f(p[k].x / 10.0f,p[k].y  / 10.0f ,p[k].z  / 10.0f);
         }
         glEnd();
      }
   }

   /* Draw the cones */
   for (j=-1;j<=1;j+=2) {
      for (i=0;i<360;i+=10) {
         
         //p[0]   = origin;
         n[0]   = p[0];
         n[0].y = -1;

         p[1].x = cradius * cos(i*DTOR);
         p[1].y = j*clength;
         p[1].z = cradius * sin(i*DTOR);
         n[1]   = p[1];
         n[1].y = 0;

         p[2].x = cradius * cos((i+10)*DTOR);
         p[2].y = j*clength;
         p[2].z = cradius * sin((i+10)*DTOR);
         n[2]   = p[2];
         n[2].y = 0;

         glBegin(GL_POLYGON);
         if (i % 30 == 0)
            glColor4f(0.2,0.2,0.2, 0.5f);
         else
            glColor4f(0.5,0.5,0.5, 0.5f);
         for (k=0;k<3;k++) {
            glNormal3f(n[k].x,n[k].y,n[k].z);
            glVertex3f(p[k].x / 10.0f,p[k].y / 10.0f,p[k].z / 10.0f);
         }
         glEnd();
      }
   }

   /* Draw the field lines */
   for (j=0;j<360;j+=20) {
      glPushMatrix();
      glRotatef((double)j,0.0,1.0,0.0);
      glBegin(GL_LINE_STRIP);
      glColor3f(0.7,0.7,0.7);
      for (i=-140;i<140;i++) {
         x = r1 + r1 * cos(i*DTOR);
         y = r2 * sin(i*DTOR);
         z = 0;
         glVertex3f(x / 10.0f,y / 10.0f,z / 10.0f);   
      }   
      glEnd();
      glPopMatrix();      
   }

   glPopMatrix(); /* Pulsar axis rotation */
   glPopMatrix(); /* Pulsar spin */
   //rotateangle += rotatespeed;
}