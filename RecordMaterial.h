//This class is used as another supporting class for sorting and graphing
class RecordMaterial
{
	private:
		string code;
		int num;
	
	public:
		RecordMaterial()
		{
		}
		RecordMaterial(string code, int num)
		{
			this->code = code;
			this->num = num;
		}
		
		string get_code()
		{
			return this->code;
		}
		
		int get_num()
		{
			return this->num;
		}
		~RecordMaterial()
		{
		}
		
};