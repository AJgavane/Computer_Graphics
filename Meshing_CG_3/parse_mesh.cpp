#include "parse_mesh.hpp"
void Polygon:: drawSelf(std::vector<vector3d_t> v_list)
{
        if(number_of_vertices < 3)
        {
                printf("Too less vertices\n");
                return;
        }
        glBegin(GL_POLYGON);
                for(int i=0; i<number_of_vertices; i++)
                {
                        glColor3f(0.4, 0.0, 0.4);
                        if(i==0)
                            glColor3f(0.2, 0.0, 0.2);    
                        glVertex3f(first(v_list[vertices[i]]), second(v_list[vertices[i]]), third(v_list[vertices[i]]));
                }
        glEnd();                        
        
}
        
void Polygon:: readVertices(FILE *fp)
{
        fscanf(fp, "%d", &number_of_vertices);
        vertices.resize(number_of_vertices);
        for(int i=0; i<number_of_vertices; i++)
        {
                fscanf(fp, "%d", &vertices[i]);
        }
        
}



void parseMesh(std::vector<Polygon> &p_list, std::vector<vector3d_t> &v_list)
{

   int n_vertices, n_faces, n_edges;
   double mx, my, mz;
   char *filename = (char*)malloc(100*sizeof(char)), *format_check = (char*)malloc(10*sizeof(char));
   FILE *off_file;
   printf("Enter the filename\n");
   scanf("%s", filename);
   if((off_file = fopen(filename, "r")) == NULL)
   {
        printf("No such file\n");
        exit(0);
   
   }
   fscanf(off_file, "%s", format_check);
   if(strcmp(format_check, "OFF")!=0)
   {
        printf("Invalid format\n");
        exit(0);
   }
   fscanf(off_file, "%d %d %d", &n_vertices, &n_faces, &n_edges);
   v_list.resize(n_vertices); p_list.resize(n_faces);
   
   for(int i=0; i<n_vertices; i++)
   {
        fscanf(off_file, "%lf %lf %lf", &mx, &my, &mz);
        first(v_list[i]) = mx;
        second(v_list[i]) = my;
        third(v_list[i]) = mz;
   }
   
   for(int i=0; i<n_faces; i++)
   {
        p_list[i].readVertices(off_file);
   
   }  
        
}
