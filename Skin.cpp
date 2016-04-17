//
//  Skin.cpp
//  cse169
//
//  Created by Karen Wolfe on 4/16/16.
//
//

#include "Skin.h"

Skin::Skin(){}
Skin::~Skin(){}

bool Skin::Load(const char* file){
    filename = file;
    Tokenizer t;
    t.Open(file);

    while(1){
        char temp[256];
        t.GetToken(temp);
        if(strcmp(temp,"positions")==0){
            numVerts = t.GetInt();
            vertices = new Vertex[numVerts];
            t.FindToken("{");
            int n = 0;
            if(DEBUG)
                printf("positions %d\n", numVerts);
            while(n < numVerts){
                vertices[n] = Vertex();
                vertices[n].SetPosition(Vector3(t.GetFloat(), t.GetFloat(), t.GetFloat()));
                n++;
                
                if(DEBUG){
                    Vector3 pos = vertices[n].GetPosition();
                    printf("\t%f %f %f\n", pos.x, pos.y, pos.z);
                }
            }
        } else if(strcmp(temp, "normals")==0){
            t.GetInt();
            t.FindToken("{");
            int n = 0;
            if(DEBUG)
                printf("normals %d\n", numVerts);
            while(n < numVerts){
                vertices[n].SetNormal(Vector3(t.GetFloat(), t.GetFloat(), t.GetFloat()));
                n++;
                
                if(DEBUG){
                    Vector3 norm = vertices[n].GetNormal();
                    printf("\t%f %f %f\n", norm.x, norm.y, norm.z);
                }
            }
        }else if(strcmp(temp, "skinweights")==0){
            t.GetInt();
            t.FindToken("{");
            int n = 0;
            if(DEBUG)
                printf("skinweights %d\n", numVerts);
            while(n < numVerts){
                int numAttachments = t.GetInt();
                if(DEBUG)
                    printf("\t%d ", numAttachments);
                int a = 0;
                while(a < numAttachments){
                    int jointNum = t.GetInt();
                    //TODO Joint j = Skeleton.Joints(t.getInt());
                    float weight = t.GetFloat();
                    a++;
                    
                    
                    if(DEBUG)
                        printf("%d %f ", jointNum, weight);
                }
                if(DEBUG)
                    printf("\n");
                n++;
            }
        } else if(strcmp(temp, "triangles")==0){
            numTriangles = t.GetInt();
            triangles = new Triangle[numTriangles];
            t.FindToken("{");
            int n = 0;
            if(DEBUG)
                printf("triangles %d\n", numTriangles);
            while(n < numTriangles){
                triangles[n] = Triangle();
                triangles[n].SetVertices(t.GetInt(), t.GetInt(), t.GetInt());
                
                if(DEBUG){
                    Triangle t = triangles[n];
                    printf("\t%d %d %d\n", t.GetVertex1(), t.GetVertex2(), t.GetVertex3());
                }
                
//                Vertex v1 = vertices[t.GetInt()];
//                Vertex v2 = vertices[t.GetInt()];
//                Vertex v3 = vertices[t.GetInt()];
//                triangle.SetVertices(v1, v2, v3);
                n++;
            }
        } else if(strcmp(temp, "bindings")==0){
            numJoints = t.GetInt();
            bindings = new Matrix34[numJoints];
            int n = 0;
            t.FindToken("{");
            if(DEBUG)
                printf("bindings %d\n", numJoints);
            while(n < numJoints){
                t.FindToken("matrix {");
                float ax = t.GetFloat();
                float ay = t.GetFloat();
                float az = t.GetFloat();
                float bx = t.GetFloat();
                float by = t.GetFloat();
                float bz = t.GetFloat();
                float cx = t.GetFloat();
                float cy = t.GetFloat();
                float cz = t.GetFloat();
                float dx = t.GetFloat();
                float dy = t.GetFloat();
                float dz = t.GetFloat();
                bindings[n] = Matrix34(ax, bx, cx, dx,
                         ay, by, cy, dy,
                         az, bz, cz, dz);
                if(DEBUG){
                            printf("\tmatrix {\n");
                            printf("\t\t%f %f %f\n", ax, ay, az);
                            printf("\t\t%f %f %f\n", bx, by, bz);
                            printf("\t\t%f %f %f\n", cx, cy, cz);
                            printf("\t\t%f %f %f\n", dx, dy, dz);
                            printf("\t}\n");
                }
                n++;
            }
        } else t.SkipLine();
    }
}

void Skin::PrintSkin(){
//    printf("positions %d {\n", numVerts);
//    for(int n = 0; n < numVerts; n++){
//        Vector3 pos = vertices[n].GetPosition();
//        printf("/t%f %f %f\n", pos.x, pos.y, pos.z);
//    }
//    printf("}\n");
//    
//    printf("normals %d {\n", numVerts);
//    for(int n = 0; n < numVerts; n++){
//        Vector3 norm = vertices[n].GetNormal();
//        printf("/t%f %f %f\n", norm.x, norm.y, norm.z);
//    }
//    printf("}\n");
//    
//    printf("skinweights %d {\n", numVerts);
//    for(int n = 0; n < numVerts; n++){
////        Vector3 norm = vertices[n].GetNormal();
////        printf("/t%f %f %f", norm.x, norm.y, norm.z);
//    }
//    printf("}\n");
//    
//    printf("triangles %d {\n", numTriangles);
//    for(int n = 0; n < numTriangles; n++){
//        Triangle t = triangles[n];
//        printf("/t%d %d %d\n", t.GetVertex1(), t.GetVertex2(), t.GetVertex3());
//    }
//    
//    printf("}\n");
//    
//    printf("bindings %d {\n", numJoints);
//    for(int n = 0; n < numJoints; n++){
//        Matrix34 m = bindings[n];
//        printf("\tmatrix {\n");
//        printf("/t%f %f %f\n", m.a.x, m.a.y, m.a.z);
//        printf("/t%f %f %f\n", m.b.x, m.b.y, m.b.z);
//        printf("/t%f %f %f\n", m.c.x, m.c.y, m.c.z);
//        printf("/t%f %f %f\n", m.d.x, m.d.y, m.d.z);
//        printf("\t}");
//    }
//    printf("}");
    
}
