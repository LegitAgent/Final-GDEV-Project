// This is the normals generator. Apart from calculating for the normals of each vertex,
// it also "smoothens" out the normals of a single vertex. We do this by
// map accumulation, or basically getting all the normals
// calculated for a single vertex, and then averaging them out
// and normalizing to get one "smoothed" normal.

#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <cstring>

using namespace std;

// replace this vectorArray with the one you need to generate normals for.
// each vertex uses: position (x, y, z), color (r, g, b), uv (s, t). 
// So each vertex is 8 floats.
float vectorArray[] =  {
0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, 0.309017f, -0.200827f, -0.077180f, -0.976582f, 
0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, 0.309017f, 0.200827f, 0.077180f, -0.976582f, 
0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, 0.587785f, -0.173827f, -0.126292f, -0.976645f, 
0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, 0.587785f, 0.173827f, 0.126292f, -0.976645f, 
0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, 0.809017f, -0.126292f, -0.173827f, -0.976645f, 
0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, 0.809017f, 0.126292f, 0.173827f, -0.976645f, 
0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, 0.951057f, -0.066396f, -0.204345f, -0.976645f, 
0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, 0.951057f, 0.066396f, 0.204345f, -0.976645f, 
-0.000000f, 0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.000000f, 1.000000f, 0.000000f, -0.214862f, -0.976645f, 
-0.000000f, 0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.000000f, 1.000000f, 0.000000f, 0.214862f, -0.976645f, 
-0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, 0.951057f, 0.066396f, -0.204345f, -0.976645f, 
-0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, 0.951057f, -0.066396f, 0.204345f, -0.976645f, 
-0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, 0.809017f, 0.126292f, -0.173827f, -0.976645f, 
-0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, 0.809017f, -0.126292f, 0.173827f, -0.976645f, 
-0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, 0.587785f, 0.173827f, -0.126292f, -0.976645f, 
-0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, 0.587785f, -0.173827f, 0.126292f, -0.976645f, 
-0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, 0.309017f, 0.204345f, -0.066396f, -0.976645f, 
-0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, 0.309017f, -0.204345f, 0.066396f, -0.976645f,
-0.487805f, -0.000000f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -1.000000f, -0.000000f, 0.214862f, 0.000000f, -0.976645f,
-0.487805f, -0.000000f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -1.000000f, -0.000000f, -0.214862f, 0.000000f, -0.976645f,
-0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, -0.309017f, 0.204345f, 0.066396f, -0.976645f,
-0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, -0.309017f, -0.204345f, -0.066396f, -0.976645f,
-0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, -0.587785f, 0.173827f, 0.126292f, -0.976645f,
-0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, -0.587785f, -0.173827f, -0.126292f, -0.976645f,
-0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, -0.809017f, 0.126292f, 0.173827f, -0.976645f,
-0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, -0.809017f, -0.126292f, -0.173827f, -0.976645f,
-0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, -0.951057f, 0.066396f, 0.204345f, -0.976645f,
-0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, -0.951057f, -0.066396f, -0.204345f, -0.976645f,
0.000000f, -0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, -1.000000f, 0.000000f, 0.214862f, -0.976645f,
0.000000f, -0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.000000f, -1.000000f, 0.000000f, -0.214862f, -0.976645f,
0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, -0.951057f, -0.066396f, 0.204345f, -0.976645f,
0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, -0.951057f, 0.066396f, -0.204345f, -0.976645f,
0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, -0.809017f, -0.126292f, 0.173827f, -0.976645f,
0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, -0.809017f, 0.126292f, -0.173827f, -0.976645f,
0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, -0.587785f, -0.173827f, 0.126292f, -0.976645f,
0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, -0.587785f, 0.173827f, -0.126292f, -0.976645f,
0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, -0.309017f, -0.148405f, 0.228292f, -0.962216f,
0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, -0.309017f, 0.148405f, -0.228292f, -0.962216f,
0.487805f, 0.000000f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, -0.214862f, 0.000000f, -0.976645f,
0.487805f, 0.000000f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 1.000000f, 0.000000f, 0.214862f, 0.000000f, -0.976645f,
0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, 0.309017f, -0.200827f, -0.077180f, -0.976582f,
0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, 0.309017f, 0.200827f, 0.077180f, -0.976582f,
0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, 0.587785f, -0.173827f, -0.126292f, -0.976645f,
0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, 0.587785f, 0.173827f, 0.126292f, -0.976645f,
0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, 0.809017f, -0.126292f, -0.173827f, -0.976645f,
0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, 0.809017f, 0.126292f, 0.173827f, -0.976645f,
0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, 0.951057f, -0.066396f, -0.204345f, -0.976645f,
0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, 0.951057f, 0.066396f, 0.204345f, -0.976645f,
-0.000000f, 0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.000000f, 1.000000f, 0.000000f, -0.214862f, -0.976645f,
-0.000000f, 0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.000000f, 1.000000f, 0.000000f, 0.214862f, -0.976645f,
-0.150740f, 0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, 0.951057f, 0.066396f, -0.204345f, -0.976645f,
-0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, 0.951057f, -0.066396f, 0.204345f, -0.976645f,
-0.286725f, 0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, 0.809017f, 0.126292f, -0.173827f, -0.976645f,
-0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, 0.809017f, -0.126292f, 0.173827f, -0.976645f,
-0.394642f, 0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, 0.587785f, 0.173827f, -0.126292f, -0.976645f,
-0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, 0.587785f, -0.173827f, 0.126292f, -0.976645f,
-0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, 0.309017f, 0.204345f, -0.066396f, -0.976645f,
-0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, 0.309017f, -0.204345f, 0.066396f, -0.976645f,
-0.487805f, -0.000000f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -1.000000f, -0.000000f, 0.214862f, 0.000000f, -0.976645f,
-0.487805f, -0.000000f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -1.000000f, -0.000000f, -0.214862f, 0.000000f, -0.976645f,
-0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.951057f, -0.309017f, 0.204345f, 0.066396f, -0.976645f,
-0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, -0.309017f, -0.204345f, -0.066396f, -0.976645f,
-0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.809017f, -0.587785f, 0.173827f, 0.126292f, -0.976645f,
-0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, -0.587785f, -0.173827f, -0.126292f, -0.976645f,
-0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.587785f, -0.809017f, 0.126292f, 0.173827f, -0.976645f,
-0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, -0.809017f, -0.126292f, -0.173827f, -0.976645f,
-0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, -0.309017f, -0.951057f, 0.066396f, 0.204345f, -0.976645f,
-0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, -0.951057f, -0.066396f, -0.204345f, -0.976645f,
0.000000f, -0.487805f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, -1.000000f, 0.000000f, 0.214862f, -0.976645f,
0.000000f, -0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.000000f, -1.000000f, 0.000000f, -0.214862f, -0.976645f,
0.150740f, -0.463930f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.309017f, -0.951057f, -0.066396f, 0.204345f, -0.976645f,
0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, -0.951057f, 0.066396f, -0.204345f, -0.976645f,
0.286725f, -0.394642f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.587785f, -0.809017f, -0.126292f, 0.173827f, -0.976645f,
0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, -0.809017f, 0.126292f, -0.173827f, -0.976645f,
0.394642f, -0.286725f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.809017f, -0.587785f, -0.173827f, 0.126292f, -0.976645f,
0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, -0.587785f, 0.173827f, -0.126292f, -0.976645f,
0.463930f, -0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, -0.309017f, -0.148405f, 0.228292f, -0.962216f,
0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, -0.309017f, 0.148405f, -0.228292f, -0.962216f,
0.487805f, 0.000000f, -0.039024f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 0.000000f, 0.000000f, 0.579969f, -0.814638f,
0.487805f, 0.000000f, 0.039024f, 0.500000f, 0.500000f, 0.500000f, 1.000000f, 0.000000f, 0.000000f, -0.579969f, -0.814638f,
0.463930f, 0.150740f, -0.146341f, 1.000000f, 1.000000f, 1.000000f, 0.951057f, 0.309017f, -0.200827f, -0.077180f, -0.976582f,
0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, 0.309017f, 0.200827f, 0.077180f, -0.976582f,
};

// Removes any normals from array and replaces the vectorArray
// Replaces the vectorArray with the new one. 
// Returns the new size of the vectorArray.
int removeNormalsFromArray(float* vectorArray, int vectorArraySize) {
  int counter = 0;

  // loop through each line in vectorArray, remove the last three
  for (int i = 0; i <= vectorArraySize - 11 ; i += 11) {
    for (int j = 0; j < 8; j++) {
      vectorArray[counter] = vectorArray[i + j];
      counter++;
    }
  }

  return counter;
}

// Generates normals for a vertex array in the format used for GL_TRIANGLES.
void generateTriangleNormals(float* vectorArray, int vectorArraySize) {
  // map of each vector's normals
  map<string, vector<glm::vec3>> vectorNormals;
  // go through each triangle
  for (int i = 0; i <= vectorArraySize - 8*3 ; i += 8*3) {
    glm::vec3 trianglePoints[3];
    string pointStrings[3];
    // populate the three points of one triangle
    for (int j = 0; j < 3; j++) {
      float x = vectorArray[i + 8*j + 0];
      float y = vectorArray[i + 8*j + 1];
      float z = vectorArray[i + 8*j + 2];
      trianglePoints[j] = glm::vec3(x, y, z);
      for (int k = 0; k < 8; k++) {
        pointStrings[j] += to_string(vectorArray[i + 8*j + k]) + "f, ";
                                                        // could this be "f, "?
      }
    }
    // get the vectors by subtraction
    glm::vec3 vector1 = trianglePoints[2] - trianglePoints[0];
    glm::vec3 vector2 = trianglePoints[1] - trianglePoints[0];
    // get the cross product of two vectors. this will be the normal vector for all three points.
    glm::vec3 cross_p = glm::cross(vector1, vector2);
    
    // add this cross product to the point's list of normals.
    for (string pointString : pointStrings) {
      vectorNormals[pointString].push_back(cross_p); 
    }
  }
  
  // after going through each triangle,
  // get the average of the calculated normals of each point
  map<string, string> averagedNormals;
  for (const auto& [point, normals] : vectorNormals) {
    float totalX = 0.0f;
    float totalY = 0.0f;
    float totalZ = 0.0f;
    for (glm::vec3 normal : normals) {
      totalX += normal.x;
      totalY += normal.y;
      totalZ += normal.z;
    }
    float averagedX = totalX / normals.size();
    float averagedY = totalY / normals.size();
    float averagedZ = totalZ / normals.size();
    // get the normalize of the average
    glm::vec3 avg = glm::normalize(glm::vec3(averagedX, averagedY, averagedZ));
    
    averagedNormals[point] = to_string(avg.x) + "f, " + 
                             to_string(avg.y) + "f, " + 
                             to_string(avg.z) + "f, ";
  }
  
  // modify the vectorArray to now include the normals of each vector
  string resultingArray = "";
  for (int i = 0; i <= vectorArraySize - 8; i += 8) {
    string point;
    for (int j = 0; j < 8; j++) {
      point += to_string(vectorArray[i + j]) + "f, ";
    }
    point += averagedNormals[point];
    resultingArray += point + '\n';
  }
  
  cout << resultingArray << endl;
  // 
}

// Generates normals for a vertex array in the format used for GL_TRIANGLE_FAN.
void generateFanNormals(float* vectorArray, int vectorArraySize) {
  // map of each vector's normals
  map<string, vector<glm::vec3>> vectorNormals;

  // get the first point
  glm::vec3 firstPoint = glm::vec3(vectorArray[0], vectorArray[1], vectorArray[2]);

  // go through each triangle, their first point will always be the first ever vector in the array
  // this loop starts from the second vector, so i starts from the x of the second vector
  for (int i = 8; i < vectorArraySize - 8 ; i += 8) {
    glm::vec3 trianglePoints[3];
    string pointStrings[3];

    // populate triangle points and point strings with the info of the first vector
    trianglePoints[0] = firstPoint;
    for (int k = 0; k < 8; k++) {
      pointStrings[0] += to_string(vectorArray[k]) + "f, ";
                                                      // could this be "f, "?
    }

    // populate the next two points of the triangle
    for (int j = 0; j < 2; j++) {
      float x = vectorArray[i + 8*j + 0];
      float y = vectorArray[i + 8*j + 1];
      float z = vectorArray[i + 8*j + 2];
      trianglePoints[j+1] = glm::vec3(x, y, z);
      for (int k = 0; k < 8; k++) {
        pointStrings[j+1] += to_string(vectorArray[i + 8*j + k]) + "f, ";
                                                        // could this be "f, "?
      }
    }

    // get the vectors by subtraction
    glm::vec3 vector1 = trianglePoints[2] - trianglePoints[0];
    glm::vec3 vector2 = trianglePoints[1] - trianglePoints[0];
    // get the cross product of two vectors. this will be the normal vector for all three points.
    glm::vec3 cross_p = glm::cross(vector1, vector2);
    
    // add this cross product to the point's list of normals.
    for (string pointString : pointStrings) {
      vectorNormals[pointString].push_back(cross_p); 
    }
  }
  
  // after going through each triangle,
  // get the average of the calculated normals of each point
  map<string, string> averagedNormals;
  for (const auto& [point, normals] : vectorNormals) {
    float totalX = 0.0f;
    float totalY = 0.0f;
    float totalZ = 0.0f;
    for (glm::vec3 normal : normals) {
      totalX += normal.x;
      totalY += normal.y;
      totalZ += normal.z;
    }
    float averagedX = totalX / normals.size();
    float averagedY = totalY / normals.size();
    float averagedZ = totalZ / normals.size();
    // get the normalize of the average
    glm::vec3 avg = glm::normalize(glm::vec3(averagedX, averagedY, averagedZ));
    
    averagedNormals[point] = to_string(avg.x) + "f, " + 
                             to_string(avg.y) + "f, " + 
                             to_string(avg.z) + "f, ";
  }
  
  // modify the vectorArray to now include the normals of each vector
  string resultingArray = "";
  for (int i = 0; i <= vectorArraySize - 8; i += 8) {
    string point;
    for (int j = 0; j < 8; j++) {
      point += to_string(vectorArray[i + j]) + "f, ";
    }
    point += averagedNormals[point];
    resultingArray += point + '\n';
  }
  
  cout << resultingArray << endl;
}

// Generates normals for a vertex array in the format used for GL_TRIANGLE_STRIP.
void generateStripNormals(float* vectorArray, int vectorArraySize) {
  // map of each vector's normals
  map<string, vector<glm::vec3>> vectorNormals;

  // go through each triangle, it shifts the pointer one vector
  for (int i = 0; i < vectorArraySize - 8*2 ; i += 8) {
    glm::vec3 trianglePoints[3];
    string pointStrings[3];

    // populate the three points of one triangle
    for (int j = 0; j < 3; j++) {
      float x = vectorArray[i + 8*j + 0];
      float y = vectorArray[i + 8*j + 1];
      float z = vectorArray[i + 8*j + 2];
      trianglePoints[j] = glm::vec3(x, y, z);
      for (int k = 0; k < 8; k++) {
        pointStrings[j] += to_string(vectorArray[i + 8*j + k]) + "f, ";
                                                        // could this be "f, "?
      }
    }
    // get the vectors by subtraction
    glm::vec3 vector1 = trianglePoints[2] - trianglePoints[0];
    glm::vec3 vector2 = trianglePoints[1] - trianglePoints[0];
    // odd triangles are clockwise, so reverse the vectors to get a proper normal config
    if ((i / 8) % 2 == 1) swap(vector1, vector2);
    // get the cross product of two vectors. this will be the normal vector for all three points.
    glm::vec3 cross_p = glm::cross(vector1, vector2);
    
    // add this cross product to the point's list of normals.
    for (string pointString : pointStrings) {
      vectorNormals[pointString].push_back(cross_p); 
    }
  }
  
  // after going through each triangle,
  // get the average of the calculated normals of each point
  map<string, string> averagedNormals;
  for (const auto& [point, normals] : vectorNormals) {
    float totalX = 0.0f;
    float totalY = 0.0f;
    float totalZ = 0.0f;
    for (glm::vec3 normal : normals) {
      totalX += normal.x;
      totalY += normal.y;
      totalZ += normal.z;
    }
    float averagedX = totalX / normals.size();
    float averagedY = totalY / normals.size();
    float averagedZ = totalZ / normals.size();
    // get the normalize of the average
    glm::vec3 avg = glm::normalize(glm::vec3(averagedX, averagedY, averagedZ));
    
    averagedNormals[point] = to_string(avg.x) + "f, " + 
                             to_string(avg.y) + "f, " + 
                             to_string(avg.z) + "f, ";
  }
  
  // modify the vectorArray to now include the normals of each vector
  string resultingArray = "";
  for (int i = 0; i <= vectorArraySize - 8; i += 8) {
    string point;
    for (int j = 0; j < 8; j++) {
      point += to_string(vectorArray[i + j]) + "f, ";
    }
    point += averagedNormals[point];
    resultingArray += point + '\n';
  }
  
  cout << resultingArray << endl;
  // 
}

int main(int argc, char *argv[]) {

  int vectorArraySize = sizeof(vectorArray) / sizeof(float);

  // DUE TO HOW ./TEST WORKS,
  // You will just have to comment out the ones u dont need.
  
  // comment this out if your array does not have normals yet
  vectorArraySize = removeNormalsFromArray(vectorArray, vectorArraySize);

  // comment out the ones you don't need here.
  // generateTriangleNormals(vectorArray, vectorArraySize);
  generateStripNormals(vectorArray, vectorArraySize);
  // generateFanNormals(vectorArray, vectorArraySize);

  return 0;
}