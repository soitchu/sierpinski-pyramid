#include <GL/glut.h>  
#include <math.h>     
#include <unistd.h>  
#include <iostream>  
#include <vector>  
#include <chrono>
#include <time.h> 
using namespace std;

int MAX_RESCURSION = 0;                 /// Used to draw the nth iteration of the sierpinski tetrahedron
const int MAX_RESCURSION_ACTUAL = 6;
const int MAX_RESCURSION_EXPO =pow(2,MAX_RESCURSION_ACTUAL-1);


struct Point{
   double x, y, z;
};

int count1 = 0;
int FPS = 0;
int FPS_LAST_TIME = time(NULL);

int WINDOW_HEIGHT = 1000;               /// Window's height
int WINDOW_WIDTH = WINDOW_HEIGHT;       /// Window's width
float TRIANGLE_SIDE = WINDOW_WIDTH;     /// Initial size of triangle's side


uint64_t timeSinceEpochMicrosec() {
  return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

/*
    A function to draw lines
*/

void drawLines(Point ini, Point final) {
    glColor3f(0,0,0);     
    glBegin(GL_LINES);
    glVertex3d(ini.x/WINDOW_WIDTH, ini.y/WINDOW_HEIGHT,ini.z/WINDOW_HEIGHT);
    glVertex3d(final.x/WINDOW_WIDTH, final.y/WINDOW_HEIGHT,final.z/WINDOW_HEIGHT);
    glEnd();
} 


/*
    A function to draw squares
*/
void drawSquare(Point ver1, Point ver2, Point ver3, Point ver4) {
    glColor3f(1,1,1); 
    glPointSize(3.0);  
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3d(ver1.x/WINDOW_WIDTH, ver1.y/WINDOW_HEIGHT,ver1.z/WINDOW_HEIGHT);
    glVertex3d(ver2.x/WINDOW_WIDTH, ver2.y/WINDOW_HEIGHT,ver2.z/WINDOW_HEIGHT);
    glVertex3d(ver3.x/WINDOW_WIDTH, ver3.y/WINDOW_HEIGHT,ver3.z/WINDOW_HEIGHT);
    glVertex3d(ver4.x/WINDOW_WIDTH, ver4.y/WINDOW_HEIGHT,ver4.z/WINDOW_HEIGHT);
    glEnd();
} 

/*
    Drawing a particular number 
*/
void drawNumbers(int x, Point position, int size){
    if(x < 0 || x > 9){
        return;
    }
    vector<vector<vector<char>>> grid= {
        {
            {' ',' ','o','o','o',' ',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ','o',' ',' ','o','o',' '},
            {' ','o',' ','o',' ','o',' '},
            {' ','o','o',' ',' ','o',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ',' ','o','o','o',' ',' '},
        },
        {
            {' ',' ',' ','o',' ',' ',' '},
            {' ',' ','o','o',' ',' ',' '},
            {' ',' ',' ','o',' ',' ',' '},
            {' ',' ',' ','o',' ',' ',' '},
            {' ',' ',' ','o',' ',' ',' '},
            {' ',' ',' ','o',' ',' ',' '},
            {' ','o','o','o','o','o',' '},
        },
        {
            {' ',' ','o','o','o',' ',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ',' ',' ',' ','o',' ',' '},
            {' ',' ',' ','o',' ',' ',' '},
            {' ',' ','o',' ',' ',' ',' '},
            {' ','o',' ',' ',' ',' ',' '},
            {' ','o','o','o','o','o',' '},
        },
        {
            {' ',' ','o','o','o',' ',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ',' ',' ',' ',' ','o',' '},
            {' ',' ',' ',' ','o',' ',' '},
            {' ',' ',' ',' ',' ','o',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ',' ','o','o','o',' ',' '},
        },
        {
            {' ',' ',' ',' ',' ','o',' '},
            {' ',' ',' ',' ','o','o',' '},
            {' ',' ',' ','o',' ','o',' '},
            {' ',' ','o',' ',' ','o',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ','o','o','o','o','o',' '},
            {' ',' ',' ',' ',' ','o',' '},
        },
        {
            {' ','o','o','o','o','o',' '},
            {' ','o',' ',' ',' ',' ',' '},
            {' ','o',' ',' ',' ',' ',' '},
            {' ','o','o','o','o',' ',' '},
            {' ',' ',' ',' ',' ','o',' '},
            {' ',' ',' ',' ',' ','o',' '},
            {' ','o','o','o','o',' ',' '},
        },{
            {' ',' ',' ','o','o','o',' '},
            {' ',' ','o',' ',' ',' ',' '},
            {' ','o',' ',' ',' ',' ',' '},
            {' ','o','o','o','o',' ',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ',' ','o','o','o',' ',' '},
        },
        {
            {' ','o','o','o','o','o',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ',' ',' ',' ','o',' ',' '},
            {' ',' ',' ','o',' ',' ',' '},
            {' ',' ','o',' ',' ',' ',' '},
            {' ',' ','o',' ',' ',' ',' '},
            {' ',' ','o',' ',' ',' ',' '},
        },
        {
            {' ',' ','o','o','o',' ',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ',' ','o','o','o',' ',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ',' ','o','o','o',' ',' '},
        },
        {
            {' ',' ','o','o','o',' ',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ','o',' ',' ',' ','o',' '},
            {' ',' ','o','o','o','o',' '},
            {' ',' ',' ',' ',' ','o',' '},
            {' ',' ',' ',' ',' ','o',' '},
            {' ',' ','o','o','o',' ',' '},
        } 
    };
    vector<vector<char>> temp = grid[x];

    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(temp[i][j] == 'o'){
                Point one = {position.x + j*size, position.y - size*i,0};
                Point two = {position.x + j*size + size, position.y - size*i,0};
                Point three = {position.x + j*size + size, position.y - size*i - size,0};
                Point four = {position.x + j*size, position.y - size*i - size,0};

 
                drawSquare(one, two, three, four);
            }
        }
    }

}

/*
    Drawing multiple numbers at once
*/
void drawNumbersMultiple(int x, Point position, int size){
    int count = 0;
    vector <int> temp;
    while(x){
        int y = x%10;
        temp.push_back(y);
        x = x/10;
    }

    for(int i = temp.size() - 1, j = 0; i >=0; i--, j++){
        drawNumbers(temp[i], (Point) {position.x + j*size*7, position.y, 0}, size);
    }
}
/*
    A function to draw Triangles
*/
void drawTriangle(Point ver1, Point ver2, Point ver3) {
    glColor3f(1,1,1); 
    glBegin(GL_POLYGON);
    glColor3f(1.0,1,1);
    glVertex3d(ver1.x/WINDOW_WIDTH, ver1.y/WINDOW_HEIGHT,ver1.z/WINDOW_HEIGHT);
    glVertex3d(ver2.x/WINDOW_WIDTH, ver2.y/WINDOW_HEIGHT,ver2.z/WINDOW_HEIGHT);
    glVertex3d(ver3.x/WINDOW_WIDTH, ver3.y/WINDOW_HEIGHT,ver3.z/WINDOW_HEIGHT);
    glEnd();
} 

/*
    The main function that draws the sierpinski tetrahedron
*/
void drawSier(float side, float centerX = 0, float centerY = 0,float centerZ = 0, int count = 0){
    if(count == MAX_RESCURSION){
        Point vertex1 = {centerX,centerY + (0.43301270189)*side, centerZ};
        Point vertex2 = {centerX - side/2,centerY - (0.43301270189)*side,centerZ+side/2};
        Point vertex3 = {centerX + side/2,centerY - (0.43301270189)*side,centerZ+side/2};
        Point vertex4 = {centerX - side/2,centerY - (0.43301270189)*side,centerZ-side/2};
        Point vertex5= {centerX + side/2,centerY - (0.43301270189)*side,centerZ-side/2};
 
        drawSquare(vertex2,vertex3,vertex5,vertex4);
        drawTriangle(vertex2,vertex3,vertex1);
        drawTriangle(vertex2,vertex4,vertex1);
        drawTriangle(vertex4,vertex5,vertex1);
        drawTriangle(vertex5,vertex3,vertex1);
 
        /// Black outlines of the tetrahedron
        drawLines(vertex2,vertex1);
        drawLines(vertex3,vertex1); 
        drawLines(vertex4,vertex1); 
        drawLines(vertex5,vertex1);
        return;
    }

    /// The main logic that constructs the sierpinski tetrahedron
    count++;        
    drawSier(side/2, centerX + side/4, centerY - (0.43301270189)*side + (0.43301270189/2)*side, centerZ + side/2 - side/4,count);
    drawSier(side/2, centerX + side/4, centerY - (0.43301270189)*side + (0.43301270189/2)*side, centerZ - side/2 + side/4,count);
    drawSier(side/2, centerX - side/4, centerY - (0.43301270189)*side + (0.43301270189/2)*side, centerZ + side/2 - side/4,count);
    drawSier(side/2, centerX - side/4, centerY - (0.43301270189)*side + (0.43301270189/2)*side, centerZ - side/2 + side/4,count);        
    drawSier(side/2, centerX, centerY + (0.43301270189)*side - (0.43301270189/2)*side, centerZ,count);
}
 
 
void myDisplay(void){

    glEnable(GL_DEPTH_TEST); 
    bool isAnimation = true;
    float scale = 1;
    float PHASE_ONE_ANIMATION = 60*2;
    float PHASE_ONE_COUNT = 0;
    float ANIMATION_RATE = 1.013;
    bool PADDING_ANIMATION = false;
    float rotation = 0;
    int FPS_TO_SHOW = FPS;
    uint64_t lastFrameTime = timeSinceEpochMicrosec();
    bool increaseMaxRecur = true;
    while(true){
        glClear(GL_COLOR_BUFFER_BIT);
        drawNumbersMultiple(FPS_TO_SHOW, (Point) {(float)(-WINDOW_WIDTH + 50), (float)(WINDOW_HEIGHT - 50), 0}, 10);

        /// FPS COUNTER

        if(FPS_LAST_TIME == time(NULL)){            
            FPS++;
        }else{
            FPS_LAST_TIME = time(NULL);
            FPS_TO_SHOW = FPS;
            FPS = 1;
        }

        /// Rotating the tetrahedron
        rotation += 0.5;
        glRotatef(rotation, 0,1,0);


        
        /// Animating the last part such that its final state is similar to the first state of the image
        if(MAX_RESCURSION != MAX_RESCURSION_ACTUAL -1){

        }else if(PADDING_ANIMATION){
            /// This is phase two of the animation
            glScalef(scale,scale,scale);

            /// Translating the tetrahedron such that the top pyramid is in the center
            glTranslatef(0,min(PHASE_ONE_COUNT/PHASE_ONE_ANIMATION,(float) 1)*(-TRIANGLE_SIDE*sqrt(3)/4 +(TRIANGLE_SIDE/MAX_RESCURSION_EXPO)*sqrt(3)/4 )/WINDOW_HEIGHT,0);

            /// Verifying if the sierpinski tetrahedron has been rotated by 90 degress
            /// This ensures that the final state and the first state look similar
            if((int)rotation%90 == 0){

                /// Restoring the translation to its initial state
                glTranslatef(0,-min(PHASE_ONE_COUNT/PHASE_ONE_ANIMATION,(float) 1)*(-TRIANGLE_SIDE*sqrt(3)/4 +(TRIANGLE_SIDE/MAX_RESCURSION_EXPO)*sqrt(3)/4 )/WINDOW_HEIGHT,0);

                /// As the animation has ended, we can go back to using count1 to change the value of MAX_RESCURSION
                isAnimation=true;
                increaseMaxRecur = false;

                MAX_RESCURSION = (MAX_RESCURSION + 1)%MAX_RESCURSION_ACTUAL;
                /// Restoring its scale to its initial value
                glScalef(1/scale,1/scale,1/scale);
                scale = 1;

                /// Defaulting the variables that help with the animation to their initial value
                PHASE_ONE_COUNT = 0;
                PADDING_ANIMATION = false;
            }
        }else{
            /// This is phase one of the animation

            /// Increasing PHASE_ONE_COUNT so that the tetrahedron translates gradually
            PHASE_ONE_COUNT++;

            /// We do not want MAX_RESCURSION to change until the animation has ended
            isAnimation = false;
            
            /// Scaling the image such that the topmost pyramid of the final sierpinski tetrahedron has the same size as
            /// first sierpinski tetrahedron
            scale = scale*ANIMATION_RATE;
            glScalef(scale,scale,scale);

            /// If the topmost pyramid of the final sierpinski tetrahedron has the same size as
            /// first sierpinski tetrahedron then stop increasing the size and start phase 2 of the animation
            if(scale >=MAX_RESCURSION_EXPO){
                /// Flag that makes the phase 2 start
                PADDING_ANIMATION = true;
            }else{
                /// If we have to continue phase 1, then make it so the topmost pyramid is at the center
                glTranslatef(0,min(PHASE_ONE_COUNT/PHASE_ONE_ANIMATION,(float) 1)*(-TRIANGLE_SIDE*sqrt(3)/4 +(TRIANGLE_SIDE/MAX_RESCURSION_EXPO)*sqrt(3)/4 )/WINDOW_HEIGHT,0);
            }

            /// When phase two begins, the else state right above this statement won't be executed, so the center won't be
            /// at the topmost pyramid. This if statement ensures that the center is indeed at the topmost pyramid.
            if(PADDING_ANIMATION){
                glTranslatef(0,min(PHASE_ONE_COUNT/PHASE_ONE_ANIMATION,(float) 1)*(-TRIANGLE_SIDE*sqrt(3)/4 +(TRIANGLE_SIDE/MAX_RESCURSION_EXPO)*sqrt(3)/4 )/WINDOW_HEIGHT,0);
            }
        }

        /// Finally drawing the sierpinski tetrahedron
        glClearColor(0, 0, 0, 1);
        glClear(GL_DEPTH_BUFFER_BIT);
        drawSier(TRIANGLE_SIDE); 
        glFlush();  

        /// Maintaining a consistent frame rate
        uint64_t lastFrameTime = timeSinceEpochMicrosec() - lastFrameTime;
        if(lastFrameTime < 16666){
            usleep(16666 - lastFrameTime);
        }

        /// If the animation is active, then translate the image to its initial state
        if(MAX_RESCURSION == MAX_RESCURSION_ACTUAL - 1){
            glTranslatef(0,-min(PHASE_ONE_COUNT/PHASE_ONE_ANIMATION,(float) 1)*(-TRIANGLE_SIDE*sqrt(3)/4 +(TRIANGLE_SIDE/MAX_RESCURSION_EXPO)*sqrt(3)/4 )/WINDOW_HEIGHT,0);
        }

        /// Restoring the initial state

        glRotatef(-rotation, 0,1,0);
        glScalef(1/scale,1/scale,1/scale);       

        /// If the variable rotation is a factor of 90, or in other words if the tetrahedron has been rotated by 90 degrees,
        /// then increase MAX_RESCURSION which will render the (MAX_RESCURSION +1)th iteration of the Sierpinski Tetrahedron. 
        /// And if MAX_RESCURSION is equal to MAX_RESCURSION_ACTUAL, MAX_RESCURSION will go back to 0, its initial state

        if((int)rotation%90 == 0 && isAnimation && (int) rotation!=0 && (ceil(rotation) == rotation) && increaseMaxRecur){
            MAX_RESCURSION = (MAX_RESCURSION + 1)%MAX_RESCURSION_ACTUAL;
            rotation =0;
        }else if(!increaseMaxRecur){
            increaseMaxRecur = true;
        }

        lastFrameTime = timeSinceEpochMicrosec();
    }
}


int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    // including glutInitDisplayMode breaks DEPTH_TEST for some reason
    // glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);  
    glutInitWindowPosition(0, 0);   
    glutCreateWindow("Sierpinski Tetrahedron");
    glutDisplayFunc(myDisplay);
    glutMainLoop();    

    return 0;
}
