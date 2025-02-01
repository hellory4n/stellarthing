using System;
using System.Numerics;

namespace starry;

/// <summary>
/// as the name implies, it's a 3d object
/// </summary>
public class Object3D {
    /// <summary>
    /// position :)
    /// </summary>
    public vec3 position { get; set; } = (0, 0, 0);
    /// <summary>
    /// not to be confused with hit videogame digital distribution service Origin™ by Electronic Arts
    /// </summary>
    public vec3 origin { get; set; } = (0, 0, 0);
    /// <summary>
    /// it's a multiplier to the crap size
    /// </summary>
    public vec3 scale { get; set; } = (1, 1, 1);
    /// <summary>
    /// rotation in quaternions. there's an euler version too because we're not unity
    /// </summary>
    public Quaternion rotationQuat { get; set; } = Quaternion.Identity;
    /// <summary>
    /// rotation in euler angles in angles not radians
    /// </summary>
    public vec3 rotationEuler {
        get {
            vec3 euler = (0, 0, 0);

            // ROLL
            double sinrCosp = 2 * (rotationQuat.W * rotationQuat.X + rotationQuat.Y * rotationQuat.Z);
            double cosrCosp = 1 - 2 * (rotationQuat.X * rotationQuat.X + rotationQuat.Y * rotationQuat.Y);
            euler.x = Math.Atan2(sinrCosp, cosrCosp);

            // PITCH
            double sinp = 2 * (rotationQuat.W * rotationQuat.Y - rotationQuat.Z *  rotationQuat.X);
            if (Math.Abs(sinp) >= 1) euler.y = Math.CopySign(Math.PI / 2, sinp);
            else euler.y = Math.Asin(sinp);

            // YAW
            double sinyCosp = 2 * (rotationQuat.W * rotationQuat.Z + rotationQuat.X * rotationQuat.Y);
            double cosyCosp = 1 - 2 * (rotationQuat.Y * rotationQuat.Y + rotationQuat.Z * rotationQuat.Z);
            euler.z = Math.Atan2(sinyCosp, cosyCosp);

            // The radian, denoted by the symbol rad, is the unit of angle in the International System of Units (SI) and is the standard unit of angular measure used in many areas of mathematics. It is defined such that one radian is the angle subtended at the centre of a circle by an arc that is equal in length to the radius.[2] The unit was formerly an SI supplementary unit and is currently a dimensionless SI derived unit,[2] defined in the SI as 1 rad = 1[3] and expressed in terms of the SI base unit metre (m) as rad = m/m.[4] Angles without explicitly specified units are generally assumed to be measured in radians, especially in mathematical writing.[5]
            return (
                StMath.rad2deg(euler.x),
                StMath.rad2deg(euler.y),
                StMath.rad2deg(euler.z)
            );
        }
        set {
            double roll = StMath.deg2rad(value.x);
            double pitch = StMath.deg2rad(value.y);
            double yaw = StMath.deg2rad(value.z);

            Quaternion q = new();
            double cy = Math.Cos(yaw * 0.5);
            double sy = Math.Sin(yaw * 0.5);
            double cp = Math.Cos(pitch * 0.5);
            double sp = Math.Sin(pitch * 0.5);
            double cr = Math.Cos(roll * 0.5);
            double sr = Math.Sin(roll * 0.5);

            q.W = (float)(cr * cp * cy + sr * sp * sy);
            q.X = (float)(sr * cp * cy - cr * sp * sy);
            q.Y = (float)(cr * sp * cy + sr * cp * sy);
            q.Z = (float)(cr * cp * sy - sr * sp * cy);
            rotationQuat = q;
        }
    }

    /// <summary>
    /// mesesessheseseshzsesehs
    /// </summary>
    public Mesh[] meshes { get; set; } = [];
    /// <summary>
    /// whats this
    /// </summary>
    public vec3 colorMask { get; set; } = (0, 0, 0);
    /// <summary>
    /// useful for when you want to simulate the demon core
    /// </summary>
    public bool glowing { get; set; } = false;
    /// <summary>
    /// what color does it glow. only works if glowing is enabled (duh)
    /// </summary>
    public color glowColor { get; set; } = color.white;
    /// <summary>
    /// oh
    /// </summary>
    public bool receiveShadows { get; set; } = false;
    public aabb box { get; set; } = new();
    public uint shader { get; set; } = 0;

    /// <summary>
    /// makes a matrix thing shitfuck crapfrick
    /// </summary>
    public Matrix4x4 getTransform()
    {
        // TODO: this might bust bcuz im stupid and all this math hurts
        Matrix4x4 m = Matrix4x4.Identity;

        // scale
        m *= Matrix4x4.CreateScale(new Vector3((float)scale.x, (float)scale.y, (float)scale.z));

        // trnasltae
        m *= Matrix4x4.CreateTranslation(new Vector3((float)position.x, (float)position.y, (float)position.z));

        // la rotación
        var matrot = Matrix4x4.CreateFromQuaternion(rotationQuat);

        // centre mate
        var t1 = Matrix4x4.CreateTranslation((float)origin.x, (float)origin.y, (float)origin.z);
        m *= t1;
        m *= matrot;
        var t2 = Matrix4x4.CreateTranslation(0, (float)-origin.y, (float)-origin.z);
        m *= t2;

        return m;
    }

    /// <summary>
    /// gets the center of the mesh model whatever
    /// </summary>
    public vec3 getCenter()
    {
        if (meshes.Length == 0) return (0, 0, 0);

        Mesh firstMesh = meshes[0];
        double minx = firstMesh.vertices[0].x;
        double maxx = firstMesh.vertices[0].x;
        double miny = firstMesh.vertices[0].y;
        double maxy = firstMesh.vertices[0].y;
        double minz = firstMesh.vertices[0].z;
        double maxz = firstMesh.vertices[0].z;
        
        // akson dendryt
        for (int i = 0; i < meshes.Length; i++) {
            Mesh mesh = meshes[i];
            for (int j = 0; j < mesh.vertices.Length; j++) {
                Vertex v = mesh.vertices[j];
                if (v.x < minx) minx = v.x;
                if (v.x > maxx) maxx = v.x;
                if (v.y < miny) miny = v.y;
                if (v.y > maxy) maxy = v.y;
                if (v.z < minz) minz = v.z;
                if (v.z > maxz) maxz = v.z;
            }
        }

        return (
            (minx + maxx) / 2,
            (miny + maxy) / 2,
            (minz + maxz) / 2
        );
    }

    /// <summary>
    /// axon dendrite
    /// </summary>
    public vec3 vec3ToObjectSpace(vec3 v)
    {
        Vector4 u = new((float)v.x, (float)v.y, (float)v.z, 1.0f);
        Matrix4x4 m = getTransform();
        Vector4 r = Vector4.Transform(u, m);
        return (r.X, r.Y, r.Z);
    }

    /// <summary>
    /// akson dendryt
    /// </summary>
    public aabb aabbToObjectSpace(aabb box)
    {
        aabb res = box;
        res.minx += position.x * scale.x;
        res.maxx += position.x * scale.x;
        res.miny += position.y * scale.y;
        res.maxy += position.y * scale.y;
        res.minz += position.z * scale.z;
        res.maxz += position.z * scale.z;
        return res;
    }

    public void create()
    {
        // man.
        Graphics.initObject(this);
    }
    public void cleanup() => Graphics.freeObject(this);
}