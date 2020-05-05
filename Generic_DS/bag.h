template <typename T>
class bag{
	T arr[100];
	int count;
public:
	bag(){
	count=0;
	};
	void bag::insert(T x){
	//	if(count<10) return;
	arr[count++]=x;
	}
	~bag(){};
};