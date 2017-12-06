#ifndef RADIO_CONTROL_H
#define RADIO_CONTROL_H

class RadioControl{
private:
	// หัฬจ
	bool beSearch;
	bool beInScan;
public:
	RadioControl(){
		beSearch=false;
	}
	bool isInSearch();
	void setInSearch(bool b);
	bool isInScan();
	void setInScan(bool b);
};

extern RadioControl radionContrl;
void saveAllRadionChanged(bool force);

#endif