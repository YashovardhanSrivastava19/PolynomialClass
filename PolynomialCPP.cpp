#include <iostream>
#include <malloc.h>
using namespace std;
// charArray contains value of first 20 superscipt numbers
const char* charArray[21]={"\u2070","\u00b9","\u00b2","\u00b3","\u2074","\u2075","\u2076","\u2077","\u2078",
"\u2079","\u00b9\u2070","\u00b9\u00b9","\u00b9\u00b2","\u00b9\u00b3","\u00b9\u2074","\u00b9\u2075","\u00b9\u2076",
"\u00b9\u2077","\u00b9\u2078","\u00b9\u2079","\u00b2\u2070"};
//Note:20 in superscipt is  the most we might need for practical purposes.
//Note:In loop traversal,make sure that it is not off by one. 
class Polynomial
{
    private:
        int *coefficients;
        int degree;
        char Symbol;
    public:
        Polynomial(int polDegree=0,char symbol='x')
        {set(polDegree,symbol);}

        void set(int degree,char sym='x')    //set all function.
        {setArray(degree); setDegree(degree); setSymbol(sym);}

        void setArray(int sizeArray)        //set array of coefficients of the polynomail. 
        {coefficients=(int *)calloc((sizeArray+1),sizeof(int));}

        void setDegree(int deg)             // set the degree of the polynomial.
        {degree=deg;}

        void setSymbol(char symbol)        // set the symbol of the polynomial(by default:'x')
        {Symbol=symbol;}

        int* getArray() const              // get array of coefficients.
        {return coefficients;}

        int getDegree() const             // get degree of the polynomial.
        {return degree;}

        void InputCoefficients(bool consolemathtypesetting=false) // Input coefficients of the polynomial.(option of equation typesetting available)
        {
            if (consolemathtypesetting==false)
            {
                for(int i=0;i<=getDegree();i++)
                {
                    cout<<"Enter coefficient of "<<Symbol<<"^"<<i<<": ";
                    cin>>(*(getArray()+i));
                    cout<<endl;
                }
                //Non zero coefficient of highest degree.
                if(getArray()[getDegree()]==0)
                {
                    cout<<"Polynomial of degree"<<getDegree()<<"cannot have zero coefficient of"<<Symbol<<"^"<<getDegree();
                    exit(2);
                }
            }
            else
            {
                for(int i=0;i<=getDegree();i++)
                {
                    cout<<"Enter coefficient of "<<Symbol<<charArray[i]<<": ";
                    cin>>(*(getArray()+i));
                    cout<<endl;
                }
                
                if(getArray()[getDegree()]==0)
                {
                    cout<<"Polynomial of degree"<<getDegree()<<"cannot have zero coefficient of"<<Symbol<<getArray()[getDegree()];
                    exit(2);
                }

            }
          
        }
        void printPoly(bool consolemathtypesetting=false) // Print the polynomial.(option of equation typesetting available)
        {
            if (consolemathtypesetting==false)
            {
                for(int i=0;i<=getDegree();i++)
                {
                 const char* sign= (getArray()[i]>0) ? "+":"-";
                 cout<<sign<<abs(getArray()[i])<<Symbol<<"^"<<i<<" ";
                }
            }
            else
            {
                for(int i=0;i<=getDegree();i++)
                {
                 const char* sign= (getArray()[i]>0) ? "+":"-";
                 cout<<sign<<abs(getArray()[i])<<Symbol<<charArray[i]<<" ";
                }
            }

        }
        //Overloaded Operators.
        Polynomial operator+(const Polynomial& p1)   // overload the + operator.
        {
            int tempDegree=max(getDegree(),p1.getDegree());
            Polynomial temp;
            temp.set(tempDegree);
            if (getDegree()==p1.getDegree())  
            {   // if the degree of the polynomials are equal,add coefficients directly. 
                for(int i=0;i<=getDegree()+1;i++)
                    temp.getArray()[i]=getArray()[i]+p1.getArray()[i];    
            }
            //if the degree is not equal,extend(in this case using realloc) the smaller array of coefficients to that of larger one and set the extended values to 0 
            else if(getDegree()>p1.getDegree())
            {
                //then we need to reallocate the memeory reserved for p1(without damaging the previous ones)
                int* newp1=(int*)realloc(p1.getArray(),(getDegree()+1)*sizeof(int));
                // from the previous size to new size,aloocate each to zero 
                for(int i=p1.getDegree()+1;i<=getDegree();i++)    // here be careful of off by one error.
                    newp1[i]=0;
                for(int i=0;i<=getDegree();i++)
                    temp.getArray()[i]=getArray()[i]+newp1[i];   
            }
            else
            {
                int* newp1=(int*)realloc(getArray(),(p1.getDegree()+1)*sizeof(int));
                // from the previous size to new size,allocate each to zero 
                for(int i=getDegree()+1;i<=p1.getDegree();i++)
                    newp1[i]=0;
                for(int i=0;i<=p1.getDegree();i++)
                    cout<<newp1[i]<<"   "<<p1.getArray()[i]<<endl;    
                for(int i=0;i<=p1.getDegree();i++)
                    temp.getArray()[i]=p1.getArray()[i]+newp1[i];
            }
            return temp;
        }
        Polynomial operator-(const Polynomial& p1)  // overload the - operator
        {
            //same concept as that of + operator.
            int tempDegree=max(getDegree(),p1.getDegree());
            Polynomial temp;
            temp.setDegree(tempDegree);
            if (getDegree()==p1.getDegree())  
            {
                for(int i=0;i<=getDegree()+1;i++)
                    temp.getArray()[i]=getArray()[i]-p1.getArray()[i];    
            }
            else if(getDegree()>p1.getDegree())
            {
                int* newp1=(int*)realloc(p1.getArray(),(getDegree()+1)*sizeof(int));
                for(int i=p1.getDegree()+1;i<=getDegree();i++) 
                    newp1[i]=0;
                for(int i=0;i<=getDegree();i++)  
                    temp.getArray()[i]=getArray()[i]-newp1[i];   
            }
            else
            {
                int* newp1=(int*)realloc(getArray(),(p1.getDegree()+1)*sizeof(int)); 
                for(int i=getDegree()+1;i<=p1.getDegree();i++)
                    newp1[i]=0;    
                for(int i=0;i<=p1.getDegree();i++)
                    temp.getArray()[i]=newp1[i]-p1.getArray()[i];  // potential mistake(reversal of terms).   
                // here,since we have copied current object's coefficient in newp1,terms of subtraction are reversed. 
            }
            return temp;
        }
        Polynomial operator*(const Polynomial& p1)    // overload the * operator 
        {
            Polynomial temp(getDegree()+p1.getDegree());  // degree of multipllied polynomial
            if (getDegree()==p1.getDegree())  
            {
                for(int i=0;i<=getDegree()+1;i++)
                {
                    for (int j=0;j<=getDegree();j++)
                        temp.getArray()[i+j] +=(getArray()[i]*p1.getArray()[i]);  //since all the elements of temp are already zero,we can do this(this is why we used calloc).   
                }    
            }
            //if the degree is not same,the same concept in + is used.
            else if(getDegree()>p1.getDegree())
            {
                //then we need to reallocate the memeory reserved for p1(without damaging the previous ones)
                int* newp1=(int*)realloc(p1.getArray(),(getDegree()+1)*sizeof(int));
                for(int i=p1.getDegree()+1;i<=getDegree();i++)
                    newp1[i]=0;
                for(int i=0;i<=getDegree();i++)
                    for(int j=0;j<=getDegree();j++)
                        temp.getArray()[i+j]+=(getArray()[i]*newp1[i]);   
            }
            else
            {
                int* newp1=(int*)realloc(getArray(),(p1.getDegree()+1)*sizeof(int)); 
                for(int i=getDegree()+1;i<=p1.getDegree();i++)
                    newp1[i]=0;    
                for(int i=0;i<=p1.getDegree();i++)
                    for(int j=0;j<=p1.getDegree();j++)
                        temp.getArray()[i+j]+=(newp1[i]*p1.getArray()[i]);                     
            }
            return temp;

        }    
        Polynomial operator+=(const Polynomial& p1)  // overload the += operator    
        {
            //since basic operators are already overloaded,we will use them.
            (*this)=(*this)+(p1);
            return *this;
        }
        Polynomial operator-=(const Polynomial& p1) // overload the -= operator
        {
            (*this)=(*this)-(p1);
            return *this;
        }
        Polynomial operator*=(const Polynomial& p1) // overload the *= operator
        {
            (*this)=(*this)*(p1);
            return *this;
        }
        Polynomial operator=(const Polynomial& p1)  // overload the = operator
        {
            // this is the only thing that came to my mind.
            set(p1.getDegree());
            for(int i=0;i<=p1.getDegree();i++)
                getArray()[i]=p1.getArray()[i];
            return *this;
        }
};

int main()
{
    //Object Instantiation(and Testing).
   Polynomial eq1(3,'u'),eq2(2,'u');
   eq1.InputCoefficients();   // pass true in InputCoefficients() and printPoly() if the console supports superscript characters. 
   eq1.printPoly();
   cout<<endl<<endl;
   eq2.InputCoefficients();
   eq2.printPoly(); 
   eq1*=eq2;
   cout<<endl;
   eq1.printPoly();
   return 0;
}
