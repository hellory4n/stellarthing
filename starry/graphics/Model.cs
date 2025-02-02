using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;

namespace starry;

/// <summary>
/// model :)
/// </summary>
public class Model : IAsset {
    public Mesh[] meshes { get; set; } = [];

    public void load(string path)
    {
        List<vec3> tmpverts = [];
        List<vec2> tmpuvs = [];
        List<vec3> tmpnormals = [];
        List<uint> indices = [];
        List<Vertex> vertices = [];
        List<Mesh> meshe = [];
        Dictionary<string, uint> vertexHash = new();
        Dictionary<string, Material> materials = new();
        Material? currentmat = null;

        // man.
        void pushIndex(string vkey)
        {
            if (vertexHash.TryGetValue(vkey, out uint found)) {
                indices.Add(found);
            }
            else {
                string[] parts = vkey.Split('/');
                int vIndex = int.Parse(parts[0]) - 1;
                int vtIndex = parts.Length > 1 && parts[1] != "" ? int.Parse(parts[1]) - 1 : -1;
                int vnIndex = parts.Length > 2 ? int.Parse(parts[2]) - 1 : -1;

                Vertex vertex = new() {
                    x = (float)tmpverts[vIndex].x,
                    y = (float)tmpverts[vIndex].y,
                    z = (float)tmpverts[vIndex].z,
                    u = (float)(vtIndex >= 0 ? tmpuvs[vtIndex].x : 0.0f),
                    v = (float)(vtIndex >= 0 ? tmpuvs[vtIndex].y : 0.0f),
                    nx = (float)(vnIndex >= 0 ? tmpnormals[vnIndex].x : 0.0f),
                    ny = (float)(vnIndex >= 0 ? tmpnormals[vnIndex].y : 0.0f),
                    nz = (float)(vnIndex >= 0 ? tmpnormals[vnIndex].z : 0.0f)
                };
                

                int index = vertices.Count;
                vertices.Add(vertex);
                vertexHash[vkey] = (uint)index;
                indices.Add((uint)index);
            }
        }

        void importMtl(string path)
        {
            string[] mtl = File.ReadAllLines(path);
            foreach (string line in mtl) {
                string linha = line.Trim();
                if (linha == "") continue;
                if (linha.StartsWith('#')) continue;

                string[] args = linha.Split(' ');

                switch (args[0]) {
                    case "newmtl":
                        if (currentmat != null) {
                            materials[currentmat.name] = currentmat;
                        }
                        currentmat = new() {
                            name = linha.Substring(7).Trim(),
                        };
                        break;
                    
                    case "map_Kd":
                        if (currentmat != null) {
                            currentmat.texturePath = Path.Combine(Starry.settings.assetPath,
                                linha.Substring(7).Trim());
                        }
                        break;
                    
                    case "Kd":
                        if (currentmat != null) {
                            double kdx = double.Parse(args[1], CultureInfo.InvariantCulture);
                            double kdy = double.Parse(args[2], CultureInfo.InvariantCulture);
                            double kdz = double.Parse(args[3], CultureInfo.InvariantCulture);
                            currentmat.diffuse = (kdx, kdy, kdz);
                        }
                        break;
                    
                    case "Ks":
                        if (currentmat != null) {
                            double ksx = double.Parse(args[1], CultureInfo.InvariantCulture);
                            double ksy = double.Parse(args[2], CultureInfo.InvariantCulture);
                            double ksz = double.Parse(args[3], CultureInfo.InvariantCulture);
                            currentmat.specular = (ksx, ksy, ksz);
                        }
                        break;
                }
            }

            if (currentmat != null) {
                materials[currentmat.name] = currentmat;
            }
        }

        string[] obj = File.ReadAllLines(path);
        foreach (string line in obj) {
            string linha = line.Trim();
            if (linha == "") continue;
            if (linha.StartsWith('#')) continue;

            string[] args = linha.Split(' ');

            switch (args[0]) {
                // vertex
                case "v":
                    double vx = double.Parse(args[1], CultureInfo.InvariantCulture);
                    double vy = double.Parse(args[2], CultureInfo.InvariantCulture);
                    double vz = double.Parse(args[3], CultureInfo.InvariantCulture);
                    tmpverts.Add((vx, vy, vz));
                    break;
                
                // texcoords
                case "vt":
                    double vtx = double.Parse(args[1], CultureInfo.InvariantCulture);
                    double vty = double.Parse(args[2], CultureInfo.InvariantCulture);
                    tmpuvs.Add((vtx, vty));
                    break;
                
                // face
                case "f":
                    pushIndex(args[1]);
                    pushIndex(args[2]);
                    pushIndex(args[3]);
                    break;
                
                // the notorious material
                case "mtllib":
                    importMtl(path.Replace(".obj", ".mtl"));
                    break;
                
                case "usemtl":
                    // man.
                    Mesh meshma = new() {
                        vertices = vertices.ToArray(),
                        indices = indices.ToArray(),
                    };
                    string mtlname = linha.Substring(7).Trim();
                    if (materials.TryGetValue(mtlname, out Material? mat)) {
                        meshma.material = mat;
                    }
                    meshe.Add(meshma);
                    vertices.Clear();
                    indices.Clear();
                    break;
            }
        }

        meshes = meshe.ToArray();
        Starry.log($"Model {path} loaded");
    }

    public void cleanup() {}
}