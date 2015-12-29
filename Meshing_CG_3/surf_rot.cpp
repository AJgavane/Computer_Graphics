#include"surf_rot.h"
void surfaceRotation(std::vector<std::pair<int, int>> pixel_2d,  char axis)
{
        std::vector<vector3d_array_t> surface_points;
        double theta = 10.0, dtheta = 10.0, st, ct, dt = 1.0/SAMPLE_SIZE;
        int sample_size =SAMPLE_SIZE+1 , i, degree=pixel_2d.size(), bezier_parameter=0;
        int rotation_count = 0;
        FILE *fp ;
        std::vector<vector3d_array_t> control_points_3d(ROT_POINTS, vector3d_array_t(degree, vector3d_t(0.0, 0.0, 0.0)) );
        std::vector<std::tuple<int, int, int>> polygons(ROT_POINTS*(sample_size-1)*2);
        surface_points.resize(ROT_POINTS);

        
        for(i=0; i<ROT_POINTS; i++)
        {
                surface_points[i].resize(sample_size);
        }
        
        if(axis=='x' || axis == 'X')
        {
                while(rotation_count<ROT_POINTS)
                {
                   ct = Cos(theta); st  = Sin(theta);
                   for(i=0; i<degree; i++)
                   {
                        first(control_points_3d[rotation_count][i])=(double)pixel_2d[i].first;
                        second(control_points_3d[rotation_count][i])=ct*(double)pixel_2d[i].second;
                        third(control_points_3d[rotation_count][i])=st*(double)pixel_2d[i].second;  
                   }                   
                   theta+=dtheta;
                   rotation_count++;    
                }                
                fp = fopen("surf_rot_x.off", "w");
        }        
        else
        {
                while(rotation_count<ROT_POINTS)
                {
                   ct = Cos(theta); st  = Sin(theta);
                   for(i=0; i<degree; i++)
                   {
                        first(control_points_3d[rotation_count][i])=ct*(double)pixel_2d[i].first;
                        second(control_points_3d[rotation_count][i])=(double)pixel_2d[i].second;
                        third(control_points_3d[rotation_count][i])=st*(double)pixel_2d[i].first;  
                   }                   
                   theta+=dtheta;
                   rotation_count++;              
                }               
                fp = fopen("surf_rot_y.off", "w");      
        }
        
        
        for(rotation_count=0; rotation_count<ROT_POINTS; rotation_count++)
        {
                bezier_parameter=0;
                for(i=0; i<sample_size; i++)
                {
                        surface_points[rotation_count][i] = Lerp3d(control_points_3d[rotation_count], i*dt);
                        bezier_parameter+=dt;
                }
                
        }
        printf("Got  %d control points, sampling %d points and rotated points about the %c axis\n", degree, sample_size, axis);        
        for(rotation_count=0; rotation_count<ROT_POINTS; rotation_count++)
        {
                for(i=0; i<sample_size-1; i++) //Exclude the endpoint of the bezier curve. 
                {
                        first(polygons[2*(rotation_count*(sample_size-1) + i)]) = rotation_count*sample_size + i; 
                        second(polygons[2*(rotation_count*(sample_size-1) + i)]) = ((rotation_count+1)%ROT_POINTS)*sample_size + i+1;
                        third(polygons[2*(rotation_count*(sample_size-1) + i)]) = ((rotation_count+1)%ROT_POINTS)*sample_size + i;
                        
                        first(polygons[2*(rotation_count*(sample_size-1) + i) + 1]) = rotation_count*sample_size + i;
                        second(polygons[2*(rotation_count*(sample_size-1) + i) + 1]) = rotation_count*sample_size + i+1;
                        third(polygons[2*(rotation_count*(sample_size-1) + i) + 1]) = ((rotation_count+1)%ROT_POINTS)*sample_size+i+1;            
                }
        }
        fprintf(fp, "OFF\n");
        fprintf(fp, "%d %d %d\n", ROT_POINTS*sample_size, ROT_POINTS*(sample_size-1)*2, 0);
        for(rotation_count=0; rotation_count<ROT_POINTS; rotation_count++)
        {
                for(i=0; i<sample_size; i++)
                {
                        fprintf(fp, "%f %f %f\n", first(surface_points[rotation_count][i]), second(surface_points[rotation_count][i]), third(surface_points[rotation_count][i]));
                        
                }
        }
        for(i=0; i<polygons.size(); i++)
        {
                fprintf(fp, "3 %d %d %d\n", first(polygons[i]), second(polygons[i]), third(polygons[i]));
        }
        fclose(fp);
}        

vector3d_t Lerp3d(vector3d_array_t a, double t)
{
        vector3d_array_t b(a.size()-1);
        if(a.size()==2)
        {
                first(b[0]) = first(a[0])*t + first(a[1])*(1-t);
                second(b[0]) = second(a[0])*t + second(a[1])*(1-t);
                third(b[0]) = third(a[0])*t + third(a[1])*(1-t);
                return b[0];
        }
        int i;
        for(i=0; i<b.size(); i++)
        {
                first(b[i]) = first(a[i])*t + first(a[i+1])*(1-t);
                second(b[i]) = second(a[i])*t + second(a[i+1])*(1-t);
                third(b[i]) = third(a[i])*t + third(a[i+1])*(1-t);                 
        }
        return Lerp3d(b, t);       
}
