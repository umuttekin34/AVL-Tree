


#include "Agac.hpp"

void DosyaOkuma(){
 	
	DugumFirma *ilk = NULL;
	DugumCalisan *ilkCalisan = NULL;
	DugumFirma *ilk2 = NULL;
	DugumFirma* basla = NULL;
	
    ifstream DosyaOku("Persons.txt");

    string sfirma;
    string sadi;
    string syili;
	int i = 0;

    while(!DosyaOku.eof())
    {
        getline(DosyaOku,sfirma,'#');
        getline(DosyaOku,sadi,'#');
        getline(DosyaOku,syili,'\n');
       
        int yili = stoi(syili);
		
		ilk2 = ara(ilk, sfirma);
		
		if(ilk2 == NULL)
			ilkCalisan = NULL;
		else
			ilkCalisan = ilk2->dugumCalisan;
		
		
		ilkCalisan = DugumEkleCalisan(ilkCalisan, OlusturCalisan(sadi,yili));
        ilk = DugumEkleFirma(ilk, ilkCalisan, OlusturFirma(sfirma));
	
    }
    DosyaOku.close();

    SiralaFirma(ilk); 
	
} 
