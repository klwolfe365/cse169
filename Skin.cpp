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

bool Skin::Load(const char* file, Skeleton* skel){
    filename = file;
    Skel = skel;
    Tokenizer t;
    t.Open(file);
    if(DEBUG)
        printf("Skeleton %s", Skel->GetFileName());

    while(1){
        char temp[256];
        t.GetToken(temp);
        //------ Load Vertex Positions ------
        if(strcmp(temp,"positions")==0){
            numVerts = t.GetInt();
            vertices = std::vector<Vertex *>(numVerts);
            updatedVertices = std::vector<Vertex *>(numVerts);
            t.FindToken("{");
            int n = 0;
            if(DEBUG)
                printf("positions %d\n", numVerts);
            while(n < numVerts){
                vertices[n] = new Vertex();
                vertices[n]->SetPosition(t.GetFloat(), t.GetFloat(), t.GetFloat());
                
                if(DEBUG){
                    Vector3 pos = vertices[n]->GetPosition();
                    printf("\t%f %f %f\n", pos.x, pos.y, pos.z);
                }
                
                updatedVertices[n] = new Vertex();
                updatedVertices[n]->SetPosition(vertices[n]->GetPosition());
                n++;
            }
        //------ Load Vertex Normals ------
        } else if(strcmp(temp, "normals")==0){
            t.GetInt();
            t.FindToken("{");
            int n = 0;
            if(DEBUG)
                printf("normals %d\n", numVerts);
            while(n < numVerts){
                vertices[n]->SetNormal(t.GetFloat(), t.GetFloat(), t.GetFloat());
                updatedVertices[n]->SetNormal(vertices[n]->GetNormal());
                if(DEBUG){
                    Vector3 norm = vertices[n]->GetNormal();
                    printf("\t%f %f %f\n", norm.x, norm.y, norm.z);
                }
                
                n++;
            }
        //------ Load Skin Weights ------
        } else if(strcmp(temp, "skinweights")==0){
            t.GetInt();
            t.FindToken("{");
            int n = 0;
            if(DEBUG)
                printf("skinweights %d\n", numVerts);
            while(n < numVerts){
                int numAttachments = t.GetInt();
                vertices[n]->numAttachments = numAttachments;
                updatedVertices[n]->numAttachments = numAttachments;
                if(DEBUG)
                    printf("\t%d ", numAttachments);
                int a = 0;
                while(a < numAttachments){
                    int jointNum = t.GetInt();
                    float weight = t.GetFloat();
                    vertices[n]->skinweights[a] = weight;
                    vertices[n]->joints[a] = jointNum;
                    updatedVertices[n]->skinweights[a] = weight;
                    updatedVertices[n]->joints[a] = jointNum;
                    a++;
                    
                    if(DEBUG)
                        printf("%d %f ", jointNum, weight);
                }
                if(DEBUG)
                    printf("\n");
                n++;
            }
        //------ Load Triangles ------
        } else if(strcmp(temp, "triangles")==0){
            numTriangles = t.GetInt();
            triangles = std::vector<Triangle *>(numTriangles);
            t.FindToken("{");
            int n = 0;
            if(DEBUG)
                printf("triangles %d\n", numTriangles);
            while(n < numTriangles){
                triangles[n] = new Triangle();
                triangles[n]->SetVertices(t.GetInt(), t.GetInt(), t.GetInt());
                
                if(DEBUG){
                    Triangle *t = triangles[n];
                    printf("\t%d %d %d\n", t->GetVertex1(), t->GetVertex2(), t->GetVertex3());
                }
                n++;
            }
        //------ Load Binding Matrices ------
        } else if(strcmp(temp, "bindings")==0){
            numJoints = t.GetInt();
            bindings = std::vector<Matrix34 *>(numJoints);
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
                bindings[n] = new Matrix34(ax, bx, cx, dx,
                         ay, by, cy, dy,
                         az, bz, cz, dz);
                if(DEBUG){
                    bindings[n]->Print();
                }
                n++;
            }
            InverseBindings();
            break;
        } else {
            t.SkipLine();
        }
    }
    t.Close();
}

void Skin::Update(){
    
    std::vector<Matrix34 *> skinningMatrices = std::vector<Matrix34 *>(numJoints);
    std::vector<Joint *> joints = Skel->GetJoints();
    for(Joint* j : joints){

        int jointNum = j->GetJointNumber();
        Matrix34 world = j->GetWorldMatrix();
        Matrix34 binv = *bindings[jointNum];
        skinningMatrices[jointNum] = new Matrix34();
        skinningMatrices[jointNum]->Dot(world, binv);
    }

    
    for(int c = 0; c < numVerts; c++){
        Vertex* v = vertices[c];
        Vector3 vTemp = Vector3();
        Vector3 nTemp = Vector3();
        Vector3 vFinal = Vector3();
        Vector3 nFinal = Vector3();
        
        for(int i = 0; i < v->numAttachments; i++){
            int jointNumber = v->joints[i];
            float weight = v->skinweights[i];
            
            skinningMatrices[jointNumber]->Transform(v->GetPosition(), vTemp);
            vFinal += weight*vTemp;
            
            skinningMatrices[jointNumber]->Transform(v->GetNormal(), nTemp);
            nFinal += weight*vTemp;
        }
        
        updatedVertices[c]->SetPosition(vFinal);
        nFinal.Normalize();
        updatedVertices[c]->SetNormal(nFinal);
    }
}

void Skin::Draw(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for(Triangle* t : triangles){
        glBegin(GL_TRIANGLES);
        Vertex* v = updatedVertices[t->GetVertex1()];
        glNormal3f(v->GetNormal().x, v->GetNormal().y, v->GetNormal().z);
        glVertex3f(v->GetPosition().x, v->GetPosition().y, v->GetPosition().z);
        
        v = updatedVertices[t->GetVertex2()];
        glNormal3f(v->GetNormal().x, v->GetNormal().y, v->GetNormal().z);
        glVertex3f(v->GetPosition().x, v->GetPosition().y, v->GetPosition().z);
        
        v = updatedVertices[t->GetVertex3()];
        glNormal3f(v->GetNormal().x, v->GetNormal().y, v->GetNormal().z);
        glVertex3f(v->GetPosition().x, v->GetPosition().y, v->GetPosition().z);
        glEnd();
    }
}

void Skin::InverseBindings(){
    std::vector<Joint *> joints = Skel->GetJoints();
    for(Matrix34* m : bindings){
        m->Inverse();
        m->Print();
    }
}