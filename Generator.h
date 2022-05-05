#include<string.h>
#include<vector>
#include<stdio.h>
#include<fstream>
#include"Record.h"
#include"RecordMaterial.h"

using namespace std;

class Generator
{
	private:
		vector<Record> container;
		//keywords are signals indicating the data
		const string KEYWORDS[8] = {"Country", "CountryCode", "NewConfirmed", "TotalConfirmed", "NewDeaths", "TotalDeaths", "NewRecovered", "TotalRecovered"};
		//space is the length of "\":\"", a signal for string related text
		const int S_SPACE = 3;
		const int N_SPACE = 2;	
		const string SIGNAL_1 = "\"";
		const string SIGNAL_2 = ",";

		//return a map for country with a certain data field (data field specific at user prompt) to make sorting easier
		vector<RecordMaterial> get_map_field(string field)
		{
			vector<RecordMaterial> graph_material;
			RecordMaterial rm;
			for(auto r:container)
			{
				
				string index = r.get_code();
				if (field=="nc")
				{
					rm = RecordMaterial(index, r.get_new_confirmed());
				}
				else if (field=="nd")
				{
					rm = RecordMaterial(index, r.get_new_deaths());
				}
				else if (field=="nr")
				{
					rm = RecordMaterial(index, r.get_new_recovered());
				}
				else if (field=="tc")
				{
					rm = RecordMaterial(index, r.get_total_confirmed());
				}
				else if (field=="td")
				{
					rm = RecordMaterial(index, r.get_total_deaths());
				}
				else 
				{
					rm = RecordMaterial(index, r.get_total_recovered());
				}
				graph_material.push_back(rm);
			
				
			}
			return graph_material;
		}

		//sort asecding; recquires map returned from get_map_filed(string field); later taken up in the graphing method
		vector<RecordMaterial> sort_asec(vector<RecordMaterial> material)
		{
			int size = material.size();
			int i, j;
			RecordMaterial comp;
			for(i = 1; i<size; i++)
			{
				comp = material[i];
				j = i-1;
				while(j>=0 && material[j].get_num()>comp.get_num())
				{
					material[j+1] = material[j];
					j = j-1;
				}
				material[j+1] = comp;
			}
			return material;
		}
		
		//sort descending, recquires map returned from get_map_field(string field); later taken up in the graphing method
		vector<RecordMaterial> sort_desc(vector<RecordMaterial> material)
		{
			int size = material.size();
			int i, j;
			RecordMaterial comp;
			for(i = 1; i<size; i++)
			{
				comp = material[i];
				j = i-1;
				while(j>=0 && material[j].get_num()<comp.get_num())
				{
					material[j+1] = material[j];
					j = j-1;
				}
				material[j+1] = comp;
			}
			return material;
		}
	
	public:
		//constructor
		Generator(string f_name)
		{
			string line;
			ifstream file;
			file.open(f_name);
			if(!file.is_open())
			{
				cout << "File does not exist!"<< endl;
				exit(0);
			}
			else{	
				int pos = 0;
				getline(file, line);
				//Data adding process; done when there is no more country record (record with field "Country") unread 
				
				while(line.find(KEYWORDS[0])!=string::npos)
				{
					string name, code, nc, tc, nd, td, nr, tr;
					/* The algorithm for spliting a line from the .json file:
					 * 1. find keyword[0]
					 * 2. erase all characters before the data
					 * 3. copy the data
					 * 4. find keyword[1] to keyword[7], repeat the above procedure for each keywords
					 */
			
				for(int i = 0; i<8; i++)
					{
						size_t find_pos = line.find(KEYWORDS[i]);
						if(i==0||i==1)
						{
							line.erase(0, find_pos+KEYWORDS[i].length()+S_SPACE);
							size_t end_pos = line.find(SIGNAL_1);
							if(i==0)
							{
								name = line.substr(0, end_pos);	
							}	
							else
							{
								code = line.substr(0, end_pos);
							}
						}
						else
						{
							line.erase(0, find_pos+KEYWORDS[i].length()+N_SPACE);
							size_t end_pos = line.find(SIGNAL_2);
							switch (i)
							{
								case 2:
									nc = line.substr(0, end_pos);
									break;
								case 3:
									tc = line.substr(0, end_pos);
									break;
								case 4:
									nd = line.substr(0, end_pos);
									break;
								case 5:
									td = line.substr(0, end_pos);
									break;
								case 6:
									nr = line.substr(0, end_pos);
									break;
								case 7:
									tr = line.substr(0, end_pos);
									break;
							}
						}
					}
					Record new_r = Record(name, code, nc, nd, nr, tc, td, tr);
					container.push_back(new_r);
				} 
			}
		}
		
		void graph(string field, string sortby)
		{
			ofstream graph("graph.txt");
			vector<RecordMaterial> g_countries= get_map_field(field);
			//The constant denominator to find out how many '#' we would use for graphing a bar;
			int denom = 1;
			if(sortby=="a")
			{
				g_countries = sort_asec(g_countries);
				if(g_countries[0].get_num()>10)
				{
					denom = 10;
				}
			}
			else
			{
				g_countries = sort_desc(g_countries);
				if(g_countries[9].get_num()>100000)
				{
					denom = 100000;
				}
				else if(g_countries[9].get_num()>10000)
				{
					denom = 10000;
				}
				else if(g_countries[9].get_num()>1000)
				{
					denom = 1000;
				}
				else if(g_countries[9].get_num()>100)
				{
					denom = 100;
				}
			}
			for(int i = 0; i<10; i++)
			{
				string bar(g_countries[i].get_num()/denom, '#');
				graph << g_countries[i].get_code()<<"||"<<bar<<endl;
			}
			string devider (g_countries[0].get_num()/denom+4, '-');
			
			//making titles and legend;
			string title;
			if (field=="nc")
			{
				title = "New Confirmed; ";
			}
			else if (field=="nd")
			{
				title = "New Deaths; ";
			}
			else if (field=="nr")
			{
				title = "New Recovered; ";
			}
			else if (field=="tc")
			{
				title = "Total Confirmed; ";
			}
			else if (field=="td")
			{
				title = "Total Deaths; ";
			}
			else 
			{
				title = "Total Recovered; ";
			}
			graph << devider << endl << title << "Each unit is approximately " << denom << endl;
			graph.close();
			
		}	
};
