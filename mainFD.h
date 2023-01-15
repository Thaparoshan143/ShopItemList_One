//function decleration
Item* AddItem(Item* r);
void InputItemInfo(Object* o);
void PrintItemInfo(Object* o);
void InfoHelperChar(char* t, char* c);
void InfoHelperUInt(char* t, unsigned int* n);
void PrintAllItemInfo(Item* r);
void DisplayMenu();
Object* ListToArray(Item* rn,int* s);
void AssignListToArrayHelper(Item* i, Object* o);
void CopyChar(char* s, char* d);
int GetListSize(Item* r);
void SaveItemInFileB(Item* r);
void SaveItemInFileTXT(Item* r);
FILE* OpenFileW(FILE* f, char* fn,char* m);


