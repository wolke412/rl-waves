#include "raylib.h"
#include "rlgl.h"

#define GRID_SIZE 40   // Size of the grid (number of quads per row/column)
#define QUAD_SIZE 1.0f // Size of each quad

// Function to generate a grid of quads (plane mesh)
Mesh GeneratePlaneMesh(int gridSize, float quadSize);

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  InitWindow(screenWidth, screenHeight, "raylib - Shader Testing Plane");

  Camera camera = {0};
  camera.position = (Vector3){5.0f, 5.0f, 5.0f};
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 90.0f;

  // Load shader
  Shader shader = LoadShader("shaders/shader.vs", "shaders/shader.fs");

  int timeLoc = GetShaderLocation(shader, "u_time");

  // Generate a plane mesh
  Mesh planeMesh = GeneratePlaneMesh(GRID_SIZE, QUAD_SIZE);
  Model planeModel = LoadModelFromMesh(planeMesh);

  planeModel.materials[0].shader = shader;

  // SetTargetFPS(60);

  float timer = 0.f;

  // Main game loop
  while (!WindowShouldClose()) {

    timer += GetFrameTime(); // Update

    float time = GetTime();

    if (timer > 1.) {
      timer = 0.;

      UnloadShader(shader);

      shader = LoadShader("shaders/shader.vs", "shaders/shader.fs");

      planeModel.materials[0].shader = shader;

      timeLoc = GetShaderLocation(shader, "u_time");
    }

    SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

    UpdateCamera(&camera, CAMERA_FREE);

    // Draw
    BeginDrawing();
    
    DrawFPS(10, 10);

    ClearBackground((Color){10, 20, 30});

    // DrawTexture(grassTexture, 0., 0., WHITE);

    BeginMode3D(camera);

    // rlEnableWireMode();
    Vector3 orig = {0, 0, 0};
    DrawModel(planeModel, orig, 1.0f, WHITE);
    // DrawCube( orig, 200., 200., 100., RED);

    // rlDisableWireMode();
    EndMode3D();
    EndDrawing();
  }

  // Cleanup
  UnloadModel(planeModel);
  UnloadShader(shader);
  CloseWindow();

  return 0;
}

// Function to generate a grid of quads (plane mesh)
Mesh GeneratePlaneMesh(int gridSize, float quadSize) {
  int vertexCount = (gridSize + 1) * (gridSize + 1);
  int triangleCount = gridSize * gridSize * 2;

  float *vertices  = (float*)MemAlloc(vertexCount * 3 * sizeof(float)); // Positions (x, y, z)
  float *texcoords = (float*)MemAlloc(vertexCount * 2 * sizeof(float)); // Texture coordinates (u, v)
  unsigned short *indices = (unsigned short *)MemAlloc(triangleCount * 3 * sizeof(unsigned short)); // Indices

  // Generate vertex positions
  int vIdx = 0;
  for (int z = 0; z <= gridSize; z++) {
    for (int x = 0; x <= gridSize; x++) {
      vertices[vIdx++] = x * quadSize; // X position
      vertices[vIdx++] = 0.0f;         // Y position (flat plane)
      vertices[vIdx++] = z * quadSize; // Z position
    }
  }

  // Generate texture coordinates
  int tIdx = 0;
  for (int z = 0; z <= gridSize; z++) {
    for (int x = 0; x <= gridSize; x++) {
      texcoords[tIdx++] = (float)x / gridSize; // U coordinate
      texcoords[tIdx++] = (float)z / gridSize; // V coordinate
    }
  }

  // Generate indices for triangles
  int iIdx = 0;
  for (int z = 0; z < gridSize; z++) {
    for (int x = 0; x < gridSize; x++) {
      int topLeft = z * (gridSize + 1) + x;
      int topRight = topLeft + 1;
      int bottomLeft = topLeft + (gridSize + 1);
      int bottomRight = bottomLeft + 1;

      // First triangle
      indices[iIdx++] = topLeft;
      indices[iIdx++] = bottomLeft;
      indices[iIdx++] = topRight;

      // Second triangle
      indices[iIdx++] = topRight;
      indices[iIdx++] = bottomLeft;
      indices[iIdx++] = bottomRight;
    }
  }

  // Create the mesh
  Mesh mesh = {0};
  mesh.vertexCount = vertexCount;
  mesh.triangleCount = triangleCount;
  mesh.vertices = vertices;
  mesh.texcoords = texcoords;
  mesh.indices = indices;

  // Upload the mesh to the GPU
  UploadMesh(&mesh, false);

  return mesh;
}
