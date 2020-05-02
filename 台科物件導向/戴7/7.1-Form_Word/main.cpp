//FormWord-inputmain1.cpp
#include"Form.h"
//題目說明:讀入txt檔，判斷每行的的字串各個字母數有沒有任何一個超過input字串各個子母數的數量，如果沒則印出，反之不印出
int main()
{
	Form form1;
	form1.SetInputWord("SWIMMING");//設定Input
	form1.ProcessInputWord();//處理Input資訊
	form1.SetFileName("words.txt");//設定檔案名稱
	form1.Load_CompareWord();//讀檔並且比較
	form1.PrintFoundWords();//印出符合的字
	return 0;
}