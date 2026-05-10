#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

// Replace this with the vertex array you need to generate normals for.
// Each vertex uses: position (x, y, z), color (r, g, b), uv (s, t).
// So each vertex is 8 floats.
float vectorArray[] = {
0.000000f, 0.000000f, 0.039024f, 0.500000f, 0.500000f, 0.500000f, 0.000000f, 0.000000f,
0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, 0.309017f,
0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, 0.587785f,
0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, 0.809017f,
0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, 0.951057f,
-0.000000f, 0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.000000f, 1.000000f,
-0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, 0.951057f,
-0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, 0.809017f,
-0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, 0.587785f,
-0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, 0.309017f,
-0.487805f, -0.000000f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -1.000000f, -0.000000f,
-0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, -0.309017f,
-0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, -0.587785f,
-0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, -0.809017f,
-0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, -0.951057f,
0.000000f, -0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.000000f, -1.000000f,
0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, -0.951057f,
0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, -0.809017f,
0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, -0.587785f,
0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, -0.309017f,
0.487805f, 0.000000f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 1.000000f, 0.000000f,
0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, 0.309017f,
0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, 0.587785f,
0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, 0.809017f,
0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, 0.951057f,
-0.000000f, 0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.000000f, 1.000000f,
-0.150740f, 0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, 0.951057f,
-0.286725f, 0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, 0.809017f,
-0.394642f, 0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, 0.587785f,
-0.463930f, 0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, 0.309017f,
-0.487805f, -0.000000f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -1.000000f, -0.000000f,
-0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.951057f, -0.309017f,
-0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.809017f, -0.587785f,
-0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.587785f, -0.809017f,
-0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, -0.309017f, -0.951057f,
0.000000f, -0.487805f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.000000f, -1.000000f,
0.150740f, -0.463930f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.309017f, -0.951057f,
0.286725f, -0.394642f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.587785f, -0.809017f,
0.394642f, -0.286725f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.809017f, -0.587785f,
0.463930f, -0.150740f, 0.146341f, 0.500000f, 0.500000f, 0.500000f, 0.951057f, -0.309017f,
0.487805f, 0.000000f, 0.039024f, 0.500000f, 0.500000f, 0.500000f, 1.000000f, 0.000000f,
};

// turns the given array into a string
string vertexKey(float* arr, int offset) {
    string key;
    for (int k = 0; k < 8; k++) {
        key += to_string(arr[offset + k]) + "f, ";
    }

    return key;
}

// accumulates the normals for a triangle defined by the three vertex indices
void accumulateTriangle(float* arr, int idxA, int idxB, int idxC, map<string, vector<glm::vec3>>& accumulated) {
    int offsets[3] = { idxA * 8, idxB * 8, idxC * 8 };

    glm::vec3 pts[3];
    string    keys[3];
    for (int j = 0; j < 3; j++) {
        pts[j]  = glm::vec3(arr[offsets[j]], arr[offsets[j]+1], arr[offsets[j]+2]);
        keys[j] = vertexKey(arr, offsets[j]);
    }

    glm::vec3 edge1  = pts[2] - pts[0];
    glm::vec3 edge2  = pts[1] - pts[0];
    glm::vec3 normal = glm::cross(edge1, edge2);

    for (const string& k : keys) {
        accumulated[k].push_back(normal);
    }
}

// averages the normals for each vertex
map<string, glm::vec3> averageNormals(const map<string, vector<glm::vec3>>& accumulated) {
    map<string, glm::vec3> result;
    for (const auto& [key, normals] : accumulated) {
        glm::vec3 sum(0.0f);
        for (const auto& n : normals) {
            sum += n;
        }
        result[key] = sum / (float)normals.size();
    }
    return result;
}

// turns the original vertex data with the averaged normals appended
void printWithNormals(float* arr, int count, const map<string, glm::vec3>& avgNormals) {
    string result;
    for (int i = 0; i < count; i++) {
        int offset = i * 8;
        string key = vertexKey(arr, offset);

        for (int j = 0; j < 8; j++) {
            result += to_string(arr[offset + j]) + "f, ";
        }

        auto it = avgNormals.find(key);
        if (it != avgNormals.end()) {
            result += to_string(it->second.x) + "f, "
                    + to_string(it->second.y) + "f, "
                    + to_string(it->second.z) + "f,";
        }
        result += '\n';
    }
    cout << result << endl;
}

// creates normals for triangle fan
void generateFanNormals(float* arr, int totalFloats) {
    int vertexCount = totalFloats / 8;
    map<string, vector<glm::vec3>> accumulated;

    for (int i = 1; i + 1 < vertexCount; i++) {
        accumulateTriangle(arr, 0, i, i+1, accumulated);
    }

    printWithNormals(arr, vertexCount, averageNormals(accumulated));
}

int main() {
    generateFanNormals(vectorArray, sizeof(vectorArray) / sizeof(float));
    return 0;
}