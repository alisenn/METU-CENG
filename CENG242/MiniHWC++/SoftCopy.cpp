#include "SoftCopy.h"
/* YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. DO NOT MODIFY THE HEADER FILE AS IT WILL BE
REPLACED BY THE ORIGINAL HEADER DURING TESTING. THE REQUIRED
HEADER FILE IS ALREADY INCLUDED FOR YOU ABOVE THIS COMMENT BLOCK.
THE CONSTRUCTOR and DESTRUCTOR ARE ALREADY IMPLEMENTED.
START YOUR IMPLEMENTATIONS BELOW THOSE. */


// DONE
SoftCopy::SoftCopy(int ISBN, double price, int startPage, int endPage) : Book(ISBN, price) {
	this->startPage = startPage;
	this->endPage = endPage;
	this->numberOfPages = (endPage - startPage) + 1;
	this->firstHalf = NULL;
	this->secondHalf = NULL;
	this->pageContent = "";
}

// DONE
SoftCopy::~SoftCopy() {
	if (firstHalf != NULL)
		delete firstHalf;
	if (secondHalf != NULL)
		delete secondHalf;
}

SoftCopy::SoftCopy(const SoftCopy& sf){
    this->next = sf.next;
    this->ISBN = sf.ISBN;
    this->price = sf.price;
    this->startPage = sf.startPage;
    this->endPage = sf.endPage;
    this->numberOfPages = (sf.endPage - sf.startPage) +1;
    this->pageContent = sf.pageContent;

    if(sf.firstHalf)
        this->firstHalf = new SoftCopy(*sf.firstHalf);
    if(sf.secondHalf)
        this->secondHalf = new SoftCopy(*sf.secondHalf);
}

SoftCopy& SoftCopy::operator=(const SoftCopy& sf){
    this->next = sf.next;
    this->ISBN = sf.ISBN;
    this->price = sf.price;
    this->startPage = sf.startPage;
    this->endPage = sf.endPage;
    this->numberOfPages = (sf.endPage - sf.startPage) +1;
    this->pageContent = sf.pageContent;

    if (firstHalf != NULL)
		delete firstHalf;
	if (secondHalf != NULL)
		delete secondHalf;

    if(sf.firstHalf)
        this->firstHalf = new SoftCopy(*sf.firstHalf);
    else
        this->firstHalf = NULL;
    if(sf.secondHalf)
        this->secondHalf = new SoftCopy(*sf.secondHalf);
    else
        this->secondHalf = NULL;


    return *this;
}

SoftCopy& SoftCopy::operator+(const SoftCopy& sf) const{
	SoftCopy* b = new SoftCopy(sf);
	SoftCopy* ths = new SoftCopy(*this);

	int middle=endPage-(numberOfPages/2);//(ths->startPage-ths->endPage)/2;
	int lsp=ths->startPage;
	int lep=middle;
	int rsp=middle+1;
	int rep=ths->endPage;

	if(lsp==b->startPage && lep==b->endPage)
			{
					ths->firstHalf=b;
					delete ths; ths= NULL;
					return *b;
			}
	if(rsp==b->startPage && rep==b->endPage)
			{
					ths->secondHalf=b;
					delete ths; ths = NULL;
					return *b;
			}
	if(b->startPage<=middle)
			{
					ths->firstHalf= new SoftCopy(ISBN,price,ths->startPage,middle);
					ths->firstHalf = new SoftCopy(*b);//+b;
			}
	else
			{
					ths->secondHalf= new SoftCopy(ISBN,price,middle,ths->endPage);
					ths->secondHalf = new SoftCopy(*b);//+b;
			}
    //return *this;
}


/*********************cengkallsdaki 0 point veriyo*********************************************/
SoftCopy& SoftCopy::operator+(const SoftCopy& sf) const{
	SoftCopy* b = new SoftCopy(sf);
	SoftCopy* ths = new SoftCopy(*this);

	int middle=endPage-(numberOfPages/2);//(ths->startPage-ths->endPage)/2;
	int lsp=ths->startPage;
	int lep=middle;
	int rsp=middle+1;
	int rep=ths->endPage;

	if(lsp==b->startPage && lep==b->endPage)
	{
		ths->firstHalf->UploadPage(b->pageContent,b->numberOfPages);
		return *ths;
	}
	if(rsp==b->startPage && rep==b->endPage)
	{
		ths->secondHalf->UploadPage(b->pageContent,b->numberOfPages);
		return *ths;
	}
	if(b->startPage<=middle)
	{
	    if(ths->firstHalf == NULL)
		    ths->firstHalf= new SoftCopy(ISBN,price,ths->startPage,middle);
		else
		    ths->firstHalf->UploadPage(b->pageContent,b->numberOfPages); //= new SoftCopy(*b);//+b;
	}
	else
	{
	    if(ths->secondHalf == NULL)
		    ths->secondHalf= new SoftCopy(ISBN,price,middle,ths->endPage);
		else
		    ths->secondHalf->UploadPage(b->pageContent,b->numberOfPages); //= new SoftCopy(*b);//+b;
	}

	return *ths;
}
/*********************cengkallsdaki 0 point veriyo*********************************************/


void SoftCopy::UploadPage(string pageContent, int pageId){

    if(this->numberOfPages==1)
    {
        this->pageContent = pageContent;
        return;
    }
    int middle=this->endPage-(numberOfPages/2);

    if(pageId <= middle )
    {

		if(this->firstHalf == NULL)
        	this->firstHalf= new SoftCopy(ISBN,price,this->startPage,middle);
        this->firstHalf->UploadPage(pageContent,pageId);
    }
    else
    {

		if(this->secondHalf == NULL)
    	    this->secondHalf= new SoftCopy(ISBN,price,middle + 1,this->endPage);
        this->secondHalf->UploadPage(pageContent,pageId);
    }
}

string SoftCopy::Display(int from, int to) const{
		cout<<"from: "<<from<<" to: "<<to<<endl;
    string res = "";
    SoftCopy* root = new SoftCopy(*this); //(SoftCopy*)next;

    int f=0,s;
    vector<SoftCopy*> s1;
    vector<SoftCopy*> s2;
    s1.push_back(root);
    while(!s1.empty() ){
        f++;
        s=s1.size()-1;

        SoftCopy* curr = s1[s];
        s1.pop_back();
        if(curr->firstHalf){
					  s1.push_back(curr->firstHalf);
				}
        if(curr->secondHalf){
					s1.push_back(curr->secondHalf);
				}

        else if(!curr->firstHalf && !curr->secondHalf){
					s2.push_back(curr);
				}

    }
    int aa = s2.size()-1;
	//aa = to;
	//if(to<aa) aa=to;

    if(aa<0) return res;
    while(aa>=0){
			//cout<<"endpage: "<<s2[aa]->endPage <<endl;
			if(s2[aa]->startPage == s2[aa]->endPage && s2[aa]->endPage<=to && s2[aa]->endPage>=from){
				res += s2[aa]->pageContent;
				res+= '\n';
			}

			aa--;
    }
		string st = res.substr(0, res.size()-1);
    return st;
}

void SoftCopy::Discount(){
	this->price = this->price * (75/100.);
}

Book* SoftCopy::Clone() const{
	return new SoftCopy(ISBN,price,startPage,endPage);
}
