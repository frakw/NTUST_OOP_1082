#ifndef _Big_Number_H_
#define _Big_Number_H_
#include <string>
#include <vector>
#include <iostream>
/*
規範:
1.integer與decimal內只有數字組成的字串
2.sign是正負號，true為正，0可為正或負(不影響計算)
3.若有小數造成無法計算，會傳入erro_message，結果會以整數計算，print會有錯誤訊息，可在標頭檔前加入#define big_number_no_error_message 來關閉警告，若要印出內容，則再加入#define big_number_error_keep_going
*/
class big_number {
public:
	big_number(std::string);//constructor，內部是由底下的input完成的
	big_number();//甚麼都不做
	void print(void) {//inline funtion 印出big_number
#ifndef big_number_no_error_message
		if (error_message.length() > 0) {//有錯誤資訊
			std::cout << error_message;
			error_message.clear();//印出一次後消除錯誤訊息
			error_message = "";
	#ifndef big_number_error_keep_going			
			return;//error後終止
	#else
			std::cout << " 以下是去除不可計算部分的結果:" << std::endl;
	#endif
		}
#endif
		if (integer.length() == 0) {//整數為空字串時，預設為0
			std::cout << 0;
		}
		else {
			if (!sign && (integer.length()!=1 || integer[0]!='0')) {//消除 -0 bug
				std::cout << "-";
			}
			std::cout << integer;
		}
		if (decimal.length())//如果小數長度為零，不輸出小數點
			std::cout << '.' << decimal;
	}
	void print(int);//強制輸出小數點後 int 位，不夠補0
	void input(std::string);//輸入一個string 存入big_number，格式:"-12345"，前面的正負號可以添加多個，空格自動省略
	void input_llint(long long int);//輸入long long int存入big_number
	void input_ullint(long long int);//輸入unsigned long long int存入big_number
	void input_ldouble(long double);//輸入double存入big_number
	long long int to_llint();//回傳int值，溢位不處理
	unsigned long long int to_ullint();//回傳int值，溢位不處理
	long double to_ldouble();//回傳double值
	void set(bool, std::string, std::string);//設定sign,integer,decimal，開發方便用
	void create_fraction();//創建分數，存入numerator與denominator
	std::vector<big_number> prime_factorization(bool);//回傳質因數分解的陣列，true從小到大 反之
	bool is_prime();//檢查是否為質數，是為true
	void clear_zero();//清除整數最前面的0 與小數點最後的0，常用
	void clear(void);//清除所有string sign設為true
	bool sign = true; // 1->正數與0 -1->負數
	char pre_operator = '+';//用於儲存前方的operator，暫時先不實做
	std::string integer = "";//整數部分
	std::string decimal = "";//小數部分
	std::string error_message = "";//錯誤資訊，若存在則不列印數字
	std::string numerator = "";//分子，做完除法會使用到這條資訊，ex: 1.0/3.0 * 3 = 1 而非 0.9999...
	std::string denominator = "";//分母，做完除法會使用到這條資訊
};

big_number big_number_formula(std::string);//傳入數學式，處理輸入，運算分流至各funtion，若有換行結束輸入計算，其餘字元與空白會被忽略
big_number big_number_add(big_number,big_number);//處理正負號相同的運算，不同分流至減法
big_number big_number_minus(big_number, big_number);//處理正負號不同的運算，相同分流至加法
big_number big_number_multiply(big_number, big_number);//乘法
big_number big_number_divide(big_number, big_number,int);//除法，int 為小數點後最大位數，會有最簡分數存入numerator與denominator
big_number big_number_remainder(big_number, big_number);//取餘數，只適用於整數，有小數會被忽視，並錯輸入錯誤訊息
big_number big_number_factorial(big_number);//階乘，有小數會傳入error message
big_number big_number_power(big_number, big_number);//次方，若有小數，會call方根
big_number big_number_root(big_number,big_number);//方根
big_number big_number_gcd(big_number, big_number);//最大公因數
big_number big_number_lcm(big_number, big_number);//最小公倍數
big_number big_number_pi(int);//回傳π到小數點後 int 位
big_number big_number_euler(int);//回傳自然指數到小數點後 int 位
big_number big_number_sin(big_number,int);//回傳sin值到小數點後 int 位
big_number big_number_cos(big_number, int);//回傳cos值到小數點後 int 位
big_number big_number_tan(big_number, int);//回傳tan值到小數點後 int 位，若不存在傳入error message
int big_number_compare(big_number, big_number);//大數比較器 a>b ->1   a==b ->0    a<b ->-1
int big_number_compare(std::string,std::string);//大數比較器(字串版) a>b ->1   a==b ->0    a<b ->-1
bool clear_unknown(std::string*);
#endif
