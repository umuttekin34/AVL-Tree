#include <iostream> 
#include <fstream>

using namespace std;

class Calisan{
	public:
	string calisanAdi;
	int baslangicYili;
};

class Firma{
	public:
	string firmaAdi;
	int calisanSayisi;
};

// calisan düğümü
class DugumCalisan{
	public: 
    Calisan *calisan;  
    DugumCalisan *sol;  
    DugumCalisan *sag;  
    int derinlik;
};

// firma düğümü
class DugumFirma{  
    public:
    Firma *firma; 
	DugumCalisan* dugumCalisan; // bu referansa ilk olusan ic agacın referansını eklenir
    DugumFirma *sol;  
    DugumFirma *sag;  
    int derinlik; 	
}; 

// calisan düğümünün derinliği return eder
int derinlikCalisan(DugumCalisan *N){  
    if (N == NULL)  
        return 0;  
    return N->derinlik;  
}

// firma düğümünün derinliği return eder(firma dis düğümdür yesil renkte olan)
int derinlikFirma(DugumFirma *N){  
    if (N == NULL)  
        return 0;  
    return N->derinlik;  
} 

// calisan dugumu olusturulur eklenen düğümün sag ve sol düğümü yoktur NULL gelen calisan bilgisi parametre olarak verilir
DugumCalisan* OlusturDugumCalisan(Calisan* calisan)  {  
    DugumCalisan* dugumCalisan = new DugumCalisan(); 
    dugumCalisan-> calisan =  calisan;  
    dugumCalisan->sol = NULL;  
    dugumCalisan->sag = NULL;  
    dugumCalisan->derinlik = 1; 
    return(dugumCalisan);  
} 

// aslında firma olusurken burada parametre verilmeli
DugumFirma* OlusturDugumFirma(Firma* firma)  {  
    DugumFirma* dugumFirma = new DugumFirma();
    dugumFirma-> firma =  firma;
    dugumFirma->sol = NULL;  
    dugumFirma->sag = NULL;  
    dugumFirma->derinlik = 1; 
    return(dugumFirma);  
} 

// sag ve sol gitme metotları
DugumCalisan *GitSag(DugumCalisan *y){ 
    DugumCalisan *x = y->sol;  
    DugumCalisan *T2 = x->sag;  
    x->sag = y;  
    y->sol = T2;  
    y->derinlik = max(derinlikCalisan(y->sol), derinlikCalisan(y->sag)) + 1;  
    x->derinlik = max(derinlikCalisan(x->sol), derinlikCalisan(x->sag)) + 1;  
    return x;  
}  

DugumCalisan *GitSol(DugumCalisan *x){  
    DugumCalisan *y = x->sag;  
    DugumCalisan *T2 = y->sol;  
    y->sol = x;  
    x->sag = T2;  
    x->derinlik = max(derinlikCalisan(x->sol), derinlikCalisan(x->sag)) + 1;  
    y->derinlik = max(derinlikCalisan(y->sol), derinlikCalisan(y->sag)) + 1;  
    return y;  
}

DugumFirma *GitSag(DugumFirma *y){  
	
    DugumFirma *x = y->sol;  
    DugumFirma *T2 = x->sag;  
    x->sag = y;  
    y->sol = T2;  
    y->derinlik = max(derinlikFirma(y->sol), derinlikFirma(y->sag)) + 1;  
    x->derinlik = max(derinlikFirma(x->sol), derinlikFirma(x->sag)) + 1;  
    return x;  
}  

DugumFirma *GitSol(DugumFirma *x){  
    DugumFirma *y = x->sag;  
    DugumFirma *T2 = y->sol;  
    y->sol = x;  
    x->sag = T2;  
    x->derinlik = max(derinlikFirma(x->sol), derinlikFirma(x->sag)) + 1;  
    y->derinlik = max(derinlikFirma(y->sol), derinlikFirma(y->sag)) + 1;  
    return y;  
}   
 
// agacın dengesi kontrol edilir AVL ağaclari icin sag sol dengesi gerekir 
int DengeCalisan(DugumCalisan *N){  
    if (N == NULL)  
        return 0;  
    return derinlikCalisan(N->sol) - derinlikCalisan(N->sag);  
} 

int DengeFirma(DugumFirma *N){  
    if (N == NULL)  
        return 0;  
    return derinlikFirma(N->sol) - derinlikFirma(N->sag);  
}

// calisan degerini return  
int CalisanSayisi(Firma *firma){
    return (firma->calisanSayisi);
} 

// calisam süresi return
int CalismaSuresi(Calisan* calisan){
	return (2020 - calisan->baslangicYili);
}

// firma düğümü icin arama yapar eger düğüm daha önce eklenmişse adresini return eder yoksa NULL 

DugumFirma* ara(DugumFirma* baslangic, string firmaAdi){
	if(baslangic == NULL) return NULL;
	
	if(baslangic->firma->firmaAdi == firmaAdi) return baslangic;
	
	DugumFirma* bul = ara(baslangic->sol, firmaAdi);
	if(bul != NULL) return bul;
	
	return ara(baslangic->sag, firmaAdi);
	
}

// ddugum ekleme metodu
DugumCalisan* DugumEkleCalisan(DugumCalisan* dugumCalisan, Calisan* calisan){  
		
	if (dugumCalisan == NULL) {
    	DugumCalisan * yeni = OlusturDugumCalisan(calisan);
        return(yeni); // bunu almam lazım   
    }
	
    if (CalismaSuresi(calisan) < CalismaSuresi(dugumCalisan->calisan)){
        dugumCalisan->sol = DugumEkleCalisan(dugumCalisan->sol, calisan);  

    }	
    else if (CalismaSuresi(calisan) > CalismaSuresi(dugumCalisan->calisan))
        dugumCalisan->sag = DugumEkleCalisan(dugumCalisan->sag, calisan);  
    else
        return dugumCalisan;  
    
 		
    dugumCalisan->derinlik = 1 + max(derinlikCalisan(dugumCalisan->sol), derinlikCalisan(dugumCalisan->sag));  
    int balance = DengeCalisan(dugumCalisan);  
    if (balance > 1 && CalismaSuresi(calisan) < CalismaSuresi(dugumCalisan->sol->calisan))
        return GitSag(dugumCalisan);  
    if (balance < -1 && CalismaSuresi(calisan) > CalismaSuresi(dugumCalisan->sag->calisan)){
        return GitSol(dugumCalisan);  
    }
    if (balance < -1 && CalismaSuresi(calisan) < CalismaSuresi(dugumCalisan->sag->calisan)){  
    	dugumCalisan->sag = GitSag(dugumCalisan->sag); 
        return GitSol(dugumCalisan);  
    }  
     if (balance > 1 && CalismaSuresi(calisan) > CalismaSuresi(dugumCalisan->sol->calisan)){ 
        dugumCalisan->sol = GitSol(dugumCalisan->sol);  
        return GitSag(dugumCalisan);  
    }
    return dugumCalisan;
}

DugumFirma* DugumEkleFirma(DugumFirma* dugumFirma, DugumCalisan* dugumCalisan, Firma* firma){  
			
	if(ara(dugumFirma, firma->firmaAdi) != NULL){
		
		DugumFirma* yeni = ara(dugumFirma, firma->firmaAdi);
		yeni->firma->calisanSayisi +=1;
		yeni->dugumCalisan = dugumCalisan;
	}else{
		if (dugumFirma == NULL)  {
    	DugumFirma * yeni = OlusturDugumFirma(firma);
		yeni->dugumCalisan = dugumCalisan; // X firması diyelim artık bu referansa sahip olmuş olur
		yeni->firma->calisanSayisi +=1;
        return(yeni);  
    }
    if (CalisanSayisi(firma) < CalisanSayisi(dugumFirma->firma)){
        dugumFirma->sol = DugumEkleFirma(dugumFirma->sol, dugumCalisan, firma);  

    }	
    else if (CalisanSayisi(firma) > CalisanSayisi(dugumFirma->firma))
        dugumFirma->sag = DugumEkleFirma(dugumFirma->sag, dugumCalisan , firma);  
    else
        return dugumFirma;  
    
 		
    dugumFirma->derinlik = 1 + max(derinlikFirma(dugumFirma->sol), derinlikFirma(dugumFirma->sag));  
    int balance = DengeFirma(dugumFirma);  
    if (balance > 1 && CalisanSayisi(firma) < CalisanSayisi(dugumFirma->sol->firma))
        return GitSag(dugumFirma);  
    if (balance < -1 && CalisanSayisi(firma) > CalisanSayisi(dugumFirma->sag->firma)){
        return GitSol(dugumFirma);  
    }
    if (balance < -1 && CalisanSayisi(firma) < CalisanSayisi(dugumFirma->sag->firma)){  
    	dugumFirma->sag = GitSag(dugumFirma->sag); 
        return GitSol(dugumFirma);  
    }  
     if (balance > 1 && CalisanSayisi(firma) > CalisanSayisi(dugumFirma->sol->firma)){ 
        dugumFirma->sol = GitSol(dugumFirma->sol);  
        return GitSag(dugumFirma);  
    }
	}
    return dugumFirma;  
}  


void SiralaCalisan(DugumCalisan *baslangic){  
    if(baslangic != NULL)  {  
    	SiralaCalisan(baslangic->sol);  
        SiralaCalisan(baslangic->sag);  

        cout << baslangic->calisan->calisanAdi << " - " << baslangic->calisan->baslangicYili << " | ";
    }  
}

void SiralaFirma(DugumFirma *baslangic){  
    if(baslangic != NULL)  {
		
    	SiralaFirma(baslangic->sol);  
        SiralaFirma(baslangic->sag);  
		
		cout << baslangic->firma->firmaAdi  << endl; 
		SiralaCalisan(baslangic->dugumCalisan);
		cout <<endl;
    }  
}

Firma *OlusturFirma(string _firmaAdi){
	Firma *yeni = new Firma();
	yeni->firmaAdi = _firmaAdi;
	yeni->calisanSayisi;
	return (yeni);
} 

Calisan *OlusturCalisan(string _calisanAdi, int _baslangicYili){
	Calisan *yeni = new Calisan();
	yeni->calisanAdi = _calisanAdi;
	yeni->baslangicYili = _baslangicYili;
	return (yeni);
} 

