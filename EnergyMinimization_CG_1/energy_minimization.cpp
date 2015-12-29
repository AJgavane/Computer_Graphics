#include"energy_minimization.hpp"

double min_length(double a, double b)
{
	return (a<b)?a:b;
}

/*Called to minimize energy. Stores output in output_pixels*/
void minimizeEnergy(std::vector<std::pair<int, int> > in_pixels, double **adjacency_matrix, std::vector<std::pair<int, int> > &output_pixels)
{
	/*Initialization the number of points in the graph.*/
	int n_nodes = in_pixels.size();

	/* Initialization of the matrices required in the Floyd Warshall all pair minimal paths algorithm*/
	std::vector<std::vector<std::vector<double> > > list_of_matrices(n_nodes + 1, std::vector<std::vector<double> >(n_nodes, std::vector<double>(n_nodes, 0.0)));

	/*Distances through the graph between two points.*/
	dblvec_t distances((n_nodes*(n_nodes-1))/2);
	/*Natural Lengths of the imaginary spring between any two points*/
	dblvec_t nat_len((n_nodes*(n_nodes-1))/2);
	/*Spring constants of the imaginary spring between any two points */
	dblvec_t spr_const((n_nodes*(n_nodes-1))/2);

	/*Delta_m values for each point.*/
	dblvec_t forces(n_nodes);

	/*del(E)/del(x) value for each point*/
	dblvec_t de_dx(n_nodes);

	/*del(E)/del(y) value for each point*/
	dblvec_t de_dy(n_nodes);

	/*del2(E)/del(x2) value for each point*/
	dblvec_t d2e_dx2(n_nodes);

	/*del2(E)/del(y2) value for each point*/
	dblvec_t d2e_dy2(n_nodes);

	/*del2(E)/del(x)del(y) value for each point*/
	dblvec_t d2e_dxdy(n_nodes);

	/*Change in x for each point*/
	dblvec_t delta_x(n_nodes);

	/*Change in y for each point*/
	dblvec_t delta_y(n_nodes);
	/*Following are temporary variables used at various stages in the code*/
	double diameter, max_d, a, b, c, d, e, energy;

	int i, j, k;
	std::vector<std::pair<double, double> > input_pixels(in_pixels.size());
	/*Initialization of the input pixels in real number space*/
	for(i=0; i<in_pixels.size(); i++)
	{
		input_pixels[i].first = (double)in_pixels[i].first;
		input_pixels[i].second = (double)in_pixels[i].second;
	}
	
	for(i=0; i<n_nodes; i++)
	{
		for(j=0;j<n_nodes; j++)
			if(adjacency_matrix[i][j]==1.0)
				adjacency_matrix[i][j] = sqrt(pow((input_pixels[i].first - input_pixels[j].first), 2) + pow((input_pixels[i].second - input_pixels[j].second), 2));
	}
	for( i=0; i<n_nodes; i++)
		for(int j=0; j<n_nodes; j++)
			list_of_matrices[0][i][j] = adjacency_matrix[i][j];
/* Following is the implementation of the Floyd-Warshall Algorithm for finding the minimum length paths between all
 * pair of points in a connected graph.*/
	for( k=1; k<=n_nodes; k++)
	{
		for(i=0; i<n_nodes; i++)
		{
			for(j=0; j<n_nodes; j++)
			{
				list_of_matrices[k][i][j] = min_length(list_of_matrices[k-1][i][j], list_of_matrices[k-1][i][k-1] + list_of_matrices[k-1][k-1][j]);
			}
		}
	}

	/*Initializing the distances b/w two points.*/
	for(i=1; i<n_nodes; i++)
		for(j=0; j<i; j++)
			distances[(i*(i-1))/2 +  j] = list_of_matrices[n_nodes][i][j];

	/* max_d stores the distance of the farthest two points in the graph*/
	max_d = max_dist(distances);
	/* diameter stores the maximum natural length possible for any spring. In effect, this limits the
	 * size of the graph by requiring that (length_of_spring)*(diameter)<=L0, where L0 is the size of
	 * square screen area.
	 * *****************HOWEVER****************
	 * As is explained in the documentation, this does not guarantee that the final graph
	 * shall completely fit in the screen area. This is because the algorithm converges to a local
	 * minimum of the energy, not global. */
	diameter = L0/max_d;
	for(i=0; i<distances.size(); i++)
	{
		nat_len[i] = diameter*distances[i];
		spr_const[i] = K0/distances[i];
	}
	/*Calculation of the initial energy of the system.*/
	energy=0;
	for(i=1; i<n_nodes; i++)
		for(j=0; j<i; j++)
			energy += 1/2.0*(spr_const[(i*(i-1))/2 +  j])*pow((distanceBetweenPoints(input_pixels[i], input_pixels[j]) - nat_len[(i*(i-1))/2 +  j]), 2);
			
	printf("initial energy is %lf\n", energy);


	/*Initialization of the different values used in the algorithm for all points.*/
	updateAll(input_pixels, nat_len, spr_const, de_dx, de_dy, forces, d2e_dx2, d2e_dy2, d2e_dxdy);

	while(maximumForce(forces, j))
	{
		do
		{
			a = d2e_dx2[j];
			b = d2e_dxdy[j];
			c = -de_dx[j];
			d = d2e_dy2[j];
			e = -de_dy[j];
			delta_x[j] = (d*c - b*e)/(a*d - b*b);
			delta_y[j] = (a*e - b*c)/(a*d - b*b);
			input_pixels[j].first+=delta_x[j];
			input_pixels[j].second+=delta_y[j];
			updateIndividual(input_pixels, nat_len, spr_const, de_dx, de_dy, forces, d2e_dx2, d2e_dy2, d2e_dxdy, j);
		}
		while(forces[j]>TOLERANCE);
		updateAll(input_pixels, nat_len, spr_const, de_dx, de_dy, forces, d2e_dx2, d2e_dy2, d2e_dxdy);

	}
	/*Final energy of the system.*/
	energy=0;
	for(i=1; i<n_nodes; i++ )
		for(j=0; j<i; j++)
		{
			energy += 1/2.0*(spr_const[(i*(i-1))/2 +  j])*pow((distanceBetweenPoints(input_pixels[i], input_pixels[j]) - nat_len[(i*(i-1))/2 +  j]), 2);
		}
	printf("Final energy is %lf\n", energy);

	/*Final value of the pixels are type-casted into integers*/
	for(i=0; i<input_pixels.size(); i++)
	{
		output_pixels[i].first=(int)input_pixels[i].first;
		output_pixels[i].second=(int)input_pixels[i].second;
	}

}

/*Following function takes the reference argument of forces array*/
bool maximumForce(dblvec_t &forces, int &j)
{
	double max = forces[0];
	int i;
	j=0;
	for(i=0; i<forces.size(); i++)
		if(forces[i]> max)
		{
			max = forces[i];
			j=i;
		}
	return (max>TOLERANCE);

}

void updateAll(std::vector<std::pair<double, double> > input_pixels, dblvec_t nat_len, dblvec_t spr_const,dblvec_t &de_dx,dblvec_t &de_dy,dblvec_t &forces,dblvec_t &d2e_dx2,dblvec_t &d2e_dy2,dblvec_t &d2e_dxdy)
{
	int i, j;
	int n_nodes = de_dx.size();
	double temp_var;

	for(j=0; j<n_nodes; j++)
	{
		temp_var=0;
		for(i=0; i<n_nodes; i++)
		{
			if(i > j)
			{
				temp_var += spr_const[(i*(i-1))/2 +  j]*(input_pixels[j].first - input_pixels[i].first)*(1.0 - nat_len[(i*(i-1)/2)  + j]/distanceBetweenPoints(input_pixels[i], input_pixels[j]));
			}
			else if(i==j)
			{
				continue;
			}
			else
			{
				temp_var += spr_const[(j*(j-1))/2 + i]*(input_pixels[j].first - input_pixels[i].first)*(1.0 - nat_len[(j*(j-1))/2 + i]/distanceBetweenPoints(input_pixels[i], input_pixels[j]));
			}

		}
		de_dx[j] = temp_var;

		temp_var=0;
		for(i=0; i<n_nodes; i++)
		{
			if(i>j)
			{
				temp_var+= spr_const[(i*(i-1))/2 +  j]*(input_pixels[j].second - input_pixels[i].second)*(1.0 - nat_len[(i*(i-1)/2) + j]/distanceBetweenPoints(input_pixels[i], input_pixels[j]));
			}
			else if(i==j)
			{
				continue;
			}
			else
			{
				temp_var+= spr_const[(j*(j-1))/2 + i]*(input_pixels[j].second - input_pixels[i].second)*(1.0 - nat_len[(j*(j-1)/2) + i]/distanceBetweenPoints(input_pixels[i], input_pixels[j]));
			}
		}
		de_dy[j] = temp_var;

		forces[j] = sqrt(pow(de_dx[j], 2.0) + pow(de_dy[j], 2.0));

		temp_var=0;
		for(i=0; i<n_nodes; i++)
		{
			if(i>j)
				temp_var+=spr_const[(i*(i-1))/2 +  j]*(1.0 - nat_len[(i*(i-1)/2)  + j]*(pow(input_pixels[j].second - input_pixels[i].second, 2.0) /pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0)));
			else if(i==j)
				continue;
			else
				temp_var+=spr_const[(j*(j-1))/2 + i]*(1.0 - nat_len[(j*(j-1)/2)  + i]*(pow(input_pixels[j].second - input_pixels[i].second, 2.0) /pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0)));
		}

		d2e_dx2[j] = temp_var;

		temp_var=0;
		for(i=0; i<n_nodes; i++)
		{
			if(i>j)
				temp_var+=spr_const[(i*(i-1))/2 +  j]*(1.0 - nat_len[(i*(i-1)/2) + j]*(pow(input_pixels[j].first - input_pixels[i].first, 2.0) /pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0)));
			else if(i==j)
				continue;
			else
				temp_var+=spr_const[(j*(j-1))/2 + i]*(1.0 - nat_len[(j*(j-1)/2) + i]*(pow(input_pixels[j].first - input_pixels[i].first, 2.0) /pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0)));
		}

		d2e_dy2[j] = temp_var;

		temp_var=0;
		for(i=0; i<n_nodes; i++)
		{
			if(i>j)
			{
				temp_var +=spr_const[(i*(i-1))/2 +  j]*nat_len[(i*(i-1))/2 +  j]*(input_pixels[j].first - input_pixels[i].first)*(input_pixels[j].second - input_pixels[i].second)/pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0);
			}
			else if(i==j)
			{
				continue;
			}
			else
			{
				temp_var +=spr_const[(j*(j-1))/2 + i]*nat_len[(j*(j-1))/2 + i]*(input_pixels[j].first - input_pixels[i].first)*(input_pixels[j].second - input_pixels[i].second)/pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0);
			}
		}
		d2e_dxdy[j] = temp_var;
	}
}

void updateIndividual(std::vector<std::pair<double, double> > input_pixels, dblvec_t nat_len, dblvec_t spr_const,dblvec_t &de_dx,dblvec_t &de_dy,dblvec_t &forces,dblvec_t &d2e_dx2,dblvec_t &d2e_dy2,dblvec_t &d2e_dxdy, int j)
{
	int i;
	int n_nodes = de_dx.size();
	double temp_var;

	temp_var=0;
	for(i=0; i<n_nodes; i++)
	{
		if(i > j)
		{
			temp_var += spr_const[(i*(i-1))/2 +  j]*(input_pixels[j].first - input_pixels[i].first)*(1.0 - nat_len[(i*(i-1)/2) + j]/distanceBetweenPoints(input_pixels[i], input_pixels[j]) );
		}
		else if(i==j)
		{
			continue;
		}
		else
		{
			temp_var += spr_const[(j*(j-1))/2 + i]*(input_pixels[j].first - input_pixels[i].first)*(1.0 - nat_len[(j*(j-1))/2 + i]/distanceBetweenPoints(input_pixels[i], input_pixels[j]));
		}

	}
	de_dx[j] = temp_var;

	temp_var=0;
	for(i=0; i<n_nodes; i++)
	{
		if(i>j)
		{
			temp_var+= spr_const[(i*(i-1))/2 +  j]*(input_pixels[j].second - input_pixels[i].second)*(1.0 - nat_len[(i*(i-1)/2) + j]/distanceBetweenPoints(input_pixels[i], input_pixels[j]));
		}
		else if(i==j)
		{
			continue;
		}
		else
		{
			temp_var+= spr_const[(j*(j-1))/2 + i]*(input_pixels[j].second - input_pixels[i].second)*(1.0 - nat_len[(j*(j-1))/2 + i]/distanceBetweenPoints(input_pixels[i], input_pixels[j]));
		}
	}
	de_dy[j] = temp_var;

	forces[j] = sqrt(pow(de_dx[j], 2.0) + pow(de_dy[j], 2.0));

	temp_var=0;
	for(i=0; i<n_nodes; i++)
	{
		if(i>j)
			temp_var+=spr_const[(i*(i-1))/2 +  j]*(1.0 - nat_len[(i*(i-1)/2) + j]*(pow(input_pixels[j].second - input_pixels[i].second, 2.0) /pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0)));
		else if(i==j)
			continue;
		else
			temp_var+=spr_const[(j*(j-1))/2 + i]*(1.0 - nat_len[(j*(j-1)/2) + i]*(pow(input_pixels[j].second - input_pixels[i].second, 2.0) /pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0)));
	}

	d2e_dx2[j] = temp_var;

	temp_var=0;
	for(i=0; i<n_nodes; i++)
	{
		if(i>j)
			temp_var+=spr_const[(i*(i-1))/2 +  j]*(1.0 - nat_len[(i*(i-1)/2)  + j]*(pow(input_pixels[j].first - input_pixels[i].first, 2.0) /pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0)));
		else if(i==j)
			continue;
		else
			temp_var+=spr_const[(j*(j-1))/2 + i]*(1.0 - nat_len[(j*(j-1)/2) + i]*(pow(input_pixels[j].first - input_pixels[i].first, 2.0) /pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0)));
	}

	d2e_dy2[j] = temp_var;

	temp_var=0;
	for(i=0; i<n_nodes; i++)
	{
		if(i>j)
		{
			temp_var +=spr_const[(i*(i-1))/2 +  j]*nat_len[(i*(i-1))/2 +  j]*(input_pixels[j].first - input_pixels[i].first)*(input_pixels[j].second - input_pixels[i].second)/pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0);
		}
		else if(i==j)
		{
			continue;
		}
		else
		{
			temp_var +=spr_const[(j*(j-1))/2 + i]*nat_len[(j*(j-1))/2 + i]*(input_pixels[j].first - input_pixels[i].first)*(input_pixels[j].second - input_pixels[i].second)/pow(distanceBetweenPoints(input_pixels[i], input_pixels[j]), 3.0);
		}
	}
	d2e_dxdy[j] = temp_var;
}

double distanceBetweenPoints(std::pair<double, double> a, std::pair<double, double> b)
{
	return sqrt(pow(a.first - b.first,2) + pow(a.second - b.second, 2));
}

double max_dist(dblvec_t distances)
{
	double max=distances[0];
	int i;
	for(i=1; i<distances.size(); i++)
		if(distances[i]>max)
			max = distances[i];

	return max;
}

