#include <string>

using namespace std;

class Record
{
	private:
		string name;
		string country_code;
		int new_confirmed;
		int new_deaths;
		int new_recovered;
		int total_confirmed;
		int total_deaths;
		int total_recovered;
		
	public:
		Record(string name, string code, string n_confirmed, string n_deaths, string n_recovered, string t_confirmed, string t_deaths, string t_recovered)
		{
			this->name = name;
			this->country_code = code;
			this->new_confirmed = stoi(n_confirmed, nullptr);
			this->new_deaths = stoi(n_deaths, nullptr);
			this->new_recovered = stoi(n_recovered, nullptr);
			this->total_confirmed = stoi(t_confirmed, nullptr);
			this->total_deaths = stoi(t_deaths, nullptr);
			this->total_recovered = stoi(t_recovered, nullptr);
		}
		const string get_name()
		{
			return this->name;
		}
		const string get_code()
		{
			return this->country_code;
		}
		const int get_new_confirmed()
		{
			return this->new_confirmed;
		}
		const int get_new_deaths()
		{
			return this->new_deaths;
		}
		const int get_new_recovered()
		{
			return this->new_recovered;
		}
		const int get_total_confirmed()
		{
			return this->total_confirmed;
		}
		const int get_total_deaths()
		{
			return this->total_deaths;
		}
		const int get_total_recovered()
		{
			return this->total_recovered;
		}
		
		~Record()
		{

		}
};	
