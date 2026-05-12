#include <map>
#include <array>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>

using namespace std;

const float COLOR_R = 1.0f;
const float COLOR_G = 1.0f;
const float COLOR_B = 1.0f;
const int SUBS = 2;
const float PI = 3.14159265358979323846f;

void pushVertex(vector<glm::vec3>& verts, float x, float y, float z) {
    verts.push_back(glm::normalize(glm::vec3(x, y, z)));
}

int getMidpoint(int a, int b, vector<glm::vec3>& verts, unordered_map<long long, int>& cache) {
    long long key = ((long long)min(a, b) << 20) | max(a, b);
    auto it = cache.find(key);
    if (it != cache.end()) return it->second;

    int idx = (int)verts.size();
    verts.push_back(glm::normalize((verts[a] + verts[b]) * 0.5f));
    cache[key] = idx;
    return idx;
}

glm::vec2 sphericalUV(const glm::vec3& n) {
    float u = atan2f(n.z, n.x) / (2.0f * PI) + 0.5f;
    float v = asinf(glm::clamp(n.y, -1.0f, 1.0f)) / PI + 0.5f;
    return { u, v };
}

vector<array<int, 3>> buildFaces(vector<glm::vec3>& verts, int subdivisions) {
    const float PHI = (1.0f + sqrtf(5.0f)) / 2.0f;

    pushVertex(verts, -1,  PHI,  0); pushVertex(verts,  1,  PHI,  0);
    pushVertex(verts, -1, -PHI,  0); pushVertex(verts,  1, -PHI,  0);
    pushVertex(verts,  0, -1,  PHI); pushVertex(verts,  0,  1,  PHI);
    pushVertex(verts,  0, -1, -PHI); pushVertex(verts,  0,  1, -PHI);
    pushVertex(verts,  PHI, 0, -1);  pushVertex(verts,  PHI, 0,  1);
    pushVertex(verts, -PHI, 0, -1);  pushVertex(verts, -PHI, 0,  1);

    vector<array<int, 3>> faces = {
        {0,11,5},{0,5,1},{0,1,7},{0,7,10},{0,10,11},
        {1,5,9},{5,11,4},{11,10,2},{10,7,6},{7,1,8},
        {3,9,4},{3,4,2},{3,2,6},{3,6,8},{3,8,9},
        {4,9,5},{2,4,11},{6,2,10},{8,6,7},{9,8,1}
    };

    for (int s = 0; s < subdivisions; s++) {
        unordered_map<long long, int> cache;
        vector<array<int, 3>> next;

        for (auto& f : faces) {
            int m01 = getMidpoint(f[0], f[1], verts, cache);
            int m12 = getMidpoint(f[1], f[2], verts, cache);
            int m20 = getMidpoint(f[2], f[0], verts, cache);
            next.push_back({f[0], m01, m20});
            next.push_back({f[1], m12, m01});
            next.push_back({f[2], m20, m12});
            next.push_back({m01,  m12, m20});
        }
        faces = next;
    }

    return faces;
}

void fixSeam(glm::vec2 uv[3]) {
    for (int i = 0; i < 3; i++) {
        bool hasHighNeighbor = false;
        for (int j = 0; j < 3; j++)
            if (uv[j].x > 0.75f) hasHighNeighbor = true;
        if (hasHighNeighbor && uv[i].x < 0.25f)
            uv[i].x += 1.0f;
    }
}

void fixPoles(glm::vec2 uv[3], const glm::vec3 pts[3]) {
    for (int i = 0; i < 3; i++) {
        if (fabsf(pts[i].y) > 0.999f)
            uv[i].x = (uv[(i+1)%3].x + uv[(i+2)%3].x) * 0.5f;
    }
}

void printVertex(const glm::vec3& p, float r, float g, float b, const glm::vec2& uv, const glm::vec3& n) {
    printf("%.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, %.6ff, \n",
        p.x, p.y, p.z,
        r, g, b,
        uv.x, uv.y,
        n.x, n.y, n.z);
}

void generateIcosphere(float r, float g, float b, int subdivisions) {
    vector<glm::vec3> verts;
    vector<array<int, 3>> faces = buildFaces(verts, subdivisions);

    int faceCount = (int)faces.size();
    printf("// GL_TRIANGLES  (%d faces, %d vertices)\n", faceCount, faceCount * 3);
    printf("float icoSphere[] = {\n");

    for (auto& f : faces) {
        glm::vec3 pts[3] = { verts[f[0]], verts[f[1]], verts[f[2]] };

        glm::vec2 uv[3];
        for (int i = 0; i < 3; i++) uv[i] = sphericalUV(pts[i]);
        fixSeam(uv);
        fixPoles(uv, pts);

        for (int i = 0; i < 3; i++) {
            // on a unit sphere the outward normal equals the position vector
            printVertex(pts[i], r, g, b, uv[i], pts[i]);
        }
    }

    printf("};\n");
}

int main() {
    generateIcosphere(COLOR_R, COLOR_G, COLOR_B, SUBS);
    return 0;
}